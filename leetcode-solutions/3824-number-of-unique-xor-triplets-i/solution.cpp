#include <vector>
#include <bit>

using namespace std;

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) {
            return n;
        }
        // Find the bit length of n: the largest power of 2 less than or equal to n, 
        // yielding the mask size 1 << bit_length(n).
        int bit_len = std::bit_width((unsigned int)n);
        return 1 << bit_len;
    }
};
