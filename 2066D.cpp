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



int count_num(const vector<int> &nums, int j, auto &&pred) {
    int cnt = 0;
    while (j >= 0) {
        if (pred(nums[j])) {
            cnt ++;
        }
        j--;
    }
    return cnt;
}

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    
    for (int i = 0;i < n;i ++) {
        cin >> nums[i];
    }


    bool push_0 = false;
    vector<int> t;
    for (int i : nums) {
        if (i == 0) {
            if (!push_0) {
                t.push_back(i);
                push_0 = true;
            }
        } else {
            t.push_back(i);
        }
    }

    vector<int> cnts(n + 1);
    int mex = 0;

    vector<int> dp;
    int ss = INT32_MAX;
    for (int i : t) {
        ss = min(ss, i);
        dp.push_back(ss);
    }

    bool pass = true;
    for (int i = t.size() - 1;i >= 0;i --) {
        if (t[i] < n + 1) {
            cnts[t[i]] = 1;
        }

        while (cnts[mex]) mex++;

        if (i > 0) {
            if (dp[i-1] < mex) {
                pass = false;
            }       
        }
    }

    if (pass) {
        cout << t.size() << '\n';
    } else {
        cout << t.size() - 1 << '\n';
    }
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}