class Solution {
private:
    int cFT(vector<int> &ls, vector<int> &ld, vector<int> &ws, vector<int> &wd) {
        int mini = INT_MAX;

        for(int i=0;i<ls.size();i++) {
            mini = min(mini, ls[i]+ld[i]);
        }
        int ans = INT_MAX;

        for(int i=0;i<ws.size();i++) {
            ans  = min(ans, max(mini, ws[i])+wd[i]);
        }
        return ans;
    }
public:
    int earliestFinishTime(vector<int>& lST, vector<int>& lD, vector<int>& wST, vector<int>& wD) {
        return min(cFT(lST,lD,wST,wD), cFT(wST,wD,lST,lD));
    }
};