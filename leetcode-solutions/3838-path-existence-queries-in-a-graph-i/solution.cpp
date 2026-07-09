#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Step 1: Precompute the connected components
        vector<int> component(n, 0);
        int current_component_id = 0;
        
        for (int i = 1; i < n; ++i) {
            // If the gap between adjacent elements is too large, it splits the component
            if (nums[i] - nums[i-1] > maxDiff) {
                current_component_id++;
            }
            component[i] = current_component_id;
        }
        
        // Step 2: Answer each query in O(1) time
        vector<bool> answer;
        answer.reserve(queries.size());
        
        for (const auto& query : queries) {
            int u = query[0];
            int v = query[1];
            
            // Nodes u and v are connected if they belong to the same component block
            answer.push_back(component[u] == component[v]);
        }
        
        return answer;
    }
};
