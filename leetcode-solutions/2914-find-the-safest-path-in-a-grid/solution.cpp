class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // If the start or end cell contains a thief, safeness factor is automatically 0
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return 0;
        }

        // dist[r][c] will store the minimum Manhattan distance to any thief
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int, int>> q;

        // Step 1: Initialize multi-source BFS with all thief positions
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }
            }
        }

        // Directions for moving up, down, left, right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // Populate the minimum distance to a thief for every cell
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Step 2: Dijkstra-like expansion using a Max-Heap to find the safest path
        // Priority queue stores elements as: {safeness_factor, {r, c}}
        priority_queue<pair<int, pair<int, int>>> pq;
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        pq.push({dist[0][0], {0, 0}});
        visited[0][0] = true;

        while (!pq.empty()) {
            auto [sf, cell] = pq.top();
            auto [r, c] = cell;
            pq.pop();

            // If we reached the bottom-right corner, return the maximum safeness factor
            if (r == n - 1 && c == n - 1) {
                return sf;
            }

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    // The safeness of the path to the neighbor is limited by the minimum safeness encountered so far
                    pq.push({min(sf, dist[nr][nc]), {nr, nc}});
                }
            }
        }

        return 0;
    }
};
