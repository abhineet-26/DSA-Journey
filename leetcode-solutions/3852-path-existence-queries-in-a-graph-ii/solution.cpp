#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Create a sorted copy of nums to enable monotonic interval step tracking
        vector<int> nums_sorted = nums;
        sort(nums_sorted.begin(), nums_sorted.end());

        // Compute R[i]: the largest index reachable moving right from index i
        vector<int> R(n);
        int j_right = 0;
        for (int i = 0; i < n; ++i) {
            while (j_right + 1 < n && nums_sorted[j_right + 1] <= nums_sorted[i] + maxDiff) {
                j_right++;
            }
            R[i] = j_right;
        }

        // Compute L[i]: the smallest index reachable moving left from index i
        vector<int> L(n);
        int j_left = 0;
        for (int i = 0; i < n; ++i) {
            while (j_left < i && nums_sorted[j_left] < nums_sorted[i] - maxDiff) {
                j_left++;
            }
            L[i] = j_left;
        }

        // Binary lifting sparse tables (18 levels is enough since 2^17 > 10^5)
        // Stored as 1D arrays for maximum cache friendliness and performance
        vector<int> up_right(18 * n);
        vector<int> up_left(18 * n);

        for (int i = 0; i < n; ++i) {
            up_right[0 * n + i] = R[i];
            up_left[0 * n + i] = L[i];
        }

        for (int j = 1; j < 18; ++j) {
            int prev_idx = (j - 1) * n;
            int curr_idx = j * n;
            for (int i = 0; i < n; ++i) {
                up_right[curr_idx + i] = up_right[prev_idx + up_right[prev_idx + i]];
                up_left[curr_idx + i] = up_left[prev_idx + up_left[prev_idx + i]];
            }
        }

        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            int u = q[0];
            int v = q[1];
            int src = nums[u];
            int dst = nums[v];

            // Trivial case: both target values are identical
            if (src == dst) {
                if (u == v) {
                    answer.push_back(0);
                } else {
                    answer.push_back(1); // Distinct elements with identical values are connected
                }
                continue;
            }

            if (src < dst) {
                // Check for a direct edge first
                if (dst - src <= maxDiff) {
                    answer.push_back(1);
                    continue;
                }

                // Greedily grab the largest possible starting index matching the first jump
                auto it = upper_bound(nums_sorted.begin(), nums_sorted.end(), src + maxDiff);
                int i1 = distance(nums_sorted.begin(), prev(it));

                int curr = i1;
                int total_steps = 1;

                if (nums_sorted[curr] >= dst - maxDiff) {
                    answer.push_back(total_steps + 1);
                    continue;
                }

                // Lift up towards the target threshold value
                for (int j = 17; j >= 0; --j) {
                    int nxt = up_right[j * n + curr];
                    if (nxt != curr && nums_sorted[nxt] < dst - maxDiff) {
                        curr = nxt;
                        total_steps += (1 << j);
                    }
                }

                // Final lookup check from the terminal lifted position
                int nxt = R[curr];
                if (nums_sorted[nxt] >= dst - maxDiff) {
                    total_steps++;
                    answer.push_back(total_steps + 1);
                } else {
                    answer.push_back(-1);
                }
            } else {
                // src > dst (Leftward lookup tracking)
                if (src - dst <= maxDiff) {
                    answer.push_back(1);
                    continue;
                }

                // Greedily grab the smallest possible starting index matching the first jump
                auto it = lower_bound(nums_sorted.begin(), nums_sorted.end(), src - maxDiff);
                int i1 = distance(nums_sorted.begin(), it);

                int curr = i1;
                int total_steps = 1;

                if (nums_sorted[curr] <= dst + maxDiff) {
                    answer.push_back(total_steps + 1);
                    continue;
                }

                // Lift up towards the target threshold value
                for (int j = 17; j >= 0; --j) {
                    int nxt = up_left[j * n + curr];
                    if (nxt != curr && nums_sorted[nxt] > dst + maxDiff) {
                        curr = nxt;
                        total_steps += (1 << j);
                    }
                }

                // Final lookup check from the terminal lifted position
                int nxt = L[curr];
                if (nums_sorted[nxt] <= dst + maxDiff) {
                    total_steps++;
                    answer.push_back(total_steps + 1);
                } else {
                    answer.push_back(-1);
                }
            }
        }

        return answer;
    }
};
