import java.util.*;

class Solution {
    public int shortestPathLength(int[][] graph) {
        int n = graph.length;
        Queue<int[]> q = new LinkedList<>();
        boolean[][][] vis = new boolean[n][1 << n][n];

        for (int i = 0; i < n; i++) {
            q.offer(new int[]{i, 1 << i});
            vis[i][1 << i][i] = true;
        }

        int steps = 0;
        while (!q.isEmpty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                int[] cur = q.poll();
                int node = cur[0], mask = cur[1];
                if (mask == (1 << n) - 1) return steps;

                for (int nei : graph[node]) {
                    int newMask = mask | (1 << nei);
                    if (!vis[nei][newMask][nei]) {
                        vis[nei][newMask][nei] = true;
                        q.offer(new int[]{nei, newMask});
                    }
                }
            }
            steps++;
        }
        return -1;
    }
}

