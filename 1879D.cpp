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

ll modn = 998244353;

ll solve(vector<ll> &v) {

    ll ans = 0;
    for (int d = 0; d < 30; d ++) {
        ll mask = (1 << d);

        ll cnt_0 = 1;
        ll cnt_1 = 0;
        ll sum_0 = -1;
        ll sum_1 = 0;
        ll s = 0;

        for  (int i = 0; i < v.size(); i ++) {
            int sign = (v[i] & mask) ? 1 : 0;
            s += sign;
            //cout << d << " : " << i << " : " << s << '\n';
            if (s % 2) {
                ans += mask * ((ll(i) * cnt_0 - sum_0) % modn);
                cnt_1 ++;
                sum_1 += i;
            } else {
                ans += mask * ((ll(i) * cnt_1 - sum_1) % modn);
                cnt_0 ++;
                sum_0 += i;
            }
            ans = ans % modn;
        }
    }

    return ans;
}

int main() {
    int n;
    cin >> n;
    vector<ll> nums;
    while (n--) {
        ll a;
        cin >> a;
        nums.push_back(a);
    }
    cout << solve(nums) << '\n';
}