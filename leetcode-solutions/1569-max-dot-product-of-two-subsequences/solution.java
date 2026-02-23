class Solution {
    public int maxDotProduct(int[] nums1, int[] nums2) {
        int m = nums1.length, n = nums2.length;
        int[][] dp = new int[m + 1][n + 1];
        int NEG_INF = Integer.MIN_VALUE / 4;

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = NEG_INF;
            }
        }

        for (int i = 1; i <= m; i++) {
            int a = nums1[i - 1];
            for (int j = 1; j <= n; j++) {
                int b = nums2[j - 1];
                int prod = a * b;
                int takeBoth = prod;
                if (dp[i - 1][j - 1] != NEG_INF) {
                    takeBoth = Math.max(takeBoth, dp[i - 1][j - 1] + prod);
                }
                int skip1 = dp[i - 1][j];
                int skip2 = dp[i][j - 1];
                dp[i][j] = Math.max(takeBoth, Math.max(skip1, skip2));
            }
        }
        return dp[m][n];
    }
}

