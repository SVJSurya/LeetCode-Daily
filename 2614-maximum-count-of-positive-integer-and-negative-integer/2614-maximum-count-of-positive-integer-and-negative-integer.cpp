class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int cntn = 0 , cntp = 0;
        for(int num : nums) {
            if(num < 0) cntn++;
            else if(num > 0) cntp++;
        }

        return max(cntp,cntn);
    }
};