class Solution {
public:
    bool isMatch(string s, string p) {
        int i = 0, j=0;
        int n = s.length() , m = p.length();
        int jstr = -1 , lasti = -1;
        while(i<n){
            if(j<m && s[i] == p[j] || p[j] == '?'){
                i++;
                j++;
            }else if( j < m && p[j] == '*'){
                jstr = j;
                lasti = i;
                j++;
            }else if(jstr != -1){
                lasti++;
                i = lasti;
                j = jstr +1;
            }else{
                return false;
            }
        }
        while(j<m && p[j] == '*'){
            j++;
        }
        return j == m;
    }
};