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

using namespace std;
using ll = long long;


vector<char> charset = {'I','T','L'};
char select_not_in(char a, char b) {
    for (char c : charset) {
        if (c != a && c != b) {
            return c;
        }
    }
    return 0;
}



void solve() {
    int n;
    cin >> n;
    int nn = n;
    if (nn == 1) {
        cout << "-1\n";
        return;
    }
    std::list<char> s;
    std::map<char,int> cnt;
    while (nn--) {
        //cout << "HERE" << n << '\n';
        char c;
        cin >> c;
        s.push_back(c);
        cnt[c] += 1;
    }

    int ops = 2 * n;
    vector<int> opss;
    
    for (int i = 0;i < ops; i ++) {
        int max_v = 0;
        for (auto &[k,v] : cnt) {
            max_v = max(max_v,v);
        }
        for (int b = 0; b < 2; b ++) {
            auto run_once = [&]() {
                auto it_left = s.begin();
                auto it_right = it_left;
                it_right++;

                while (it_right != s.end()) {
                    if (*it_left != *it_right) {
                        char t = select_not_in(*it_left, *it_right);
                        if ((cnt[t] == max_v) == b) {
                            cnt[t] += 1;
                            s.insert(it_right, t);
                            opss.push_back(std::distance(s.begin(), it_left) + 1);
                            return true;
                        }
                    }
                    it_left ++;
                    it_right ++;
                }
                return false;
            };
            if (run_once()) break;
        }
       
        
        if (cnt['I'] == cnt['T'] && cnt['T'] == cnt['L']) {
            break;
        }
    
    }

    if (!(cnt['I'] == cnt['T'] && cnt['T'] == cnt['L'])) {
        cout << -1 << '\n';
        return;
    }

    cout << opss.size() << '\n';
    for (int i : opss) {
        cout << i << '\n';
    }

    for (char c : s) {
        cout << c;
    } cout << '\n';
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}