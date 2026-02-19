#include <unordered_set>
#include <unordered_map>
#include <span>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <array>
#include <math.h>
#include <iomanip>
#include <queue>
#include <list>
#include <random>
#include <optional>
 
using namespace std;
using ll = long long;
 

struct TrieNode {
    ll s = 0;
    ll cnt = 0;
    int children[27];
    TrieNode(int s_, int cnt_) : s(s_),cnt(cnt_) {
        for (int i = 0;i < 27;i ++) {
            children[i] = -1;
        }
    }
};


struct Trie {
    TrieNode root{0,0};
    vector<TrieNode> nodes{1000500, TrieNode{0,0}};
    int pos = 0;
    int alloc() {
        return pos++;
    }
    
    void push(const string& s) {
        auto cur = &root;

        int n = s.size();
        for (char c : s) {
            auto next = cur->children[c - 'a'];
            if (next == -1) {
                cur->children[c-'a'] = alloc();
                next = cur->children[c-'a'];
            }
            nodes[next].s += n;
            nodes[next].cnt ++;
            n --;
            cur = &nodes[next];
        }
        auto last = cur->children[26];
        if (last == -1) {
            last = (cur->children[26] = alloc());
        }
        nodes[last].cnt ++;
    }

    TrieNode* get_node(int i) {
        if (i == -1) return nullptr;
        return &nodes[i];
    }
};

void solve() {
    int n;
    cin >> n;
    vector<string> vs;
    for (int i = 0;i < n;i ++) {
        string s;
        cin >> s;
        vs.push_back(std::move(s));
    }

    Trie trie;
    for (const auto & s : vs) {
        trie.push(s);
    }

    ll ans = 0;
    for (const auto& s : vs) {
        auto cur = &trie.root;
        for (int i = s.size() - 1;i >= 0;i --) {
            char c = s[i];
            for (int cho = 0;cho < 26;cho ++) {
                if (c == (cho + 'a')) continue;
                if (cur->children[cho] == -1) continue;
                ans += (i + 1) * trie.get_node(cur->children[cho])->cnt + trie.get_node(cur->children[cho])->s;
            }
            if (cur->children[26] != -1) {
                ans += (i + 1) * trie.get_node(cur->children[26])->cnt;
            }

            cur = trie.get_node(cur->children[c - 'a']);
            if (!cur) break;
        }
        if (cur) {
            for (const auto& ptr : cur->children) {
                if (ptr != -1)
                    ans += trie.get_node(ptr)->s;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    solve();
}