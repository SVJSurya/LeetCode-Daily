class Solution {
public:
    string smallestNumber(string pattern) {
        string res;
        stack<int> st;

        for(int i =0;i<=pattern.size();i++) {
            st.push(i+1);

            if(i == pattern.size() || pattern[i] == 'I') {
                while(!st.empty()) {
                    res += to_string(st.top());
                    st.pop();
                }
            }
        }
        return res;
    }
};