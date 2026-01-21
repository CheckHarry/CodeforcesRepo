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
#include <random>

using namespace std;
using ll = long long;



void solve() {
    int n;
    cin >> n;
    
    vector<ll> ss(n);
    ll s = 0;
    for (int i = 0;i < n;i ++) {
        ll a;
        cin >> a;
        s += a;
        ss[i] = s;
    }

    ll ss_min = std::numeric_limits<ll>::max();
    ll ans = std::numeric_limits<ll>::min();
    ll th = -1;

    for (int i = n - 1;i >= 0;i --) {
        ss_min = min(ss_min, ss[i]);
        ll ans_tmp = ss[i] + ss.back() - ss_min;
        if (ans <= ans_tmp) {
            ans = ans_tmp;
            th = ss[i];
        }
    }

    ll ans_tmp = ss.back() - ss_min;
    if (ans <= ans_tmp) {
        ans = ans_tmp;
        th = 0;
    }

    cout << th << '\n';
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}