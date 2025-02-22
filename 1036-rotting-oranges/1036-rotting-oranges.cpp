class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        int visited[n][m]; // visited array to track approached oranges
        queue<pair<pair<int, int>, int>> q; // DS to store rotten and time stamp

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) { // if rotten
                    q.push({{i, j}, 0}); // pushed to queue (initially at t = 0)
                    visited[i][j] = 2; // marked as visited -> 2
                } else {
                    visited[i][j] = 0; // if not rooten then visited -> 0
                }
            }
        }
        int dirr[] = {-1, 0, 1, 0}; // track of row possibilities
        int dirc[] = {0, 1, 0, -1}; // track of column possibilities
        int tc = 0; 
        while (!q.empty()) {
            int r = q.front().first.first;
            int c = q.front().first.second;
            int t = q.front().second;
            tc = max(tc, t);
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nr = r + dirr[i];
                int nc = c + dirc[i];
                if (nr >= 0 && nc >= 0 && nc < m && nr < n &&
                    visited[nr][nc] != 2 && grid[nr][nc] == 1) {
                    q.push({{nr, nc}, t+1});
                    visited[nr][nc] = 2;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (visited[i][j] != 2 && grid[i][j] == 1)
                    return -1;
            }
        }

        return tc;
    }
};