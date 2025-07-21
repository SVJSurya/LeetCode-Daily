class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> mp;
        mp[0] = 1;
        int t =0, cnt = 0;

        for(int n : nums) {
            t += n;
            if(mp.find(t - k) != mp.end()) {
                cnt += mp[t- k];
            }
            mp[t]++;
        }
        return cnt;
    }
};