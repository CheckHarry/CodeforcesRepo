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
 



ll find_max_can_fit(
    const vector<ll>& mons,
    ll c,
    auto dp
) {
    ll sum = 0;
    for (ll i : mons) {
        sum += i;
    }

    if (c >= sum)  {
        return sum;
    }

   

    for (ll i = 1000000; i >= 0; i --) {
        if (dp[i] && i <= c) {
            return i;
        }
    }

    return 0;
}


void solve() {
    ll w, f, n;
    cin >> w >> f >> n;
    vector<ll> mons(n);
    ll mons_sum = 0;
    for (int i = 0;i < n;i ++) {
        cin >> mons[i];
        mons_sum += mons[i];
    }

    std::bitset<1000001> dp;
    dp[0] = 1;
    for (ll i : mons) {
        dp |= (dp << i);
    }

    ll left = 1;
    ll right = max(mons_sum / w + 1, mons_sum / f + 1);

    auto check_t = [&](ll t) {
            ll w_mana = t * w;
        ll f_mana = t * f;

        ll w_max_can_kill = find_max_can_fit(mons, w_mana, dp);
        ll f_max_can_kill = find_max_can_fit(mons, f_mana, dp);

        //cout << t << " : " << w_max_can_kill << " , " << f_max_can_kill << '\n';
        if (f_mana >= (mons_sum - w_max_can_kill)) {
            //cout << t << '\n';
            return true;
        }

        
        if (w_mana >= (mons_sum - f_max_can_kill)) {
            //cout << t << '\n';
            return true;
        }

        return false;
    };

    while (left + 1 < right) {
        ll mid = (left + right) / 2;
        if (check_t(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    if (check_t(left)) {
        cout << left << '\n';
        return;
    } else {
        cout << right << '\n';
        return;
    }

}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}