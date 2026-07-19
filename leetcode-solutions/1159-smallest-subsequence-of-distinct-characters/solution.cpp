#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string smallestSubsequence(string s) {
        // Map to store the last index of each character
        vector<int> last_occurrence(26, 0);
        for (int i = 0; i < s.length(); ++i) {
            last_occurrence[s[i] - 'a'] = i;
        }

        // To keep track of characters already in our result
        vector<bool> in_result(26, false);
        string result = "";

        for (int i = 0; i < s.length(); ++i) {
            char current_char = s[i];
            
            // If already included, skip
            if (in_result[current_char - 'a']) continue;

            // While the current character is smaller than the back of our result
            // AND the character at the back appears later in the string:
            // remove the back character because we can add it later
            while (!result.empty() && current_char < result.back() && i < last_occurrence[result.back() - 'a']) {
                in_result[result.back() - 'a'] = false;
                result.pop_back();
            }

            // Add the current character to result
            result.push_back(current_char);
            in_result[current_char - 'a'] = true;
        }

        return result;
    }
};
