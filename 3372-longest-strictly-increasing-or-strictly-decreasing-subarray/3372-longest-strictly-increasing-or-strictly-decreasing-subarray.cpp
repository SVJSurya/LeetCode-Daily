class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int inc = 1, dec = 1;
        int maxl = 1;

        for (int i = 0; i < nums.size() - 1; i++) {
            if (nums[i + 1] > nums[i]) {
                inc++;
                dec = 1;  
            } else if (nums[i + 1] < nums[i]) {
                dec++;
                inc = 1;  
            } else {
                inc = 1;
                dec = 1;
            }
            maxl = max(maxl, max(inc, dec));
        }
        return maxl;
    }
};