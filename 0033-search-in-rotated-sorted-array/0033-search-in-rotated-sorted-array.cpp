class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = n-1;
        while( l <= r ) {
            int m = l + ( r-l )/2;
            int s = nums[0];
            if(nums[m] == target) return m;
            if(nums[l] <= nums[m]) {
                if(nums[l] <= target && target < nums[m]) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            
            else {
                if (nums[m] < target && target <= nums[r]) l = m + 1;
                else r = m - 1;
            }
        }
        return -1;
    }
};