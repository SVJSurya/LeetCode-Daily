class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), cnt = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    bool comm = false;
                    for (int k = 0; k < m; k++) {
                        if (k != j && grid[i][k] == 1) {
                            comm = true;
                            break;
                        }
                    }

                    if (comm) {
                        cnt++;
                    } else {
                        for (int l = 0; l < n; l++) {
                            if (l != i && grid[l][j] == 1) {
                                comm = true;
                                break;
                            }
                        }
                        if (comm) {
                            cnt++;
                        }
                    }
                }
            }
        }
        return cnt;
    }
};