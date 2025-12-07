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


vector<int> coins = {1,3,6,10,15};
int dp[2000];

int solve(int n) {
    
    if (n < 1000) return dp[n];

    int e = (n % 15) + 15 * 5;
    int ans = (n - e) / 15;
    
    return ans + dp[e];
}


int main() {
    
    for (int i = 1; i < 2000; i ++) {
        dp[i] = INT32_MAX;
    }

    for (int i: coins)
        dp[i] = 1;


    for (int i = 1; i < 1500; i ++) {
        for (int a : coins) {
            dp[i + a] = min(dp[i] + 1,dp[i + a]);
        }
    }

    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        cout << solve(n) << '\n';
    }
}