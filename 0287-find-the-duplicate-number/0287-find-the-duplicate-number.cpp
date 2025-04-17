class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_map<int,int> mp;
        int res = 0;
        for(int n : nums) {
            mp[n]++;
            if(mp[n] > 1) res = n;
        }
        return res;
    }
};