class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int maxw = 0;
        int l = 0, r = n-1;
        int minw = INT_MAX; 
        while(l < r) {
            minw  = min(height[l], height[r]);
            maxw = max(maxw, minw*(r-l));
            height[l] < height[r] ? l++ : r--;
        }
        return maxw;
    }
};