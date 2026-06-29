class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int count = 0;
        
        // Check each pattern to see if it is a substring of word
        for (const string& p : patterns) {
            if (word.find(p) != string::npos) {
                count++;
            }
        }
        
        return count;
    }
};
