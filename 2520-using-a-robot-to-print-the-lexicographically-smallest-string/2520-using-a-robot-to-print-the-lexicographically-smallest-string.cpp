class Solution {
public:
    string robotWithString(string s) {
        unordered_map<char,int> mp;
        for(char c : s) {
            mp[c]++;
        }

        stack<char> st;
        string res;
        char minc = 'a';
        for(char c : s) {
            st.emplace(c);
            mp[c]--;
            while(minc != 'z' && mp[minc] == 0) {
                minc++;
            }
            while(!st.empty() && st.top() <= minc) {
                res.push_back(st.top());
                st.pop();
            }
        } 
        return res;
    }
};