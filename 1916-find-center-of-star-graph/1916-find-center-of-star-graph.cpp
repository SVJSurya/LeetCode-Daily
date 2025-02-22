class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        int f1 = edges[0][0];
        int f2 = edges[0][1];
        int s1 = edges[1][0];
        int s2 = edges[1][1];

        return (f1 == s1 || f1 == s2) ? f1 : f2;
    }
};