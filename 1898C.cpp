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


using namespace std;
using ll = long long;

void solve(int n,int m,int k) {
    if (k < (n + m - 2)) {
        cout << "NO\n";
        return;
    }
    if ((k - n - m + 2) % 2) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    map<pair<int,int>,int> h;
    map<pair<int,int>,int> v;
    int a = 0;
    v[{0,0}] = 0;
    v[{0,1}] = 0;
    h[{1,0}] = 1;
    for (int i = 0; i < m - 1; i ++) {
        h[{0, i}] = a;
        a = 1 - a; 
    }

    for (int i = 0; i < n - 1; i ++) {
        v[{i, m - 1}] = a;
        a = 1 - a; 
    }

    h[{n - 1, m - 2}] = a;
    h[{n - 2, m - 2}] = a;
    v[{n - 2, m - 3}] = a;
    a = 1 - a;
    v[{n - 2, m - 2}] = a;
    h[{n - 1, m - 3}] = a;
    h[{n - 2, m - 3}] = a;

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m - 1; j ++) {
            if (h.find({i,j}) != h.end()) {
                cout << (h[{i,j}] ? "R" : "B") << " ";
            } else {
                cout << "B ";
            }
        } cout << '\n';
    }

    for (int i = 0; i < n - 1; i ++) {
        for (int j = 0; j < m; j ++) {
            if (v.find({i,j}) != v.end()) {
                cout << (v[{i,j}] ? "R" : "B") << " ";
            } else {
                cout << "B ";
            }
        } cout << '\n';
    }

}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n, m, k;
        cin >> n >> m >> k;
        solve(n,m,k);
    }
}