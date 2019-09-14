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

主要是基于交换。每次将这个数换到其对应所处的位置上。即nums[i]==i+1

```cpp
class Solution
{
public:
    int firstMissingPositive(vector<int> &nums)
    {

        for (int i = 0; i < nums.size(); i++)
        {

            while (nums[i] > 0 && nums[i] <= nums.size() && nums[nums[i] - 1] != nums[i])
            {
                int temp = nums[i];
                nums[i] = nums[temp - 1];
                nums[temp - 1] = temp;
            }
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != i + 1)
                return i + 1;
        }
        return nums.size() + 1;
    }
};
```

## [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

数组给出一组高度，求去由此构成的形状能蓄多少水。

对每一个位置分别计算。对于一个位置来说，其能蓄多少水取决于其左边最大值leftmax和右边最大值rightmax，值为min\(leftmax,rightmax\)-height。

用两个指针分别指向左右两侧，如果左边的值较小，那么此时min\(leftmax,rightmax\)必定是取决于左边，所以只需要考虑左边部分。比较当前指针指向的值height\[left\]和Leftmax的大小，如果leftmax较小，就更新其值，如果leftmax较大，则可以容纳leftmax-height\[left\]。对于右侧同理。

```cpp
class Solution
{
  public:
    int trap(vector<int> &height)
    {

        int left = 0, right = height.size() - 1;
        int leftmax = 0, rightmax = 0;
        int ret = 0;
        while (left <= right)
        {
            if (height[left] < height[right])
            {
                if (height[left] > leftmax)
                    leftmax = height[left];
                else
                    ret += leftmax - height[left];
                left++;
            }
            else
            {
                if (height[right] > rightmax)
                    rightmax = height[right];
                else
                    ret += rightmax - height[right];
                right--;
            }
        }
        return ret;
    }
};
```

## [44. Wildcard Matching](https://leetcode.com/problems/wildcard-matching/)

