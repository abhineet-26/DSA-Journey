class Solution {
    public int shortestPath(int[][] grid, int k) {
        int m = grid.length, n = grid[0].length;
        int[][] dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        Queue<int[]> q = new LinkedList<>();
        boolean[][][] vis = new boolean[m][n][k + 1];
        q.offer(new int[]{0, 0, k}); // r, c, k
        vis[0][0][k] = true;

        int steps = 0;
        while (!q.isEmpty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                int[] cur = q.poll();
                int r = cur[0], c = cur[1], rem = cur[2];

                if (r == m - 1 && c == n - 1) return steps;

                for (int[] d : dirs) {
                    int nr = r + d[0], nc = c + d[1];
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                        int obst = grid[nr][nc];
                        if (obst == 0 || rem > 0) {
                            int newRem = rem - (obst == 1 ? 1 : 0);
                            if (!vis[nr][nc][newRem]) {
                                vis[nr][nc][newRem] = true;
                                q.offer(new int[]{nr, nc, newRem});
                            }
                        }
                    }
                }
            }
            steps++;
        }
        return -1;
    }
}

