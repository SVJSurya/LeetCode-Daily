class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,int> mp;
        vector<int> res;

        for(int m : nums) {
            mp[m]++;
        }

        for(auto& it : mp) {
            if(it.second > n/3) res.push_back(it.first);
        }
        return res;
    }
};