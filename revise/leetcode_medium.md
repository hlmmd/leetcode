# medium

## [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)


记录每个字符上一次出现的位置，以及开始计算字符串长度的起始位置（起始字符index-1）。如果上一次出现的位置比起始位置大，那么说明这个字符出现了重复，修改start位置，改为上一次出现该字符的位置。将初值都设为-1很有技巧。

```cpp
class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {

        vector<int> index(128, -1);
        int start = -1;
        int ret = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (index[s[i]] > start)
            {
                start = index[s[i]];
            }
            ret = max(ret, i - start);
            index[s[i]] = i;
        }

        return ret;
    }
};
```


## [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)

```cpp
class Solution
{
  public:
    string longestPalindrome(string s)
    {
        int maxlen = 0;
        int start, end;
        string ret = s;
        for (int i = 0; i < s.length(); i++)
        {
            int len = max(expendPalindrome(s, i, i), expendPalindrome(s, i, i + 1));
            //分奇数长度和偶数长度两种情况分开别拓展，取值
            if (len > maxlen)
            {
                maxlen = len;
                start = i - (len - 1) / 2;
                ret = s.substr(start, maxlen);
                //比较得到最长的子串，并计算其起始和终止下标，返回string
            }
        }

        return ret;
    }

    int expendPalindrome(string s, int start, int end)
    {
        //左端和右端没到边界且相等，则可以获得一个更长的回文子串
        while (start >= 0 && end < s.length() && s[start] == s[end])
        {
            start--;
            end++;
        }
        return end - start - 1;
    }
};
```

## [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

给一串高度，选两个组成容器，求容器最大的容积

即 max\(  \(end-start\)\*min\(height\[end\]-height\[start\]\)\)

```cpp
class Solution
{
  public:
    int maxArea(vector<int> &height)
    {

        int ret = 0;
        int start = 0, end = height.size() - 1;

        while (start <= end)
        {
            int val = (end - start) * min(height[start], height[end]);
            ret = max(val, ret);
            if (height[start] < height[end])
                start++;
            else
                end--;
        }

        return ret;
    }
};
```

## [15. 3Sum](https://leetcode.com/problems/3sum/)

三个数字的和为0。转换为two sum，先排序，再固定数，另外两个数的和为-nums[i]。注意处理重复即可。

```cpp
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++)
        {
            int target = -nums[i];
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right)
            {
                int sum = nums[left] + nums[right];
                if (sum < target)
                    left++;
                else if (sum > target)
                    right--;
                else
                {
                    vector<int> temp(3);
                    temp[0] = nums[i];
                    temp[1] = nums[left];
                    temp[2] = nums[right];
                    ret.push_back(temp);
                    while (left < nums.size() && nums[left] == temp[1])
                        left++;
                    while (right >= 0 && nums[right] == temp[2])
                        right--;
                }
            }
            while (i + 1 < nums.size() && nums[i + 1] == nums[i])
                i++;
        }

        return ret;
    }
};
```

## [24. Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/)

交换相邻的两个结点。申请dummy结点，省去考虑头结点的情况。first和second分别指向要交换的两个结点的前一个结点。

```cpp
class Solution
{
public:
    ListNode *swapPairs(ListNode *head)
    {

        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *first = dummy, *second = head, *p;

        while (second && second->next)
        {
            first->next = second->next;
            second->next = first->next->next;
            first->next->next = second;
            first = second;
            second = first->next;
        }
        return dummy->next;
    }
};
```

## [31. Next Permutation](https://leetcode.com/problems/next-permutation/)

求下一个全排列。有标准库函数 next_permutation(nums.begin(), nums.end());

找到最后一个出现增序的位置(即从右往左第一个)，如果不存在，那么直接翻转整个数组即可。

如果存在，设为k，nums[k] \< nums[k+1]，查找[k+1,n-1]中大于nums[k]最后一个数。交换。

然后翻转[k+1,end]即可

