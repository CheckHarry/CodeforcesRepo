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
#include <optional> 


using namespace  std;
using ll = long long;


ll modnum = 1000000000 + 7;

// Standard function for modular exponentiation: (base^exp) % mod
long long power(long long base, long long exp) {
    long long res = 1;
    base %= modnum;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % modnum;
        base = (base * base) % modnum;
        exp /= 2;
    }
    return res;
}

std::vector<long long> getBatchInverses(const std::vector<ll>& nums) {
    int n = nums.size();
    if (n == 0) return {};

    std::vector<long long> inverses(n);
    std::vector<long long> prefix(n);

    // Step 1: Compute Prefix Products
    prefix[0] = nums[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = (prefix[i - 1] * nums[i]) % modnum;
    }

    // Step 2: Compute Inverse of the TOTAL product (The only O(log MOD) step)
    long long invTotal = power(prefix[n - 1], modnum - 2);

    // Step 3: Iterate backwards to recover individual inverses
    // Formula: inv(nums[i]) = prefix[i-1] * inv(prefix[i])
    for (int i = n - 1; i > 0; i--) {
        // invTotal currently holds inv(prefix[i])
        inverses[i] = (invTotal * prefix[i - 1]) % modnum;
        
        // Update invTotal to become inv(prefix[i-1]) for the next iteration
        // inv(prefix[i-1]) = inv(prefix[i]) * nums[i]
        invTotal = (invTotal * nums[i]) % modnum; 
    }
    // Handle the first element separately
    inverses[0] = invTotal;

    return inverses;
}

ll solve(vector<ll> &v, ll m) {
    sort(v.begin(), v.end());

    ll s = 0;
    vector<pair<ll,ll>> vv;
    optional<ll> k;
    for (ll i : v) {
        if (k && k.value() != i) {
            vv.push_back(std::make_pair(k.value(),s));
            k = i;
            s = 1;
        } else if (k) {
            s ++;
        } else {
            k = i;
            s = 1;
        }
    }
    vv.push_back(std::make_pair(k.value(),s));

    // for (const auto& [k, v] : vv) {
    //     cout << k << " , " << v << '\n';
    // }

    if (m > vv.size()) {
        return 0;
    }

    ll i = 0;
    ll ans = 0;
    ll prd = 1;
    for (;i < m; i ++) {
        prd *= vv[i].second;
        prd = prd % modnum; 
    }

    std::vector<ll> v_to_inverse;
    for (const auto &[_,v] : vv) {
        v_to_inverse.push_back(v);
    }
    auto vv_inverse = getBatchInverses(v_to_inverse);

    for (;i < ll(vv.size()); i ++) {
        if((vv[i - 1].first - vv[i - m].first) < m)
            ans = (ans + prd) % modnum;
        prd *= vv_inverse[i - m];
        prd = prd % modnum;
        prd *= vv[i].second;
        prd = prd % modnum;
    }
    
    if((vv[vv.size() - 1].first - vv[vv.size() - m].first) < m)
        ans = (ans + prd) % modnum;

    return ans;

}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n,m;
        cin >> n >> m;
        vector<ll> nums;
        while (n --) {
            ll a;
            cin >> a;
            nums.push_back(a);
        }
        cout  << solve(nums, m) << '\n';
    }
}