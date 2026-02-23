import java.util.*;

class Solution {

    private int find(int x, int[] parent) {
        if (parent[x] != x) parent[x] = find(parent[x], parent);
        return parent[x];
    }

    private void union(int x, int y, int[] parent, int[] rank) {
        int rx = find(x, parent), ry = find(y, parent);
        if (rx == ry) return;
        if (rank[rx] < rank[ry]) parent[rx] = ry;
        else if (rank[rx] > rank[ry]) parent[ry] = rx;
        else {
            parent[ry] = rx;
            rank[rx]++;
        }
    }

    public int minCostConnectPoints(int[][] points) {
        int n = points.length;
        List<int[]> edges = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int w = Math.abs(points[i][0] - points[j][0]) +
                        Math.abs(points[i][1] - points[j][1]);
                edges.add(new int[]{i, j, w});
            }
        }

        edges.sort((a, b) -> Integer.compare(a[2], b[2]));

        int[] parent = new int[n];
        int[] rank = new int[n];
        for (int i = 0; i < n; i++) parent[i] = i;

        int cost = 0, used = 0;
        for (int[] e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (find(u, parent) != find(v, parent)) {
                union(u, v, parent, rank);
                cost += w;
                used++;
                if (used == n - 1) break;
            }
        }
        return cost;
    }
}

