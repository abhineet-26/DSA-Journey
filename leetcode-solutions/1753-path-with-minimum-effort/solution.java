import java.util.*;

class Solution {
    public int minimumEffortPath(int[][] heights) {
        int m = heights.length, n = heights[0].length;
        int[][] dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        int[][] dist = new int[m][n];
        for (int i = 0; i < m; i++) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
        }
        dist[0][0] = 0;

        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[2] - b[2]);
        pq.offer(new int[]{0, 0, 0}); // r, c, effort

        while (!pq.isEmpty()) {
            int[] cur = pq.poll();
            int r = cur[0], c = cur[1], eff = cur[2];

            if (eff > dist[r][c]) continue;
            if (r == m - 1 && c == n - 1) return eff;

            for (int[] d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int newEff = Math.max(eff, Math.abs(heights[nr][nc] - heights[r][c]));
                    if (newEff < dist[nr][nc]) {
                        dist[nr][nc] = newEff;
                        pq.offer(new int[]{nr, nc, newEff});
                    }
                }
            }
        }
        return -1;
    }
}

