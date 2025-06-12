class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end(),greater<int>());
        return nums[nums.size()/2];
    }
};
