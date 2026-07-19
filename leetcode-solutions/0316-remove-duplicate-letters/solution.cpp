#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        // Map to store the last index of each character
        vector<int> last_occurrence(26, 0);
        for (int i = 0; i < s.length(); ++i) {
            last_occurrence[s[i] - 'a'] = i;
        }

        // Tracks characters currently in the result stack
        vector<bool> in_result(26, false);
        string result = "";

        for (int i = 0; i < s.length(); ++i) {
            char current_char = s[i];
            
            // If already included in our result stack, skip it
            if (in_result[current_char - 'a']) continue;

            // While the stack is not empty, the current char is smaller than the 
            // character at the top, AND the top char appears later in the string:
            // remove the top char (we can add it later)
            while (!result.empty() && current_char < result.back() && i < last_occurrence[result.back() - 'a']) {
                in_result[result.back() - 'a'] = false;
                result.pop_back();
            }

            // Add the current character and mark as included
            result.push_back(current_char);
            in_result[current_char - 'a'] = true;
        }

        return result;
    }
};
