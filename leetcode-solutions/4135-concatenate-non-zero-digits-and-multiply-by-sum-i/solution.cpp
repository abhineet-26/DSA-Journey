class Solution {
public:
    long long sumAndMultiply(int n) {
        vector<int> digits;
        
        // Extract all non-zero digits from right to left
        while (n > 0) {
            int d = n % 10;
            if (d != 0) {
                digits.push_back(d);
            }
            n /= 10;
        }
        
        long long x = 0;
        long long sum = 0;
        
        // Process digits from left to right (reverse of how they were collected)
        for (int i = (int)digits.size() - 1; i >= 0; --i) {
            x = x * 10 + digits[i];
            sum += digits[i];
        }
        
        return x * sum;
    }
};