类似正则表达式的字符串匹配。动态规划。dp\[i\]\[j\]表示s的前i个字符和p前j个字符是否匹配。注意dp\[i\]\[j\]和s\[i-1\]\[s\[j-1\]对应。

首先dp\[0\]\[0\]=true，因为两个空串是匹配的。然后，给dp\[0\]\[j\]赋值，当p\[j-1\]为'\*'才能和空串匹配。而对于dp\[i\]\[0\]，s非空而p为空，必定不匹配。

处理了为0的下标后，不用考虑i-1、j-1越界的情况，方便编写代码。

如果p\[j-1\]是'\*'，那么可以匹配s的最后一个字符，所以dp\[i\]\[j\] = dp\[i-1\]\[j\]。或者\*匹配空串，dp\[i\]\[j\] = dp\[i\]\[j-1\]。二者满足一个即可，所以用或运算。

如果p\[j-1\]是'?'，则可以和s\[i-1\]匹配。或者s\[i-1\]==p\[j-1\]，直接匹配。此时dp\[i\]\[j\] = dp\[i-1\]\[j-1\]

其他情况均不匹配，dp\[i\]\[j\]保持false，不需要赋值。

```cpp
class Solution
{
public:
    bool isMatch(string s, string p)
    {

        vector<vector<bool>> dp(s.length() + 1, vector<bool>(p.length() + 1, false));
        dp[0][0] = true;

        for (int j = 1; j <= p.length(); j++)
        {
            dp[0][j] = dp[0][j - 1] && p[j - 1] == '*';
        }

        for (int i = 1; i <= s.length(); i++)
        {
            for (int j = 1; j <= p.length(); j++)
            {
                if (p[j - 1] == '*')
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                else if (p[j - 1] == '?' || p[j - 1] == s[i - 1])
                    dp[i][j] = dp[i - 1][j - 1];
            }
        }
        return dp[s.length()][p.length()];
    }
};
```

直接解析

i,j分别表示当前s、p的字符。先判断是否相同，p\[j\]是否是'?'。然后如果p\[j\]是'\*'，就用starindex来记录这个\*的下标，用si来记录此时i指针的值，用于回溯。记录后j++，因为'\*'可以当作空处理。如果之后不匹配再回退。当两个条件都不满足时，需要回退，重新匹配'\*'，用starindex找到上一个\*的位置，将j仍然赋值为其后一位。并将i也赋值为si（即之前i值）的后一位，这样表示用'\*'匹配了s中的第i个字符。

```cpp
class Solution
{
  public:
    bool isMatch(string s, string p)
    {
        int i = 0, j = 0;
        int si;
        int starindex = -1;
        while (s[i])
        {
            if (s[i] == p[j] || p[j] == '?')
            {
                i++;
                j++;
            }
            else if (p[j] == '*')
            {
                starindex = j;
                j++;
                si = i;
            }
            else if (starindex != -1)
            {
                j = starindex + 1;
                i = ++si;
            }
            else
                return false;
        }

        while (p[j] == '*')
            j++;
        return p[j] == 0;
    }
};
```

## [45. Jump Game II](https://leetcode.com/problems/jump-game-ii/)

从0开始跳，最少多少步能跳到末尾。nums\[i\]表示能跳的步数。

BFS。每一层遍历时求出最大能跳到的地方，如果满足就直接返回。

```cpp
class Solution
{
  public:
    int jump(vector<int> &nums)
    {

        if (nums.size() <= 1)
            return 0;
        int level = 0, currentMax = 0, i = 0, nextMax = 0;

        while (i < nums.size() && (currentMax - i + 1 > 0))
        {
            level++;
            for (; i <= currentMax; i++)
            {
                nextMax = max(nextMax, A[i] + i);
                if (nextMax >= n - 1)
                    return level;
            }
            currentMax = nextMax;
        }
        return 0;
    }
};
```

## [51. N-Queens](https://leetcode.com/problems/n-queens/)

N皇后问题。求出所有解。

第一次做的时候，是将整个map全部遍历一次，但实际上因为每一行不能出现相同的皇后，所以每次只要安排第row行的皇后即可。这样只需要遍历n次，并安排合理的col值即可。

此外，在判断两条斜线方向是否有冲突的时候，只需要判断上半部分即可。因为从上往下遍历，下面在没有遍历到的情况下全是'.' 当row==n时表示完成遍历，得到一个解，将其放入ret中返回。

```cpp
class Solution
{
  public:
    vector<vector<string>> ret;

    vector<vector<string>> solveNQueens(int n)
    {
        string temp(n, '.');
        vector<string> solution(n, temp);
        helper(solution, 0, n);
        return ret;
    }

    void helper(vector<string> &map, int row, int n)
    {
        if (row == n){
            ret.push_back(map);
            return ;
        }
        for (int col = 0; col < n; col++)
        {
            if (IsValid(map, row, col, n))
            {
                map[row][col] = 'Q';
                helper(map, row + 1, n);
                map[row][col] = '.';
            }
        }
    }

    bool IsValid(vector<string> &map, int row, int col, int n)
    {
        for (int i = 0; i <= row; i++)
        {
            if (map[i][col] == 'Q')
                return false;
        }

        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            if (map[i][j] == 'Q')
                return false;
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
            if (map[i][j] == 'Q')
                return false;
        return true;
    }
};
```

或者通过位运算来检查45°方向

```cpp
class Solution
{
    int n;
    string getNq(int p)
    {
        string s(n, '.');
        s[p] = 'Q';
        return s;
    }
    void nQueens(int p, int l, int m, int r, vector<vector<string>> &res)
    {
        static vector<string> ans;
        if (p >= n)
        {
            res.push_back(ans);
            return;
        }
        int mask = l | m | r;
        for (int i = 0, b = 1; i < n; ++i, b <<= 1)
            if (!(mask & b))
            {
                ans.push_back(getNq(i));
                nQueens(p + 1, (l | b) << 1, m | b, (r | b) >> 1, res);
                ans.pop_back();
            }
    }

public:
    vector<vector<string>> solveNQueens(int n)
    {
        this->n = n;
        vector<vector<string>> res;
        nQueens(0, 0, 0, 0, res);
        return res;
    }
};
```

## [57. Insert Interval](https://leetcode.com/problems/insert-interval/)

将一个新的区间合并到一个已经排序的区间集中。

```cpp
class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        vector<vector<int>> ret;

        int i = 0;
        while (i < intervals.size() && intervals[i][1] < newInterval[0])
        {
            ret.push_back(intervals[i++]);
        }

        while (i < intervals.size() && intervals[i][0] <= newInterval[1])
        {
            newInterval[0] = min(intervals[i][0], newInterval[0]);
            newInterval[1] = max(intervals[i][1], newInterval[1]);
            i++;
        }
        ret.push_back(newInterval);
        while (i < intervals.size())
            ret.push_back(intervals[i++]);
        return ret;
    }
};
```

## [72. Edit Distance](https://leetcode.com/problems/edit-distance/)

字符串编辑距离。word1可以通过三种操作：插入一个字符、删除一个字符、替换一个字符来变成word2。求从word1到word2的最小操作数。

动态规划，用dp\[i\]\[j\]表示字符串word1\[0,i\)到word2\[0,j\)的编辑距离。注意，dp\[i\]\[j\]对应word1\[i-1\]和word2\[j-1\]

如果word1\[i-1\]==word2\[j-1\]那么不需要进行修改，仍能保持相同，所以此时dp\[i\]\[j\] = dp\[i-1\]\[j-1\]。

如果word1\[i-1\]!=word2\[j-1\]，此时可能需要三种操作。

1：直接将word2\[j-1\]替换为word1\[i-1\]，此时dp\[i\]\[j\] = dp\[i-1\]\[j-1\]+1

2: word1\[0,i-1\)能编辑成word2\[0,j\)，那么word1\[0,i\)只需要删除word1\[i-1\]即可，dp\[i\]\[j\] = dp\[i-1\]\[j\]+1

3: word2直接添加一个字符，此时dp\[i\]\[j\] = dp\[i\]\[j-1\]+1

以上三种情况取最小值即可。

```cpp
class Solution
{
  public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++)
        {
            dp[i][0] = i;
        }
        for (int j = 1; j <= n; j++)
        {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
                }
            }
        }
        return dp[m][n];
    }
};
```

## [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)

s包含t的最小子串。

滑动窗口。用一个map来记录t中字符出现次数。count用来表示出现次数复合要求的个数，当count==t.size\(\)的时候，s中的字符串包含t

设定begin和end两个指针，先移动end指针，将map对应的值+1，当s\[end\]在t中时，判断此时map\[s\[end\]\]的值是否小于等于0，如果满足，就将count++。当counter==t.size\(\)时，先判断此时的字符串长度d，并更新d和head（用来记录子串起始位置）。然后移动head指针，如果map\[s\[begin\]\]&lt;0，说明此时的窗口内的字符串已经不能包含t了，count--，跳出循环，继续往后移动end。

```cpp
class Solution
{
  public:
    string minWindow(string s, string t)
    {
        vector<int> map(128, 0);
        for (auto c : t)
            map[c]--;
        int counter = 0, begin = 0, end = 0, d = INT_MAX, head = 0;
        while (end < s.size())
        {
            map[s[end]]++;
            if (map[s[end]] <= 0)
                counter++;
            end++;

            while (counter == t.size())
            {
                if (end - begin < d)
                {
                    d = end - begin;
                    head = begin;
                }

                map[s[begin]]--;
                if (map[s[begin]] < 0)
                    counter--;

                begin++;
            }
        }

        return d == INT_MAX ? "" : s.substr(head, d);
    }
};
```

## [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

单调栈问题

```cpp
class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int ret = 0;

        int n = heights.size();
        vector<int> left(n, 1);
        vector<int> right(n, 1);

        stack<int> st;

        for (int i = 0; i < n; i++)
        {
            while (!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            left[i] = st.empty() ? i + 1 : i - st.top();
            st.push(i);
        }

        while (!st.empty())
            st.pop();

        for (int i = n - 1; i >= 0; i--)
        {
            while (!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            right[i] = st.empty() ? n - i : st.top() - i;
            st.push(i);
        }

        for (int i = 0; i < n; i++)
        {
            ret = max(ret, heights[i] * (left[i] + right[i] - 1));
        }

        return ret;
    }
};
```

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

