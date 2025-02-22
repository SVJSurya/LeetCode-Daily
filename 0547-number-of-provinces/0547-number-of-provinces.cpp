class Solution {
private:
    void dfs(vector<vector<int>> &isConnected, vector<int> &visited,int i) {
        visited[i] = 1;
        for(int j = 0; j < isConnected.size(); j++) {
            if(isConnected[i][j] == 1 && visited[j] == 0) {
                dfs(isConnected,visited,j);
            }
        }
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size(), cnt = 0;
        vector<int> visited(n);

        for(int i = 0; i < n; i++) {
            if(visited[i] == 0) {
                cnt++;
                dfs(isConnected,visited,i);
            }
        }
        return cnt;
    }
};