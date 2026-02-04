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

using namespace std;
using ll = long long;

template <typename T> class SegmentTree {
  private:
    int n;
    std::vector<T> tree;
    T neutral_element;
    std::function<T(T, T)> op;

    void build(int node, int start, int end, const std::vector<T>& data) {
        if (start == end) {

            tree[node] = data[start];
        } else {
            int mid = (start + end) / 2;

            build(2 * node, start, mid, data);

            build(2 * node + 1, mid + 1, end, data);

            tree[node] = op(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update(int node, int start, int end, int idx, T val) {
        if (start == end) {

            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }

            tree[node] = op(tree[2 * node], tree[2 * node + 1]);
        }
    }

    T query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return neutral_element;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        T p1 = query(2 * node, start, mid, l, r);
        T p2 = query(2 * node + 1, mid + 1, end, l, r);
        return op(p1, p2);
    }

  public:
    SegmentTree(const std::vector<T>& data, std::function<T(T, T)> operation, T neutral)
        : n(data.size()), op(operation), neutral_element(neutral) {

        tree.resize(4 * n);

        if (n > 0) {
            build(1, 0, n - 1, data);
        }
    }

    void update(int idx, T val) {
        if (idx < 0 || idx >= n)
            return;
        update(1, 0, n - 1, idx, val);
    }

    T query(int l, int r) {
        if (l > r || l < 0 || r >= n)
            return neutral_element;
        return query(1, 0, n - 1, l, r);
    }
};

struct range {
    int left;
    int right;
    int index;
};

vector<range> get_range_frm(const vector<ll>& vec) {
    int n = vec.size();
    vector<range> ranges(n);

    auto comp = [](int a, int b) { return a >= b; };

    for (int i = 1; i < n; i++) {
        int k = i - 1;
        while (k >= 0 && comp(vec[i], vec[k])) {
            k = ranges[k].left - 1;
        }
        ranges[i].left = k + 1;
        ranges[i].index = i;
    }

    for (int i = n - 1; i >= 0; i--) {
        int k = i + 1;
        while (k < n && comp(vec[i], vec[k])) {
            k = ranges[k].right + 1;
        }
        ranges[i].right = k - 1;
        ranges[i].index = i;
    }

    return ranges;
}

void solve() {
    int n;
    cin >> n;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    ll ss = 0;
    vector<ll> pre(n);
    for (int i = 0; i < n; i++) {
        ss += nums[i];
        pre[i] = ss;
    }

    vector<ll> maxs(n);
    vector<ll> mins(n);
    ll maxn = std::numeric_limits<ll>::min();
    ll minn = std::numeric_limits<ll>::max();
    for (int i = 0; i < n; i++) {
        minn = min(pre[i], minn);
        mins[i] = minn;
    }

    for (int i = n - 1; i >= 0; i--) {
        maxn = max(pre[i], maxn);
        maxs[i] = maxn;
    }

    auto ranges = get_range_frm(nums);

    SegmentTree<ll> seg_tree_max{pre, [](ll a, ll b) -> ll { return max(a, b); },
                                 std::numeric_limits<ll>::min()};

    SegmentTree<ll> seg_tree_min{pre, [](ll a, ll b) -> ll { return min(a, b); },
                                 std::numeric_limits<ll>::max()};

    for (int i = 0; i < n; i++) {
        ll min_element = min_element = seg_tree_min.query(max(ranges[i].left - 1, 0), i - 1);
        if (ranges[i].left == 0) {
            min_element = min(min_element, 0ll);
        }

        ll max_element = seg_tree_max.query(i, ranges[i].right);

        if ((max_element - min_element) > nums[i]) {
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