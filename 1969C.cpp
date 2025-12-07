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

ll solve(const vector<ll>& v,ll k) {
    if (v.size() == 1) return v[0];
    if (k == 0) {
        ll ans = 0;
        for (ll i : v) {
            ans += i;
        }
        return ans;
    }
    //if (v.size() == 2) return 2 * min(v[0], v[1]);
    
    vector<vector<entry>> dp0(k + 1, vector<entry>(k + 1, {INT64_MAX, INT64_MAX}));
    vector<vector<entry>> dp1(k + 1, vector<entry>(k + 1, {INT64_MAX, INT64_MAX}));
    auto reset = [k](auto &dp) {
        for (ll i = 0; i < k + 1; i ++) {
            for (ll j = 0; j < k + 1; j ++) {
                dp[i][j] = {INT64_MAX, INT64_MAX};
            }
        }
    };

    dp0[0][0] = {v[0], v[0]};

    for (ll i = 1;i < v.size(); i ++) {
        for (ll a = 0;a < k + 1;a ++) {
            for (ll b = 0;b < k + 1;b ++) {
                if ((i == a) && (b == 0)) {
                    // boundary conditions
                    dp1[a][0] = {v[i] , v[i] * (a + 1)};
                    continue;
                }
                if (b == 0) {
                    
                    ll m_new = INT64_MAX;
                    for (ll c = 0; c < a + 1; c ++) {
                        m_new = min(m_new, dp0[a][c].m);
                        if (c > 0 && dp0[a][c].d > v[i] && dp0[a][c].m != INT64_MAX) {
                            m_new = min(m_new, dp0[a][c].m - c * dp0[a][c].d + c * v[i]);
                        }
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
                
                    dp1[a][b] = {d_new,m_new};
                }
            }
        }
        swap(dp0,dp1);
        reset(dp1);
    }

    // for (ll i = 0;i < v.size(); i ++) {
    //     cout << "================= " << i << '\n';
    //     for (ll a = 0;a < k + 1;a ++) {
    //         for (ll b = 0;b < k + 1;b ++) {
    //             cout << "[" << dp[i][a][b].d << " , " << dp[i][a][b].m << "] ";
    //         }
    //         cout << '\n';
    //     }
    // }

    ll ans = INT64_MAX;
    for (ll a = 0;a < k + 1;a ++) {
        for (ll b = 0;b < k + 1;b ++) {
            ans = min(dp0[a][b].m, ans);
        }
    }

    return ans;
}

int main() {
    ll tests;
    cin >> tests;
    while (tests--) {
        ll n , k;
        cin >> n >> k;
        vector<ll> nums(n);
        for (ll i = 0;i < n; i ++) {
            cin >> nums[i];
        }
        cout << solve(nums, k) << '\n';
    }
}