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
 
using namespace std;
using ll = long long;
 

struct conf {
    int e = -1;
    int x;
    int y;
};

int find_a_b_left(
    const vector<int>& ds,
    const vector<int>& fs,
    int c
) {
    int ds_p = 0;
    int fs_p = fs.size() - 1;
    int e = -1;

    for (;ds_p < ds.size();ds_p ++) {
        while (ds[ds_p] + fs[fs_p] > c && fs_p > 0) {
            fs_p --;
        }
        if (ds[ds_p] + fs[fs_p] <= c && ds[ds_p] + fs[fs_p] > e) {
            e = ds[ds_p] + fs[fs_p];
        }
    }
    // for (int x : ds) {
    //     for (int y: fs) {
    //         if (x + y <= c && x + y > e) {
    //             e = x + y;
    //         }
    //     }
    // }

    return e;
}

int find_a_b_right(
    const vector<int>& ds,
    const vector<int>& fs,
    int c
) {
    int ds_p = 0;
    int fs_p = fs.size() - 1;
    int e = INT32_MAX;

    for (;ds_p < ds.size();ds_p ++) {
        while (fs_p > 0 && ds[ds_p] + fs[fs_p - 1] >= c) {
            fs_p --;
        }
        if (ds[ds_p] + fs[fs_p] >= c && ds[ds_p] + fs[fs_p] < e) {
            e = ds[ds_p] + fs[fs_p];
        }
    }
    // for (int x : ds) {
    //     for (int y: fs) {
    //         if (x + y >= c && x + y < e) {
    //             e = x + y;
    //         }
    //     }
    // }


    return e;
}
 
void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    
    vector<int> nums;
    vector<int> ds;
    vector<int> fs;
    for (int i = 0;i < n;i ++) {
        nums.emplace_back();
        cin >> nums.back();
    }
    for (int i = 0;i < m;i ++) {
        ds.emplace_back();
        cin >> ds.back();
    }
    for (int i = 0;i < k;i ++) {
        fs.emplace_back();
        cin >> fs.back();
    }
 
    map<int,int> cnt;
    for (int i = 0; i + 1< n; i ++) {
        cnt[nums[i + 1] - nums[i]] += 1;
    }
 
    if (cnt.rbegin() -> second > 1) {
        cout << cnt.rbegin() -> first << '\n';
        return;
    }
 
    int target = cnt.rbegin() -> first;
    cnt.erase(target);
 
    std::optional<int> second_big;
    if (cnt.size() > 0) {
        second_big = cnt.rbegin() -> first;
    }

 
    int a, b;
    for (int i = 0; i + 1< n; i ++) {
        if (target == (nums[i + 1] - nums[i])) {
            a = nums[i];
            b = nums[i + 1];
            break;
        }
    }
 
    sort(ds.begin(), ds.end());
    sort(fs.begin(), fs.end());
    int ans = target;

    auto fit_to_second_big = [&](int e) {
        if (e == -1 || e == INT32_MAX) {
            return ans;
        }
        if (!(a <= e && e <= b)) {
            return ans;
        }

        int tt = min(max(e - a, b - e),target);
        if (second_big) {
            return max(tt, second_big.value());
        } else {
            return tt;
        }
    };


 
    vector<int> to_approach = {
        (a + b) / 2 - 1,
        (a + b) / 2,
        (a + b) / 2 + 1,
        
    };

    if (second_big) {
        to_approach.push_back(b - second_big.value());
        to_approach.push_back(a + second_big.value());
    }

    for (int c : to_approach) {
        int e = find_a_b_left(ds,fs,c);
        ans = min(ans, fit_to_second_big(e));
        int e2 = find_a_b_right(ds,fs,c);
        ans = min(ans, fit_to_second_big(e2));
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