class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        
        // DEFENSIVE GUARD: If the array is empty, no subarrays exist.
        if (n == 0) return 0;

        // Since the prefix sum can range from -n to +n, we use an array of size 
        // 2*n + 1 and offset all indices by n to avoid negative indexing.
        vector<int> freq(2 * n + 1, 0);
        
        int current_p = 0;
        freq[current_p + n] = 1; // P[0] = 0 has been seen exactly once initially
        
        long long less_count = 0;
        long long total_subarrays = 0;
        
        for (int i = 0; i < n; i++) {
            int change = (nums[i] == target) ? 1 : -1;
            
            if (change == 1) {
                // current_p is about to increase by 1.
                // The elements less than the new current_p will include everything 
                // less than old current_p, plus everything equal to old current_p.
                less_count += freq[current_p + n];
                current_p += 1;
            } else {
                // current_p is about to decrease by 1.
                // The elements less than the new current_p will be everything 
                // less than old current_p, MINUS everything equal to the new current_p.
                current_p -= 1;
                less_count -= freq[current_p + n];
            }
            
            // Accumulate the number of valid starting positions for the current subarray end
            total_subarrays += less_count;
            
            // Document the current prefix sum in our frequency tracker
            freq[current_p + n]++;
        }
        
        return total_subarrays;
    }
};
