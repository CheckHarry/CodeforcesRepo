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


struct Node {
    ll min_val;
    ll max_val;
    ll min_max_right;
};

struct Segtree {
    size_t n;
    vector<Node> tree;

    Node unit = {
        INT64_MAX,
        INT64_MIN,
        INT64_MAX,
    };

    Segtree(const vector<ll>& nums,const unordered_map<ll,vector<int>>& index) : n(nums.size()), tree{4 * n + 1} {
        _build(1,n,1,nums,index);
    }   

    static Node combine(const Node& left,const Node& right) {
        return {
            min(left.min_val,right.min_val),
            max(left.max_val,right.max_val),
            min(left.min_max_right,right.min_max_right)
        };
    }

    Node _build(int l,int r,int i,const vector<ll>& nums,const unordered_map<ll,vector<int>>& index) {
        if (l == r) {
            tree[i].max_val = nums[l - 1];
            tree[i].min_val = nums[l - 1];
            tree[i].min_max_right = index.at(nums[l - 1]).back();
            return tree[i];
        }

        int mid = (l + r) / 2;
        auto node_left = _build(l,mid,2*i,nums,index);
        auto node_right = _build(mid + 1,r,2*i + 1,nums,index);

        tree[i] = combine(node_left,node_right);
        
        return tree[i];
    }   


    Node _query(int l,int r,int i,int target_l,int target_r) {
        if (r < target_l || target_r < l) {
            return unit;
        }

        if (l == r) {
            return tree[i];
        }

        if (target_l <= l && r <= target_r) {
            return tree[i];
        }

        int mid = (l + r) / 2;
        auto node_left = _query(l,mid,2*i,target_l,target_r);
        auto node_right = _query(mid + 1,r,2*i + 1,target_l,target_r);
        return combine(node_left,node_right);
    }

    Node query(int target_l,int target_r) {
        return _query(1,n,1,target_l,target_r);
    }

    void _set_null(int l,int r,int i,int index) {
        if (l == r && index == l) {
            tree[i] = unit;
            return;
        }

        if (index < l || r < index) {
            return;
        }
        
        int mid = (l + r) / 2;
        _set_null(l,mid,2 * i,index);
        _set_null(mid + 1,r,2 * i + 1,index);
     
        tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
    }

    void set_null(int index) {
        _set_null(1,n,1,index);
    }

    void _print(int l,int r,int i) {
        if (l == r) {
            cout << tree[i].min_max_right << " ";
            return;
        }

        int mid = (l + r) / 2;
        _print(l,mid,2 * i);
        _print(mid + 1,r,2 * i + 1);
    }

    void print() {
        _print(1,n,1);
    }
};


void solve() {
    int n;
    cin >> n;
    vector<ll> nums(n);
    for (int i = 0;i < n;i ++) {
        cin >> nums[i];
    }

    unordered_map<ll,vector<int>> index;
    for (int i = 0;i < n;i ++) {
        index[nums[i]].push_back(i);
    }

    Segtree segtree(nums,index);
    vector<ll> ans;
    int pos = 1;
    int start = 0;

    while (ans.size() < index.size()) {
        int left =  start;
        int right = n - 1;

        while (left + 1 < right) {
            int mid = (left + right) / 2;
            auto node = segtree.query(start + 1,mid + 1);
            if (node.min_max_right >= mid) {
                left = mid;
            } else {
                right = mid;
            }
        }
        
        int right_index;
        if (segtree.query(start + 1,right + 1).min_max_right >= right) {
            right_index = right;
        } else {
            right_index = left;
        }

        
        auto node = segtree.query(start + 1,right_index + 1);
        ll val = pos % 2 ? node.max_val : node.min_val;
        //cout << i + 1 << " " << right_index + 1 << " : " << val << '\n';
        ans.push_back(val);

        for (const auto &index_null : index[val]) {
            //cout << " set null : " << index_null << '\n';
            segtree.set_null(index_null + 1);
        }
        start = index[val][0] + 1;
        //segtree.print();
        //cout << '\n';

        pos ++;
    }


    cout << ans.size() << '\n';
    for (auto v : ans) {
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