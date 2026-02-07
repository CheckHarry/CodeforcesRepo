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
    int n,x;
    cin >> n >> x;
    vector<int> nums(n);
    for (int i = 0;i < n;i ++) {
        cin >> nums[i];
    }

    vector<int> digits;
    int xx = x;
    while (xx) {
        digits.push_back(xx % 2);
        xx >>= 1;
    }

    vector<int> p;
    int prefix_sum = 0;
    for (int i : nums) {
        prefix_sum ^= i;
        p.push_back(prefix_sum);
    }

    int ans = -1;
    int mask = 0;
    for (int i = 29;i >= 0;i --) {
        if (((1 << i) & x) == 0) {
            mask |= (1 << i);
        } else {
            int tmp_mask = (mask) | (1 << i);
            if ((p.back() & tmp_mask) == 0) {
                int ans_tmp = 0;
                for (int pre : p) {
                    if ((pre & tmp_mask) == 0) {
                        ans_tmp ++;
                    }
                }
                ans = max(ans, ans_tmp);
            }
        }
    }

    if ((p.back() & mask) == 0) {
        int ans_tmp = 0;
        for (int pre : p) {
            if ((pre & mask) == 0) {
                ans_tmp ++;
            }
        }
        ans = max(ans, ans_tmp);
    }

    cout << ans << '\n';
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}