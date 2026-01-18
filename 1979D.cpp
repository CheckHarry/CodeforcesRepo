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
#include <bitset>
 
using namespace std;
using ll = long long;



void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> nums;
    for (int i = 0;i < n;i ++) {
        char c;
        cin >> c;
        if (c == '0') nums.push_back(0);
        else nums.push_back(1);
    }

    vector<pair<int,int>> gps;

    int cnt = 0;
    int cur = -1;
    for (int i = 0;i < n;i ++) {
        if (cur != nums[i] && cur != -1) {
            gps.push_back({cnt, cur});
            cnt = 1;
        } else {
            cnt ++;
        }
        cur = nums[i];
    }

    if (cur != -1) {
        gps.push_back({cnt, cur});
    }

    if (gps.size() == 1) {
        if (gps[0].first == k) {
            cout << "1\n";
        } else {
            cout << "-1\n";
        }
        return;
    }

    int not_equal_k = 0;
    for (auto [cnt, chr] : gps) {
        if (cnt != k) not_equal_k++;
    }

    if (not_equal_k == 0) {
        int pos = 0;
        for (int i = 0;i + 1 < gps.size();i ++) {
            if (gps[i].second != gps.back().second) {
                cout << pos + gps[i].first << '\n';
                return;
            }
            pos += gps[i].first;
        }
    }

    if (not_equal_k == 1) {
        if (gps.back().first != k) {
            cout << "-1\n";
            return;
        }

        int pos = 0;
        for (int i = 0;i + 1 < gps.size();i ++) {
            if (gps[i].first != k) {
                if (gps[i].first != 2 * k) {
                    cout << "-1\n";
                    return;
                }
                if (gps[i].second == gps.back().second) {
                    cout << "-1\n";
                    return;
                }

                cout << pos + k << '\n';
                return;
            }
            pos += gps[i].first;
        }
    }

    if (not_equal_k == 2) {
        if (gps.back().first >= k) {
            cout << "-1\n";
            return;
        }

        int pos = 0;
        for (int i = 0;i + 1 < gps.size();i ++) {
            if (gps[i].first != k) {
                int to_fill = k - gps.back().first;

                if (gps[i].second != gps.back().second) {
                    cout << "-1\n";
                    return;
                }

                if (gps[i].first < to_fill) {
                    cout << "-1\n";
                    return;
                }

                if (gps[i].first - to_fill != 0 && gps[i].first - to_fill != k) {
                    cout << "-1\n";
                    return;
                }

                cout << pos + to_fill << '\n';
                return;
            }
            pos += gps[i].first;
        }
    }

    cout << "-1\n";
}



int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}