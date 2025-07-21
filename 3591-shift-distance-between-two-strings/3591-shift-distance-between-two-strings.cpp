class Solution {
public:
    long long shiftDistance(string s, string t, vector<int>& nextCost, vector<int>& previousCost) {
        int n = s.length();
        vector<long long> nxt(26,0);
        vector<long long> prv(26,0);

        for(int i=0;i<26;i++) {
            nxt[i] = nextCost[i];
            prv[i] = previousCost[i];
        }

        for(int i=1;i<26;i++) {
            nxt[i] += nxt[i-1];
        }

        for(int i=24;i>=0;i--) {
            prv[i] += prv[i+1];
        }

        long cost = 0;
        for(int i=0;i<n;i++) {
            if(s[i] != t[i]) {
                int st = s[i] - 'a', end = t[i] - 'a';
                if(st < end) {
                    long fw = nxt[end-1] - (st > 0 ? nxt[st-1] : 0);
                    long bw = prv[0] - (st+1 < 26 ? prv[st+1] : 0) + (end == 25 ? 0 : prv[end+1]);
                    cost += min(fw,bw);
                }
                else {
                    long bw = prv[end+1] - (st >= 25 ? 0 : prv[st+1]);
                    long fw = nxt[25] - nxt[st-1] + (end != 0 ? nxt[end-1] : 0);
                    cost += min(fw,bw);
                }
            }
        }
        return cost;
    }
};