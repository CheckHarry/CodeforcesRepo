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


vector<int> primes;


void solve(int n) {
    vector<bool> used(int)
}

int main() {
    vector<int> primes_b(100005, 1);
    for (int i = 2; i < primes_b.size(); i ++) {
        if (primes_b[i]) {
            primes.push_back(i);
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