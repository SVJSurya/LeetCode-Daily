class Solution {
public:
    int p1 = 0 , p2 = 0;
    int getmin(vector<int> &n1,vector<int> &n2) {
        if(p1 < n1.size() && p2 < n2.size()) {
            return n1[p1] < n2[p2] ? n1[p1++] : n2[p2++]; 
        } else if( p1 < n1.size()) return n1[p1++];
        else if( p2 < n2.size()) return n2[p2++];
        return -1;
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size() , m = nums2.size();

        if( (m+n)%2 == 0) {
            for(int i=0;i<(m+n)/2 - 1;i++) {
                int j = getmin(nums1,nums2);
            }
            return (double) (getmin(nums1,nums2) + getmin(nums1,nums2)) / 2;
        } else {
            for(int i=0;i<(m+n)/2;i++) {
                int j = getmin(nums1,nums2);
            }
            return getmin(nums1,nums2);
        }
        return -1;
    }
};