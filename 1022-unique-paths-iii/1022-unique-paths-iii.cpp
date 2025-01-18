class Solution {
public:
    int bt(vector<vector<int>>& grid, int sx, int sy, int ex, int ey, int nul) {
        if (sx < 0 || sx >= grid.size() || sy < 0 || sy >= grid[0].size() ||
            grid[sx][sy] == -1)
            return 0;
        
        if(sx == ex && sy == ey) 
            return nul == 0 ? 1:0;

        grid[sx][sy] = -1;
        int path = 0;

        path += bt(grid,sx+1,sy,ex,ey,nul-1);
        path += bt(grid,sx-1,sy,ex,ey,nul-1);
        path += bt(grid,sx,sy+1,ex,ey,nul-1);
        path += bt(grid,sx,sy-1,ex,ey,nul-1);

        grid[sx][sy] = 0;
        return path;
    }
    int uniquePathsIII(vector<vector<int>>& grid) {
        int sx, sy, ex, ey = 0, nul;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    sx = i;
                    sy = j;
                } else if (grid[i][j] == 2) {
                    ex = i;
                    ey = j;
                } else if (grid[i][j] == 0) {
                    nul++;
                }
            }
        }
        return bt(grid, sx, sy, ex, ey, nul + 1);
    }
};