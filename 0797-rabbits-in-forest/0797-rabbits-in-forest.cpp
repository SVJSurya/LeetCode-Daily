class Solution {
public:
    int numRabbits(vector<int>& answers) {
        unordered_map<int,int> mp;
        for(int num : answers) {
            mp[num]++;
        }
        int cnt = 0;
        for(auto &it : mp) {
            int Gsize = it.first + 1;
            int Gs = (it.second + it.first) / Gsize;
            cnt += Gs * Gsize;
        }
        return cnt;
    }
};