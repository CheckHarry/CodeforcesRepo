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


void solve(int a, int b, int c) {
    if (c < max(a,b) || c > max(a,b) + 1) {
        cout << "-1\n";
        return;
    }

    if (c > max(a,b)) {
               
    }

}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int a,b,c;
        cin >> a >> b >> c;
        solve(a,b,c);
    }
}