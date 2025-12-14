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


struct op {
    int x;
    int y;
};

void solve(int n) {
    unordered_set<int> s;
    vector<op> vv;
    vector<op> vv2;
    
    int nn = n;
    while (nn >= 3) {
        s.insert(nn);
        int tmp = nn;
        nn = static_cast<int>(sqrt(nn)) + 1;
        vv.push_back({tmp, nn});
        vv.push_back({tmp, nn});
    }
    //cout << " nn is " << nn << '\n';
    s.insert(nn);
    s.insert(nn - 1);

    for (int i = 1; i <= n; i ++) {
        if (s.find(i) == s.end()) {
            vv2.push_back({i, i + 1});
        }
    }

    cout << vv2.size() + vv.size() << '\n';
    for (const auto &op : vv2) {
        cout << op.x << " " << op.y << '\n';
    }
    for (const auto &op : vv) {
        cout << op.x << " " << op.y << '\n';
    }
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        solve(n);
    }
}