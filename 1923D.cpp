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
#include <list>
#include <random>
#include <optional>
#include <bitset>
 
using namespace std;
using ll = long long;


vector<int> solve_left_side(
    const vector<ll>& nums,
    int n
) {
    vector<int> prev_diff(n, -1);
    vector<ll> prev_sum(n, 0);
    vector<int> ans(n, INT32_MAX);

    ll sum = 0;
    for (int i = 1;i < n;i ++) {
        if (nums[i - 1] == nums[i]) {
            prev_diff[i] = prev_diff[i - 1];
        } else {
            prev_diff[i] = i - 1;
        }
    }
    for (int i = 0;i < n;i ++) {
        sum += nums[i];
        prev_sum[i] = sum;
    }

    for (int i = 1;i < n;i ++) {
        
        if (nums[i - 1] > nums[i]) {
            ans[i] = 1;
            continue;
        }

        if (prev_diff[i - 1] == -1) continue;

        ll b = prev_sum[i - 1] - nums[i];
        auto it = std::lower_bound(prev_sum.begin(), prev_sum.begin() + i, b);
    
        if (it != prev_sum.begin() || (prev_sum[i - 1] > nums[i] && prev_diff[i - 1] != -1)) {
            int index = std::distance(prev_sum.begin(), it);
            index = min(index, prev_diff[i - 1]);
            ans[i] = min(ans[i], i - index);
            continue;
        } 
    }    


    return ans;
}


void solve()
{
    int n;
    cin >> n;
    vector<ll> nums(n);
    for (int i = 0;i < n;i ++) {
        cin >> nums[i];
    }

    vector<int> ans(n, INT32_MAX);

    auto ans1 = solve_left_side(nums, n);
    reverse(nums.begin(), nums.end());
    auto ans2 = solve_left_side(nums, n);
    reverse(ans2.begin(), ans2.end());

    for (int i = 0;i < n;i ++) {
        ans[i] = min(ans[i], ans1[i]);
        ans[i] = min(ans[i], ans2[i]);
        if (ans[i] == INT32_MAX) {
            ans[i] = -1;
        }
    }

    for (int i: ans) {
        cout << i << " ";
    } cout << '\n';
}



int main()
{
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}