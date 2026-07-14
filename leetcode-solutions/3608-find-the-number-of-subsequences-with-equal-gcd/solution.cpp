#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        int n = nums.size();
        int M = 0;
        for (int x : nums) {
            M = max(M, x);
        }
        
        // Precompute the GCD values to optimize inner loop speed
        vector<vector<int>> gcd_table(M + 1, vector<int>(M + 1, 0));
        for (int i = 0; i <= M; ++i) {
            for (int j = 0; j <= M; ++j) {
                if (i == 0) gcd_table[i][j] = j;
                else if (j == 0) gcd_table[i][j] = i;
                else std::gcd(i, j); // Standard C++ std::gcd
                gcd_table[i][j] = std::gcd(i, j);
            }
        }
        
        const int MOD = 1e9 + 7;
        vector<vector<int>> dp(M + 1, vector<int>(M + 1, 0));
        dp[0][0] = 1; // Base case: both subsequences are empty
        
        for (int x : nums) {
            vector<vector<int>> next_dp = dp; // Option 1: skip the element x
            
            for (int g1 = 0; g1 <= M; ++g1) {
                for (int g2 = 0; g2 <= M; ++g2) {
                    if (dp[g1][g2] == 0) continue;
                    
                    int val = dp[g1][g2];
                    
                    // Option 2: Add to the first subsequence
                    int ng1 = gcd_table[g1][x];
                    next_dp[ng1][g2] = (next_dp[ng1][g2] + val) % MOD;
                    
                    // Option 3: Add to the second subsequence
                    int ng2 = gcd_table[g2][x];
                    next_dp[g1][ng2] = (next_dp[g1][ng2] + val) % MOD;
                }
            }
            dp = move(next_dp);
        }
        
        long long ans = 0;
        // Sum up all valid non-empty matching GCDs
        for (int g = 1; g <= M; ++g) {
            ans = (ans + dp[g][g]) % MOD;
        }
        
        return ans;
    }
};
