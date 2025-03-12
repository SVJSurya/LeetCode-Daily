class Solution {
public:
    string answerString(string word, int numFriends) {
        if(numFriends == 1) return word;
        int n = word.size();
        int len = n - numFriends;
        string str , str2 = "";
        for(int i=0;i<n;i++) {
            str2 = word.substr(i,len+1);
            if(str2 > str) {
                str = str2;
            }
        }
        return str;
    }
};