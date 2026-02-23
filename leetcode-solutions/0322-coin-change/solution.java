class Solution {
    public int coinChange(int[] coins, int amount) {
        int max = amount + 1;
        int[] dp = new int[amount + 1];
        for (int i = 1; i <= amount; i++) dp[i] = max;

        dp[0] = 0;
        for (int coin : coins) {
            for (int a = coin; a <= amount; a++) {
                dp[a] = Math.min(dp[a], dp[a - coin] + 1);
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
}

