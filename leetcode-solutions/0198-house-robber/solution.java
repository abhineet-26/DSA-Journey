class Solution {
    public int rob(int[] nums) {
        int n = nums.length;
        if (n == 1) return nums[0];
        int prev2 = 0;
        int prev1 = nums[0];

        for (int i = 1; i < n; i++) {
            int pick = nums[i] + prev2;
            int skip = prev1;
            int cur = Math.max(pick, skip);
            prev2 = prev1;
            prev1 = cur;
        }
        return prev1;
    }
}

