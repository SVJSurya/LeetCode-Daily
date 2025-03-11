class Solution {
public:
    int numberOfSubstrings(string s) {
        int m = s.size();

        vector<int> track = {-1 , -1 , -1};
        int t =0 ;
        for(int i=0;i<m;i++) {
            track[s[i] - 'a'] = i;
            t += min({track[0] , track[1] , track[2]}) + 1;
        }

        return t;
    }
};