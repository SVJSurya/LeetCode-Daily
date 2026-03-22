class Solution {
public:
    int dig_sum(long long n) {
        int sum = 0;
        while(n) {
            sum += n%10;
            n /= 10;
        }
        return sum;
    }
    long long makeIntegerBeautiful(long long n, int target) {
        long n0 = n, base = 1;
        while (dig_sum(n) > target) {
            n = n / 10 + 1;
            base *= 10;
        }
        return n * base - n0;
        
    }
};