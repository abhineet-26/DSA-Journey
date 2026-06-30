class Solution {
public:
    int numberOfSubstrings(string s) {
        int last_a = -1, last_b = -1, last_c = -1;
        int count = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            // Update the last seen position for the current character
            if (s[i] == 'a') last_a = i;
            else if (s[i] == 'b') last_b = i;
            else if (s[i] == 'c') last_c = i;
            
            // If all three characters have been encountered at least once
            if (last_a != -1 && last_b != -1 && last_c != -1) {
                // All substrings starting from index 0 up to min(last_a, last_b, last_c) are valid
                count += min({last_a, last_b, last_c}) + 1;
            }
        }
        
        return count;
    }
};
