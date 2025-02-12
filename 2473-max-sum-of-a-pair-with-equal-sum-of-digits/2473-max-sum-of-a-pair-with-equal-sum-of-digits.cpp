class Solution {
private:
    int dig_sum(int n) {
        int ans = 0;
        while(n){
            int d = n%10;
            ans += d;
            n /= 10;
        }
        return ans;
    }
public:
    int maximumSum(vector<int>& nums) {
        int ans = -1;
        unordered_map<int,vector<int>> mp;

        for(int num : nums) {
            mp[dig_sum(num)].push_back(num);
        } 

        for(auto &[key,vec] : mp) {
            if(vec.size() > 1) {
                sort(vec.rbegin(),vec.rend());
                ans = max(vec[0]+vec[1],ans);
            }
        }
        return ans;
    }
};