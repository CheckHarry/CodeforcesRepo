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



void solve(const std::string& s) {
    vector<int> cnt(26,0);

    for (char c : s) {
        cnt[c - 'a'] ++;
    }
    vector<char> ans(s.size());

    auto set = [&](int i, char c) {
        //cout << "set ans " << i << " to " << c << '\n';
        ans[i] = c;
    };
    int left = 0;
    int right = s.size() - 1;
    while (left < right) {
        vector<int> pos;
        int acc = 0;
        for (int i = 0;i < 26; i ++) {
            if (cnt[i]) {
                acc += cnt[i];
                pos.push_back(i);
            }
                
            if (acc >= 2) break;
        }

        if (acc < 2) break;

        if (pos.size() == 1) {
            cnt[pos[0]] -= 2;
            set(left++, pos[0] + 'a');
            set(right--, pos[0] + 'a');
        } else if (pos.size() == 2) {
            int test_count = 0;
            for (int i = pos[0] + 1; i < 26; i ++) {
                if (i != pos[1])
                    test_count += cnt[i];
            }
            if (cnt[pos[1]] >= 2) {
                if (test_count == 0) {
                    set(left++, pos[1] + 'a');
                    set(right--, pos[1] + 'a');
                    cnt[pos[1]] -= 2;
                    continue;
                } 
                
                set(left++, pos[1] + 'a');
                set(right--, pos[0] + 'a');
                cnt[pos[0]] --;
                cnt[pos[1]] --;
                break;  
            } else {
                set(left++, pos[1] + 'a');
                set(right--, pos[0] + 'a');
                cnt[pos[0]] --;
                cnt[pos[1]] --;
                break;
            }
            
        } else {
            std::cout << "ERROR\n";
            return;
        }
    }
        

    while (left <= right) {
        for (int i = 0;i < 26; i ++) {
            if (cnt[i]) {
                set(left++, i + 'a');
                cnt[i] --;
                break;
            }
        }
    }

    std::string s1(ans.begin(), ans.end());
    std::string s2(ans.begin(), ans.end());
    reverse(s2.begin(),s2.end());

 
        cout << s1 << '\n';
    
}

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        std::string s;
        cin >> s;
        solve(s);
    }
}



// baccb
// b   