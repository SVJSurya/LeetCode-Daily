class Solution {
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        int n = nums.size();
        unordered_map<int,int> cnt;
        long long res = 0;
        int pre = 0;
        cnt[0] = 1;
        for(int i=0;i<n;i++) {
            pre += nums[i]%modulo == k;
            res += cnt[(pre - k + modulo) % modulo];
            cnt[pre % modulo]++;
        } 
        return res;
    }
};