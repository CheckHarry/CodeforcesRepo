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



void dfs(const vector<int>& nums, vector<int> &seen, vector<int>& cyc, int pos, int cnt) {
    if (seen[pos] == 3) return;

    if (seen[pos] == 1) {
        seen[pos] = 2;
        cyc[pos] = cnt - cyc[pos];
        return;
    }

    if (seen[pos]) {
        return;
    }

    if (seen[pos] == 0) {
        seen[pos] = 1;
        cyc[pos] = cnt;
    }

    dfs(nums,seen, cyc ,nums[pos], cnt + 1);

    if (seen[pos] != 2) {
        seen[pos] = 3;
    }
}

void dfs2(
    const vector<vector<int>>& adj_lists,
    vector<int> &seen,int pos
) {
    for (int i : adj_lists[pos]) {
        if (seen[i]) continue;
        seen[i] = 1;
        dfs2(adj_lists, seen, i);
    }
}


void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> nums(n + 1);
    for (int i = 1;i <= n;i ++) {
        int a;
        cin >> a;
        nums[i] = a;
    }

    if (k == 1) {
        for (int i = 1;i <= n;i ++) {
            if (nums[i] != i) {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
        return;
    }

    vector<int> seen(n + 1);
    vector<int> cyc(n + 1);

    for (int i = 1;i <= n;i ++) {
        if (seen[i]) continue;
        dfs(nums,seen, cyc,i,0);
    }

    for (int i = 1;i <= n;i ++) {
        if (seen[i] == 2) {
            if (cyc[i] == k) {
                seen[i] = 2;
            } else {
                cout << "NO\n";
                return;
            }
                
        } else {
            seen[i] = 0;
        }
    }

    vector<vector<int>> adj_lists(n + 1);
    for (int i = 1;i <= n;i ++) {
        adj_lists[nums[i]].push_back(i);
    }

    for (int i = 1;i <= n;i ++) {
        if (seen[i] == 2) {
            dfs2(adj_lists, seen, i);
        }
    }

    for (int i = 1;i <= n;i ++) {
        if (!seen[i]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}



int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}