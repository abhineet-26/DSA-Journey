#include <vector>
#include <algorithm>
#include <numeric> // For std::gcd

class Solution {
public:
    int findGCD(std::vector<int>& nums) {
        // Use std::minmax_element to find both min and max in a single pass
        auto [min_it, max_it] = std::minmax_element(nums.begin(), nums.end());
        
        // Return the greatest common divisor of the two values
        // std::gcd is available in <numeric> since C++17
        return std::gcd(*min_it, *max_it);
    }
};
