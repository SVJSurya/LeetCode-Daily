class Solution {
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        unordered_map<int, unordered_set<int>> mp;
        for(int st : stones) {
            mp[st] = unordered_set<int>();
        }
        mp[0].insert(1);
        
        for(int i=0;i<n;i++) {
            int cst = stones[i];
            for(int j : mp[cst]) {
                int nps = cst + j;
                if(nps == stones[n-1]) return true;
                if(mp.find(nps) != mp.end()) {
                    if(j-1 > 0) mp[nps].insert(j-1);
                    mp[nps].insert(j);
                    mp[nps].insert(j+1);
                }
            }
        }
        return false;
    }
};