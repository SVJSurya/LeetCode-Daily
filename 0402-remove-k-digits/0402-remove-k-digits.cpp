class Solution {
public:
    string removeKdigits(string num, int k) {
        string ans;
        stack<char> st;

        for(char ch : num) {
            while(!st.empty() && st.top() > ch && k>0 ) {
                st.pop();
                k--;
                if( k == 0) break;
            }
            st.push(ch);
        }

        while(!st.empty() && k) {
            st.pop();
            k--;
        }

        while(!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

        while(ans.size() > 0 && ans.back() == '0') {
            ans.pop_back();
        }

        reverse(ans.begin(),ans.end());
        return ans == "" ? "0" : ans ;
    }
};