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
 



int parents[200001];
int height[200001];
int h_max = -1;
void dfs(int pos, vector<int> &seen, const vector<unordered_set<int>> &adjs, int h) {
    for (int i : adjs[pos]) {
        if (seen[i]) continue;
        parents[i] = pos;
        height[i] = h;
        h_max = max(h, h_max);
        seen[i] = 1;
        dfs(i,seen,adjs,h + 1);
    }
}

void solve() {
    int n;
    cin >> n;
    vector<unordered_set<int>> adjs(n + 1);
    for (int i = 0;i < n - 1;i ++) {
        int x , y;
        cin >> x >> y;
        adjs[x].insert(y);
        adjs[y].insert(x);
    }
    parents[1] = -1;
    height[1] = 0;
    h_max = -1;
    vector<int> seen(n + 1);
    seen[1] = 1;
    dfs(1,seen,adjs,1);
    vector<vector<int>> reverse_mapping(200001);
    for (int i = 1;i <= n;i ++) {
        reverse_mapping[height[i]].push_back(i);
    }
    

    vector<int> removed(n + 1);
  
    int max_width = -1;
    int max_width_h = -1;
    for (int h = 0;h <= h_max;h ++) {
        if ((int)reverse_mapping[h].size() >= max_width) {
            max_width = reverse_mapping[h].size();
            max_width_h = h;
        }
    }

    
    vector<deque<int>> ops(max_width);
    for (int i = 0; i < reverse_mapping[max_width_h].size();i ++) {
        ops[i].push_back(reverse_mapping[max_width_h][i]);
    }

    for (int h = max_width_h + 1;h <= h_max;h ++) {
        deque<int> pending;
        for (int k = 0;k < ops.size();k ++) {
            pending.push_back(k);
        }
        
        for (int node : reverse_mapping[h]) {
            while (ops[pending.front()].back() == parents[node]) {
                int a = pending.front();
                pending.pop_front();
                pending.push_back(a);
            }
            ops[pending.front()].push_back(node);
            pending.pop_front();
        }
    } 

    for (int h = max_width_h - 1;h >= 0;h --) {
        deque<int> pending;
        for (int k = 0;k < ops.size();k ++) {
            pending.push_back(k);
        }
        
        for (int node : reverse_mapping[h]) {
            while (parents[ops[pending.front()].front()] == node) {
                int a = pending.front();
                pending.pop_front();
                pending.push_back(a);
            }
            
            cout << "push " << ops[pending.front()].front() << " " << node << '\n';
            ops[pending.front()].push_front(node);
            pending.pop_front();
        }
    } 
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}