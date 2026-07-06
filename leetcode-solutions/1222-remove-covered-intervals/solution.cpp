class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        // Sort: ascending by start point; if tied, descending by end point
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) {
                return a[1] > b[1];
            }
            return a[0] < b[0];
        });
        
        int remaining_count = 0;
        int max_r = 0;
        
        for (const auto& interval : intervals) {
            int r = interval[1];
            // If the current interval extends beyond the maximum right boundary seen so far
            if (r > max_r) {
                remaining_count++;
                max_r = r; // Update the furthest right boundary
            }
        }
        
        return remaining_count;
    }
};
