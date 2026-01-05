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


static constexpr ll modnum = 1000000007;
int mapp[100001];
int nums[100001];
void solve() {
    int n;
    cin >> n;
    int nn = n;
    int a;
    int pos = 0;
    while (nn--) {
        cin >> a;
        nums[pos] = a;
        mapp[a] = pos++;
    }
    int left = INT32_MAX;
    int right = INT32_MIN;
    
    ll ans = 1;
    for (int i = 0; i < n; i ++) {
        left = min(left, mapp[i]);
        right = max(right, mapp[i]);
        if (i == nums[left] || i == nums[right]) {
            continue;
        }
        ans = ans * ll(right - left + 1 - i);
        ans = ans % modnum;
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