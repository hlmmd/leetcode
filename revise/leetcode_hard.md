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

重点就是判断添加一个数后，是否满足每一行每一列以及所有的小格内没有重复数字。

```cpp
class Solution
{
public:
    bool isvalid(vector<vector<char>> &board)
    {
        //	print(board);
        int n = 9;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == '.')
                {
                    int xa = i / 3 * 3;
                    int xb = j / 3 * 3;
                    for (int x = 1 + '0'; x <= 9 + '0'; x++)
                    {
                        bool valid = true;

                        for (int k = 0; k < 9; k++)
                        {
                            if (x == board[i][k] || x == board[k][j] || board[xa + k / 3][xb + k % 3] == x)
                            {
                                valid = false;
                                break;
                            }
                        }
                        if (valid == false)
                            continue;

                        board[i][j] = x;
                        if (isvalid(board))
                            return true;
                        else
                            board[i][j] = '.';
                    }
                    return false;
                }
            }
        }
        return true;
    }

    void solveSudoku(vector<vector<char>> &board)
    {
        isvalid(board);
    }
};
```

## [41. First Missing Positive](https://leetcode.com/problems/first-missing-positive/)

给一个整数数组，找到第一个没出现的正整数

## [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

## [44. Wildcard Matching](https://leetcode.com/problems/wildcard-matching/)

正则表达式?和\*

## [45. Jump Game II](https://leetcode.com/problems/jump-game-ii/)

## [51. N-Queens](https://leetcode.com/problems/n-queens/)

N 皇后问题

## [57. Insert Interval](https://leetcode.com/problems/insert-interval/)

将一个新的区间合并到一个已经排序的区间集中。

## [72. Edit Distance](https://leetcode.com/problems/edit-distance/)

字符串的编辑距离

## [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

## [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

## [85. Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)

01矩阵，找到最大的全1矩阵，返回面积。

## [97. Interleaving String](https://leetcode.com/problems/interleaving-string/)

## [99. Recover Binary Search Tree](https://leetcode.com/problems/recover-binary-search-tree/)

## [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)

## [123. Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)

## [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)

## [126. Word Ladder II](https://leetcode.com/problems/word-ladder-ii/)

## [128. Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/)

最长的连续序列。

## [132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/)

