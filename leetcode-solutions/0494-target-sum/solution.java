class Solution {
    public int findTargetSumWays(int[] nums, int target) {
        int sum = 0;
        for (int x : nums) sum += x;
        if (sum < Math.abs(target)) return 0;
        if (((sum + target) & 1) == 1) return 0;
        int S = (sum + target) / 2;

        int[] dp = new int[S + 1];
        dp[0] = 1;
        for (int num : nums) {
            for (int s = S; s >= num; s--) {
                dp[s] += dp[s - num];
            }
        }
        return dp[S];
    }
}

