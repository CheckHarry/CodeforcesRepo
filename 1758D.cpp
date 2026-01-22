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




/*


1 2 3 ... 1 + T - 2 .... 1 + k

k ^ 2

T : 4
1 2 3 4
1 2 3 5

e = 1

2 3 4 6

e * T + (T - 1) * (T) / 2 + 1 + k < k ^ 2

e < (k ^ 2 - k - 1 - (T - 1) * (T) / 2) / T

e  < (k ^ 2 - k -1) / T - (T - 1) / 2


(k - T + 1) * (T - 2)  +  e * T + (T - 1) * (T) / 2 + 1 + k >= k ^ 2

  e >= (k ^ 2 - (k - T + 1) * (T - 2) - 1 - k - (T - 1) * (T) / 2) / T

  e >= (k ^ 2 - k -1) / T - (T - 1) / 2   - (k - T + 1) * (T - 2) / T
*/


void solve()
{
    ll n;
    cin >> n;

    if (n == 2) {
        cout << "1 3\n";
        return;
    }

    ll e;
    ll k = n - 1;
    for (;;k ++) {
        ll U = (k * k - k - 1 - ((n - 1) * n) / 2);
        ll V = (k - n + 1) * (n - 2);

        double RHS = double(U) / double(n);
        double LHS = double(U - V) / double(n);
        //cout << LHS << " " << RHS << '\n';
        if (std::floor(RHS) >= LHS) {
            e = std::floor(RHS);
            break;
        }
    }
   
    ll sum = 0;
    vector<ll> ans;
    for (ll i = 0;i + 1 < n;i ++) {
        ans.push_back(i + 1 + e);
        sum += i + 1 + e;
    } 

    ans.push_back(1 + e + k);
    sum += 1 + e + k;
    
    int pos = ans.size() - 2;
    while (sum < k * k) {
        ans[pos] ++;
        sum ++;
        pos --;
        if (pos == 0) {
            pos = ans.size() - 2;
        }
    }

    // cout << sum << '\n';
    // cout << k << '\n';
    //cout << ans.size() << '\n';
    for (ll i : ans) {
        cout << i << ' ';
    } cout << '\n';


    // cout << " sum is " << accumulate(ans.begin(), ans.end(), 0ll) << '\n';
    // cout << "k is " << ans.back() - ans[0] << '\n';
}



int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}