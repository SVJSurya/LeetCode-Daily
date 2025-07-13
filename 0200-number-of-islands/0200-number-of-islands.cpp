class Solution {
public:

    void dfs(int r, int c, vector<vector<char>> &grid, vector<vector<bool>> &vis) {
        int n = grid.size();
        int m = grid[0].size();
        if(r < 0 || c<0 || r>=n || c >=m || grid[r][c] == '0' || vis[r][c] == true) return;

        vis[r][c] = true;
        dfs(r+1, c, grid, vis);
        dfs(r-1, c, grid, vis);
        dfs(r, c+1, grid, vis);
        dfs(r, c-1, grid, vis);

    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<bool>> vis(n, vector<bool>(m, false));
        int cnt = 0;
        for(int i=0;i<n;i++ ) {
            for(int j=0;j<m;j++) {
                if(grid[i][j] == '1' && !vis[i][j]) {
                    cnt++;
                    dfs(i, j, grid, vis);
                }
            }
        }        
        return cnt;
    }
};