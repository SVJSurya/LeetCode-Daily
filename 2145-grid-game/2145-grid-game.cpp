class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        long long f_sum = 0 , s_sum = 0;
        long long pts = LLONG_MAX;

        int n = grid[0].size();

        for(int i=0;i<n;i++) {
            f_sum += grid[0][i]; 
        }

        for(int i=0;i<n;i++) {
            f_sum -= grid[0][i];
            pts = min(pts,max(f_sum,s_sum));
            s_sum += grid[1][i];
        }
        return pts;
    }
};