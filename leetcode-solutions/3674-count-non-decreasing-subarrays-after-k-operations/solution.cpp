
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int LOG = 17;

        while ((1 << LOG) <= n) LOG++;

        vector<long long> pref(n + 1, 0);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + nums[i];
        }

        // Find next greater or equal element
        vector<int> nxt(n, n);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                st.pop();
            }

            if (!st.empty()) {
                nxt[i] = st.top();
            }

            st.push(i);
        }

        // Binary lifting tables
        vector<vector<int>> up(LOG, vector<int>(n, n));
        vector<vector<long long>> cost(LOG, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            up[0][i] = nxt[i];

            int len = nxt[i] - i - 1;

            cost[0][i] = 1LL * nums[i] * len
                       - (pref[nxt[i]] - pref[i + 1]);
        }

        // Build binary lifting tables
        for (int b = 1; b < LOG; b++) {
            for (int i = 0; i < n; i++) {
                int mid = up[b - 1][i];

                if (mid < n) {
                    up[b][i] = up[b - 1][mid];

                    cost[b][i] = cost[b - 1][i]
                               + cost[b - 1][mid];
                }
                else {
                    up[b][i] = n;
                    cost[b][i] = cost[b - 1][i];
                }
            }
        }

        // Calculate cost of making nums[l...r] non-decreasing
        auto getCost = [&](int l, int r) -> long long {
            long long total = 0;
            int p = l;

            for (int b = LOG - 1; b >= 0; b--) {
                int next = up[b][p];

                if (next <= r) {
                    total += cost[b][p];
                    p = next;
                }
            }

            total += 1LL * nums[p] * (r - p)
                   - (pref[r + 1] - pref[p + 1]);

            return total;
        };

        // Binary search for each starting index
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int low = i;
            int high = n - 1;
            int best = i - 1;

            while (low <= high) {
                int mid = low + (high - low) / 2;

                if (getCost(i, mid) <= k) {
                    best = mid;
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }

            ans += best - i + 1;
        }

        return ans;
    }
};

