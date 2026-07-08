#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        long long MOD = 1e9 + 7;
        int m = s.length();
        
        vector<int> A;
        vector<int> pos;
        A.reserve(m);
        pos.reserve(m);
        
        // Step 1: Collect all non-zero digits and their original positions
        for (int i = 0; i < m; ++i) {
            if (s[i] != '0') {
                A.push_back(s[i] - '0');
                pos.push_back(i);
            }
        }
        
        int n_nz = A.size();
        
        // Step 2: Compute prefix representations for value (P) and sum (S)
        vector<long long> P(n_nz, 0);
        vector<long long> S(n_nz, 0);
        if (n_nz > 0) {
            P[0] = A[0] % MOD;
            S[0] = A[0];
            for (int i = 1; i < n_nz; ++i) {
                P[i] = (P[i - 1] * 10 + A[i]) % MOD;
                S[i] = S[i - 1] + A[i];
            }
        }
        
        // Precompute powers of 10 modulo MOD
        vector<long long> pow10(m + 1, 1);
        for (int i = 1; i <= m; ++i) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }
        
        // Step 3: Map each original string index to the filtered non-zero array
        vector<int> next_nonzero(m, -1);
        vector<int> prev_nonzero(m, -1);
        
        int last = 0;
        for (int i = 0; i < m; ++i) {
            while (last < n_nz && pos[last] < i) {
                last++;
            }
            next_nonzero[i] = (last < n_nz) ? last : -1;
        }
        
        last = n_nz - 1;
        for (int i = m - 1; i >= 0; --i) {
            while (last >= 0 && pos[last] > i) {
                last--;
            }
            prev_nonzero[i] = last;
        }
        
        // Step 4: Answer each query in O(1) time
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];
            
            int L = next_nonzero[l];
            int R = prev_nonzero[r];
            
            if (L == -1 || R == -1 || L > R) {
                ans.push_back(0);
            } else {
                // Extract concatenated number x modulo 10^9 + 7
                long long x_val = P[R];
                if (L > 0) {
                    x_val = (x_val - P[L - 1] * pow10[R - L + 1]) % MOD;
                    if (x_val < 0) x_val += MOD;
                }
                
                // Extract sum of digits
                long long sum_val = S[R];
                if (L > 0) {
                    sum_val -= S[L - 1];
                }
                
                long long query_ans = (x_val * (sum_val % MOD)) % MOD;
                ans.push_back(query_ans);
            }
        }
        
        return ans;
    }
};
