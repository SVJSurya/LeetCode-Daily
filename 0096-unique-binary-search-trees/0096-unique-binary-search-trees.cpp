class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 1;

        for(int i=1;i<=n;i++) {
            for(int j=1;j<=i;j++) {
                int l = j-1;
                int r = i-j;
                dp[i] += dp[l]*dp[r];
            }
        } 
        return dp[n];
    }
};