class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> count;
        for (int num : nums) {
            count[num]++;
        }

        // Since nums.length >= 2, we can always choose at least 1 element
        int max_len = 1; 

        // Handle the special case for 1
        if (count.find(1) != count.end()) {
            int c = count[1];
            if (c % 2 == 0) {
                max_len = max(max_len, c - 1);
            } else {
                max_len = max(max_len, c);
            }
        }

        // Process all other numbers as potential starting values
        for (auto& p : count) {
            long long x = p.first;
            if (x == 1) continue;

            long long curr = x;
            int len = 0;
            
            while (true) {
                auto it = count.find(curr);
                int c = (it != count.end()) ? it->second : 0;

                if (c >= 2) {
                    len += 2;
                    long long next_curr = curr * curr;
                    // If next_curr exceeds maximum element constraint, it doesn't exist
                    if (next_curr > 1e9) {
                        len -= 1; // Current element becomes the peak
                        break;
                    }
                    curr = next_curr;
                } else if (c == 1) {
                    len += 1; // This element becomes the peak
                    break;
                } else {
                    len -= 1; // The previous element becomes the peak
                    break;
                }
            }
            max_len = max(max_len, len);
        }

        return max_len;
    }
};
