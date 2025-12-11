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


int solve(vector<ll>& v, int m) {
    sort(v.begin(), v.end());
    unordered_map<ll, vector<ll>> factors;
    for (ll i : v) {
        if (factors.find(i) != factors.end()) continue;
        factors[i] = getAllFactors(i);
    }

    int sat = 0;
    vector<int> factors_cnt(m + 1);

    int left = 0;
    int right = 0;

    

    auto add = [&](int index) {
        for (ll i : factors[v[index]]) {
            if (i <= m) {
                if (factors_cnt[i] == 0) sat ++;
                factors_cnt[i] ++;
            }
        }
    };

    auto remove = [&](int index) {
        for (ll i : factors[v[index]]) {
            if (i <= m) {
                factors_cnt[i] --;
                if (factors_cnt[i] == 0) sat --;
            }
        }
    };

    
    ll ans = INT32_MAX;
    while (right < v.size()) {     
        add(right);
        if (sat == m) {
            //cout << left << " , " << right << " satisfy ! \n";
            ans = min(ans, v[right] - v[left]);
        }

        while (left < right) {
            remove(left);
            if (sat != m) {
                add(left);
                break;
            }
            left ++;
            //cout << left << " , " << right << " satisfy ! \n";
            ans = min(ans, v[right] - v[left]);
        }

        right ++;
    }

    return ans == INT32_MAX ? -1 : ans;
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n, m;
        cin >> n >> m;
        vector<ll> nums;
        while (n --) {
            ll a;
            cin >> a;
            nums.push_back(a);
        }
        cout << solve(nums, m) << '\n';
    }
}