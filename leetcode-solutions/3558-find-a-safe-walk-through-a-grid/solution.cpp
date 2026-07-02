class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        
        // dist[i][j] stores the minimum health points lost to reach cell (i, j)
        vector<vector<int>> dist(m, vector<int>(n, 1e9));
        dist[0][0] = grid[0][0];
        
        deque<pair<int, int>> dq;
        dq.push_front({0, 0});
        
        // Direction vectors for moving Up, Down, Left, and Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!dq.empty()) {
            auto [r, c] = dq.front();
            dq.pop_front();
            
            // Explore all 4 neighbors
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // Ensure the neighbor is within bounds
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int weight = grid[nr][nc];
                    
                    // Relaxation step
                    if (dist[r][c] + weight < dist[nr][nc]) {
                        dist[nr][nc] = dist[r][c] + weight;
                        
                        // 0-1 BFS optimization based on edge weight
                        if (weight == 0) {
                            dq.push_front({nr, nc});
                        } else {
                            dq.push_back({nr, nc});
                        }
                    }
                }
            }
        }
        
        // Walk is safe if remaining health (health - min_lost) >= 1
        return dist[m - 1][n - 1] < health;
    }
};
