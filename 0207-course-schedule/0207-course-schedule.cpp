class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[numCourses];
        vector<int> indegree(numCourses, 0);
        vector<int> res;

        for(auto x : prerequisites) {
            adj[x[0]].push_back(x[1]);
            indegree[x[1]]++;
        }

        queue<int> q;

        for(int i=0;i<numCourses;i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }

        while(!q.empty()) {
            auto t = q.front();
            res.push_back(t);
            q.pop();

            for(auto x : adj[t]) {
                indegree[x]--;
                if(indegree[x] == 0) {
                    q.push(x);
                }
            }
        }

        return res.size() == numCourses;
    }
};






























class Solution {
private:
    vector<vector<int>> adj;
    vector<int> vis;
public:
    bool canFinish(int numCourses, vector<vector<int>>& prereqs) {
        adj.resize(numCourses);
        vis.resize(numCourses, 0);
        for (auto const& e : prereqs) {
            adj[e[1]].emplace_back(e[0]);
        }
        for (int i = 0; i < numCourses; ++i) {
            if (hasCycle(i)) return false;
        }
        return true;
    }

    bool hasCycle(int cur) {
        if (vis[cur] == 2) return false;
        if (vis[cur] == 1) return true;

        vis[cur] = 1;
        for (auto const nex : adj[cur]) {
            if (hasCycle(nex)) return true;
        }
        vis[cur] = 2;
        return false;
    }
};