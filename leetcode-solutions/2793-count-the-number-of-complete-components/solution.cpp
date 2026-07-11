#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        // Step 1: Build the adjacency list
        vector<vector<int>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        vector<bool> visited(n, false);
        int completeComponentsCount = 0;
        
        // Step 2: Iterate through all vertices to find components
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                vector<int> component;
                queue<int> q;
                
                // Start BFS traversal
                q.push(i);
                visited[i] = true;
                
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    component.push_back(u);
                    
                    for (int v : adj[u]) {
                        if (!visited[v]) {
                            visited[v] = true;
                            q.push(v);
                        }
                    }
                }
                
                // Step 3: Verify if the component is complete
                int numVertices = component.size();
                bool isComplete = true;
                
                for (int u : component) {
                    if (adj[u].size() != numVertices - 1) {
                        isComplete = false;
                        break;
                    }
                }
                
                if (isComplete) {
                    completeComponentsCount++;
                }
            }
        }
        
        return completeComponentsCount;
    }
};
