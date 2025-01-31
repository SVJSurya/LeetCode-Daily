class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size(), res = 0, index = 2;
        unordered_map<int, int> area;
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        function<int(int, int, int)> dfs = [&](int r, int c, int idx) {
            if (r < 0 || c < 0 || r >= n || c >= n || grid[r][c] != 1)
                return 0;
            grid[r][c] = idx;
            int size = 1;
            for (auto& d : directions)
                size += dfs(r + d[0], c + d[1], idx);
            return size;
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    area[index] = dfs(i, j, index);
                    res = max(res, area[index++]);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    unordered_set<int> seen;
                    int newSize = 1;
                    for (auto& d : directions) {
                        int ni = i + d[0], nj = j + d[1];
                        if (ni >= 0 && nj >= 0 && ni < n && nj < n &&
                            grid[ni][nj] > 1 &&
                            seen.find(grid[ni][nj]) == seen.end()) {
                            seen.insert(grid[ni][nj]);
                            newSize += area[grid[ni][nj]];
                        }
                    }
                    res = max(res, newSize);
                }
            }
        }
        return res;
    }
};