class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int cnt = 0;
        for(int num : nums) {
            int l = to_string(num).length();
            if(l%2 == 0 ) cnt++;
        }
        return cnt;
    }
};