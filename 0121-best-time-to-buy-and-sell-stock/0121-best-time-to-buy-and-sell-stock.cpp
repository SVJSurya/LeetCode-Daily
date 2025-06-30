class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int mini = prices[0];
        int res = 0;
        for(int i=1;i<n;i++) {
            int pr = prices[i] - mini;
            res = max( res, pr);
            mini = min(prices[i], mini);
        }
        return res;
    }
};