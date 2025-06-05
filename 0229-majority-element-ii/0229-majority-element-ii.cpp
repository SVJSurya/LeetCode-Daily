class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        int c1 =0 , c2 =0 ;
        int e1 = INT_MIN, e2 = INT_MIN;

        for(int m : nums) {
            if(m == e1) c1++;
            else if(m == e2) c2++;
            else if(c1 == 0) {
                e1 = m;
                c1 = 1;
            }
            else if(c2 == 0) {
                e2 = m;
                c2 = 1;
            }
            else {
                c1--;
                c2--;
            }
        }

        c1 = 0;
        c2 = 0;

        for(int m : nums) {
            if(m == e1) c1++;
            else if(m == e2) c2++;
        }
        vector<int>res;
        if(c1 > n/3) res.push_back(e1);
        if(c2 > n/3) res.push_back(e2);

        return res;
    }
};