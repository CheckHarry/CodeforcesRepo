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


int mceil(int a, int b) {
    if (a % b == 0) return a / b;
    return (a / b) + 1;
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int x , y;
        cin >> x >> y;
        int ans = INT32_MAX;
        double heu = (x + y);
        heu = sqrt(heu);
        int range = int(heu);
        for (int i = -100; i <= 100; i ++) {
            if (range + i > 0) {
                ans = min((range + i - 1) + mceil(x,range + i) + mceil(y,range + i), ans);
            }
        }
        cout << ans << '\n';
    }
}

/*
0???1
0?1
011
001

1?0
110
100

*/