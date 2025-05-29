class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res = "";
        int n = strs.size();
        sort(strs.begin(), strs.end());

        string s1 = strs[0];
        string s2 = strs[n-1];
        int m = min(s1.size(), s2.size());
        for(int i=0;i<m;i++) {
            if(s1[i] != s2[i]) {
                return res;
            }
            res += s1[i];
        }
        return res;
    }
};