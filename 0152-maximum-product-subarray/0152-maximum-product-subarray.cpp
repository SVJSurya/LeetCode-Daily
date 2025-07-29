class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = INT_MIN;
        int pr = 1;

        for(int i=0;i<nums.size();i++) {
            pr *= nums[i];
            ans = max(pr, ans);
            if(pr==0) pr = 1;
        }
        pr = 1;
        for(int i=nums.size()-1;i>=0;i--) {
            pr *= nums[i];
            ans = max(ans, pr);
            if(pr==0) pr = 1;
        }
        return ans;
    }
};