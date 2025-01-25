class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<pair<int,int>> vp(n);
        for(int i=0;i<n;i++)vp[i]={nums[i],i};

        sort(vp.begin(),vp.end());
        vector<int> ind;
        ind.push_back(vp[0].second);
        int prv=0;
        for(int i=1;i<n;i++){
            if(abs(vp[i].first-vp[i-1].first)<=limit){
                ind.push_back(vp[i].second);
            }
            else{
                sort(ind.begin()+prv,ind.end());
                prv=i;
                ind.push_back(vp[i].second);

            }
        }
        sort(ind.begin()+prv,ind.end());

        for(int i=0;i<n;i++){
            nums[ind[i]]=vp[i].first;
        }
        return nums;
    }
};