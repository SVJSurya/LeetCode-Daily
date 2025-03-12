class Solution {
public:
    int ptr1 = 0 , ptr2 = 0;
    int getmin(vector<int> &n1, vector<int> &n2) {
        if(ptr1 < n1.size() && ptr2 < n2.size()) {
            return n1[ptr1] < n2[ptr2] ? n1[ptr1++] : n2[ptr2++];
        } else if(ptr1 < n1.size()) return n1[ptr1++];
        else if( ptr2 < n2.size()) return n2[ptr2++];
        return -1;
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size() , n = nums2.size();
        if( (m+n)%2 == 0) {
            for(int i=0;i<(m+n)/2-1;i++) {
                int j = getmin(nums1,nums2);
            }
            return (double) (getmin(nums1,nums2) + getmin(nums1,nums2)) /2;
        } else {
            for(int i=0;i<(m+n)/2;i++) {
                int j = getmin(nums1,nums2);
            }
            return getmin(nums1,nums2);
        }
        return -1;
    }
};