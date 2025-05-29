class Solution {
public:
    string reverseWords(string s) {
        vector<string> vec;
        string ress = "";
        string a = "";
        for(char c : s) {
            if(c != ' ') {
                a += c;
            } else if(!a.empty()) {
                vec.push_back(a);
                a = "";
            }
        }
        if(!a.empty()) vec.push_back(a);
        for(int i=vec.size()-1;i>=0;i--) {
            ress += vec[i];
            if(i > 0) ress += " ";
        }
        return ress;
    }
};