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
#include <list>
#include <random>
#include <optional>
 
using namespace std;
using ll = long long;
 

void solve() {
    int n;
    cin >> n;
    
    vector<int> parents(n, -1);

    parents[1] = 0;
    
    int i = 2;
    for ( ;i < n; i ++) {
        int x;
        cout << "? " << i << " " << 1 << std::endl;
        cin >> x;
        if (x == -1) {
            std::exit(-1);
        }
        if (x == 0) {
            parents[i] = 1;
            break;
        } else {
            parents[i] = 0;
        }
    }

    i ++;
    
    int k = 2;
    for (;i < n; i ++) {
        while (true) {
            int x;
            cout << "? " << i << " " << k << std::endl;
            cin >> x;
            if (x == -1) {
                std::exit(-1);
            }
            if (x == 0) {
                parents[i] = k;
                k ++;
                break;
            } else {
                k ++;
            }
        }
    }   

    cout << "! ";
    for (int i = 1;i < n; i ++) {
        cout << parents[i] << " ";
    } cout << std::endl;


}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}