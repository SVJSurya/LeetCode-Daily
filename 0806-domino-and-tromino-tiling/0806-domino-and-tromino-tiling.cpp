class Solution {
public:
    int numTilings(int n) {
        const int MOD = 1e9 + 7;
        if (n <= 1) return 1;
        if (n == 2) return 2;
        if (n == 3) return 5;

        // Create dp array of size n + 1
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;

        // Use recurrence: dp[i] = dp[i-1] + dp[i-2] + 2 * dp[i-3]
        for (int i = 4; i <= n; ++i) {
            dp[i] = (2*dp[i-1] % MOD + dp[i-3]) % MOD;
        }

        return dp[n];
    }
};