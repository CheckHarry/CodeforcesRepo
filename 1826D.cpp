#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;  




int solve(
    vector<int> nums
) {
    int a = INT32_MIN;
    int b = INT32_MIN;
    int ans = INT32_MIN;
    for (int i = nums.size() - 1; i >= 0;i --){
        //cout << a << " , " << b <<  ":" << ans << '\n';
        int a0 = INT32_MIN, b0 = INT32_MIN;
        a0 = max(nums[i] - i, a);
        if (a != INT32_MIN) {
            b0 = max(a + nums[i], b);
        }
        //cout << "::::" << a0 << " , " << b0 <<  ":" << ans << '\n';

        if (b != INT32_MIN) {
            ans = max(ans, b + nums[i] + i);
        }

        a = a0;
        b = b0;
    }
    //cout << '\n';
    return ans;
};


int main() {
    int test_cnt;
    cin >> test_cnt;
    vector<int> ans;
    for (int i = 0; i < test_cnt;i ++) {
        int nums_cnt;
        cin >> nums_cnt;
        vector<int> nums;
        for (int j = 0; j < nums_cnt;j ++) {
            int a;
            cin >> a;
            nums.push_back(a);
        }
        ans.push_back(solve(nums));
    }

    for (int i: ans) {
        cout << i << '\n';
    }



}