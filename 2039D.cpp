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

std::vector<long long> getAllFactors(long long n) {
    std::vector<long long> factors;
    
    if (n <= 0) {
        return factors; // Return empty for non-positive numbers
    }

    // We iterate up to the square root of n.
    // Using sqrt() returns a double, so we cast to long long.
    long long limit = static_cast<long long>(std::sqrt(n));

    for (long long i = 1; i <= limit; ++i) {
        if (n % i == 0) {
            // If i divides n, then i is a factor.
            factors.push_back(i);

            // If i is a factor, then n/i is also a factor.
            // We must check if i != n/i to avoid adding the square root twice
            // (e.g., for n=36, don't add 6 twice).
            if (i != n / i) {
                factors.push_back(n / i);
            }
        }
    }

    // The factors are currently added in pairs (small, large), so they are not sorted.
    // Example for 12: 1, 12, 2, 6, 3, 4
    // We use std::sort to order them: 1, 2, 3, 4, 6, 12
    std::sort(factors.begin(), factors.end());

    return factors;
}


std::vector<std::vector<int>> findAllFactors(int n) {
    // 1-based indexing, so size is n + 1
    std::vector<std::vector<int>> factors(n + 1);

    for (int i = 1; i <= n; ++i) {
        // Iterate through multiples of i
        for (int j = i; j <= n; j += i) {
            factors[j].push_back(i);
        }
    }
    return factors;
}


void solve(vector<int>& v, int m) {
    vector<int> ans(m + 1, -1);

    ans[1] = v[v.size() - 1];

    auto factors = findAllFactors(m);

    for (int i = 2; i <= m; i ++) {
        unordered_set<int> ss;
        for (int j : factors[i]) {
            if (j != i) {
                ss.insert(ans[j]);
            }
        }

        for (int j = v.size() - 1; j >= 0; j --) {
            if (ss.find(v[j]) == ss.end()) {
                ans[i] = v[j];
                break;
            }
        }
        
        if (ans[i] == -1) {
            cout << "-1\n";
            return;
        }
    }

    for (int i = 1; i <= m; i ++) {
        cout << ans[i] << " ";
    } cout << '\n';
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n, m;
        cin >> n >> m;
        vector<int> v;
        while (m--) {
            int a;
            cin >> a;
            v.push_back(a);
        }
        solve(v, n);
    }
}
