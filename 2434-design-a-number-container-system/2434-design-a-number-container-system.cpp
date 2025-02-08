class NumberContainers {
public:
    NumberContainers() {}
    
    void change(int index, int number) {
        if(nums1.find(index) != nums1.end()) {
            int prev = nums1[index];
            nums[prev].erase(index);
            if(nums[prev].empty()) {
                nums.erase(prev);
            }
        }
        nums1[index] = number;
        nums[number].insert(index);
    }
    
    int find(int number) {
        if(nums.find(number) != nums.end()) {
            return *nums[number].begin();
        }
        return -1;
    }
private:
    unordered_map<int , set<int>> nums;
    unordered_map<int , int> nums1;
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */