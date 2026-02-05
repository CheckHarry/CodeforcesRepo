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

using namespace std;
using ll = long long;



vector<ll> find_primes() {
    vector<ll> bitmap(100005);
    for (int i = 2;i < 100005;i ++) {
        if (bitmap[i]) continue;
        for (int j = 2 * i;j < 100005;j += i) {
            bitmap[j] = 1;
        }
    }
    vector<ll> res;
    for (int i = 2;i < 100005;i ++) {
        if (!bitmap[i]) res.push_back(i);
    }
    return res;
}

ll gcd(ll a,ll b) {
    if (a > b) return gcd(b, a);

    if (b % a == 0) return a;

    return gcd(a, b % a);
}

static vector<ll> primes = find_primes();


vector<int> get_factors_index(ll a) {
    vector<int> index;
    for (int i = 0;i < primes.size();i ++) {
        if (a % primes[i] == 0) {
            index.push_back(i);
            while (a % primes[i] == 0) {
                a /= primes[i];
            }
        }
        if (a == 1) break;
    }
    return index;
}

void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<ll>> matrix;
    for (int i = 0;i < n;i ++) {
        vector<ll> row(m);
        for (int j = 0;j < m;j ++) {
            cin >> row[j];
        }
        matrix.push_back(row);
    }

    vector<vector<unordered_set<ll>>> dp(n,vector<unordered_set<ll>>(m));
    for (int i = 0;i < n;i ++) {
        for (int j = 0;j < m;j ++) {

            ll num = matrix[i][j];
            
            if (i == 0 && j == 0) {
                dp[i][j].insert(num);
            }

            if (i > 0) {
                for (const auto& v : dp[i - 1][j]) {
                    dp[i][j].insert(gcd(num, v));
                }
            }

            if (j > 0) {
                for (const auto& v : dp[i][j - 1]) {
                    dp[i][j].insert(gcd(num, v));
                }
            }
        }
    }

    ll ans = 1;
    for (const auto& v : dp.back().back()) {
        ans = max(ans, v);
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