class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> merged;
        if(intervals.empty()) return merged;
        sort(intervals.begin(), intervals.end());
        pair<int, int> p = {intervals[0][0], intervals[0][1]};

        for(auto &it : intervals) {
            int st = it[0] , end = it[1];
            if(st <= p.second) {
                p.second = max(end, p.second);
            } else {
                merged.push_back({p.first, p.second});
                p = {st, end};
            }
        }
        merged.push_back({p.first, p.second});
        return merged;
    }
};