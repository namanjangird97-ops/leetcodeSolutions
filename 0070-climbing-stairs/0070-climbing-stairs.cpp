class Solution {
private:
    int solve(int indx, vector<int>& dp) {
        if (indx == 0 || indx == 1) return 1;
        
        if (dp[indx] != -1) return dp[indx];
        
        return dp[indx] = solve(indx - 1, dp) + solve(indx - 2, dp);
    }

public:
    int climbStairs(int n) {
        
        vector<int> dp(n + 1, -1);
        return solve(n, dp);
    }
};