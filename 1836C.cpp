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

// n ^ 2 + n - 2 * k   (-1 + sqrt(1 + 8 * k)) / 2

void solve(int a, int b, int c, ll k) {
    if (c < max(a,b) || c > max(a,b) + 1) {
        cout << "-1\n";
        return;
    }

    if (c > max(a,b)) {
        ll upper = (pow10(a) - pow10(a - 1)) * (pow10(b) - pow10(b - 1));
        if (upper < k) {
            cout << "-1\n";
            return;
        }

    
        if (a < b) {
            double e = (-1.0 + std::sqrt(1 + 8 * k)) / 2.0;
            ll ee = ll(ceil(e));
            ll rest = k - (ee * (ee - 1)) / 2;
            cout << "ee" << " is " << ee << '\n';
            cout << "rest" << " is " << rest << '\n';
            ll C = pow10(c - 1) + rest - 1;
            ll A = pow10(a - 1) - 1 + ee;
            cout << A << " + " << C - A << " = " << C << '\n';
        } else {
            // 10000 90000 100000 <= 10000
            // 10000 + 10001 + ..... + 90000 (when A = 90000)
            // sum ( 10000 + i) i from 0 to 80000

            // 99001 999 100000 <= 100000 - 999
            // 10000 + 10001 + ..... + 90000 (when A = 90000)
            // sum ( 10000 + i) i from 0 to 80000
        }
    }

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