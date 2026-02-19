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


struct op{
    int a,b,c;
};

void solve() {
    int n,m;
    cin >> n >> m;
    vector<unordered_set<int>> adjs(n + 1);
    if (n <= 2) {
        cout << "0\n";
        return;
    }
    
    for (int i = 0;i < m;i ++) {
        int a,b;
        cin >> a >> b;
        adjs[a].insert(b);
        adjs[b].insert(a);
    }

    map<int,unordered_set<int>> degree_map;
    for (int i = 1;i <= n;i ++) {
        degree_map[adjs[i].size()].insert(i);
    }

    vector<op> ops;

    auto toggle = [&](int a,int b) {
        int degree_a = adjs[a].size();
        int degree_b = adjs[b].size();
        int degree_a_new = degree_a;
        int degree_b_new = degree_b;
        if (adjs[a].find(b) == adjs[a].end()) {
            adjs[a].insert(b);
            adjs[b].insert(a)   ;
            degree_a_new += 1;
            degree_b_new += 1;
        } else {
            adjs[a].erase(b);
            adjs[b].erase(a);
            degree_a_new -= 1;
            degree_b_new -= 1;
        }
        degree_map[degree_a].erase(a);
        degree_map[degree_a_new].insert(a);
        degree_map[degree_b].erase(b);
        degree_map[degree_b_new].insert(b);
    };

    auto right = degree_map.rbegin();
    for (;right != degree_map.rend();right++) {
        if (right->first < 2) break;
        while (!right->second.empty()) {
            int a = *right->second.begin();
            int b = *adjs[a].begin();
            int c = *(++adjs[a].begin());
            toggle(a,b);
            toggle(b,c);
            toggle(a,c);
            ops.push_back({a,b,c});
        }
    }

    if (degree_map[1].size() > 0) {
        vector<int> single_nodes;
        vector<pair<int,int>> two_nodes;
        while (!degree_map[0].empty()) {
            single_nodes.push_back(*degree_map[0].begin());
            degree_map[0].erase(*degree_map[0].begin());;
        }
        
        while (!degree_map[1].empty()) {
            int a = *degree_map[1].begin();
            int b = *adjs[a].begin();
            two_nodes.push_back({a,b});
            degree_map[1].erase(a);
            degree_map[1].erase(b);
        }

        if (single_nodes.empty()) {
            single_nodes.push_back(two_nodes.back().first);
            two_nodes.pop_back();
        }

        for (int i = 0;i < two_nodes.size();i ++) {
            ops.push_back({single_nodes[0],two_nodes[i].first,two_nodes[i].second});
        }

        int k = two_nodes[0].first;
        for (int i = 1;i < single_nodes.size(); i ++) {
            ops.push_back({single_nodes[0],k,single_nodes[i]});
            k = single_nodes[i];
        }
    }

    cout << ops.size() << '\n';
    for (const auto &[a,b,c] : ops)  {
        cout << a << " " << b << " " << c << '\n';
    }

    /*
    for (const auto& [degree,s] : degree_map) {
        cout << "\ndegree: " << degree << '\n';
        for (const auto& v : s) {
            cout << v  << '\n';
        } cout << '\n';
    }

    for (int node = 1;node <= n;node ++) {
        cout << "\node: " << node << '\n';
        for (const auto& v : adjs[node]) {
            cout << v  << '\n';
        } cout << '\n';
    }*/
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}