class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        std::unordered_set<std::string> obstacleSet;
        for (const auto& obstacle : obstacles) {
            obstacleSet.insert(std::to_string(obstacle[0]) + "," +
                               std::to_string(obstacle[1]));
        }

        int x = 0, y = 0, direction = 0;
        int maxDistance = 0;
        std::vector<std::vector<int>> directions = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        for (int cmd : commands) {
            if (cmd == -2) {
                direction = (direction + 3) % 4;
            } else if (cmd == -1) {
                direction = (direction + 1) % 4;
            } else {
                for (int i = 0; i < cmd; ++i) {
                    int nextX = x + directions[direction][0];
                    int nextY = y + directions[direction][1];
                    if (obstacleSet.find(std::to_string(nextX) + "," +
                                         std::to_string(nextY)) ==
                        obstacleSet.end()) {
                        x = nextX;
                        y = nextY;
                        maxDistance = std::max(maxDistance, x * x + y * y);
                    } else {
                        break;
                    }
                }
            }
        }
        return maxDistance;
    }
};