class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        long s = 0, maxi = 0, mini = 0;
        for(int i:differences) {
            s += i;
            mini = min(mini,s);
            maxi = max(maxi,s);
        }

        return max(0L, upper - lower - maxi + mini +1);
    }
};