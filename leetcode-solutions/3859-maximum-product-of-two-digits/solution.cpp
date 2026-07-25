#include <vector>
#include <algorithm>

class Solution {
public:
    int maxProduct(int n) {
        std::vector<int> digits;
        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
        
        int max_prod = 0;
        int size = digits.size();
        
        // Compare every pair of distinct indices
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                int prod = digits[i] * digits[j];
                if (prod > max_prod) {
                    max_prod = prod;
                }
            }
        }
        
        return max_prod;
    }
};
