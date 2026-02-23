class Solution {
    public String shortestCommonSupersequence(String str1, String str2) {
        int m = str1.length(), n = str2.length();
        int[][] dp = new int[m + 1][n + 1];

        for (int i = 1; i <= m; i++) {
            char a = str1.charAt(i - 1);
            for (int j = 1; j <= n; j++) {
                char b = str2.charAt(j - 1);
                if (a == b) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        StringBuilder sb = new StringBuilder();
        int i = m, j = n;
        while (i > 0 && j > 0) {
            char a = str1.charAt(i - 1);
            char b = str2.charAt(j - 1);
            if (a == b) {
                sb.append(a);
                i--; j--;
            } else if (dp[i - 1][j] >= dp[i][j - 1]) {
                sb.append(a);
                i--;
            } else {
                sb.append(b);
                j--;
            }
        }
        while (i > 0) sb.append(str1.charAt(--i));
        while (j > 0) sb.append(str2.charAt(--j));

        return sb.reverse().toString();
    }
}

