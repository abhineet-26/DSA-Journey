import java.util.*;

class Solution {
    public double maxProbability(int n, int[][] edges, double[] succProb, int start, int end) {
        if (start == end) return 1.0;

        List<double[]>[] graph = new List[n];
        for (int i = 0; i < n; i++) graph[i] = new ArrayList<>();

        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0], v = edges[i][1];
            double p = succProb[i];
            graph[u].add(new double[]{v, p});
            graph[v].add(new double[]{u, p});
        }

        double[] prob = new double[n];
        Arrays.fill(prob, -1.0);
        prob[start] = 1.0;

        PriorityQueue<double[]> pq = new PriorityQueue<>((a, b) -> Double.compare(b[1], a[1]));
        pq.offer(new double[]{start, 1.0});

        while (!pq.isEmpty()) {
            double[] cur = pq.poll();
            int node = (int) cur[0];
            double p = cur[1];

            if (p < prob[node]) continue;

            for (double[] nei : graph[node]) {
                int neiNode = (int) nei[0];
                double newProb = p * nei[1];
                if (newProb > prob[neiNode]) {
                    prob[neiNode] = newProb;
                    pq.offer(new double[]{neiNode, newProb});
                }
            }
        }
        return prob[end] < 0 ? 0.0 : prob[end];
    }
}

