class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> arr;

        for(int num : nums) {
            auto it = lower_bound(arr.begin(), arr.end(), num);
            if(it == arr.end()) {
                arr.push_back(num);
            }
            else {
                *it = num;
            }
        }
        return arr.size();
    }
};