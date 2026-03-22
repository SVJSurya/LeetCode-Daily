class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();
        int num_masks = 1 << n;

        unordered_map<string,int> skill_to_id;
        for(int i=0;i<n;i++) skill_to_id[req_skills[i]] = i;

        vector<vector<int>> dp(num_masks);

        for(int i=0;i<people.size();i++) {
            int person_skill_mask = 0;
            for(const string& s:people[i]) {
                if(skill_to_id.count(s)) person_skill_mask |= (1 << skill_to_id[s]);
            }
            for(int mask = 0;mask < num_masks;mask++) {
                if(mask > 0 && dp[mask].empty()) continue;
                int new_mask = mask | person_skill_mask;

                if(new_mask != mask && (dp[new_mask].empty() || dp[new_mask].size() > dp[mask].size() + 1)) {
                    dp[new_mask] = dp[mask];
                    dp[new_mask].push_back(i);
                }
            }
        }
        return dp[num_masks  -1];
    }
};