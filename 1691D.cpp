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
#include <optional> 
#include <limits>


using namespace  std;
using ll = long long;

template <typename T>
class SegmentTree {
private:
    int n;                      // Size of the input array
    std::vector<T> tree;        // The segment tree array
    T neutral_element;          // Neutral element for the operation (e.g., 0 for sum, INF for min)
    std::function<T(T, T)> op;  // The operation function (e.g., addition, min, max)

    // Build the tree
    // node: current node index in the tree array
    // start: start index of the segment covered by this node
    // end: end index of the segment covered by this node
    // data: the initial input array
    void build(int node, int start, int end, const std::vector<T>& data) {
        if (start == end) {
            // Leaf node will have a single element
            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;
            // Recurse on the left child
            build(2 * node, start, mid, data);
            // Recurse on the right child
            build(2 * node + 1, mid + 1, end, data);
            // Internal node will have the result of operation on its children
            tree[node] = op(tree[2 * node], tree[2 * node + 1]);
        }
    }

    // Update a value at a specific index
    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {
            // Leaf node
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                // If idx is in the left child, recurse on the left child
                update(2 * node, start, mid, idx, val);
            } else {
                // If idx is in the right child, recurse on the right child
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            // Update internal node
            tree[node] = op(tree[2 * node], tree[2 * node + 1]);
        }
    }

    // Query the range [l, r]
    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            // Range represented by a node is completely outside the given range
            return neutral_element;
        }
        if (l <= start && end <= r) {
            // Range represented by a node is completely inside the given range
            return tree[node];
        }
        // Range represented by a node is partially inside and partially outside
        int mid = (start + end) / 2;
        T p1 = query(2 * node, start, mid, l, r);
        T p2 = query(2 * node + 1, mid + 1, end, l, r);
        return op(p1, p2);
    }

public:
    // Constructor
    // data: input array
    // operation: lambda or function pointer for the merge logic (e.g., [](int a, int b){ return a + b; })
    // neutral: identity element (0 for sum, INT_MAX for min, etc.)
    SegmentTree(const std::vector<T>& data, std::function<T(T, T)> operation, T neutral) 
        : n(data.size()), op(operation), neutral_element(neutral) {
        
        // Resize tree to 4*n to be safe
        tree.resize(4 * n);
        
        // Build the tree starting from root (node 1) covering range [0, n-1]
        if (n > 0) {
            build(1, 0, n - 1, data);
        }
    }

    // Public update function (0-based index)
    void update(int idx, T val) {
        if (idx < 0 || idx >= n) return; // Bounds check
        update(1, 0, n - 1, idx, val);
    }

    // Public query function (0-based range [l, r])
    T query(int l, int r) {
        if (l > r || l < 0 || r >= n) return neutral_element; // Bounds check
        return query(1, 0, n - 1, l, r);
    }
};

struct range {
    int left;
    int right;
    int index;
};

vector<range> get_range_frm(const vector<ll> &vec) {
    int n = vec.size();
    vector<range> ranges(n);

    auto comp = [] (int a, int b) {
        return a >= b;
    };

    for (int i = 1;i < n;i ++) {
        int k = i - 1;
        while (k >= 0 && comp(vec[i],vec[k])) {
            k = ranges[k].left - 1;
        }
        ranges[i].left = k + 1;
        ranges[i].index = i;
    }    

    for (int i = n - 1;i >= 0;i --) {
        int k = i + 1;
        while (k < n && comp(vec[i],vec[k])) {
            k = ranges[k].right + 1;
        }
        ranges[i].right = k - 1;
        ranges[i].index = i;
    }    

    return ranges;
}


void solve()
{
    int n;
    cin >> n;
    vector<ll> nums(n);
    for (int i = 0;i < n;i ++) {
        cin >> nums[i];
    }

    ll ss = 0;
    vector<ll> pre(n);
    for (int i = 0;i < n;i ++) {
        ss += nums[i];
        pre[i] = ss;
    }

    vector<ll> maxs(n);
    vector<ll> mins(n);
    ll maxn = std::numeric_limits<ll>::min();
    ll minn = std::numeric_limits<ll>::max();
    for (int i = 0;i < n;i ++) {
        minn = min(pre[i], minn);
        mins[i] = minn;
    }

    for (int i = n - 1;i >= 0;i --) {
        maxn = max(pre[i], maxn);
        maxs[i] = maxn;
    }

    auto ranges = get_range_frm(nums);

    vector<pair<ll,int>> min_stack;
    vector<pair<ll,int>> max_stack;

    int min_stack_pos = 0;
    int max_stack_pos = 0;

    for (int i = 0;i < n;i ++) {
        // while (min_stack_pos < i) {
        //     while (!min_stack.empty() && min_stack.back().first > pre[min_stack_pos]) {
        //         min_stack.pop_back();
        //     }
        //     min_stack.push_back({pre[min_stack_pos],min_stack_pos});
        //     min_stack_pos ++;
        // }

        // while (max_stack_pos <= ranges[i].right) {
        //     while (!max_stack.empty() && max_stack.back().first < pre[max_stack_pos]) {
        //         max_stack.pop_back();
        //     }
        //     max_stack.push_back({pre[max_stack_pos],max_stack_pos});
        //     max_stack_pos ++;
        // }

        // ll min_element = std::numeric_limits<ll>::max();
        // for (int j = min_stack.size() - 1;j >= 0;j --) {
        //     if (min_stack[j].second < ranges[i].left - 1) break;
        //     min_element = min(min_element, min_stack[j].first);
        // }

        // ll max_element = std::numeric_limits<ll>::min();
        // for (int j = max_stack.size() - 1;j >= 0;j --) {
        //     if (max_stack[j].second <= i) break;
        //     max_element = min(max_element, min_stack[j].first);
        // }

        ll min_element = std::numeric_limits<ll>::max();
        for (int j = i - 1;j >= 0;j --) {
            if (j < ranges[i].left - 1) break;
            min_element = min(min_element, pre[j]);
        }
        if (ranges[i].left == 0) {
            min_element = min(min_element, 0ll);
        }

        ll max_element = std::numeric_limits<ll>::min();
        for (int j = i;j <= ranges[i].right ;j ++) {
            max_element = max(max_element, pre[i]);
        }

        if (max_element - min_element > nums[i]) {
            cout << "NO\n";
            return;
        }

    } 
    cout << "YES\n";
}



int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}