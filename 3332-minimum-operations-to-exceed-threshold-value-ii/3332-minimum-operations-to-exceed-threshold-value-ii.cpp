class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        priority_queue<long, vector<long>, greater<long>> mH(nums.begin(),nums.end());
        int cnt = 0;

        while (mH.top() < k) {
            long x = mH.top();
            mH.pop();
            long y = mH.top();
            mH.pop();
            mH.push(min(x, y) * 2 + max(x, y));

            cnt++;
        }
        return cnt;
    }
};