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
#include <random>

using namespace std;
using ll = long long;

 
void solve() {
    int n, k;
    cin >> n >> k;

    int max_cnt = (n * (n + 1)) / 2;
    int target = max_cnt - k;
    vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));

    dp[0][0] = 0;

    for (int i = 0; i <= n; i ++) {
        for (int j = 0; j < target + 1;j ++) {
            if (dp[i][j] != -1) {
                for (int len = 1; len <= n ; len ++) {
                    int inc = (len * (len + 1)) / 2;
                    if (i + len < n + 1 && (j + inc) < target + 1) {
                        dp[i + len][j + inc] = len;
                    }
                }
            }
        }
    }
    if (dp.back().back() == -1) {
        cout << 0 << '\n';
        return;
    }

    int i = n;
    int j = target;
    vector<int> conf;
    int right = n;
    while (i > 0) {
        int len = dp[i][j];
        for (int num = right - len + 1;num <= right; num ++) {
            cout << num << " ";
        }
        right -= len;
        
        i -= len;
        j -= (len * (len + 1)) / 2;
    }
    cout << '\n';
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}