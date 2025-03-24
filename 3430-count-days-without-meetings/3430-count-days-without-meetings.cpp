class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        int res = 0, last = 0;
        sort(meetings.begin(), meetings.end());

        for(auto & meet : meetings) {
            int st = meet[0] , end = meet[1];
            if( st > last+1) {
                res += st - last - 1;
            }
            last = max(last,end);
        }

        res += days - last;
        return res;
    }
};