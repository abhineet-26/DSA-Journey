#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        // Step 1: Build the adjacency list containing only online nodes and collect distinct edge costs
        vector<vector<pair<int, int>>> adj(n);
        vector<int> in_degree(n, 0);
        vector<int> distinct_costs;
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];
            // An edge is only usable if both endpoints are online
            if (online[u] && online[v]) {
                adj[u].push_back({v, cost});
                in_degree[v]++;
                distinct_costs.push_back(cost);
            }
        }
        
        // Step 2: Precompute the global topological sort using Kahn's algorithm
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (in_degree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> topo_order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo_order.push_back(u);
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        // Step 3: Sort and remove duplicate costs to prepare for binary search
        sort(distinct_costs.begin(), distinct_costs.end());
        distinct_costs.erase(unique(distinct_costs.begin(), distinct_costs.end()), distinct_costs.end());
        
        if (distinct_costs.empty()) {
            return -1;
        }
        
        // A sufficiently large value for infinity that won't cause long long overflow
        const long long INF = 1e17;
        
        // Lambda helper function to check if a valid path exists with min edge cost >= X
        auto check = [&](int X) -> bool {
            vector<long long> dist(n, INF);
            dist[0] = 0;
            
            for (int u : topo_order) {
                if (dist[u] == INF) continue;
                for (const auto& neighbor : adj[u]) {
                    int v = neighbor.first;
                    int cost = neighbor.second;
                    
                    // Only traverse edges meeting the minimum cost threshold
                    if (cost >= X) {
                        if (dist[u] + cost < dist[v]) {
                            dist[v] = dist[u] + cost;
                        }
                    }
                }
            }
            return dist[n - 1] <= k;
        };
        
        // Step 4: Binary search over the sorted unique edge costs
        int low = 0, high = distinct_costs.size() - 1;
        int ans = -1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(distinct_costs[mid])) {
                ans = distinct_costs[mid];
                low = mid + 1; // Try to find a larger minimum edge cost
            } else {
                high = mid - 1; // Threshold is too high, lower it
            }
        }
        
        return ans;
    }
};
