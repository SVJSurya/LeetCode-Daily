class Solution {
public:
    string reverseWords(string s) {
       string temp , ans;
        int l = 0 ,r = s.size() - 1;
        while(l <= r){
            char c = s[l];
            if(c != ' '){
                temp += c;
            }else{
                if(!temp.empty()){
                    if(!ans.empty()){
                        ans = temp + " " + ans;
                    }else{
                        ans = temp;
                    }
                    temp = "";
                }
            }
            l++;
        }
        if(!temp.empty()){
            if(!ans.empty()){
                ans = temp + " " + ans;
            }
            else{
                ans = temp;
            } 
        }
        
        return ans;
    }
};