class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n+1, vector<int> (2, 0));
        
        for(int i=n-1;i>=0;i--){
            for(int j =0;j<=1;j++){
                if(j==0){
                    dp[i][j] += max(0 + dp[i+1][0], -prices[i] + dp[i+1][1]);
                }
                if(j==1){
                    dp[i][j] += max(0 + dp[i+1][1], prices[i] + dp[i+1][0]);
                }
            }
        }
        return dp[0][0];
    }
};