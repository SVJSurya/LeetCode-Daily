class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if(k == nums.size())
            return nums;
        unordered_map<int,int> mp;
        for(int num : nums) mp[num]++;
        auto comp = [&mp](int n, int m){return mp[n]>mp[m];};
        priority_queue<int, vector<int>, decltype(comp)> heap(comp);
        for(pair<int,int> p: mp) {
            heap.push(p.first);
            if(heap.size() > k) heap.pop();
        }
        vector<int> TopFreq(k);
        for(int i=k-1;i>=0;i--) {
            TopFreq[i] = heap.top();
            heap.pop();
        }
        return TopFreq;
    }
};