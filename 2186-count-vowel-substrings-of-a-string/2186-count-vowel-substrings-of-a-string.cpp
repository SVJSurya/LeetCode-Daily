class Solution {
public:
    bool isVowel(char c) {
        c = tolower(c);
        return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';
    }
    int countVowelSubstrings(string s) {
        int ans = 0, n = s.size();
    for (int i = 0; i < n; ++i) {
        unordered_set<char> seen;
        for (int j = i; j < n && isVowel(s[j]); ++j) {
            seen.insert(s[j]);
            if (seen.size() == 5)
                ans++;
        }
    }
    return ans;
    }
};