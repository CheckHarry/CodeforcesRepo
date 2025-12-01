#include <iostream>
#include <vector>
#include <string>
#include <algorithm>



using namespace std;

const int INF = 1e9;

void solve() {
    int n, m, k;
    if (!(cin >> n >> m >> k)) return;
    string s;
    cin >> s;

    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    // b[i] = 1 if s[i] != s[i+1], else 0.
    // We want to maximize sum(b[i]).
    vector<int> b(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        b[i] = (s[i] != s[i+1]);
    }

    // dp_global[w] = max ones achievable with total cost w
    // Initialize with -1 to indicate unreachable states
    vector<int> dp_global(m + 1, -1);
    dp_global[0] = 0;

    // Identify which chains have start/end toggles
    // Start toggle corresponds to operation j=0, flipping b[k-1]
    // End toggle corresponds to operation j=n-k, flipping b[n-k-1]
    int start_chain = (k - 1) % k;
    int end_chain = (n - k - 1) % k;
    if (end_chain < 0) end_chain += k;

    // Toggles exist only if indices are within bounds of b (0 to n-2)
    // b[k-1] exists if k-1 < n-1 => k < n
    // b[n-k-1] exists if n-k-1 >= 0 => n > k
    bool has_start = (k < n);
    bool has_end = (k < n);

    // Process each chain
    for (int r = 0; r < k; ++r) {
        vector<int> chain_bits;
        for (int i = r; i < n - 1; i += k) {
            chain_bits.push_back(b[i]);
        }

        if (chain_bits.empty()) continue;

        bool is_start = (has_start && r == start_chain);
        bool is_end = (has_end && r == end_chain);

        int len = chain_bits.size();

        // dp[j][p] -> min cost to get j zeros, with parity p
        // Using two vectors to save memory/allocations: dp0 for p=0, dp1 for p=1
        vector<int> dp0(len + 1, INF), dp1(len + 1, INF);

        // Initialization
        if (is_start) {
            dp0[0] = 0;       // Start with p=0 (no start toggle used)
            dp1[0] = 1;       // Start with p=1 (start toggle used, cost 1)
        } else {
            dp0[0] = 0;
        }

        for (int i = 0; i < len; ++i) {
            vector<int> next0(len + 1, INF), next1(len + 1, INF);
            int current_val = chain_bits[i];

            // Iterate through possible number of zeros so far
            for (int j = 0; j <= i; ++j) {
                // Transition from p=0
                if (dp0[j] != INF) {
                    int p = 0; 
                    int c = dp0[j];
                    
                    // Option 1: Make current bit 0
                    {
                        int flip = (current_val != 0);
                        int np = p ^ flip;
                        int cost = c + (np ? 1 : 0); // Add 1 to cost if interval continues
                        if (cost <= m) {
                            if (np == 0) next0[j + 1] = min(next0[j + 1], cost);
                            else         next1[j + 1] = min(next1[j + 1], cost);
                        }
                    }
                    // Option 2: Make current bit 1
                    {
                        int flip = (current_val != 1);
                        int np = p ^ flip;
                        int cost = c + (np ? 1 : 0);
                        if (cost <= m) {
                            if (np == 0) next0[j] = min(next0[j], cost);
                            else         next1[j] = min(next1[j], cost);
                        }
                    }
                }

                // Transition from p=1
                if (dp1[j] != INF) {
                    int p = 1; 
                    int c = dp1[j];
                    
                    // Option 1: Make current bit 0
                    {
                        int flip = (current_val != 0);
                        int np = p ^ flip;
                        int cost = c + (np ? 1 : 0);
                        if (cost <= m) {
                            if (np == 0) next0[j + 1] = min(next0[j + 1], cost);
                            else         next1[j + 1] = min(next1[j + 1], cost);
                        }
                    }
                    // Option 2: Make current bit 1
                    {
                        int flip = (current_val != 1);
                        int np = p ^ flip;
                        int cost = c + (np ? 1 : 0);
                        if (cost <= m) {
                            if (np == 0) next0[j] = min(next0[j], cost);
                            else         next1[j] = min(next1[j], cost);
                        }
                    }
                }
            }
            dp0 = move(next0);
            dp1 = move(next1);
        }

        // Collect valid results (cost, ones) for this chain
        vector<pair<int, int>> items;
        for (int j = 0; j <= len; ++j) {
            int cost = INF;
            if (is_end) {
                // Can end with p=0 (closed) or p=1 (closed by end toggle, cost +1)
                int c0 = dp0[j];
                int c1 = (dp1[j] == INF ? INF : dp1[j] + 1);
                cost = min(c0, c1);
            } else {
                // Must end with p=0
                cost = dp0[j];
            }

            if (cost <= m) {
                items.push_back({cost, len - j});
            }
        }

        // Merge into global DP (Knapsack)
        // We must pick exactly one outcome from this chain
        vector<int> next_global(m + 1, -1);
        for (auto& item : items) {
            int c = item.first;
            int v = item.second;
            for (int w = 0; w <= m - c; ++w) {
                if (dp_global[w] != -1) {
                    next_global[w + c] = max(next_global[w + c], dp_global[w] + v);
                }
            }
        }
        dp_global = next_global;
    }

    int max_segments = 0;
    for (int w = 0; w <= m; ++w) {
        if (dp_global[w] != -1) {
            max_segments = max(max_segments, dp_global[w]);
        }
    }
    
    // Total segments = 1 + sum(b)
    cout << max_segments + 1 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}