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


int binary_search(const vector<int>& v, int x) {
    int left = 0;
    int right = v.size() - 1;  

    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (v[mid] <= x) {
            left = mid;
        } else {
            right = mid;
        }
    }

    if (v[right] <= x) {
        return v[right];
    } else {
        return v[left];
    }
}


string solve(const string& s){
    vector<int> z(s.size());

    int pos = -1;
    int a = -1;
    for (int i = 1;i < s.size(); i ++) {
        if (pos != -1 && a >= i) {
            z[i] = std::min(z[i - pos], int(a - i));
        }
        while (i + z[i] < s.size() && s[i + z[i]] == s[z[i]]) {
            z[i] ++;    
        }

        if (i + z[i] > a) {
            pos = i;
            a = i + z[i];
        }
    }

    vector<int> ss;
    int valid_mm = -1;
    int valid_pos = -1;
    for (int i = 1; i <= s.size(); i ++) {
        int b = s.size() - i;

        if (!ss.empty() && z[b] >= ss[0]) {
            int ss_b = binary_search(ss, z[b]);
            if (ss_b > valid_mm) {
                valid_mm = ss_b;
                valid_pos = b;
            }
        }
        
        if (z[b] == i) {
            ss.push_back(i);
        }
    }

    if (valid_mm == -1) {
        return "Just a legend";
    }

    return s.substr(valid_pos, valid_mm);

}

int main() {
    string s;
    cin >> s;
    cout << solve(s) << '\n';
} 
// xfixfixausidhjiuasdhiuxfix
// xfixfiausidhjiuasdhiuxfix