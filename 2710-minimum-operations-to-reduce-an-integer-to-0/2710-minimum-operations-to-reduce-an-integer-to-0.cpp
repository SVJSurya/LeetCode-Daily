class Solution {
public:
    int minOperations(int n) {
        int a = 1, y = 1;
        if(n <= 0) return 0;
        if(n == 1) return 1;
        while(a*2 < n) a *= 2;
        y = a*2 - n;
        a = n - a;
        int l = minOperations(a);
        int h = minOperations(y);

        return min(l,h) +1;
    }
};