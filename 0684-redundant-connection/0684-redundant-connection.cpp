class Solution {
public:
    
    int findPar(int p,vector<int>par){
        if(p==par[p]){
            return p;
        }
        return findPar(par[p],par);
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
          vector<int> p(2000, 0);
        for(int i = 0; i < p.size(); i++ )
            p[i] = i;
        
        vector<int> res;
        for(auto v : edges ){
            int n1 = v[0], n2 = v[1]; 
            while(n1 != p[n1]) n1 = p[n1];
            while(n2 != p[n2]) n2 = p[n2];
            if( n1 == n2 )
                res = v;
            else 
                p[n1] = n2;
        }
        return res;
    }
};