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


int get_left_most(int n) {
    int pos = -1;
    while (n) {
        n = (n >> 1);
        pos ++;
    }

    return pos;
}

void solve() {
    int n,k;
    cin >> n >> k;

    vector<ll> ans;

    // k > 1
    if (k > 1) {
        int left_most = get_left_most(k - 1);
        
        for (int i = 0;i < left_most;i ++) {
            ans.push_back(1 << i);
        }

        if ((k - 1 - ((1 << left_most) - 1)) > 0) {
            ans.push_back(k - 1 - ((1 << left_most) - 1));
        }
    }
        

    ans.push_back(k + 1);
    ans.push_back(3 * k);

    int t = 2;
    while (true) {
        ans.push_back(t * k);
        t *= 2;
        if (t * k >= n) break;
    }

    cout << ans.size() << '\n';
    for (ll i : ans) {
        cout << i << " ";
    } cout << '\n';

}


int main()
{
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}
    
