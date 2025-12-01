import sys
import random
import subprocess

# Configuration
SOLVER_EXECUTABLE = "./solution"  # Path to your compiled C++ binary
NUM_TEST_CASES = 10000               # Number of random test cases to run
MAX_N = 4                        # Maximum N for random tests (keep small for debugging)

def generate_sequence(n):
    """Generates a random sequence of length 2n with pairs of 1..n."""
    seq = list(range(1, n + 1)) * 2
    random.shuffle(seq)
    return seq

def calculate_mad(query_indices, sequence):
    """Calculates the MAD value for a given subset of indices."""
    counts = {}
    for idx in query_indices:
        # Adjust for 1-based indexing
        val = sequence[idx - 1]
        counts[val] = counts.get(val, 0) + 1
    
    max_dup = 0
    for val, count in counts.items():
        if count >= 2:
            if val > max_dup:
                max_dup = val
    return max_dup

def run_test_case(t_idx):
    # 1. Generate a random N and sequence
    n = random.randint(2, MAX_N)
    hidden_sequence = generate_sequence(n)
    
    print(f"Test Case #{t_idx + 1}: n={n}")
    # print(f"Hidden Sequence: {hidden_sequence}") # Uncomment to see the answer

    # 2. Start the C++ solver process
    # We use Popen to interact with stdin/stdout
    process = subprocess.Popen(
        [SOLVER_EXECUTABLE],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        bufsize=0 # Unbuffered
    )

    try:
        # 3. Send '1' (test cases) and 'n' to the solver
        # The solver expects t then n. We simulate 1 test case per process run for simplicity here,
        # or we could run the process once and loop inside. 
        # Let's run the process once per test case to isolate failures.
        process.stdin.write(f"1\n{n}\n")
        process.stdin.flush()

        queries_count = 0
        max_queries = 3 * n

        while True:
            # Read a line from the solver
            line = process.stdout.readline()
            if not line:
                break
            
            line = line.strip()
            if not line:
                continue

            # Check if it's an answer or a query
            if line.startswith("!"):
                # It's the final answer
                parts = list(map(int, line[1:].split()))
                if parts == hidden_sequence:
                    print("Verdict: OK")
                    return True
                else:
                    print(f"Verdict: WRONG ANSWER")
                    print(f"Expected: {hidden_sequence}")
                    print(f"Got:      {parts}")
                    return False
            
            elif line.startswith("?"):
                # It's a query
                queries_count += 1
                if queries_count > max_queries:
                    print(f"Verdict: QUERY LIMIT EXCEEDED ({queries_count} > {max_queries})")
                    return False

                parts = list(map(int, line[1:].split()))
                k = parts[0]
                indices = parts[1:]

                # Basic validation
                if k != len(indices):
                    print(f"Error: Query length mismatch. K={k}, provided={len(indices)}")
                    return False
                
                # Calculate MAD response
                response = calculate_mad(indices, hidden_sequence)
                print(line)
                print(response)
                # Send response back
                process.stdin.write(f"{response}\n")
                process.stdin.flush()
            
            else:
                print(f"Error: Malformed output from solver: {line}")
                return False

    except BrokenPipeError:
        print("Error: Solver closed connection unexpectedly.")
        return False
    except Exception as e:
        print(f"Error: {e}")
        return False
    finally:
        # Clean up process
        if process.poll() is None:
            process.terminate()

def main():
    # Check if solver exists
    import os
    if not os.path.exists(SOLVER_EXECUTABLE) and not os.path.exists(SOLVER_EXECUTABLE + ".exe"):
        print(f"Error: Executable '{SOLVER_EXECUTABLE}' not found.")
        print("Please compile your C++ code first: g++ solution.cpp -o solution")
        return

    print(f"Running {NUM_TEST_CASES} random test cases...")
    print("-" * 40)

    passed = 0
    for i in range(NUM_TEST_CASES):
        if run_test_case(i):
            passed += 1
        else:
            print("Stopping due to failure.")
            break
        print("-" * 40)
    
    print(f"Summary: {passed}/{NUM_TEST_CASES} tests passed.")

if __name__ == "__main__":
    main()
    
    # 2 2 3 1 3 1