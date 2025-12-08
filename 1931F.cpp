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


using namespace std;
using ll = long long;


bool dfs(int n, const vector<unordered_set<int>> &nexts, vector<int> &seen) {
    //cout << " see " << n << '\n';
    if (seen[n] == 1) return false;
    if (seen[n] == 2) return true;
    seen[n] = 1;
    for (int i : nexts[n]) {
        if (!dfs(i,nexts,seen)) return false;
    }
    seen[n] = 2;

    return true;
}

bool solve(const vector<unordered_set<int>> &nexts, int n) {
    vector<int> seen(n+1,0);
    for (int i = 1; i <= n; i ++) {
        if (seen[i]) continue;
        //cout << " === " << i << '\n';
        if (!dfs(i,nexts,seen)) return false;
    }
    return true;
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n , k;
        cin >> n >> k;
        vector<unordered_set<int>> nexts(n + 1);
        for (int i = 0; i < k; i ++) {
            int a;
            cin >> a;
            vector<int> v;
            for (int j = 1; j < n; j ++) {
                cin >> a;
                v.push_back(a);
            }

            for (int j = 0; j < v.size(); j ++) {
                if (j + 1 < v.size())
                    nexts[v[j]].insert(v[j + 1]);
            }

        }
        cout <<  (solve(nexts,n) ? "YES" : "NO") << '\n';
    }
}