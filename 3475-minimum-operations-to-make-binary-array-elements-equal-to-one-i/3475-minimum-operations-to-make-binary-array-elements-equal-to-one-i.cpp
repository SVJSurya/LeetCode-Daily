class Solution {
public:
    int minOperations(vector<int>& nums) {
        int cnt  = 0;
        for(int i=2;i<nums.size();i++) {
            if(nums[i-2] == 0) {
                cnt++;
                nums[i-2] ^= 1;
                nums[i-1] ^= 1;
                nums[i] ^= 1;
            }
        }

        int s = accumulate(nums.begin(),nums.end(),0);
        if( s == nums.size()) return cnt;
        return -1;
    }
};