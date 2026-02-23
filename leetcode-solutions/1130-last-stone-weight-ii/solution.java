class Solution {
    public int lastStoneWeightII(int[] stones) {
        int sum = 0;
        for (int x : stones) sum += x;
        int target = sum / 2;

        boolean[] dp = new boolean[target + 1];
        dp[0] = true;

        for (int w : stones) {
            for (int s = target; s >= w; s--) {
                dp[s] = dp[s] || dp[s - w];
            }
        }

        int best = 0;
        for (int s = target; s >= 0; s--) {
            if (dp[s]) {
                best = s;
                break;
            }
        }
        return sum - 2 * best;
    }
}

