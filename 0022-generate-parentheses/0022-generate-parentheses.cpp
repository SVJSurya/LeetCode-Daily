class Solution {
public:
    void gen(int open, int close, string curr, vector<string>& res) {
        if(open == 0 && close == 0) {
            res.push_back(curr);
            return;
        }

        if(open > 0) {
            gen(open-1, close, curr+"(" , res);
        }

        if(close > open) {
            gen(open, close-1, curr+")" , res);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> res;

        gen(n, n, "" ,res);

        return res;
    }
};