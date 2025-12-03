#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <span>
#include <set>
#include <map>
#include <vector>
#include <source_location>

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <array>

using namespace std;



int modnum = 1000000000 + 7;
using ll = long long;
ll fast_pow(int x, int n) {
    if (n == 0) return 1;
    if (n == 1) return x;

    ll a = fast_pow(x, n >> 1);
    if (n % 2) {
        return (a * a * ll(x)) % modnum;
    } else {
        return (a * a) % modnum;
    }
}


int solve(const vector<int> &nums, int k) {
    vector<int> mp(64,0);
    vector<int> dp(64,0);
    for (int i: nums) {
        for (int k = 0; k < 64; k ++) {
            if ((k & i) == k) mp[k] ++;
        }
    }

    for (int i = 63; i >= 0; i --) {
        if (mp[i] == 0) continue;
        
        ll a = fast_pow(2,mp[i]) - 1;

        for (int k = 63; k >= 0; k --) {
            if ((k & i) == i) {
                a = (a - dp[k] + modnum) % modnum;
                //cout << a << '\n';
            }
        }
        dp[i] = a;
    }

    int ans = 0;
    for (int i = 0; i < 64 ; i ++) {
        if (__builtin_popcount(i) == k) {
            ans = (ans + dp[i]) % modnum;
        }
    }
    return ans;
}


int main() {
    int test;
    cin >> test;
    while (test--) {
        int n;
        int k;
        cin >> n >> k;
        vector<int> nums;
        while (n --) {
            int a;
            cin >> a;
            nums.push_back(a);
        }
        cout << solve(nums, k) << '\n';
    }
}