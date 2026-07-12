class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        // Handle empty array edge case
        if (arr.empty()) return {};

        // 1. Create a copy of the original array
        vector<int> sorted_arr = arr;

        // 2. Sort the array
        sort(sorted_arr.begin(), sorted_arr.end());

        // 3. Remove all duplicate elements
        sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());

        // 4. Transform each original element into its rank
        vector<int> ranks(arr.size());
        for (int i = 0; i < arr.size(); ++i) {
            // Find the element in the sorted unique array
            auto it = lower_bound(sorted_arr.begin(), sorted_arr.end(), arr[i]);
            // The rank is the 0-based index difference plus 1
            ranks[i] = (it - sorted_arr.begin()) + 1;
        }

        return ranks;
    }
};
