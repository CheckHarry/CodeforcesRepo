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
#include <queue>

using namespace std;
using ll = long long;


void recur(const vector<vector<int>>& adjs, vector<int> &distances,int pos,vector<int> &seen,int cur_distance,int n) {
    seen[pos] = 1;
    int recur_cnt = 0;
    for (int i : adjs[pos]) {
        if (seen[i]) continue;
        recur_cnt ++;
        distances[i] = cur_distance + 1;
        recur(adjs,distances,i,seen,cur_distance+1,n);
    }
}

enum class OpType {
    one,
    two
};

struct Op {
    OpType op;
    int node;
    friend ostream& operator<<(ostream& os,const Op& op) {
        if (op.op == OpType::one) {
            os << "1";
        } else {
            os << "2 " << op.node;
        }
        return os;
    }
};


void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adjs(n + 1);
    vector<int> degrees(n + 1);
    for (int i = 1;i <= n - 1;i ++) {
        int a,b;
        cin >> a >> b;
        adjs[a].push_back(b);
        adjs[b].push_back(a);
        degrees[a] ++;
        degrees[b] ++;
    }

    vector<int> distances(n + 1);
    vector<int> seen(n + 1);

    recur(adjs,distances,1,seen,0,n);

    queue<int> q;
    for (int i = 1;i <= n;i ++) {
        if (degrees[i] == 1 && i != n) {
            q.push(i);
        }
    }

    vector<Op> ops;

    int steps_walked = 0;
    while (!q.empty()) {
        int next = q.front();
        q.pop();
        if (abs(steps_walked - distances[next]) % 2 == 0) {
            ops.push_back(Op{OpType::one, 0});
            steps_walked ++;
        } else {
            ops.push_back(Op{OpType::one, 0});
            ops.push_back(Op{OpType::one, 0});
            steps_walked += 2;
        }
        ops.push_back(Op{OpType::two,next});
        int tmp_index = -1;
        for (int i : adjs[next]) {
            degrees[i] -= 1;
            if (degrees[i] == 1) {
                tmp_index = i;
            }
        }
        if (tmp_index != n && tmp_index != -1) {
            q.push(tmp_index);
        }
    }

    cout << ops.size() << '\n';
    for (const auto& op : ops) {
        cout << op << '\n';
    }
}


int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        solve();
    }
}

/*

1
7
1 2
1 3
3 4
4 5
4 7
6 7
*/