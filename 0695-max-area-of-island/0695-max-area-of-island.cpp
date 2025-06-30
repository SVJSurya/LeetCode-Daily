class Solution {
public:
    int dfs( vector<vector<int>>& grid, vector<vector<bool>>& vis, int r, int c) {
        int n = grid.size() , m = grid[0].size();
        if( r < 0 || r >= n || c < 0 || c >= m || vis[r][c] || grid[r][c] == 0) return 0;

        vis[r][c] = true;
        return 1+ dfs(grid, vis, r+1,c) + dfs(grid, vis, r, c+1) + 
        dfs(grid, vis, r-1,c) + dfs(grid, vis, r, c-1);

    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int r = grid.size(), col = grid[0].size();
        vector<vector<bool>> vis(r,vector<bool>(col, false));

        int maxc = 0;
        for(int i=0;i<r;i++) {
            for(int j =0 ;j<col;j++) {
                if(grid[i][j] == 1 && !vis[i][j]) {
                    maxc = max(maxc, dfs(grid, vis, i ,j));
                }
            }
        }
        return maxc;
    }
};