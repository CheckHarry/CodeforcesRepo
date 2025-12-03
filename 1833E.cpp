#include <unordered_set>
#include <unordered_map>
#include <span>
#include <set>
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <array>
#include <math.h>
#include <iomanip> 

using namespace std;

using ll = long long;

int most_left_pos(int a) {
    if (a == 0) return 0;
    int b = 0;
    while (a) {
        a = (a >> 1);
        b ++;
    }
    return b;
}


ll calc(int n,ll a,ll b) {
    int la = most_left_pos(a);
    int lb = most_left_pos(b);
    if (la == lb) {
        if (a > b) n ++;
        return n;
    }

    else if (la > lb) {
        int e = la - lb;
        b = (b << e);
        return calc(n, a, b) + e;
    }

    else {
        ll e = lb - la;
        if (n >= e) {
            return calc(0,(a << e), b) + n - e;
        } else {
            return 0;
        } 
    }
}

ll solve(vector<ll>& v) {
    ll ans = 0;
    ll n = 0;
    for (int i = 1;i < v.size(); i ++) {
        n = calc(n,v[i-1],v[i]);
        ans += n;
    }

    return ans;
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        std::vector<ll> nums;
        while (n--) {
            ll a;
            cin >> a;
            nums.push_back(a);
        }
        cout << solve(nums) << '\n';
    }
}
