class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        // max_score[i][j] initialized to -1 (unreachable)
        vector<vector<int>> max_score(n, vector<int>(n, -1));
        // paths[i][j] initialized to 0
        vector<vector<int>> paths(n, vector<int>(n, 0));
        
        const int MOD = 1e9 + 7;
        
        // Base case: Start at 'S' (bottom-right)
        max_score[n-1][n-1] = 0;
        paths[n-1][n-1] = 1;
        
        // Traverse the board from bottom-right to top-left
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                // Skip the starting square as it's already set
                if (i == n - 1 && j == n - 1) continue;
                // Skip obstacles
                if (board[i][j] == 'X') continue;
                
                int best_prev = -1;
                
                // Check Down neighbor
                if (i + 1 < n && max_score[i+1][j] > best_prev) {
                    best_prev = max_score[i+1][j];
                }
                // Check Right neighbor
                if (j + 1 < n && max_score[i][j+1] > best_prev) {
                    best_prev = max_score[i][j+1];
                }
                // Check Down-Right neighbor
                if (i + 1 < n && j + 1 < n && max_score[i+1][j+1] > best_prev) {
                    best_prev = max_score[i+1][j+1];
                }
                
                // If all transitions are unreachable, this cell remains unreachable
                if (best_prev == -1) continue;
                
                // Calculate current cell's value ('E' counts as 0)
                int v = (board[i][j] == 'E') ? 0 : (board[i][j] - '0');
                max_score[i][j] = best_prev + v;
                
                // Sum paths from all neighbors that provide the maximum score
                long long current_paths = 0;
                if (i + 1 < n && max_score[i+1][j] == best_prev) {
                    current_paths = (current_paths + paths[i+1][j]) % MOD;
                }
                if (j + 1 < n && max_score[i][j+1] == best_prev) {
                    current_paths = (current_paths + paths[i][j+1]) % MOD;
                }
                if (i + 1 < n && j + 1 < n && max_score[i+1][j+1] == best_prev) {
                    current_paths = (current_paths + paths[i+1][j+1]) % MOD;
                }
                
                paths[i][j] = current_paths;
            }
        }
        
        // If the destination 'E' (0,0) is unreachable, return [0, 0]
        if (max_score[0][0] == -1) {
            return {0, 0};
        }
        
        return {max_score[0][0], paths[0][0]};
    }
};
