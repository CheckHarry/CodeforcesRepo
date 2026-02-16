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
    vector<ll> nums(n);
    for (int i = 0;i < n;i ++) {
        cin >> nums[i];
    }

    array<ll,65> cnt{};
    ll ss = 0;
    for (ll i : nums) {
        ss ^= i;
        for (int pos = 0;pos < 65;pos ++) {
            if (ss & (1ull << pos)) {
                cnt[pos] ++;
            }
        }
    }

    ss = 0;
    ll ans = 0;
    array<ll,65> cnt2{};
    for (int i = 0;i < n;i ++) {
        int pos = 63;
        for (;pos >= 0;pos --) {
            if (nums[i] & (1ull << pos)) break;
        }

        
        ans += (cnt2[pos]) * (cnt[pos]);
        ans += (i - cnt2[pos] + 1) * ((n - i) - cnt[pos]);
        //cout << pos << " " << ans << " " << (cnt2[pos]) * (cnt[pos]) << " " << (i - cnt2[pos] + 1) * ((n - i) - cnt[pos]) <<  '\n';
        
        ss ^= nums[i];
        for (int b = 0;b < 65;b ++) {
            if (ss & (1ull << b)) {
                cnt2[b] ++;
                cnt[b] --;
            }
        }
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