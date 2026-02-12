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



void solve() {
    int n;
    cin >> n;
    vector<pair<string,string>> vecs(n);
    for (int i = 0;i < n;i ++) {
        cin >> vecs[i].first >> vecs[i].second;
    }

    vector<vector<int>> adj_matrix(n,vector<int>(n, 0));
    for (int i = 0;i < n;i ++) {
        for (int j = i + 1;j < n;j ++) {
            if (vecs[i].first == vecs[j].first || vecs[i].second == vecs[j].second) {
                adj_matrix[i][j] = 1;
                adj_matrix[j][i] = 1;
            }
        }   
    }

    int limit = (1 << n);
    vector<vector<int>> dp(limit + 1,vector<int>(n, -1));
    for (int i = 0;i < n;i ++) {
        dp[1 << i][i] = 0;
    }
 
    for (int mask = 1; mask <= limit;mask ++) {
        for (int i = 0;i < n;i ++) {
            if (!(mask & (1 << i))) continue;

            int prev_mask = mask ^ (1 << i);

            if (prev_mask == 0) continue;

            for (int j = 0;j < n;j ++) {
                if (!(prev_mask & (1 << j))) continue;
                if (!(adj_matrix[i][j])) continue;
                if (dp[prev_mask][j] == -1) continue;
                
                dp[mask][i] = max(dp[mask][i],dp[prev_mask][j] + 1);
            }
        }
    }

    int max_path = 0;
    for (int mask = 1;mask <= limit;mask ++) {
        for (int i = 0;i < n;i ++) {
            max_path = max(max_path,dp[mask][i]);   
        }
    }
    
    cout << n - max_path - 1 << '\n';
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}