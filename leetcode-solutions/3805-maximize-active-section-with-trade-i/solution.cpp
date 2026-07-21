#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.length();
        int ans = 0;
        int max_gain = 0;
        int prev_zero_len = INT_MIN; // Use INT_MIN to denote no valid preceding zero block yet
        
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            int len = j - i;
            
            if (s[i] == '1') {
                ans += len;
            } else {
                if (prev_zero_len != INT_MIN) {
                    max_gain = max(max_gain, prev_zero_len + len);
                }
                prev_zero_len = len;
            }
            i = j;
        }
        
        return ans + max_gain;
    }
};
