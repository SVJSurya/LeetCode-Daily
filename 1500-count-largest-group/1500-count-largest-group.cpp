class Solution {
public:
    int dig_sum(int num) {
        int s = 0;
        while(num > 0) {
            int d = num %10;
            s += d;
            num /= 10; 
        }
        return s;
    }
    int countLargestGroup(int n) {
        unordered_map<int,int> mp;
        for(int i=1;i<=n;i++) {
            int sum = dig_sum(i);
            mp[sum]++;
        }
        int max_s = 0;
        for(auto &m : mp) {
            if(m.second > max_s) max_s = m.second;
        }
        int cnt = 0;
        for(auto &m : mp) {
            if(m.second == max_s) cnt++;
        }
        return cnt;
    }
};