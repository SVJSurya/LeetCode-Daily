class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int n = grid.size();
        int totalSum = n * n * (n * n + 1) / 2; 
        vector<int> freq(n * n + 1, 0);
        int repeated, actualSum = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int val = grid[i][j];
                actualSum += val;
                if (++freq[val] == 2) repeated = val;
            }
        }

        return {repeated, totalSum - (actualSum - repeated)};
    }
};