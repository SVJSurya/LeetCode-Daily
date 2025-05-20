class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        unordered_map<int, vector<int>> mp;
        mp[0] = {1, 3};
        mp[1] = {0, 2, 4};
        mp[2] = {1, 5};
        mp[3] = {0, 4};
        mp[4] = {1, 3, 5};
        mp[5] = {4, 2};

        string puz = "";
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                puz += to_string(board[i][j]);
            }
        }
        unordered_set<string> seen;
        queue<pair<string, int>> q;
        q.push({puz, 0});
        seen.insert(puz);

        while (!q.empty()) {
            string s = q.front().first;
            int cnt = q.front().second;
            q.pop();

            if (s == "123450") return cnt;

            int pos = s.find('0');

            for (int a : mp[pos]) {
                swap(s[pos], s[a]);
                if (seen.find(s) == seen.end()) {
                    q.push({s, cnt + 1});
                    seen.insert(s);
                }
                swap(s[pos], s[a]);
            }
        }

        return -1;
    }
};