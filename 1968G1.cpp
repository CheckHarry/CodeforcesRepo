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


vector<int> zfunction(const vector<char> &str) {
    vector<int> zfunction(str.size());

    int ref = -1;
    for (int i = 1;i < str.size();i ++) {
        if (ref != -1 && ref + zfunction[ref] > i) {
            zfunction[i] = min(zfunction[i - ref], ref + zfunction[ref] - i);
        }

        while (i + zfunction[i] < str.size() && str[i + zfunction[i]] == str[zfunction[i]]) {
            zfunction[i] ++;
        }

        if (ref == -1 || (ref + zfunction[ref] < i + zfunction[i])) {
            ref = i;
        }
    }

    return zfunction;
}

bool check(
    const vector<char> &str,
    const vector<int> &z,
    int k,
    int part_target
) {
    vector<int> first_be_k(str.size(), -1);

    int be_k = -1;
    for (int i = str.size() - 1;i >= 0;i --) {
        first_be_k[i] = be_k;
        if (z[i] >= k) {
            be_k = i;
        }
    }
    
    int part = 1;
    int pos = 0;

    // for (int i : first_be_k) {
    //     cout << i << " ";
    // } cout << '\n';

    while (pos < str.size()) {
        int cur = pos;
        while (pos != -1 && (pos - cur) < k) {
            pos = first_be_k[pos];
        }
        if (pos == -1) break;
        part ++;
        if (part >= part_target) break;
    }

    return part >= part_target;
}


void solve() {
    int n,k;
    cin >> n >> k >> k;
    vector<char> str(n);
    for (int i = 0;i < n;i ++) {
        cin >> str[i];
    }

    auto z = zfunction(str);

    int upper = n / k;
    int left = 0;
    int right = upper;

    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (check(str,z,mid,k)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (check(str,z,right,k)) {
        cout << right << '\n';
    } else {
        cout << left << '\n';
    }
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}