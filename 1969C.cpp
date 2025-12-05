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

struct entry {
    ll d;
    ll m;
};

ll solve(const vector<int>& v,int k) {
    if (v.size() == 1) return v[0];
    if (k == 0) {
        ll ans = 0;
        for (int i : v) {
            ans += i;
        }
        return ans;
    }
    //if (v.size() == 2) return 2 * min(v[0], v[1]);
    
    vector<vector<entry>> dp0(k + 1, vector<entry>(k + 1, {INT64_MAX, INT64_MAX}));
    vector<vector<entry>> dp1(k + 1, vector<entry>(k + 1, {INT64_MAX, INT64_MAX}));
    auto reset = [k](auto &dp) {
        for (int i = 0; i < k + 1; i ++) {
            for (int j = 0; j < k + 1; j ++) {
                dp[i][j] = {INT64_MAX, INT64_MAX};
            }
        }
    };

    dp0[1][1] = {v[1], v[1]};
    dp0[0][0] = {v[0], v[0]};

    for (int i = 1;i < v.size(); i ++) {
        for (int a = 0;a < k + 1;a ++) {
            for (int b = 0;b < k + 1;b ++) {
                //cout << i << " : " << a << " , " << b << '\n';
                if (b == 0) {
                    
                    ll m_new = INT64_MAX;
                    for (int c = 0; c < a + 1; c ++) {
                        m_new = min(m_new, dp0[a][c].m);
                    }
                    if (m_new != INT64_MAX)
                        dp1[a][b] = {v[i], m_new + v[i]};
                } else {
                    if (a == 0) continue;
                    ll m = dp0[a - 1][b - 1].m;
                    ll d = dp0[a - 1][b - 1].d;
                    if (m == INT64_MAX) continue;
                    ll m_new = m + d;
                    ll d_new = d;
                    if (i + 1 < v.size() && d > v[i + 1]) {
                        m_new = m - ((b - 1) * d) + b * v[i + 1];
                        d_new = v[i + 1];
                    }
                    dp1[a][b] = {d_new,m_new};
                }
            }
        }
        swap(dp0,dp1);
        reset(dp1);
    }

    // for (int i = 0;i < v.size(); i ++) {
    //     cout << "================= " << i << '\n';
    //     for (int a = 0;a < k + 1;a ++) {
    //         for (int b = 0;b < k + 1;b ++) {
    //             cout << "[" << dp[i][a][b].d << " , " << dp[i][a][b].m << "] ";
    //         }
    //         cout << '\n';
    //     }
    // }

    ll ans = INT64_MAX;
    for (int a = 0;a < k + 1;a ++) {
        for (int b = 0;b < k + 1;b ++) {
            ans = min(dp0[a][b].m, ans);
        }
    }

    return ans;
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n , k;
        cin >> n >> k;
        vector<int> nums(n);
        for (int i = 0;i < n; i ++) {
            cin >> nums[i];
        }
        cout << solve(nums, k) << '\n';
    }
}