```cpp
class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        int n = nums.size(), k, l;
        for (k = n - 2; k >= 0; k--)
        {
            if (nums[k] < nums[k + 1])
            {
                break;
            }
        }
        if (k < 0)
        {
            reverse(nums.begin(), nums.end());
        }
        else
        {
            for (l = n - 1; l > k; l--)
            {
                if (nums[l] > nums[k])
                {
                    break;
                }
            }
            swap(nums[k], nums[l]);
            reverse(nums.begin() + k + 1, nums.end());
        }
    }
};
```

## [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

## [36. Valid Sudoku](https://leetcode.com/problems/valid-sudoku/)

判断数独是否合法。

```cpp
class Solution
{
public:
    bool isValidSudoku(vector<vector<char>> &board)
    {

        vector<vector<int>> used1(9, vector<int>(9, 0));
        vector<vector<int>> used2(9, vector<int>(9, 0));
        vector<vector<int>> used3(9, vector<int>(9, 0));

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '1';
                    int pos = i / 3 * 3 + j / 3;

                    if (used1[i][num] || used2[j][num] || used3[pos][num])
                        return false;

                    used1[i][num] = used2[j][num] = used3[pos][num] = 1;
                }
            }
        }

        return true;
    }
};
```

## [46. Permutations](https://leetcode.com/problems/permutations/)

一种基于dfs递归，一种基于交换

```cpp
class Solution
{
public:
    vector<vector<int>> ret;

    void get(vector<int> &temp, vector<int> &nums)
    {
        if (temp.size() == nums.size())
        {
            ret.push_back(temp);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (find(temp.begin(), temp.end(), nums[i]) != temp.end())
                continue;

            temp.push_back(nums[i]);

            get(temp, nums);

            temp.pop_back();
        }
        return;
    }

    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<int> temp;
        get(temp, nums);
        return ret;
    }
};
```

```cpp
class Solution
{
public:
    vector<vector<int>> permute(vector<int> &num)
    {
        vector<vector<int>> result;

        permuteRecursive(num, 0, result);
        return result;
    }

    void permuteRecursive(vector<int> &num, int begin, vector<vector<int>> &result)
    {
        if (begin >= num.size())
        {
            result.push_back(num);
            return;
        }

        for (int i = begin; i < num.size(); i++)
        {
            swap(num[begin], num[i]);
            permuteRecursive(num, begin + 1, result);
            swap(num[begin], num[i]);
        }
    }
};
```

## [48. Rotate Image](https://leetcode.com/problems/rotate-image/)

旋转矩阵。

分为逆时针和顺时针，都可以通过reverse和swap达到。

```cpp
/*
 * clockwise rotate
 * first reverse up to down, then swap the symmetry 
 * 1 2 3     7 8 9     7 4 1
 * 4 5 6  => 4 5 6  => 8 5 2
 * 7 8 9     1 2 3     9 6 3
*/
void rotate(vector<vector<int> > &matrix) {
    reverse(matrix.begin(), matrix.end());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix[i].size(); ++j)
            swap(matrix[i][j], matrix[j][i]);
    }
}

/*
 * anticlockwise rotate
 * first reverse left to right, then swap the symmetry
 * 1 2 3     3 2 1     3 6 9
 * 4 5 6  => 6 5 4  => 2 5 8
 * 7 8 9     9 8 7     1 4 7
*/
void anti_rotate(vector<vector<int> > &matrix) {
    for (auto vi : matrix) reverse(vi.begin(), vi.end());
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix[i].size(); ++j)
            swap(matrix[i][j], matrix[j][i]);
    }
}
```

## [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)

合并区间。利用sort先排序，再判断下一区间的左边界和当前区间右边界的关系

```cpp
class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {

        vector<vector<int>> ret;

        if (intervals.size() == 0)
            return ret;
        auto comp = [](vector<int> &v1, vector<int> &v2) {
            if(v1[0]==v2[0])return v1[1]<v2[1];return v1[0]<v2[0]; };
        sort(intervals.begin(), intervals.end(), comp);

        ret.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] > ret.back()[1])
                ret.push_back(intervals[i]);
            else if (ret.back()[1] < intervals[i][1])
                ret.back()[1] = intervals[i][1];
        }

        return ret;
    }
};
```

## [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)

矩阵中两点的最短路径 dp

