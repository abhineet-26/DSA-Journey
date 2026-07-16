#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> prefixGcd(n);
        long long mx = 0;
        
        // Step 1: Construct the prefixGcd array
        for (int i = 0; i < n; ++i) {
            mx = max(mx, (long long)nums[i]);
            prefixGcd[i] = std::gcd((long long)nums[i], mx);
        }
        
        // Step 2: Sort prefixGcd in non-decreasing order
        sort(prefixGcd.begin(), prefixGcd.end());
        
        long long total_sum = 0;
        int left = 0, right = n - 1;
        
        // Step 3: Form pairs using two pointers from outer ends inward
        while (left < right) {
            total_sum += std::gcd(prefixGcd[left], prefixGcd[right]);
            left++;
            right--;
        }
        
        return total_sum;
    }
};
