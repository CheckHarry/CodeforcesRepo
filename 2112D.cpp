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


using namespace  std;
using ll = long long;

struct edge {
    int x;
    int y;
};

void dfs(
    int n,
    const vector<vector<edge>>& adjs,
    vector<int>& seen,
    bool out
) {
    for (const auto& [x,y] : adjs[n]) {
        if (seen[y]) continue;
        seen[y] = 1;
        if (out) {
            cout << n << " " << y << '\n';
        } else {
            cout << y << " " << n << '\n';
        }
        dfs(y,adjs,seen,!out);
    }

}

void solve(
    int n,
    const vector<vector<edge>>& adjs
) {
    vector<int> degree(n + 1);
    vector<int> seen(n + 1);

    for (int i = 1;i < adjs.size(); i ++) {
        degree[i] = adjs[i].size();
    }

    for (int i = 1; i <= n; i ++) {
        if (degree[i] == 2) {
            seen[i] = 1;
            int k1 , k2;
            k1 = adjs[i][0].y;
            k2 = adjs[i][1].y;


            cout << "YES" << '\n';
            cout << k1 << " " << i << '\n';
            cout << i << " " << k2 << '\n';
            seen[k1] = 1;
            seen[k2] = 1;
            dfs(k1,adjs,seen,true);
            dfs(k2,adjs,seen,false);
            return;
        }
    }

    cout << "NO\n";
}





int main() {
    int tests;
    cin >> tests;
    while (tests--)  {
        int n;
        cin >> n;
        int u, v;
        
        vector<vector<edge>> adjs(n+1);
        for (int i = 1; i <= n - 1; i ++) {
            cin >> u >> v;
            adjs[u].push_back({u,v});
            adjs[v].push_back({v,u});
        }

        solve(n,adjs);

    }
}