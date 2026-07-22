#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// Safe Sparse Table for Range Maximum Queries
class SparseTableMax {
public:
    SparseTableMax() : n(0) {}
    SparseTableMax(const vector<int>& nums) : n(nums.size()) {
        if (n == 0) return;
        int max_log = __lg(n) + 1;
        st.assign(max_log, vector<int>(n));
        for (size_t j = 0; j < n; ++j) st[0][j] = nums[j];
        for (int i = 1; i < max_log; ++i) {
            for (size_t j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r || st.empty() || l < 0 || r >= (int)n) return 0;
        int i = __lg(r - l + 1);
        return max(st[i][l], st[i][r - (1 << i) + 1]);
    }

private:
    size_t n;
    vector<vector<int>> st;
};

// Safe Sparse Table for Range Minimum Queries
class SparseTableMin {
public:
    SparseTableMin() : n(0) {}
    SparseTableMin(const vector<int>& nums) : n(nums.size()) {
        if (n == 0) return;
        int max_log = __lg(n) + 1;
        st.assign(max_log, vector<int>(n));
        for (size_t j = 0; j < n; ++j) st[0][j] = nums[j];
        for (int i = 1; i < max_log; ++i) {
            for (size_t j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r || st.empty() || l < 0 || r >= (int)n) return INT_MAX;
        int i = __lg(r - l + 1);
        return min(st[i][l], st[i][r - (1 << i) + 1]);
    }

private:
    size_t n;
    vector<vector<int>> st;
};

struct Group {
    int start;
    int end;
    int length;
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        
        vector<int> prefixOnes(n + 1, 0);
        vector<Group> zeroGroups;
        vector<int> left_group(n, -1);
        vector<int> right_group(n, -1);
        
        for (int i = 0; i < n; i++) {
            prefixOnes[i + 1] = prefixOnes[i] + (s[i] == '1' ? 1 : 0);
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') {
                    zeroGroups.back().end = i;
                    zeroGroups.back().length++;
                } else {
                    zeroGroups.push_back({i, i, 1});
                }
            }
        }
        
        int total_ones = prefixOnes[n];
        int numZeroGroups = zeroGroups.size();
        
        // Precompute group mapping in O(N) for O(1) range queries
        int curr_idx = 0;
        for (int i = 0; i < n; i++) {
            while (curr_idx < numZeroGroups && zeroGroups[curr_idx].end < i) curr_idx++;
            if (curr_idx < numZeroGroups) left_group[i] = curr_idx;
        }
        
        curr_idx = numZeroGroups - 1;
        for (int i = n - 1; i >= 0; i--) {
            while (curr_idx >= 0 && zeroGroups[curr_idx].start > i) curr_idx--;
            if (curr_idx >= 0) right_group[i] = curr_idx;
        }
        
        // Build sparse tables over zero-groups
        vector<int> z_lengths, o_lengths, merge_lengths;
        for (int i = 0; i < numZeroGroups; i++) {
            z_lengths.push_back(zeroGroups[i].length);
            if (i + 1 < numZeroGroups) {
                int ones_between = zeroGroups[i + 1].start - zeroGroups[i].end - 1;
                o_lengths.push_back(ones_between);
                merge_lengths.push_back(zeroGroups[i].length + zeroGroups[i + 1].length);
            }
        }
        
        SparseTableMax st_z(z_lengths);
        SparseTableMax st_merge(merge_lengths);
        SparseTableMin st_o_min(o_lengths);
        
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            int L = left_group[l];
            int R = right_group[r];
            
            // If fewer than 2 zero-groups exist in the substring, no valid trade is possible.
            // The number of active sections remains the initial total count of '1's in s.
            if (L == -1 || R == -1 || L >= R) {
                ans.push_back(total_ones);
                continue;
            }
            
            // Calculate truncated lengths at the boundaries of the substring
            int z_first = zeroGroups[L].end - max(zeroGroups[L].start, l) + 1;
            int z_last = min(zeroGroups[R].end, r) - zeroGroups[R].start + 1;
            
            // 1. Maximize adjacent merged zero-blocks
            int max_adjacent = 0;
            if (L + 1 == R) {
                max_adjacent = z_first + z_last;
            } else {
                max_adjacent = max(z_first + zeroGroups[L + 1].length, zeroGroups[R - 1].length + z_last);
                max_adjacent = max(max_adjacent, st_merge.query(L + 1, R - 2));
            }
            
            // 2. Maximize (largest zero-block) - (smallest intervening one-block)
            int min_one = st_o_min.query(L, R - 1);
            int max_z = max({z_first, z_last, st_z.query(L + 1, R - 1)});
            int max_separate = max_z - min_one;
            
            int best_gain = max(max_adjacent, max_separate);
            ans.push_back(total_ones + best_gain);
        }
        
        return ans;
    }
};
