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
#include <optional> 


using namespace  std;
using ll = long long;


struct range {
    int left;
    int right;
    int index;
};



vector<range> get_range_frm(const vector<int> &vec, bool ge) {
    int n = vec.size();
    vector<range> ranges(n);

    auto comp = [&] (int a, int b) {
        if (ge) {
            return a >= b;
        } else {
            return a <= b;
        }
    };

    for (int i = 1;i < n;i ++) {
        int k = i - 1;
        while (k >= 0 && comp(vec[i],vec[k])) {
            k = ranges[k].left - 1;
        }
        ranges[i].left = k + 1;
        ranges[i].index = i;
    }    

    for (int i = n - 1;i >= 0;i --) {
        int k = i + 1;
        while (k < n && comp(vec[i],vec[k])) {
            k = ranges[k].right + 1;
        }
        ranges[i].right = k - 1;
        ranges[i].index = i;
    }    

    return ranges;
}

void solve() {
    int n;
    cin >> n;
    vector<int> frm(n);
    vector<int> dst(n);
    for (int i = 0;i < n;i ++) {
        cin >> frm[i];
    }

    for (int i = 0;i < n;i ++) {
        cin >> dst[i];
    }

    auto ranges = get_range_frm(frm, true);
    auto ranges2 = get_range_frm(dst, false);

    unordered_map<int,vector<range>> mapp;
    for (int i = 0;i < ranges.size();i ++) {
        mapp[frm[i]].push_back(ranges[i]);
    }

    for (int i = 0;i < n;i ++) {
        bool found = false;
        for (const auto& range : mapp[dst[i]]) {
            if (ranges2[i].left > range.index || ranges2[i].right < range.index) continue;
            if (range.left <= i && i <= range.right) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}
