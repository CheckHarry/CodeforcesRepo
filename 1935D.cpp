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
    ll n, c;
    cin >> n >> c;
    vector<ll> nums;
    for (int i = 0; i < n; i ++) {
        nums.emplace_back();
        cin >> nums.back();
    }
    
    ll even_cnt = 0;
    ll in_both = 0;
    ll y_x = 0;
    ll x_y = 0;

    for (ll i = 0;i < nums.size();i++) {
        y_x += c - nums[i] + 1;
        x_y += (nums[i] / 2) + 1;
        if (nums[i] % 2 == 0) {
            even_cnt ++;
        }

        if (nums[i] % 2) {
            in_both += (i + 1 - even_cnt);
        } else {
            in_both += (even_cnt);
        }
    }

    cout << (((c + 1) * (c + 2)) / 2) - (x_y + y_x - in_both) << '\n';
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}

 