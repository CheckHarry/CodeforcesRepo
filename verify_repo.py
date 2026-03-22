#!/usr/bin/env python3
"""
verify_repo.py — Cross-references your local Codeforces repo against the
Codeforces API to find (1) filename typos and (2) un-AC'd solutions.

Usage:
    python verify_repo.py --handle YOUR_CF_HANDLE --repo ~/codeforce
"""

import argparse
import re
import time
import sys
from pathlib import Path
from urllib.request import urlopen
from urllib.error import URLError
import json


def fetch_json(url: str, retries: int = 3, delay: float = 2.0) -> dict:
    """Fetch JSON from Codeforces API with polite retry logic."""
    for attempt in range(retries):
        try:
            with urlopen(url, timeout=30) as resp:
                data = json.loads(resp.read().decode())
                if data.get("status") != "OK":
                    print(f"  API error: {data.get('comment', 'unknown')}", file=sys.stderr)
                    time.sleep(delay)
                    continue
                return data
        except (URLError, TimeoutError) as e:
            print(f"  Attempt {attempt+1} failed: {e}", file=sys.stderr)
            time.sleep(delay)
    sys.exit("Failed to fetch from Codeforces API after retries.")


def parse_filename(name: str) -> tuple[int, str] | None:
    """
    Extract (contestId, problemIndex) from a filename like '1826D.cpp'.
    Handles multi-letter indices like '1381A2' → (1381, 'A2').
    """
    m = re.match(r"^(\d+)([A-Za-z]\d*)\.cpp$", name)
    if m:
        return int(m.group(1)), m.group(2).upper()
    return None


def main():
    parser = argparse.ArgumentParser(description="Verify Codeforces repo solutions.")
    parser.add_argument("--handle", required=True, help="Your Codeforces handle")
    parser.add_argument("--repo", default=".", help="Path to your repo (default: cwd)")
    args = parser.parse_args()

    repo = Path(args.repo)
    cpp_files = sorted(repo.glob("*.cpp"))

    # ── Step 1: Parse all filenames ──────────────────────────────────
    file_problems: dict[str, tuple[int, str]] = {}  # filename → (contestId, index)
    unparseable: list[str] = []

    for f in cpp_files:
        parsed = parse_filename(f.name)
        if parsed:
            file_problems[f.name] = parsed
        else:
            unparseable.append(f.name)

    print(f"Found {len(file_problems)} solution files, {len(unparseable)} unparseable.\n")

    # ── Step 2: Fetch all CF problems (1 API call) ───────────────────
    print("Fetching problem catalog...")
    prob_data = fetch_json("https://codeforces.com/api/problemset.problems")
    all_problems: set[tuple[int, str]] = set()
    for p in prob_data["result"]["problems"]:
        all_problems.add((p["contestId"], p["index"]))
    print(f"  {len(all_problems)} problems in catalog.\n")

    # Be polite: wait before next call
    time.sleep(1)

    # ── Step 3: Fetch user submissions (1 API call) ──────────────────
    print(f"Fetching submissions for handle '{args.handle}'...")
    sub_data = fetch_json(
        f"https://codeforces.com/api/user.status?handle={args.handle}&from=1&count=100000"
    )

    accepted: set[tuple[int, str]] = set()
    attempted: set[tuple[int, str]] = set()
    for s in sub_data["result"]:
        prob = s["problem"]
        key = (prob["contestId"], prob["index"])
        attempted.add(key)
        if s["verdict"] == "OK":
            accepted.add(key)
    print(f"  {len(accepted)} problems AC'd, {len(attempted)} attempted total.\n")

    # ── Step 4: Report ───────────────────────────────────────────────
    typos = []       # filename refers to a non-existent problem
    not_accepted = [] # problem exists but you never got AC
    not_attempted = [] # problem exists but you never submitted at all
    good = []

    for fname, (cid, idx) in sorted(file_problems.items()):
        key = (cid, idx)
        if key not in all_problems:
            typos.append((fname, cid, idx))
        elif key in accepted:
            good.append(fname)
        elif key in attempted:
            not_accepted.append((fname, cid, idx))
        else:
            not_attempted.append((fname, cid, idx))

    # — Typos —
    if typos:
        print("❌ LIKELY TYPOS (problem ID doesn't exist):")
        for fname, cid, idx in typos:
            # Suggest close matches
            suggestions = [
                f"{c}{i}" for c, i in all_problems
                if abs(c - cid) <= 5 and i == idx  # nearby contest, same letter
            ]
            hint = f"  (did you mean: {', '.join(sorted(suggestions)[:5])}?)" if suggestions else ""
            print(f"   {fname} → {cid}{idx} not found{hint}")
        print()

    # — Not AC'd —
    if not_accepted:
        print("⚠️  NOT ACCEPTED (submitted but never AC'd):")
        for fname, cid, idx in not_accepted:
            print(f"   {fname} → {cid}{idx}")
        print()

    # — Never submitted —
    if not_attempted:
        print("🔍 NEVER SUBMITTED (file exists but no submission on record):")
        for fname, cid, idx in not_attempted:
            print(f"   {fname} → {cid}{idx}")
        print()

    # — Summary —
    if unparseable:
        print(f"📎 UNPARSEABLE FILENAMES: {', '.join(unparseable)}\n")

    print(f"✅ {len(good)} files match an AC'd submission.")
    print(f"   {len(typos)} likely typos, {len(not_accepted)} not AC'd, "
          f"{len(not_attempted)} never submitted.")


if __name__ == "__main__":
    main()