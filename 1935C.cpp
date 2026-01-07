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

using namespace std;
using ll = long long;



bool try_ans(const vector<pair<ll,ll>> &nums,ll limit,ll l) {
    if (limit > nums.size()) return false;
    
    
    for (int i = 0; i < nums.size(); i ++) {
        priority_queue<ll> pq;
        ll ss = 0;
        for (int j = i + 1; j < nums.size(); j ++) {
            if (2 + pq.size() == limit) {
                ll sum = ss + nums[i].second + nums[j].second + nums[j].first - nums[i].first;
                if (sum <= l) {
                    return true;
                }
            }
            pq.push(nums[j].second);
            ss += nums[j].second;
            if (pq.size() > (limit - 2)) {
                ss -= pq.top();
                pq.pop();
            }
        }
    }

    return false;
}


void solve() {
    ll n, l;
    cin >> n >> l;
    vector<pair<ll,ll>> nums;
    ll min_ele = INT32_MAX;
    while (n--) {
        ll a, b;
        cin >> a >> b;
        nums.emplace_back(b,a);
        min_ele = min(a, min_ele);
    }
    if (min_ele > l) {
        cout << "0\n";
        return;
    }

    sort(nums.begin(),nums.end());
    
    ll left = 2;
    ll right = nums.size();

    while (left + 1 < right) {
        ll mid = (left + right) / 2;
        if (try_ans(nums, mid, l)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (try_ans(nums, right, l)) {
        cout << right << '\n';
        return;
    }

    if (try_ans(nums, left, l)) {
        cout << left << '\n';
        return;
    }

    cout << "1\n";
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}