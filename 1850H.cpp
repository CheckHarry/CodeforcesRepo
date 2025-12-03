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
#include <assert.h>
#include <optional>

using namespace std;


using ll = long long;

struct con {
    ll x;
    ll y;
    ll d;
};


void dfs(
    vector<vector<pair<ll,ll>>>& adjs,
    vector<optional<ll>>& seen,
    ll n
) {

    //assert(seen.find(n) != seen.end());
    ll current_pos = seen[n].value();
    
    for (const auto &[i, d] : adjs[n]) {
        if (seen[i]) continue;
        seen[i] = current_pos + d;
        dfs(adjs, seen, i);
    }
}

bool solve(int n, int m, const vector<con>& cons) {
    vector<vector<pair<ll,ll>>> adjs(n + 1);
    vector<optional<ll>> seen(n+1);

    for (const auto &[x,y,d] : cons) {
        adjs[x].push_back({y,d});
        adjs[y].push_back({x,-d});
    }

    for (int i = 1; i <= n; i ++) {
        if (seen[i]) continue;
        seen[i] = 0;
        dfs(adjs,seen,i);
    }

    // for (int i = 1; i <= n; i ++) {
    //     cout << i << " : " << (seen[i] ? seen[i].value() : -2) << '\n';
    // }
   
    for (const auto &[x,y,d] : cons) {
        //cout << x << " , " << y << '\n';
        if ((seen[y].value() - seen[x].value()) != d) return false;
    }

    return true;
}


int main() {
    int tests;
    cin >> tests;

    while (tests--) {
        int n , m;
        cin >> n >> m;
        vector<con> v(m);
        for (int i = 0; i < m; i ++) {
            cin >> v[i].x;
            cin >> v[i].y;
            cin >> v[i].d;
        }
        cout << (solve(n,m,v) ? "YES" : "NO") << '\n';
    }
}