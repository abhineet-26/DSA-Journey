#include <vector>

using namespace std;

class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int offset = n; // Offset to handle negative prefix sums
        vector<int> bit(2 * n + 2, 0); // Fenwick tree container

        // Helper function to update the Fenwick Tree
        auto update = [&](int idx, int val) {
            idx += 1; // Convert to 1-based indexing
            while (idx < bit.size()) {
                bit[idx] += val;
                idx += idx & (-idx);
            }
        };

        // Helper function to query prefix sum frequencies up to a certain value
        auto query = [&](int idx) {
            idx += 1; // Convert to 1-based indexing
            int sum = 0;
            while (idx > 0) {
                sum += bit[idx];
                idx -= idx & (-idx);
            }
            return sum;
        };

        // Base case: Before processing any elements, the initial prefix sum is 0
        update(0 + offset, 1);

        int ans = 0;
        int curr_sum = 0;

        for (int num : nums) {
            // Transform element to +1 or -1
            if (num == target) {
                curr_sum += 1;
            } else {
                curr_sum -= 1;
            }

            // Count all previous prefix sums strictly less than curr_sum
            ans += query(curr_sum - 1 + offset);

            // Add the current prefix sum to the tracker
            update(curr_sum + offset, 1);
        }

        return ans;
    }
};
