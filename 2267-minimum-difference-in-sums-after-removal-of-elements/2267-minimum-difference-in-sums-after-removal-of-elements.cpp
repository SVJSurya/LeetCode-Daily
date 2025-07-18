class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int n = nums.size() / 3;
        int sz = nums.size();

        // Left min heap: get n smallest sum from first i
        priority_queue<int> maxHeap;
        vector<long long> left(n * 3, 0);
        long long leftSum = 0;

        for (int i = 0; i < 2 * n; ++i) {
            maxHeap.push(nums[i]);
            leftSum += nums[i];
            if (maxHeap.size() > n) {
                leftSum -= maxHeap.top();
                maxHeap.pop();
            }
            if (maxHeap.size() == n) {
                left[i] = leftSum;
            }
        }

        // Right max heap: get n largest sum from last i
        priority_queue<int, vector<int>, greater<int>> minHeap;
        vector<long long> right(n * 3 + 1, 0);
        long long rightSum = 0;

        for (int i = sz - 1; i >= n; --i) {
            minHeap.push(nums[i]);
            rightSum += nums[i];
            if (minHeap.size() > n) {
                rightSum -= minHeap.top();
                minHeap.pop();
            }
            if (minHeap.size() == n) {
                right[i] = rightSum;
            }
        }

        long long res = LLONG_MAX;
        for (int i = n - 1; i < 2 * n; ++i) {
            res = min(res, left[i] - right[i + 1]);
        }

        return res;
    }
};
