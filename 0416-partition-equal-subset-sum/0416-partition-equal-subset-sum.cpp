class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int t = accumulate(nums.begin(), nums.end(),0);
        if(t % 2 != 0) return false;

        int target = t/2;
        vector<bool> dp(t+1,0);
        dp[0] = true;

        for (int num : nums) {
            for (int j = target; j >= num; --j) {
                dp[j] = dp[j] || dp[j - num];
            }
        }

        return dp[target];
    }
};