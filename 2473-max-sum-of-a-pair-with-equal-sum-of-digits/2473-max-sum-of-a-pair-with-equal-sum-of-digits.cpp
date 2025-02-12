class Solution {
private:
    int dig_sum(int n) {
        int ans = 0;
        while(n){
            int d = n%10;
            ans += d;
            n /= 10;
        }
        return ans;
    }
public:
    int maximumSum(vector<int>& nums) {
        vector<int> v(100,-1);
        int sum , ans = -1;

        for(int i=0;i<nums.size();i++) {
            sum = dig_sum(nums[i]);
            if(v[sum]!=-1){
                ans = max(ans,v[sum]+nums[i]);
                v[sum] = max(v[sum],nums[i]);
            } else {
                v[sum] = nums[i];
            }            
        }
        return ans;
    }
};