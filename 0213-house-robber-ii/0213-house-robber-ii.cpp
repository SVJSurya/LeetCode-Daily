class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 0)return 0;
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0],nums[1]);
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for(int i=2;i<n;i++) {
            dp[i] = max(dp[i-2]+nums[i], dp[i-1]);
        }
        vector<int> dpn(n);
        dpn[0] = nums[1];
        dpn[1] = max(nums[1], nums[2]);
        for(int i=2;i<n-1;i++) {
            dpn[i] = max(dpn[i-1], dpn[i-2] + nums[i+1]);
        }
        return max(dp[n-2], dpn[n-2]);
    }
};