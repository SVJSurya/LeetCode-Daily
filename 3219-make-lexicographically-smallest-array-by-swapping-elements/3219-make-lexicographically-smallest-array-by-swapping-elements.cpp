class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        vector<int> temp(nums);
        sort(temp.begin(), temp.end());

        int currGroup = 0;
        unordered_map<int, int> numToGroup;
        numToGroup.insert(pair<int, int>(temp[0], currGroup));

        unordered_map<int, list<int>> groupToList;
        groupToList.insert(
            pair<int, list<int>>(currGroup, list<int>(1, temp[0])));

        for (int i = 1; i < nums.size(); i++) {
            if (abs(temp[i] - temp[i - 1]) > limit) {
                currGroup++;
            }
            numToGroup.insert(pair<int, int>(temp[i], currGroup));
            if (groupToList.find(currGroup) == groupToList.end()) {
                groupToList[currGroup] = list<int>();
            }
            groupToList[currGroup].push_back(temp[i]);
        }
        for (int i = 0; i < nums.size(); i++) {
            int num = nums[i];
            int group = numToGroup[num];
            nums[i] = *groupToList[group].begin();
            groupToList[group].pop_front();
        }

        return nums;
    }
};