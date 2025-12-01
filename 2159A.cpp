//#include "parselib.hpp"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <span>
#include <set>
#include <map>
#include <vector>
#include <source_location>

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <array>

// =====================================================
// FAST I/O AND PARSING LIBRARY
// =====================================================

namespace IO {
    // 1. Fast I/O Setup
    void setup() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
    }

    // 2. Generic Input for Fundamental Types
    template <typename T>
    void read(T& x) {
        std::cin >> x;
    }

    // 3. Input for std::pair
    template <typename T1, typename T2>
    void read(std::pair<T1, T2>& p) {
        read(p.first);
        read(p.second);
    }

    // 4. Input for std::vector
    template <typename T>
    void read(std::vector<T>& v) {
        for (auto& x : v) {
            read(x);
        }
    }

    // 5. Input for std::array
    template <typename T, std::size_t N>
    void read(std::array<T, N>& a) {
        for (auto& x : a) {
            read(x);
        }
    }

    // 6. Input for C-style array (requires size to be known or passed differently, 
    //    but usually handled via loops in main. Here is a wrapper if size is known at compile time)
    template <typename T, size_t N>
    void read(T (&a)[N]) {
        for (size_t i = 0; i < N; ++i) {
            read(a[i]);
        }
    }

    // 7. Variadic Template to read multiple arguments
    template <typename T, typename... Args>
    void read(T& head, Args&... tail) {
        read(head);
        read(tail...);
    }
}

using namespace std;
using namespace IO;

int query(const vector<int>& qs, int a, int b, const std::source_location location =
               std::source_location::current()) {

    // std::cout << "file: "
    //           << location.file_name() << '('
    //           << location.line() << ':'
    //           << location.column() << ") `"
    //           << location.function_name() << '\n';
    cout << "? " << (b - a) + 1 << " ";
    for (int i = a;i <= b;i ++) {
        cout << qs[i] + 1 << " ";
    }
    cout << '\n';
    cout.flush();
    int res;
    cin >> res;

    return res;
}


void solve(int n) {
    if (n == 1) {
        cout << "! 1 1\n";
        return;
    }

    map<int,int> m;
    set<int> s;

    int q_size = 0;
    int index = 0;
    
    for (int i = 0; i < 2*n;) {
        if (s.empty()) {
            s.insert(i);
            i += 1;
        } else {
            vector<int> q;
            for (const int val : s) q.push_back(val);
            q.push_back(i);
            q_size ++;
            if (q_size > 3 * n) {
                std::cout << "EXIT";
                std::exit(100);
            }
            int res = query(q,0,q.size()-1);
            if (res) {
                m[i] = res;
            } else {
                s.insert(i);
            }
            i += 1;
        }
    }

    vector<int> q;
    for (const auto& [k, v]: m) {
        q.push_back(k);
    }
    //cout << "HERE\n"
    while (!s.empty()) {
        int p = *s.begin();
        q.push_back(p);
        q_size ++;
        if (q_size > 3 * n) {
                std::cout << "EXIT";
                std::exit(100);
            }
        int res = query(q, 0, q.size() - 1);
        m[p] = res;
        q.pop_back();
        s.erase(p);
    }

    cout << "! ";
    for (const auto& [k, v] : m) {
        cout << v << " ";
    }
    cout << '\n';
    cout.flush();

}


int main() {
    int testcases;
    cin >> testcases;
    while (testcases --) {
        int n;
        cin >> n;
        solve(n);
    }
}

/*
? 2 1 2
3
? 2 3 4
0
? 3 3 4 5
1
? 3 3 4 6
2
? 5 1 2 5 6 3
3
? 5 1 2 5 6 4
3
Verdict: WRONG ANSWER
Expected: [3, 3, 2, 1, 1, 2]
Got:      [3, 3, 3, 3, 1, 2]
*/