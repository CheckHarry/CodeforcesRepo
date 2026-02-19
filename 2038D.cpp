#include <algorithm>
#include <array>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <optional>
#include <set>
#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cstring>

using namespace std;
using ll = long long;



void solve() {
    int n;
    cin >> n;
    
    int cnt_00;
    int cnt_11;
    cout << "1 00" << std::endl;
    cin >> cnt_00;
    cout << "1 11" << std::endl;
    cin >> cnt_11;
    

    int cnt_01_add_10 = (n - 1 - cnt_00 - cnt_11);
    if (cnt_01_add_10 % 2) {
        int cnt_01;
        cout << "1 01" << std::endl;
        cin >> cnt_01;
        if (cnt_01 > cnt_01_add_10 - cnt_01) {
            cout << "0 1 0" << std::endl;
        } else {
            cout << "0 1 1" << std::endl;
        }
    } else {
        int cnt_01 = cnt_01_add_10 / 2;
        int cnt_0;
        cout << "1 0" << std::endl;
        cin >> cnt_0;
        int last_sign = cnt_0 - cnt_01 - cnt_00;
        //cout << " last_sign : " << last_sign << '\n';
        if (last_sign) {
            cout << "0 1 0" << std::endl;
        } else {
            cout << "0 1 1" << std::endl;
        }
    }  

    int verdict;
    cin >> verdict;
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}