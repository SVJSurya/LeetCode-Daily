class Solution {
public:
    vector<int> constructRectangle(int area) {
        int tar = static_cast<int>(sqrt(area));
        while(area % tar != 0) {
            tar--;
        }
        return {area/tar, tar};
    }
};