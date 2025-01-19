class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if (heightMap.empty() || heightMap[0].empty())
            return 0;

        int m = heightMap.size();
        int n = heightMap[0].size();
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,          greater<>>minHeap;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            minHeap.emplace(heightMap[i][0], i, 0);
            minHeap.emplace(heightMap[i][n - 1], i, n - 1);
            visited[i][0] = visited[i][n - 1] = true;
        }
        for (int j = 1; j < n - 1; ++j) {
            minHeap.emplace(heightMap[0][j], 0, j);
            minHeap.emplace(heightMap[m - 1][j], m - 1, j);
            visited[0][j] = visited[m - 1][j] = true;
        }
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int waterTrapped = 0;

        while (!minHeap.empty()) {
            auto [height, x, y] = minHeap.top();
            minHeap.pop();

            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && ny >= 0 && nx < m && ny < n &&
                    !visited[nx][ny]) {
                    waterTrapped += max(0, height - heightMap[nx][ny]);
                    minHeap.emplace(max(height, heightMap[nx][ny]), nx, ny);
                    visited[nx][ny] = true;
                }
            }
        }

        return waterTrapped;
    }
};