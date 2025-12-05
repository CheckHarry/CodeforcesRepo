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



int solve(vector<int>& x,vector<int>& y) {
    auto vx = x;
    auto vy = y;
    int n = vx.size();
    sort(vx.begin(), vx.end());
    sort(vy.begin(), vy.end());
    for (int i = 0; i < n; i ++) {
        if (vx[i] != vy[i]) return false;
    }

    unordered_map<int,int> mp;
    for (int i = 0; i < n; i ++) {
        mp[x[i]] = i;
    }

    for (int i = 0; i < n; i ++) {
        y[i] = mp[y[i]];
    }

    int k = 0;
    vector<int> seen(n);
    for (int i = 0; i < n; i ++) {
        if (seen[i]) continue;

        int l = 0;
        int s = i;
        while (!seen[s]) {
            seen[s] = 1;
            s = y[s];
            l ++;
        }
        k += (l - 1);
    } 

    return (k % 2) == 0;
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        vector<int> v1;
        vector<int> v2;
        int nn = n;
        while (nn --) {
            int b;
            cin >> b;
            v1.push_back(b);
        }
        nn = n;
        while (nn --) {
            int b;
            cin >> b;
            v2.push_back(b);
        }
        cout << (solve(v1,v2) ? "YES" : "NO") << '\n';
    }
}