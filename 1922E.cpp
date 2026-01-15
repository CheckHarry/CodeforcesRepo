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
#include <bitset>
 
using namespace std;
using ll = long long;


vector<ll> decompose(ll a) {
    vector<ll> res;

    int k = 1;
    while (a > 0) {
        for (int i = 1; i < 64; i ++) {
            ll num = (1ULL << i) - k;
            if (num > a) {
                res.push_back(i - 1);
                a -= ((1ULL << (i - 1)) - k);
                k = 0;
                break;
            }
        }
    }
    return res;
}

void solve() {
    ll a;
    cin >> a;

    vector<ll> ans;
    auto decomposed = decompose(a - 1);
    sort(decomposed.begin(), decomposed.end());

    for (int i = 1; i <= decomposed.back(); i ++) {
        ans.push_back(i);
    }

    decomposed.pop_back();
    while (!decomposed.empty()) {
        ans.push_back(decomposed.back() + 1);
        decomposed.pop_back();
    }

    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << i << " ";
    }
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}