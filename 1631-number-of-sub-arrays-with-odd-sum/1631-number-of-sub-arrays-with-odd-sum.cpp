class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        long long oCnt = 0, prefixsum = 0;

        for(int a: arr) {
            prefixsum += a;
            oCnt += prefixsum % 2;
        }
        oCnt += (arr.size() - oCnt) * oCnt;

        return oCnt % 1'000'000'007;
    }
};