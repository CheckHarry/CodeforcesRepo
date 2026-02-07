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



void solve() {
    int n;
    cin >> n;
    vector<ll> powers(n + 1);
    vector<int> permutation(n + 1);
    for (int i = 1;i <= n;i ++) {
        cin >> powers[i];
    }
    for (int i = 1;i <= n;i ++) {
        cin >> permutation[i];
    }

    vector<pair<ll, int>> sorted_mushrooms(n + 1);
    for(int i=1; i<=n; i++) {
        sorted_mushrooms[i] = {powers[i], i};
    }
    sort(sorted_mushrooms.begin() + 1, sorted_mushrooms.end());

    vector<int> original_to_sorted(n + 1);
    for(int i=1; i<=n; i++) {
        original_to_sorted[sorted_mushrooms[i].second] = i;
    }

    for (int &i : permutation) {
        i = original_to_sorted[i];
    }

    sort(powers.begin() + 1, powers.end());

    vector<int> banned(n + 1);
    vector<int> used(n + 1);
    ll strength = -1;
    ll min_power = std::numeric_limits<ll>::max();
    int target_k = 0;
    int pos = n;
    int cnt = 0;
    for (int k = 1;2 * k - 1 <= n; k ++) {
        if (k > 1) {
            // evict p_{k - 1}
            int index = permutation[k - 1];
            banned[index] = 1;
            if (used[index]) {
                cnt --;
            }
            used[index] = 0;
        }

        while (cnt < k) {
            for (;pos >= 1;pos --) {
                if (!banned[pos] && !used[pos]) {
                    used[pos] = 1;
                    cnt ++;
                    min_power = min(powers[pos], min_power);
                    break;
                }
            }
            if (pos <= 0) break;
        }

        if (cnt == k) {
            ll tmp_strength = k * min_power;
            if (tmp_strength > strength) {
                strength = tmp_strength;
                target_k = k;
            }
        }
    }

    cout << strength << " " << target_k << '\n';
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}