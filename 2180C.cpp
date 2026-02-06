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
    int n, k;
    cin >> n >> k;

    vector<int> digits;
    
    int nn = n;
    while (nn) {
        digits.push_back(nn % 2);
        nn = (nn >> 1);
    }

    if (k % 2 == 0) {
        vector<int> vv(k);
        vector<int> free(k);
        int free_count = 0;
        for (int i = digits.size() - 1;i >= 0;i --) {
            for (auto &v : vv) {
                v *= 2;
            }
            if (digits[i] == 1) {
                int index_to_free = -1;
                for (int index = 0;index < k;index ++) {
                    if (free[index] == 0) {
                        index_to_free = index;
                        free[index] = 1;
                        free_count ++;
                        break;
                    }
                }
                index_to_free = (index_to_free == -1) ? (k - 1) : index_to_free;
                for (int index = 0;index < k; index ++) {
                    if (index_to_free != index) {
                        vv[index] += 1;
                    }
                }
            } else {
                int c = free_count / 2;
                int fill = 0;
                for (int index = 0;index < vv.size(); index ++) {
                    if (free[index] && fill < 2 * c) {
                        vv[index] += 1;
                        fill ++;
                    }
                }
            }
        }
        for (int v : vv) {
            cout << v << " ";
        } cout << '\n';

        return;
    }

    vector<int> vv(k);

    for (int i = digits.size() - 1;i >= 0;i --) {
        for (auto &v : vv) {
            v *= 2;
        }

        if (digits[i]) {
            for (int j = 0;j < k;j ++) {
                vv[j] += 1;
            }
        }
    }

    for (int v : vv) {
        cout << v << " ";
    } cout << '\n';
    
}



int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}