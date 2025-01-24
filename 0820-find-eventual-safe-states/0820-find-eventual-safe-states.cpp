class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> v1(n);
        vector<vector<int>> adj(n);
        for(int i=0;i<n;i++) {
            for(auto node : graph[i]) {
                adj[node].push_back(i);
                v1[i]++;
            }
        }

        queue<int> q;

        for(int i=0;i<n;i++) {
            if(v1[i] == 0) {
                q.push(i);
            }
        }

        vector<bool> safe(n);
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            safe[node] = true;

            for(auto & neighbour : adj[node] ) {
                v1[neighbour]--;
                if(v1[neighbour] == 0) {
                    q.push(neighbour);
                }
            }
        }

        vector<int> safenode;
        for(int i=0;i<n;i++) {
            if(safe[i]) {
                safenode.push_back(i);
            }
        }
        return safenode;
    }
};