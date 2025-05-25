class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        unordered_map<string, int> mp;

        for(auto word : words) {
            mp[word]++;
        }

        int cnt = 0, isPalin = 0;
        for(auto& [word, freq] : mp) {
            string s = word;
            reverse(s.begin(), s.end());
            if( word == s) {
                cnt += (freq/2)*4;
                if(freq % 2) isPalin = 1;
            } else if( word < s && mp.count(s)) {
                cnt += min(freq, mp[s])*4;
            }
        }
        return cnt + isPalin * 2;
    }
};