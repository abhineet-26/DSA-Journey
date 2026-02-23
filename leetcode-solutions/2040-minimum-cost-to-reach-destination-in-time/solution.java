import java.util.*;

class Solution {
    public int minCost(int maxTime, int[][] edges, int[] passingFees) {
        int n = passingFees.length;
        List<int[]>[] graph = new List[n];
        for (int i = 0; i < n; i++) graph[i] = new ArrayList<>();

        for (int[] e : edges) {
            graph[e[0]].add(new int[]{e[1], e[2]});
            graph[e[1]].add(new int[]{e[0], e[2]});
        }

        int[][] dist = new int[maxTime + 1][n];
        for (int i = 0; i <= maxTime; i++) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
        }
        dist[0][0] = passingFees[0];

        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        pq.offer(new int[]{passingFees[0], 0, 0}); // cost, time, node

        while (!pq.isEmpty()) {
            int[] cur = pq.poll();
            int cost = cur[0], time = cur[1], node = cur[2];

            if (time > maxTime || cost > dist[time][node]) continue;

            for (int[] nei : graph[node]) {
                int neiNode = nei[0], weight = nei[1];
                int newTime = time + weight;
                if (newTime <= maxTime) {
                    int newCost = cost + passingFees[neiNode];
                    if (newCost < dist[newTime][neiNode]) {
                        dist[newTime][neiNode] = newCost;
                        pq.offer(new int[]{newCost, newTime, neiNode});
                    }
                }
            }
        }

        int ans = Integer.MAX_VALUE;
        for (int t = 0; t <= maxTime; t++) {
            ans = Math.min(ans, dist[t][n - 1]);
        }
        return ans == Integer.MAX_VALUE ? -1 : ans;
    }
}

