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

int gen_len(int n) {
    int len = 0;
    while (n) {
        len ++;
        n /= 10;
    }
    return len;
}

void solve(int n) {
    int len = gen_len(n);
    std::string ee = std::to_string(n);

    vector<int> ans;
    for (int a = 1; a <= 10000; a ++) {
        for (int b = a * len ; abs(b - a * len) <= 7 && b >= 1; b --) {
            if (b >= 10000) continue;
            int diff = a * len - b;
            int rhs = a * n - b;
            if (diff == 0) continue;
            if (gen_len(rhs) != diff) continue;
            std::string k1 = std::to_string(rhs);            
            bool is_sol = true;
            for (int i = 0; i < diff; i ++) {
                if (ee[i % len] != k1[i]) {
                    is_sol = false;
                    break;
                }
            }
            if (is_sol) {
                ans.push_back(a);
                ans.push_back(b);
            }
        }
    }

    cout << ans.size() / 2 << 
    for (int i = 0;i < ans.size(); i += 2) {
        cout << ans[i] << " " << ans[i + 1] << '\n';
    }
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int a;
        cin >> a;
        solve(a);
    }
} 