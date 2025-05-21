class Solution {
public:
    int nextGreaterElement(int n) {
        string s = to_string(n);
        if(!next_permutation(s.begin(),s.end())) {
            return -1;
        }

        long long s1 = stoll(s);
        if( s1 > INT_MAX) return -1;
        else return s1;
    }
};