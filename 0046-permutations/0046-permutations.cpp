class Solution {
public:
    void f(int i, vector<vector<int>> &perm, vector<int> &nums) {
        if(i == nums.size()) {
            perm.push_back(nums);
            return ;
        }
        for(int j=i;j<nums.size();j++) {
            swap(nums[i],nums[j]);
            f(i+1,perm,nums);
            swap(nums[i], nums[j]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> perm;
        f(0,perm,nums);
        return perm;
    }
};