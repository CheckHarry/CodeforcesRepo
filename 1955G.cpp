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

ll gcd(ll a,ll b) {
    if (a > b) return gcd(b, a);

    if (b % a == 0) return a;

    return gcd(a, b % a);
}

bool dp[101][101];
bool check(int n, int m, const vector<vector<ll>>& matrix,int c) {
    memset(dp,0,sizeof(dp));
    for (int i = 0;i < n;i ++) {
        for (int j = 0;j < m;j ++) {
            if (i == 0 && j == 0) {
                dp[0][0] = true;
            }

            if (i > 0) {
                dp[i][j] = dp[i][j] || dp[i - 1][j] && ((matrix[i][j] % c) == 0);
            }

            if (j > 0) {
                dp[i][j] = dp[i][j] || dp[i][j - 1] && ((matrix[i][j] % c) == 0);
            }
        }
    }

    return dp[n-1][m-1];

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

    ll start_val = matrix[0][0];
    ll end_val = matrix[n - 1][m - 1];
    ll common_gcd = gcd(start_val, end_val);
 
    
    vector<ll> divisors;
    for (ll i = 1; i * i <= common_gcd; ++i) {
        if (common_gcd % i == 0) {
            divisors.push_back(i);
            if (i * i != common_gcd) {
                divisors.push_back(common_gcd / i);
            }
        }
    }
 
    sort(divisors.rbegin(), divisors.rend());
 
    for (ll d : divisors) {
        if (check(n, m, matrix, d)) {
            cout << d << "\n";
            return;
        }
    }
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}