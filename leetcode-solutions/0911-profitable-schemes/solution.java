class Solution {
    private static final int MOD = 1_000_000_007;

    public int profitableSchemes(int n, int minProfit, int[] group, int[] profit) {
        int m = group.length;
        int[][] dp = new int[n + 1][minProfit + 1];
        dp[0][0] = 1;

        for (int idx = 0; idx < m; idx++) {
            int g = group[idx];
            int p = profit[idx];

            for (int people = n; people >= g; people--) {
                for (int prof = minProfit; prof >= 0; prof--) {
                    int newProfit = Math.min(minProfit, prof + p);
                    dp[people][newProfit] =
                        (dp[people][newProfit] + dp[people - g][prof]) % MOD;
                }
            }
        }

        int ans = 0;
        for (int people = 0; people <= n; people++) {
            ans = (ans + dp[people][minProfit]) % MOD;
        }
        return ans;
    }
}

