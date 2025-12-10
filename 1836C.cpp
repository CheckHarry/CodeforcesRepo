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

ll pow10(ll a) {
    ll res = 1;
    while (a--) {
        res *= ll(10);
    }
    return res;
}

ll count(ll a,ll b,ll c,ll i) {
    ll ret = min(pow10(b) - 1, pow10(c) - 1 - i) - max(pow10(b - 1), pow10(c - 1) - i) + 1;

    if (1 > ret) return 0;
    else return ret;
}

void solve(int a, int b, int c, ll k) {
    if (c < max(a,b) || c > max(a,b) + 1) {
        cout << "-1\n";
        return;
    }

    ll s = k;
    ll A = pow10(a - 1) - 1;

    while ((s > 0) && A < pow10(a)) {
        s = s - count(a,b,c,++A);
    }

    if (A >= pow10(a)) {
        cout << "-1\n";
        return;
    }

    ll B = min(pow10(b) - 1, pow10(c) - 1 - A) + s;
    cout << A << " + " << B << " = " << A + B << '\n';

}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int a,b,c;
        ll k;
        cin >> a >> b >> c >> k;
        solve(a,b,c,k);
    }
}