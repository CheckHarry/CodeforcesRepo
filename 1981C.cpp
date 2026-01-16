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
#include <random>

using namespace std;
using ll = long long;


vector<int> min_ops(ll a,ll b) {
    vector<int> va;
    vector<int> vb;

    while (a) {
        va.push_back(a % 2);
        a = a >> 1;
    }

    while (b) {
        vb.push_back(b % 2);
        b = b >> 1;
    }

    reverse(va.begin(), va.end());
    reverse(vb.begin(), vb.end());

    int i = 0;
    for (;i < min(va.size(), vb.size());i ++) {
        if (va[i] != vb[i]) {
            break;
        }
    }

    vector<int> ops;
    for (int j = 0;j < va.size() - i;j ++) {
        ops.push_back(-1);
    }

    for (int j = i;j < vb.size();j ++) {
        if (vb[j]) {
            ops.push_back(2);
        } else {
            ops.push_back(1);
        }
    }

    return ops;
}

void solve() {
    int n;
    cin >> n;
    vector<ll> nums;
    for (int i = 0; i < n;i ++) {
        nums.emplace_back();
        cin >> nums.back();
    }

    vector<pair<ll,int>> neigbour;

    for (int i = 0;i < n;i ++) {
        if (nums[i] != -1) {
            neigbour.push_back({nums[i], i});
        }
    }

    for (int i = 1;i < neigbour.size();i ++) {
        auto [x, xi] = neigbour[i - 1];
        auto [y, yi] = neigbour[i];

        auto ops = min_ops(x, y);

        if (ops.size() > (yi - xi)) {
            cout << "-1\n";
            return;
        }

        if (((yi - xi) - ops.size()) % 2 != 0) {
            cout << "-1\n";
            return;
        }

        ll initial = x;
        for (int i = 0;i < ops.size();i ++) {
            if (ops[i] == -1) {
                initial /= 2;
            } else if (ops[i] == 1) {
                initial *= 2;
            } else if (ops[i] == 2) {
                initial *= 2;
                initial += 1;
            }        
            nums[xi + i + 1] = initial;
        }

        int dir = 1;
        for (int k = xi + ops.size() + 1;k < yi;k ++) {
            if (dir) {
                initial *= 2;
            } else {
                initial /= 2;
            }

            nums[k] = initial;
            dir = 1 - dir;
        }
    }

    if (neigbour.size()) {
        int dir = 1;
        ll initial = neigbour[0].first;
        for (int i = neigbour[0].second;i >= 0;i --) {
            nums[i] = initial;
            if (dir) {
                initial *= 2;
            } else {
                initial /= 2;
            }
            dir = 1 - dir;
        }

        dir = 1;
        initial = neigbour.back().first;
        for (int i = neigbour.back().second;i < n;i ++) {
            nums[i] = initial;
            if (dir) {
                initial *= 2;
            } else {
                initial /= 2;
            }
            dir = 1 - dir;
        }
    } else {
        for (int i = 0; i < n;i ++) {
            if (i % 2) {
                nums[i] = 1;
            } else {
                nums[i] = 2;
            }
        }
    }

    for (ll i : nums) {
        cout << i << " ";
    } cout << '\n';

}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}
    
