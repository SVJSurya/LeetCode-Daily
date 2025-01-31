class Solution {
public:
    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n + 1);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        vector<int> colors(n + 1, 0);
        function<bool(int, int)> bfs = [&](int node, int color) {
            queue<int> q;
            q.push(node);
            colors[node] = color;
            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                for (int neighbor : graph[curr]) {
                    if (colors[neighbor] == 0) {
                        colors[neighbor] = -colors[curr];
                        q.push(neighbor);
                    } else if (colors[neighbor] == colors[curr]) {
                        return false;
                    }
                }
            }
            return true;
        };

        for (int i = 1; i <= n; i++) {
            if (colors[i] == 0 && !bfs(i, 1))
                return -1;
        }

        int maxGroups = 0;
        vector<int> visited(n + 1, 0);
        function<int(int)> maxDepth = [&](int node) {
            queue<int> q;
            unordered_map<int, int> depth;
            q.push(node);
            depth[node] = 1;
            int maxDepth = 1;
            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                for (int neighbor : graph[curr]) {
                    if (depth.find(neighbor) == depth.end()) {
                        depth[neighbor] = depth[curr] + 1;
                        maxDepth = max(maxDepth, depth[neighbor]);
                        q.push(neighbor);
                    }
                }
            }
            return maxDepth;
        };

        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                queue<int> q;
                q.push(i);
                visited[i] = 1;
                vector<int> component;
                while (!q.empty()) {
                    int curr = q.front();
                    q.pop();
                    component.push_back(curr);
                    for (int neighbor : graph[curr]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = 1;
                            q.push(neighbor);
                        }
                    }
                }
                int localMax = 0;
                for (int node : component) {
                    localMax = max(localMax, maxDepth(node));
                }
                maxGroups += localMax;
            }
        }
        return maxGroups;
    }
};