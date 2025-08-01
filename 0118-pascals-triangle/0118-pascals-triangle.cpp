class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        res.push_back({1});

        for(int i=1;i<numRows;i++) {
            vector<int> r;
            vector<int>& pr = res[i-1];
            r.push_back(1);

            for(int j=1;j<i;j++) {
                r.push_back(pr[j-1] + pr[j]);
            } 
            r.push_back(1);
            res.push_back(r);
        }
        return res;
    }
};