```cpp
class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size();
        if (m == 0 || grid[0].size() == 0)
            return 0;
        int n = grid[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        dp[1][1] = grid[0][0];

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != 1 || j != 1)
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
            }
        }

        return dp[m][n];
    }
};
```

## [73. Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/)

将矩阵中为0的元素所有行所有列都设置为0，O(1)空间

用第一行或者第一列的数存储对应行列是否需要置为0，此时row0和col0会冲突，所以单独用一个变量来存储。

第一个循环设置好01，第二个循环给矩阵赋值。

```cpp
class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int col0 = 1, rows = matrix.size(), cols = matrix[0].size();

        for (int i = 0; i < rows; i++)
        {
            if (matrix[i][0] == 0)
                col0 = 0;
            for (int j = 1; j < cols; j++)
                if (matrix[i][j] == 0)
                    matrix[i][0] = matrix[0][j] = 0;
        }

        for (int i = rows - 1; i >= 0; i--)
        {
            for (int j = cols - 1; j >= 1; j--)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            if (col0 == 0)
                matrix[i][0] = 0;
        }
    }
};
```

## [78. Subsets](https://leetcode.com/problems/subsets/)

求一个集合的子集。

```cpp
class Solution
{
public:
    vector<vector<int>> ret;

    void get(int start, int end, int k, vector<int> &temp, vector<int> &nums)
    {

        if (temp.size() == k)
        {
            ret.push_back(temp);
            return;
        }

        for (int i = start; i < end; i++)
        {
            temp.push_back(nums[i]);
            get(i + 1, end, k, temp, nums);
            temp.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int> &nums)
    {
        int n = nums.size();
        for (int i = 0; i <= n; i++)
        {

            vector<int> temp;
            get(0, n, i, temp, nums);
        }
        return ret;
    }
};
```

## [79. Word Search](https://leetcode.com/problems/word-search/)

二维矩阵中寻找单词

定义一个指针指向单词，每次dfs找到了下一个字符就移动指针，如果不相同直接返回false。

```cpp
class Solution
{
public:
    int m;
    int n;

    bool exist(vector<vector<char>> &board, string word)
    {
        m = board.size();
        if (m == 0 || board[0].size() == 0)
            return false;
        n = board[0].size();
        string temp = "";
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (canfind(board, word.c_str(), i, j))
                    return true;
            }
        }
        return false;
    }

    bool canfind(vector<vector<char>> &board, const char *str, int x, int y)
    {
        if (*str == 0)
            return true;

        if (x < 0 || x >= m || y < 0 || y >= n || board[x][y] == 0 || *str != board[x][y])
            return false;

        char t = board[x][y];
        board[x][y] = 0;

        if (canfind(board, str + 1, x + 1, y) || canfind(board, str + 1, x - 1, y) || canfind(board, str + 1, x, y + 1) || canfind(board, str + 1, x, y - 1))
            return true;

        board[x][y] = t;

        return false;
    }
};
```

## [92. Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/)

**翻转链表一部分**

```cpp
class Solution
{
public:
    ListNode *reverseBetween(ListNode *head, int m, int n)
    {
        ListNode *dummy = new ListNode(0), *pre = dummy, *cur;
        dummy->next = head;
        for (int i = 0; i < m - 1; i++)
        {
            pre = pre->next;
        }
        cur = pre->next;
        for (int i = 0; i < n - m; i++)
        {
            ListNode *temp = pre->next;
            pre->next = cur->next;
            cur->next = cur->next->next;
            pre->next->next = temp;
        }
        return dummy->next;
    }
};
```

## [95. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/)

不同的二叉搜索树

## [96. Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/)

不同的二叉搜索树个数

## [120. Triangle](https://leetcode.com/problems/triangle/)

一个三角形二位数组，求一个从上往下的路径，使得路径和最小。要求O(n)空间。利用动态规划，从底往上求解，只保存下一层的信息，并用上一层的信息计算出当前层的最小值，覆盖原值。

```cpp
class Solution
{
public:
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int m = triangle.size();
        if (m == 0)
            return 0;

        vector<int> dp(m, 0);

        for (int i = m - 1; i >= 0; i--)
        {
            for (int j = 0; j <= i; j++)
            {
                if (i == m - 1)
                    dp[j] = triangle[i][j];
                else
                    dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
            }
        }

        return dp[0];
    }
};
```

