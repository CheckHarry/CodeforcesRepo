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
#include <cstring>
using namespace std;
using ll = long long;
 

static constexpr ll modnum = 998244353;

struct Edge {
    int u;
    int v;
    int w;
    friend bool operator<(const Edge& lhs, const Edge& rhs) {
        return lhs.w < rhs.w;
    }
};

struct UnionFind
{
    UnionFind(int n) : parents(n), rank(n) {
        for (int i = 0;i < n;i ++) {
            parents[i] = i;
            rank[i] = 1;
        }
    }

    int get_parent(int n) {
        if (parents[n] == n) {
            return n;
        } else {
            return parents[n] = get_parent(parents[n]);
        }
    }

    void merge(int x,int y) {
        int px = get_parent(x);
        int py = get_parent(y);
        if (px == py) return;
        parents[px] = py;
        rank[py] += rank[px];
    }

    int get_component_size(int x) {
        int px = get_parent(x);
        return rank[px];
    }


    private:
    vector<int> parents;
    vector<int> rank;
};



ll fast_pow(ll a,ll pow) {
    if (pow == 1) {
        return a;
    }
    if (pow == 0) {
        return 1;
    }

    ll k = fast_pow(a, pow / 2);
    ll res = (k * k) % modnum;
    if (pow % 2) {
        return (res * a) % modnum;
    }
    return res;
}

void solve() {
    int n, S;
    cin >> n >> S;
    vector<Edge> edges;
    
    for (int i = 0;i + 1 < n;i ++) {
        int u,v,w;
        cin >> u >> v >> w;
        edges.push_back({u,v,w});
    }

    sort(edges.begin(),edges.end());
    
    ll ans = 1;
    UnionFind uf(n + 1);
    for (const auto &edge : edges) {
        ll usize = uf.get_component_size(edge.u);
        ll vsize = uf.get_component_size(edge.v);
        uf.merge(edge.u,edge.v);
        ans = (ans * fast_pow(S - edge.w + 1, usize * vsize - 1)) % modnum;
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