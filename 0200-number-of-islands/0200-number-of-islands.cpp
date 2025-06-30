class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int islands = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        vector<pair<int, int>> directions = {{0,1},{1,0},{0,-1},{-1,0}};
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    islands++;
                    q.push({i, j});
                    visited[i][j] = true;
                    while (!q.empty()) {
                        auto [x, y] = q.front(); q.pop();
                        for (auto [dx, dy] : directions) {
                            int nx = x + dx, ny = y + dy;
                            if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                                grid[nx][ny] == '1' && !visited[nx][ny]) {
                                q.push({nx, ny});
                                visited[nx][ny] = true;
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }
};