## [131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/)

切分字符串，使每个子串都是回文序列

DFS 当检测到一个子串是回文序列时，截断，继续递归。

```cpp
class Solution
{
public:
    vector<vector<string>> ret;

    vector<vector<string>> partition(string s)
    {

        vector<string> temp;

        helper(s, 0, temp);
        return ret;
    }

    bool IsPalindrome(string s, int left, int right)
    {
        while (left <= right)
        {
            if (s[left] != s[right])
                return false;
            left++;
            right--;
        }
        return true;
    }

    void helper(string s, int start, vector<string> &temp)
    {
        if (start == s.length())
        {
            ret.push_back(temp);
            return;
        }

        for (int i = start; i < s.length(); i++)
        {
            if (IsPalindrome(s, start, i))
            {
                temp.push_back(s.substr(start, i - start + 1));
                helper(s, i + 1, temp);
                temp.pop_back();
            }
        }
    }
};
```

## [137. Single Number II](https://leetcode.com/problems/single-number-ii/)

一个数字出现了一次，其他所有数字都出现了三次

 统计每一位的出现次数，再%3.

```cpp
int singleNumber(vector<int> &s)
{
    vector<int> t(32); ////Made a array contain 32 elements.
    int sz = s.size();
    int i, j, n;
    for (i = 0; i < sz; ++i)
    {
        n = s[i];
        for (j = 31; j >= 0; --j)
        {
            t[j] += n & 1; //Find the last digit.
            n >>= 1;
            if (!n)
                break;
        }
    }
    int res = 0;
    for (j = 31; j >= 0; --j)
    {
        n = t[j] % 3; //"3" represents k times.
        if (n)
            res += 1 << (31 - j);
    }
    return res;
}
```

```text
The code seems tricky and hard to understand at first glance.
However, if you consider the problem in Boolean algebra form, everything becomes clear.

What we need to do is to store the number of '1's of every bit. Since each of the 32 bits follow the same rules, we just need to consider 1 bit. We know a number appears 3 times at most, so we need 2 bits to store that. Now we have 4 state, 00, 01, 10 and 11, but we only need 3 of them.

In this solution, 00, 01 and 10 are chosen. Let 'ones' represents the first bit, 'twos' represents the second bit. Then we need to set rules for 'ones' and 'twos' so that they act as we hopes. The complete loop is 00->10->01->00(0->1->2->3/0).

For 'ones', we can get 'ones = ones ^ A[i]; if (twos == 1) then ones = 0', that can be tansformed to 'ones = (ones ^ A[i]) & ~twos'.

Similarly, for 'twos', we can get 'twos = twos ^ A[i]; if (ones* == 1) then twos = 0' and 'twos = (twos ^ A[i]) & ~ones'. Notice that 'ones*' is the value of 'ones' after calculation, that is why twos is
calculated later.
```

```cpp
class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {

        int ones = 0, twos = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            ones = (ones ^ nums[i]) & ~twos;
            twos = (twos ^ nums[i]) & ~ones;
        }
        return ones;
    }
};
```

## [139. Word Break](https://leetcode.com/problems/word-break/)

单词拆分

动态规划，先将vector转为set，方便查找。dp[i]表示子串[0-i]是否能拆分。那么如果有dp[j]==true，即0-j能拆分，而且[j+1,i]是word中的单词的话，那么p[0-i]也是能拆分的。

```cpp
class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {

        unordered_set dict(wordDict.begin(), wordDict.end());
        if (wordDict.size() == 0)
            return false;

        vector<bool> dp(s.length() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.length(); i++)
        {
            for (int j = 0; j < i; j++)
            {

                if (dp[j] == true && dict.find(s.substr(j, i - j)) != dict.end())
                {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp.back();
    }
};
```

## [144. Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)

二叉树先序遍历，非递归实现

## [148. Sort List](https://leetcode.com/problems/sort-list/)

链表排序

## [152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)

连续子系列的最大乘积

## [173. Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator/)

二叉搜索树的迭代器

## [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)

二叉树的右视图
