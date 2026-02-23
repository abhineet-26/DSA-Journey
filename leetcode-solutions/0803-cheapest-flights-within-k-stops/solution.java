class Solution {
    public int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {
        int[][] dist = new int[k + 2][n];
        for (int i = 0; i < k + 2; i++) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
        }
        dist[0][src] = 0;

        for (int stops = 1; stops <= k + 1; stops++) {
            for (int[] f : flights) {
                int u = f[0], v = f[1], p = f[2];
                if (dist[stops - 1][u] != Integer.MAX_VALUE) {
                    dist[stops][v] = Math.min(dist[stops][v],
                                              dist[stops - 1][u] + p);
                }
            }
        }

        int ans = Integer.MAX_VALUE;
        for (int stops = 1; stops <= k + 1; stops++) {
            ans = Math.min(ans, dist[stops][dst]);
        }
        return ans == Integer.MAX_VALUE ? -1 : ans;
    }
}

