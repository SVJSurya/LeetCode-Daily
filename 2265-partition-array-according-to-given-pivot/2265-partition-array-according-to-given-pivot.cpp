class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        vector<int> rs(nums.size());
        int left = 0;
        int right = nums.size() - 1;
        for(int i=0 , j= nums.size() -1;i<nums.size();i++,j--) {
            if(nums[i] < pivot) {
                rs[left] = nums[i];
                left++;
            }
            if(nums[j] > pivot) {
                rs[right] = nums[j];
                right--;
            }
        }
        while(left <= right) {
            rs[left] = pivot;
            left++;
        }

        return rs;
    }
};