class Solution {
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> res;
        for(auto& query : queries) {
            int k = query[0];
            int trim = query[1];

            vector<pair<string,int>> tr;
            for(int i=0;i<n;i++) {
                string trimmed = nums[i].substr(nums[i].size() - trim);
                tr.emplace_back(trimmed,i);
            }

            sort(tr.begin(),tr.end());

            res.push_back(tr[k-1].second);
        }
        return res;
    }
};