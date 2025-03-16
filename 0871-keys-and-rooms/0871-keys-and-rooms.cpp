class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<int> visited(n,0);

        stack<int> st;
        visited[0] = 1;

        for(auto i : rooms[0]) {
            st.push(i);
        }

        while(!st.empty()) {
            int key = st.top();
            st.pop();
            if(visited[key]) continue;
            for(auto i : rooms[key]) {
                st.push(i);
            }
            visited[key] = 1;
        }

        for(int i=0;i<n;i++) {
            if(visited[i] == 0) return false;
        }
        return true;
    }
};