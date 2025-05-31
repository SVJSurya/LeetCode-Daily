class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mp;
        for(auto ch : s) {
            mp[ch]++;
        }

        priority_queue<pair<int, char>> pq;

        for(auto &it : mp) {
            pq.push({it.second, it.first});
        }

        string res = "";
        while(!pq.empty()) {
            auto [f, ch] = pq.top();
            pq.pop();
            res.append(f, ch);
        }

        return res;
    }
};