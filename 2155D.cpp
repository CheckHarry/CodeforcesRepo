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


std::random_device rd;
std::mt19937 g(rd());
 

void solve() {
    int n;
    cin >> n;

    vector<pair<int,int>> v;
    for (int i = 1; i <= n; i ++) {
        for (int j = i + 1; j <= n; j ++) {
            v.push_back({i,j});
        }
    }

    std::shuffle(v.begin(), v.end(), g);

    for (auto &[i,j] : v) {
        cout << i << " " << j << std::endl;
        int ans;
        cin >> ans;
        if (ans == 1) {
            return;
        }
        if (ans == -1) {
            cout << "ERROR!";
            std::exit(1);
            return;
        }
    }
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}