class Solution {
public:
    bool rotateString(string s, string goal) {
        if(s.length() != goal.length()) return false;
        bool res = true;
        int n = s.size();
        for(int i=0;i<n;i++) {
            bool f = false;
            for(int i=0;i<n;i++) {
                if(goal[i%n] == s[i]) {
                    f = true;
                }
                if(f) break;
            }
            res = res & !f;
        }
        return res;
    }
};