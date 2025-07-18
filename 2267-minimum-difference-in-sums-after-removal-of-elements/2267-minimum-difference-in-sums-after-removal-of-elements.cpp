class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int n = nums.size();
        int k = n/3;
        vector<long long> l(n), r(n);
        priority_queue<int> lH;
        priority_queue<int, vector<int>, greater<int>> rH;
        long long ls =0 , rs =0 ,mindiff = LLONG_MAX;

        for(int i=0;i<k;i++) {
            lH.push(nums[i]);
            ls += nums[i];
        }
        l[k-1] = ls;

        for(int i=k;i<n-k;i++) {
            if(!lH.empty() && nums[i] < lH.top()) {
                ls += nums[i] - lH.top();
                lH.pop();
                lH.push(nums[i]);
            }
            l[i] = ls;
        }

        for(int i = n-1;i>= n-k;i--) {
            rH.push(nums[i]);
            rs += nums[i];
        }
        r[n-k] = rs;

        for(int i=n-k-1;i>=k-1;i--) {
            if(!rH.empty() && nums[i] > rH.top()) {
                rs += nums[i] - rH.top();
                rH.pop();
                rH.push(nums[i]);
            }
            r[i] = rs;
        }

        for(int i = k-1;i<n-k;i++) {
            mindiff = min(mindiff, l[i] - r[i+1]);
        }

        return mindiff;
    }
};