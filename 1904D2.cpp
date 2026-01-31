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



vector<range> get_range_frm(const vector<int> &vec, bool le) {
    int n = vec.size();
    vector<range> ranges(n);
    vector<pair<int,int>> st;

    for (int i = 0;i < n;i ++) {
        auto pred = [=] () {
            if (le) {
                return st.back().first <= vec[i];
            } else {
                return st.back().first > vec[i];
            }
        };
        while (!st.empty() && pred()) {
            ranges[st.back().second].right = i - 1;
            st.pop_back();
        }

        ranges[i].index = i;
        st.push_back({vec[i], i});
    }    

    while (!st.empty()) {
        ranges[st.back().second].right = n - 1;
        st.pop_back();
    }

    for (int i = n - 1;i >= 0;i --) {
        auto pred = [=] () {
            if (le) {
                return st.back().first <= vec[i];
            } else {
                return st.back().first > vec[i];
            }
        };
        while (!st.empty() && pred()) {
            ranges[st.back().second].left = i + 1;
            st.pop_back();
        }

        ranges[i].index = i;
        st.push_back({vec[i], i});
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

    for (int i = 0;i < ranges2.size();i ++) {
        cout << i << " " << ranges2[i].left << " " << ranges2[i].right << '\n';
        //mapp[frm[i]].push_back(ranges2[i]);
    }

    unordered_map<int,vector<range>> mapp;
    for (int i = 0;i < ranges.size();i ++) {
        //cout << i << " " << ranges[i].left << " " << ranges[i].right << '\n';
        mapp[frm[i]].push_back(ranges[i]);
    }

    for (int i = 0;i < n;i ++) {
        bool found = false;
        for (const auto& range : mapp[dst[i]]) {
            if (ranges2[i].left > range.index || ranges2[i].right < range.index) continue;
            if (range.left <= i && i <= range.right) {
                found = true;
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
