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

struct edge {
    ll dst;
    ll weight;
};


struct node {
    ll index;
    ll s;
    friend bool operator<(const node& lhs,const node& rhs) {
        if (lhs.index == rhs.index) {
            return lhs.s < rhs.s;
        }
        return lhs.index < rhs.index;
    }
};


void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> adj_list(n + 1);
    vector<ll> slownesses(n + 1);
    for (int i = 0;i < m;i ++) {
        ll u,v,w;
        cin >> u >> v >> w;
        adj_list[u].push_back({v,w});
        adj_list[v].push_back({u,w});
    }

    for (int i = 0;i < n;i ++) {
        ll s;
        cin >> s;
        slownesses[i + 1] = s;
    }


    priority_queue<pair<ll,node>, std::vector<pair<ll,node>>, std::greater<pair<ll,node>>> pq;
    map<node,ll> distances;
    
    pq.push({0,{1,slownesses[1]}});
    distances[{1,slownesses[1]}] = 0;

    while (!pq.empty()) {
        auto [distance, node] = pq.top();
        auto [index, slowness] = node;
        pq.pop();
        for (auto adj : adj_list[index]) {
            auto [next_index, w] = adj;
            auto next_index_slowness = slownesses[next_index];
            ll next_slowness = (next_index_slowness < slowness) ? next_index_slowness : slowness;
            ll next_distance = distance + w * slowness;
            if (distances.find({next_index,next_slowness}) == distances.end()) {
                distances[{next_index, next_slowness}] = next_distance;
                pq.push({next_distance, {next_index, next_slowness}});
            } else if (distances[{next_index,next_slowness}] > next_distance) {
                distances[{next_index, next_slowness}] = next_distance;
                pq.push({next_distance, {next_index, next_slowness}});
            }
        }
    }

    ll ans = std::numeric_limits<ll>::max();
    for (const auto& [node,d] : distances) {
        if (node.index == n) {
            ans = min(d,ans);
        }
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