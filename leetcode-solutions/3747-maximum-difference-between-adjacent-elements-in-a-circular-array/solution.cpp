class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int n = nums.size();
        int absdiff = 0;
        for (int i = 0; i < n; i++) {
            int next = (i + 1) % n; 
            int temp = abs(nums[i] - nums[next]);
            if (temp > absdiff) {
                absdiff = temp;
            }
        }
        return absdiff;
    }
};
