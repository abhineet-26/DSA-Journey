#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int max_val = 0;
        for (int x : nums) max_val = max(max_val, x);
        
        vector<int> count(max_val + 1, 0);
        for (int x : nums) count[x]++;
        
        // Count pairs with GCD as a multiple of g
        vector<long long> gcd_counts(max_val + 1, 0);
        for (int g = 1; g <= max_val; ++g) {
            long long cnt = 0;
            for (int multiple = g; multiple <= max_val; multiple += g) {
                cnt += count[multiple];
            }
            gcd_counts[g] = cnt * (cnt - 1) / 2;
        }
        
        // Inclusion-Exclusion to get count of pairs with GCD exactly g
        for (int g = max_val; g >= 1; --g) {
            for (int multiple = 2 * g; multiple <= max_val; multiple += g) {
                gcd_counts[g] -= gcd_counts[multiple];
            }
        }
        
        // Prefix sum: prefix_gcd[g] is total pairs with GCD <= g
        vector<long long> prefix_gcd(max_val + 1);
        for (int g = 1; g <= max_val; ++g) {
            prefix_gcd[g] = prefix_gcd[g - 1] + gcd_counts[g];
        }
        
        vector<int> result;
        result.reserve(queries.size());
        for (long long q : queries) {
            // Find the first index g where prefix_gcd[g] > q
            // q is 0-indexed, so we want the smallest g where the cumulative count 
            // of pairs is at least q + 1.
            auto it = upper_bound(prefix_gcd.begin() + 1, prefix_gcd.end(), q);
            result.push_back(distance(prefix_gcd.begin(), it));
        }
        
        return result;
    }
};
