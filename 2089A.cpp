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


using namespace  std;
using ll = long long;


unordered_set<int> primes;


void solve(int n) {
    vector<bool> used(n + 1,0);
    used[2] = 1;
    vector<int> ans;
    ans.push_back(2);

    ll s = 2;
    ll count = 1;
    while (true) {
        ll avg = s / count;
        if (s % count) avg += 1;
    }
}

int main() {
    vector<int> primes_b(100005, 1);
    for (int i = 2; i < primes_b.size(); i ++) {
        if (primes_b[i]) {
            primes.insert(i);
        }
        for (int j = 2 * i; j < primes_b.size(); j += i) {
            primes_b[j] = 0;
        }
    }

    int tests;
    while (tests--) {
        int n;
        cin >> n;
        solve(n);
    }
}