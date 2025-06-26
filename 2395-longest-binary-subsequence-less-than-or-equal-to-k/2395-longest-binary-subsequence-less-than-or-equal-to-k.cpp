#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubsequence(string s, int k) {
        int sm = 0;
        int cnt = 0;
        int bits = (int)(log(k)/log(2)) + 1;

        for(int i=0;i<s.size();i++) {
            char ch = s[s.size() - i - 1];
            if(ch == '1') {
                if(i < bits && sm + (1 << i) <= k) {
                    sm += 1 << i;
                    cnt++;
                }
            } else {
                cnt++;
            }
        }
        return cnt;
    }
};