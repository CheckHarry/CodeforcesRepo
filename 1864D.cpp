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
#include <optional> 


using namespace  std;
using ll = long long;




int solve(int n) {
    vector<int> mask_l(n, 0);
    vector<int> mask_r(n, 0);
    int le = 0;
    int pos_l = 0;
    int pos_r = 0;

    int ans = 0;
    for (int i = 0; i < n; i ++) {
        
        int s = le;
        char cc;
        
        for (int j = 0; j < n; j ++) {
            cin >> cc;
            s += mask_l[(pos_l + j) % n]; 
            s -= mask_r[(pos_r + j) % n];
                
            if ((s % 2) != (cc - '0')) {
                ans++;
                mask_l[(pos_l + j) % n] += 1;
                if (j + 1 < n) {
                    s += 1;
                    mask_r[(pos_r + j + 1) % n] += 1;
                }
            } 
        } 


        le += mask_l[pos_l];
        mask_l[pos_l] = 0;
        pos_l = (pos_l + 1) % n;

        mask_r[(pos_r - 1 + n) % n] = 0;
        pos_r = (pos_r - 1 + n) % n;        
    }

    return ans;
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        cout  << solve(n) << '\n';
    }
    
}

// 100
// 000
// 000

// 000
// 110
// 111

// 000
// 010
// 001

// 000
// 000
// 110