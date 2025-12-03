#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <span>
#include <set>
#include <map>
#include <vector>
#include <source_location>

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <array>

using namespace std;


bool check(std::string s, int k) {
    vector<int> v(s.size(),0);
    int a = 0;
    int i = 0;
    for (; i < s.size() - k; i ++) {
        a += v[i];
        bool is1 = (s[i] == '0') ? (a % 2 == 1) : (! (a%2 == 1));
        
        if (!is1) {
            if ((i + k) < s.size())
                v[i + k] -= 1;
            a += 1;
        } 
    }
    for (; i < s.size(); i ++) {
        a += v[i];
        bool is1 = (s[i] == '0') ? (a % 2 == 1) : (! (a%2 == 1));
        if (!is1) {
            if (i == (s.size() - k)) a ++;
            else return false;
        }
    }
    return true;
}

int solve(const std::string& s) {
    int a = 1;
    vector<int> m(s.size() + 1, 1);
    
    int checkcnt = 0;
    for (int i = 2; i <= s.size(); i ++) {
        if (m[i] == 0) {
            //cout << "skip " << i << '\n';
            continue;
        }
        checkcnt ++;
        if (check(s,i)) {
            a = max(i, a);
        } else {
            for (int j = 1; i * j < m.size(); j ++) {
                m[j * i] = 0;
            }
        }
    }
    
    return a;
}

int main() {
    int tests;
    cin >> tests;
    while (tests --) {
        int n;
        cin >> n;
        char c;
        string a;
        cin >> a;
        
        cout << solve(a) << '\n';
    }
}