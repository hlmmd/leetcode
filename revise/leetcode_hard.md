# leetcode Hard

## [10. Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/)

正则表达式.和\*的匹配

```cpp
class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int m = s.length();
        int n = p.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        dp[0][0] = 1;
        if (p[0] == '*')
            return 0;
        for (int i = 0; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i >= 1 && (p[j - 1] == '.' || s[i - 1] == p[j - 1]))
                {
                    dp[i][j] |= dp[i - 1][j - 1];
                }
                else if (p[j - 1] == '*')
                {
                    dp[i][j] |= dp[i][j - 2];
                    if (i >= 1 && (p[j - 2] == '.' || p[j - 2] == s[i - 1]))
                        dp[i][j] |= (dp[i - 1][j]);
                }
            }
        }

        return dp[m][n];
    }
};
```

## [23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)

## [32. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/)

给一个括号字符串，求最长的合法括号子串

## [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)

解数独