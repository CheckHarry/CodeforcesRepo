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

void sim(string& s1, vector<int> ops) {
    for (int i : ops) {
        for (int j = 0; j <= i - 1; j ++) {
            if (s1[j] == '0')  s1[j] = '1';
            else s1[j] = '0';
        }
        reverse(s1.begin(), s1.begin() + i);
        cout << s1 << '\n';
    }
}

void solve(const string& s1,const string& s2) {
    int s = 0;
    int left = 0;
    int right = s1.size() - 1;
    vector<int> ans;
    while (left <= right) {
        int sign1;
        if (s % 2 == 0) {
            sign1 = s1[left++];
        } else {
            sign1 = s1[right--];    
        }
        int sign2 = s2[s2.size() - s - 1];
        bool eql = (sign1 == sign2);
        if ((eql && (s % 2 == 0)) || (!eql && (s % 2 == 1))) {
            ans.push_back(1);
        }
        ans.push_back(s2.size() - s);
        s ++;
    }
    cout << ans.size() << " ";
    for (int i : ans) {
        cout << i << " ";
    }
    cout << '\n';
    // auto ss = s1;
    // sim(ss, ans);
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        string s1;
        string s2;
        cin >> s1;
        cin >> s2;
        solve(s1,s2);
    }
}