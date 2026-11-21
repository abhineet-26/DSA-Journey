
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        // Build the original tree
        vector<vector<int>> adj(n);

        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);
        vector<int> prev(n, -1);

        // Step 1: Find new parents using original tree
        // Iterative DFS with enter/exit states

        stack<pair<int, bool>> st;
        st.push({0, false});

        while (!st.empty()) {
            auto [u, exit] = st.top();
            st.pop();

            int c = s[u] - 'a';

            if (!exit) {
                // Save previous ancestor with same character
                prev[u] = last[c];

                // Update parent if matching ancestor exists
                if (last[c] != -1) {
                    newParent[u] = last[c];
                }

                // Current node becomes the latest ancestor
                last[c] = u;

                st.push({u, true});

                // Traverse original children
                for (int v : adj[u]) {
                    st.push({v, false});
                }
            }
            else {
                // Restore ancestor state while backtracking
                last[c] = prev[u];
            }
        }

        // Step 2: Build the modified tree
        vector<vector<int>> tree(n);

        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        // Step 3: Calculate subtree sizes
        vector<int> ans(n, 1);
        vector<int> order;
        
        stack<int> dfs;
        dfs.push(0);

        while (!dfs.empty()) {
            int u = dfs.top();
            dfs.pop();

            order.push_back(u);

            for (int v : tree[u]) {
                dfs.push(v);
            }
        }

        // Process children before parents
        for (int i = n - 1; i > 0; i--) {
            int u = order[i];
            ans[newParent[u]] += ans[u];
        }

        return ans;
    }
};

