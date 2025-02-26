class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int minps = 0 , maxps = 0;

        int ps = 0;
        for(int num : nums) {
            ps += num;

            minps = min(minps, ps);
            maxps = max(maxps, ps);
        }

        return maxps - minps;
    }
};