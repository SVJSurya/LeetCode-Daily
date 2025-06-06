class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        
        long long l = 1 , r = *max_element(candies.begin(),candies.end());
        int res =0;

        while( l<=r ) {
            long long mid = l + (r - l)/2;
            long long cnt = 0;
            for(int st : candies) {
                cnt += st/mid;
            }
            if(cnt >= k) {
                res = mid;
                l = mid+1;
            } else r = mid -1;
        }
        return res;
    }
};