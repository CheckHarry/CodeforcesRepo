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
 

ll delta(ll x, ll y) {
    if (x == 1) return 0;
    int t = 0; 

    while (y <  x) {
        y *= y;
        t ++;
    }

    while (y >= x * x) {
        x *= x;
        t --;
    }
    return t;
}

void solve() {
    int n;
    cin >> n;
    
    vector<ll> nums(n);
    for (int i = 0;i < n; i ++) {
        cin >> nums[i];
    }

    ll a = INT32_MIN;
    for (int i = 0;i < n;i ++) {
        if (nums[i] == 1 && a > 1) {
            cout << "-1\n";
            return;
        }
        a = max(a, nums[i]);
    }

    ll k = 0;
    ll ans = 0;
    for (int i = 1;i < n;i ++) {
        ll x = nums[i - 1];
        ll y = nums[i];

        ll t = delta(x, y);
        k += t;
        if (k < 0) k = 0;
        ans += k;
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