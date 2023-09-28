class Solution {
public:
    int solve(vector<int> &obstacles, int currLane, int currPos, int n, vector<vector<int> > &dp) {
        //base case
        if(currPos == n)
            return 0;
        
        if(dp[currLane][currPos] != -1)
            return dp[currLane][currPos];
        
        if(obstacles[currPos+1] != currLane)
            return solve(obstacles, currLane, currPos + 1, n,dp);
        else {
            int ans = INT_MAX;
            for(int i = 1; i <= 3; i++) {
                if(currLane != i && obstacles[currPos] != i)
                    ans = min(ans, 1 + solve(obstacles, i, currPos+1, n, dp));
            }
            dp[currLane][currPos] = ans;
            return dp[currLane][currPos];
        }
        
    }

    int solveTab(vector<int> &obstacles) {
        int n = obstacles.size()-1;
        vector<vector<int> > dp(4, vector<int>(n+1, 1e9));
        dp[0][n] = 0;
        dp[1][n] = 0;
        dp[2][n] = 0;
        dp[3][n] = 0;

        for(int currpos = n-1; currpos >= 0; currpos--) {
            for(int currlane = 1; currlane <= 3; currlane++) {
        
                if(obstacles[currpos+1] != currlane)
                    dp[currlane][currpos] = dp[currlane][currpos+1];
                
                else {
                    int ans = 1e9;
                    for(int i = 1; i <= 3; i++) {
                        if(currlane != i && obstacles[currpos] != i)
                            ans = min(ans, 1 + dp[i][currpos+1]);
                    }
                    dp[currlane][currpos] = ans;
                }
            }
        }
        return min(dp[2][0], min(1+dp[1][0], 1+dp[3][0]));

    }

    int solveFast(vector<int> &obstacles) {
        int n = obstacles.size()-1;
        vector<int> curr(4, 1e9);
        vector<int> next(4, 1e9);

        next[0] = 0;
        next[1] = 0;
        next[2] = 0;
        next[3] = 0;

        for(int currpos = n-1; currpos >= 0; currpos--) {
            for(int currlane = 1; currlane <= 3; currlane++) {
        
                if(obstacles[currpos+1] != currlane)
                    curr[currlane] = next[currlane];
                
                else {
                    int ans = 1e9;
                    for(int i = 1; i <= 3; i++) {
                        if(currlane != i && obstacles[currpos] != i)
                            ans = min(ans, 1 + next[i]);
                    }
                    curr[currlane] = ans;
                }
            }
            next = curr;
        }
        return min(next[2], min(1+next[1], 1+next[3]));
    }

    int minSideJumps(vector<int>& obstacles) {
        // int n = obstacles.size() - 1;
        // vector<vector<int> > dp(4, vector<int>(obstacles.size(), -1));
        // return solve(obstacles, 2, 0, n, dp);

        return solveFast(obstacles);
    }
};