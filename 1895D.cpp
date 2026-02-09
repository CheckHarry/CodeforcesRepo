#include <algorithm>
#include <array>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <optional>
#include <set>
#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cstring>
using namespace std;
using ll = long long;

int get_left_most_bits(int n) {
    int res = 0; 
    while (n) {
        n = (n >> 1);
        res ++;
    }

    return res;
}

vector<int> get_bits_with_pad(int n,int len) {
    vector<int> bits(len);

    int pos = bits.size() - 1;

    while (n) {
        bits[pos] = n % 2;
        n = (n >> 1);
        pos --;
    }
    return bits;
}

struct TrieNode {
    int num;
    vector<TrieNode*> children{2, nullptr};
    TrieNode(int n) : num(n) {};
    ~TrieNode() {for (auto ptr : children) {delete ptr;}}
};


class Trie {
    public:
    TrieNode root{0};
    void push(const vector<int>& v) {
        auto cur = &root;
        int pos = 0;

        while (pos < v.size()) {
            auto next = cur->children[v[pos]];
            if (!next) {
                cur->children[v[pos]] = new TrieNode{v[pos]};
                next = cur->children[v[pos]];
            }
            cur = next;
            pos ++;
        }
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n - 1);
    for (int i = 0;i < n - 1;i ++) {
        cin >> nums[i];
    }

    vector<int> p;
    
    p.push_back(0);
    int ss = 0;
    for (int i : nums) {
        ss ^= i;
        p.push_back(ss);
    }
    
    int len = get_left_most_bits(n) + 1;
    Trie trie;

    for (int num : p) {
        auto a = get_bits_with_pad(num,len);
        trie.push(a);
    }

    auto n_bits = get_bits_with_pad(n-1,len);
    int b1 = -1;
   
    for (int i = 0;i <= n - 1;i ++) {
        auto a = get_bits_with_pad(i,len);
        auto cur = &trie.root;
        int pos = 0;
        while (cur && pos < a.size()) {
            if (n_bits[pos] == 1) {
                if (cur->children[a[pos] == 0]) {
                    cur = cur->children[a[pos] == 0];
                } else {
                    b1 = i;
                    break;
                }
            } else {
                if (a[pos] == 0) {
                    if (cur->children[1]) break;
                    cur = cur->children[0];
                } else {
                    if (cur->children[0]) break;
                    cur = cur->children[1];
                }
            }
            pos ++;
        }
        if (b1 != -1) break;
        if (pos == a.size()) {
            b1 = i;
            break;
        }
    }

    cout << b1 << " ";
    for (int i = 0;i < nums.size();i ++) {
        b1 ^= nums[i];
        cout << b1 << " "; 
    } cout << '\n';
}

int main() {
    solve();
}