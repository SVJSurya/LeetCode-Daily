class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();

        vector<vector<long long>> dp(n+1, vector<long long> (2,0));

        dp[n][1] = 0;
        dp[n][0] = INT_MIN;

        for(int idx = n-1;idx >= 0;idx--) {
            for( int e=0;e<=1;e++) {
                long long op = dp[idx+1][e^1] + (nums[idx]^k);
                long long dop = dp[idx+1][e] + nums[idx];

                dp[idx][e] = max(op, dop);
            }
        }
        return dp[0][1];
    }
};