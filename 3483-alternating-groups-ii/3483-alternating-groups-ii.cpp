class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int l  = colors.size();
        int res = 0;

        int altcnt = 1;
        int lcol = colors[0];

        for(int i =1;i<l+k-1;i++) {
            int idx = i%l;
            if(colors[idx] == lcol) {
                altcnt = 1;
                lcol = colors[idx];
                continue;
            }
            altcnt += 1;

            if(altcnt >= k) {
                res++;
            }

            lcol = colors[idx];
        }

        return res;
    }
};