class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
       long long rs = 0, tt = 0;
       int n = nums.size();
       for(int i=0,j=0;j<n;j++) {
            tt += nums[j];
            while(i <= j && tt*(j-i+1) >= k) {
                tt -= nums[i];
                i++;
            }
            rs += j -i +1;
       } 
       return rs;
    }
};