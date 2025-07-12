class Solution {
public:
    void bfs(int r, int c, vector<vector<int>>& vis, vector<vector<int>>& h) {
        int n = h.size();
        int m = h[0].size();

        vis[r][c] = 1;

        queue<pair<int, int>> q;
        q.push({r, c});
        int dirr[] = {0, -1, 0, 1};
        int dirc[] = {-1, 0, 1, 0};

        while (!q.empty()) {
            auto [rr, cc] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nr = rr + dirr[i];
                int nc = cc + dirc[i];
                if (nr >= 0 && nc >= 0 && nr < n && nc < m &&
                    h[nr][nc] >= h[rr][cc] && vis[nr][nc] == 0) {
                    q.push({nr, nc});
                    vis[nr][nc] = 1;
                }
            }
        }
    }
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& h) {
        int n = h.size();
        int m = h[0].size();

        vector<vector<int>> vis1(n, vector<int>(m, 0));
        vector<vector<int>> vis2(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            bfs(i, 0, vis1, h);
            bfs(i, m - 1, vis2, h);
        }
        for (int i = 0; i < m; i++) {
            bfs(0, i, vis1, h);
            bfs(n - 1, i, vis2, h);
        }
        vector<vector<int>> ans;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (vis1[i][j] == 1 && vis2[i][j] == 1) {
                    ans.push_back({i, j});
                }
            }
        }
        return ans;
    }
};