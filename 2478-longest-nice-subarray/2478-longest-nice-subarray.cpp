class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int bits = 0;
        int l = 0, res = 0;

        for(int i=0;i<nums.size();i++) {
            while((bits & nums[i]) != 0) {
                bits ^= nums[l];
                l++;
            }

            bits |= nums[i];
            res = max(res, i - l + 1);
        }
        return res;
    }
};