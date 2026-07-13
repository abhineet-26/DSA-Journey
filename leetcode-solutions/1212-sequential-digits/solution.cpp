class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> result;
        
        // Sequential numbers can only have lengths from 2 to 9 digits
        for (int len = 2; len <= 9; ++len) {
            // The starting digit cannot exceed 10 - len (e.g., if len is 3, max start is 7 for 789)
            for (int start = 1; start <= 10 - len; ++start) {
                int num = 0;
                int current_digit = start;
                
                // Construct the sequential number mathematically
                for (int i = 0; i < len; ++i) {
                    num = num * 10 + current_digit;
                    current_digit++;
                }
                
                // Check if it falls within the required range
                if (num >= low && num <= high) {
                    result.push_back(num);
                }
            }
        }
        
        return result;
    }
};
