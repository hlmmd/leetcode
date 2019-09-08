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

对多个有序的链表进行排序。

使用优先队列。将每个链表的第一个数进队，这样队头就是最小值，队头出队后写入返回链表中，再将对应的链表下一个值进队。

```cpp
class Solution
{
public:
    struct compare
    {
        bool operator()(const ListNode *l, const ListNode *r)
        {
            return l->val > r->val;
        }
    };
    ListNode *mergeKLists(vector<ListNode *> &lists)
    { //priority_queue
        priority_queue<ListNode *, vector<ListNode *>, compare> q;
        for (auto l : lists)
        {
            if (l)
                q.push(l);
        }
        if (q.empty())
            return NULL;

        ListNode *result = q.top();
        q.pop();
        if (result->next)
            q.push(result->next);
        ListNode *tail = result;
        while (!q.empty())
        {
            tail->next = q.top();
            q.pop();
            tail = tail->next;
            if (tail->next)
                q.push(tail->next);
        }
        return result;
    }
};
```

## [32. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/)

给一个括号字符串，求最长的合法括号子串

动态规划，dp[i] = dp[i-1]+2;用leftCount

然后要加上之前已经匹配的括号，以区分(())和()()

```cpp
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        vector<int> dp(s.length(), 0);
        int result = 0;
        int leftCount = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '(')
            {
                leftCount++;
            }
            else if (leftCount > 0)
            {
                dp[i] = dp[i - 1] + 2;
                //前面已经的匹配的括号如()()
                dp[i] += (i - dp[i]) >= 0 ? dp[i - dp[i]] : 0;
                result = max(result, dp[i]);
                leftCount--;
            }
        }
        return result;
    }
};
```

## [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)

解数独