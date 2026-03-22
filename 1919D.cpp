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
 


struct node {
    int prev;
    int next;
    int num;
    int index;
    friend bool operator<(const node& left,const node& right) {
        if (left.num == right.num) {
            return left.index < right.index;
        }
        return left.num < right.num;
    }
};

node nodes[200001];
void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0;i < n;i ++) {
        cin >> nums[i];
    }

    memset(nodes,0,sizeof(nodes));
    for (int i = 0;i < n;i ++) {
        if (i == 0) {
            nodes[i] = node{-1,-1,nums[i],i};
        } else {
            nodes[i - 1].next = i;
            nodes[i] = node{i - 1,-1,nums[i],i};
        }
    }

    
    
    priority_queue<node> pq;
    unordered_set<int> erased;

    auto check = [&](int i) -> bool {
        if (nodes[i].prev != -1 && nodes[nodes[i].prev].num == nodes[i].num - 1) {
            return true;
        }
        if (nodes[i].next != -1 && nodes[nodes[i].next].num == nodes[i].num - 1) {
            return true;
        }
        return false;
    };
    for (int i = 0;i < n;i ++) {
        if (check(i)) {
            pq.push(nodes[i]);
            erased.insert(i);
        }
    }
  
    while (!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        int prev = nodes[node.index].prev;
        int next = nodes[node.index].next;
        //cout << "erase " << node.num << " index " << node.index << '\n';
        if (prev != -1) {
            nodes[prev].next = next;
        }
        if (next != -1) {
            nodes[next].prev = prev;
        }   
        if (prev != -1 && erased.find(prev) == erased.end() && check(prev)) {
            pq.push(nodes[prev]);
            erased.insert(prev);
        }
        if (next != -1 && erased.find(next) == erased.end() && check(next)) {
            pq.push(nodes[next]);
            erased.insert(next);
        }
    }
    
    if (erased.size() == n - 1) {
        for (int i = 0;i < n;i ++) {
            if (erased.find(i) == erased.end() && nodes[i].num > 0) {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}

/*
2 x3 2 2 x3 x3 2 x3 x2 1 1 x2 x2 1 0 1 x2 x2 x3
*/