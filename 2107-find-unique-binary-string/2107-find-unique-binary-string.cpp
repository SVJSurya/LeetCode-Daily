class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        unordered_set<int> integer;

        for(string num : nums) {
            integer.insert(stoi(num, 0, 2));
        }

        int n = nums.size();
        for(int i = 0; i <= n; i++) {
            if( integer.find(i) == integer.end()) {
                string ans = bitset<16>(i).to_string();
                return ans.substr(16 - n);
            }
        }
        return  "";
    }
};