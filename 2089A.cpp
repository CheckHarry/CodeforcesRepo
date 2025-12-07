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


int help(ll s, ll cnt, ll p, ll target) {
    if ((s + p) % (cnt + 1) == 0) {
        if ((s + p) / (cnt + 1) == target) return true;
        return false;
    }

    if ((s + p) / (cnt + 1) == target - 1) return true;

    return false;
}


void solve(int n) {
    int left = 0;
    int right = primes.size() - 1;

    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (primes[mid] <= (n / 2)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    ll p = primes[left];
    ll s = 0;
    ll cnt = 0;
    int lp = p;
    int rp = p + 1;
    
    vector<ll> pp;
    while (true) {
        if (1 <= lp && help(s,cnt,lp,p)) {
            pp.push_back(lp);
            s += lp;
            lp --;
            cnt ++;
        } else if (rp <= n && help(s,cnt,rp,p)) {
            pp.push_back(rp);
            s += rp;
            rp ++;
            cnt ++;
        }
        else break;
    }

    while (1 <= lp || rp <= n) {
        if (1 <= lp) 
            pp.push_back(lp--);
        else if (rp <= n) 
            pp.push_back(rp++);
    }

    for (ll i : pp) {
        cout << i << " ";
    }
    cout << '\n';
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
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        solve(n);
    }
}