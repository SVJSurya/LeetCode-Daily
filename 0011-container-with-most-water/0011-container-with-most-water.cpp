class Solution {
public:
    int maxArea(vector<int>& height) {
        int left =0 ,right = height.size()-1;
        int m_area = 0;

        while(left < right) {
            int h = min(height[left] , height[right]);
            int w = right - left;
            int area = w*h;
            m_area = max(m_area,area);

            if(height[left] > height[right]) {
                right--;
            }else {
                left++;
            }
        }
        return m_area;
    }
};