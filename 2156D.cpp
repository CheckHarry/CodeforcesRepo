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



void solve() {
    int n;
    cin >> n;

    vector<int> banned(n + 1);
    vector<int> possible(n + 1, 1);
    int ans = -1;
    for (int b = 0;(1 << b) <= n;b ++) {
        int cnt_0 = 0;
        int cnt_1 = 0;
        for (int num = 1;num <= n;num ++) {
            if (!possible[num]) continue;
            if (num & (1 << b)) {
                cnt_1 ++;
            } else {
                cnt_0 ++;
            }
        }
        
        vector<int> indexes_0;
        vector<int> indexes_1;
        for (int index = 1;index <= n - 1;index ++) {
            if (banned[index]) {
                continue;
            }
            cout << "? " << index << " " << (1<<b) << std::endl;
            int res;
            cin >> res;
            if (res == 0) {
                indexes_0.push_back(index);
            } else {
                indexes_1.push_back(index);
            }
            if (indexes_0.size() == cnt_0 || indexes_1.size() == cnt_1) {
                break;
            }
        }

        if (indexes_0.size() == cnt_0) {
            for (int index : indexes_0) {
                banned[index] ++;
            }
            for (int i = 1;i <= n;i ++) {
                if ((i & (1 << b)) == 0) {
                    possible[i] = 0;
                }
            }
        } else {
            for (int index : indexes_1) {
                banned[index] ++;
            }
            for (int i = 1;i <= n;i ++) {
                if ((i & (1 << b))) {
                    possible[i] = 0;
                }
            }
        }

        int possible_count = 0;
        
        for (int i = 1;i <= n;i ++) {
            if (possible[i]) {
                possible_count += 1;
                ans = i;
            }
        }

        if (possible_count == 1) break;
    }

    cout << "! " << ans << std::endl;
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}
