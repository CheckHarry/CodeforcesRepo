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
 




int cnt[10010];
ll res = 0;


void dfs(int pos, int l, int n) {
    if (l >= n - 1) {
        res ++;
        return;
    }
    
    if (cnt[pos - 1 + 5001]) {
        cnt[pos - 1 + 5001] --;
        dfs(pos - 1, l + 1, n);
        cnt[pos - 1 + 5001] ++;
    }

    if (cnt[pos + 1 + 5001]) {
        cnt[pos + 1 + 5001] --;
        dfs(pos + 1, l + 1, n);
        cnt[pos + 1 + 5001] ++;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0;i < n;i ++) {
        cin >> nums[i];
    }
    memset(cnt,0,sizeof(cnt));
    res = 0;
    for (int i : nums) {
        cnt[i + 5001] ++;
    }
    if (cnt[5002]) {
        cnt[5002] --;
        dfs(1,0,n);
        cnt[5002] ++;
    }
     
    if (cnt[5000]) {
        cnt[5000] --;
        dfs(-1,0,n);
        cnt[5000] ++;
    }

    cout << res << '\n';
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}