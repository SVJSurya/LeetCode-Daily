class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long long cnt = 0, f = -1, min_val = -1, max_val = -1;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] < minK || nums[i] > maxK) f = i;
            if(nums[i] == minK) min_val = i;
            if(nums[i] == maxK) max_val = i;
            long long subarr = min(min_val, max_val) - f;
            if(subarr > 0) cnt += subarr;
        }
        return cnt;
    }
};