class Solution {
    vector<int> LPS(const string &s) {
        int n = s.size();
        vector<int> l(n,0);
        int len = 0 ,i =1;
        while(i<len) {
            if(s[i] == s[len]) {
                l[i++] = ++len;
            }
            else {
                if(len != 0) {
                    len = l[len - 1];
                }else {
                    l[i++] = 0;
                }
            }
        }
        return l;
    }
public:
    string removeOccurrences(string s, string part) {
        vector<int> lps = LPS(s);
        string res;
        int i = 0 , j = 0;

        for(char c : s) {
            res.push_back(c);
            if(res.size() >= part.size()) {
                bool m = true;
                for(int k=0;k<=part.size();k++) {
                    if(res[res.size()-part.size()+k] != part[k]) {
                        m = false;
                        break;
                    }
                }
                if(m) {
                    res.resize(res.size()-part.size());
                }
            }
        }
        return res;
    }
};