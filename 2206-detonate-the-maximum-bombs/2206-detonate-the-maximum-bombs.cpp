class Solution {
public:
    int dfs(int node, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        int count = 1; 
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                count += dfs(neighbor, adj, visited);
            }
        }
        return count;
    }

    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();

        vector<vector<int>> adj(n);

        for(int i=0;i<n;i++) {
            int dx = bombs[i][0];
            int dy = bombs[i][1];
            int r = bombs[i][2];

            for(int j=0;j<n;j++) {
                int cnt  = 0;
                if( i == j) continue;

                long long x2 = bombs[j][0], y2 = bombs[j][1];
                long long dxx = dx - x2, dyy = dy - y2;
                long long dist = dxx * dxx + dyy * dyy;

                if(dist<=(long long)r*r){
                    adj[i].push_back(j);
                } 
            }
        }
        int res = 0;
        for (int i = 0; i < n; i++) {
            vector<bool> vis(n, false);
            res = max(res, dfs(i, adj, vis));
        }

        return res;
    }
};

