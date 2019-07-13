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

用栈

```CPP
class Solution
{
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        if (root == NULL)
        {
            return vector<int>();
        }
        vector<int> result;
        stack<TreeNode *> treeStack;
        treeStack.push(root);
        while (!treeStack.empty())
        {
            TreeNode *temp = treeStack.top();
            result.push_back(temp->val);
            treeStack.pop();
            if (temp->right != NULL)
            {
                treeStack.push(temp->right);
            }
            if (temp->left != NULL)
            {
                treeStack.push(temp->left);
            }
        }
        return result;
    }
};
```

## [148. Sort List](https://leetcode.com/problems/sort-list/)

链表排序

```cpp
class Solution
{
public:
    ListNode *sortList(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *slow = head, *fast = head;
        ListNode *pre;
        while (fast != NULL && fast->next != NULL)
        {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        //先用快慢两指针找到链表的中部(slow指针)
        pre->next = NULL;

        ListNode *l1 = sortList(head);
        ListNode *l2 = sortList(slow);
        //递归调用sortList，用分治思想将链表分解，得到两个有序的链表
        return Merge(l1, l2);
        //归并排序，将两个有序的链表合并
    }

    ListNode *Merge(ListNode *l1, ListNode *l2)
    {
        ListNode *l = new ListNode(0);
        ListNode *p;
        p = l;

        while (l1 && l2)
        {
            //比较l1和l2 val的大小，取较小值作为链表的下一个结点
            if (l1->val < l2->val)
            {
                p->next = l1;
                l1 = l1->next;
            }
            else
            {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        //将剩余的链表接到尾部（此时l1,l2只剩下一个)
        p->next = l1 ? l1 : l2;

        return l->next;
    }
};
```

## [152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)

连续子系列的最大乘积

记录最大乘积的同时，记录最小乘积。因为乘以一个负数后最小乘积就变成最大乘积了。同时要和nums[i]比较，因为要考虑0

```cpp
class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;

        int maxp, minp, ret;
        ret = maxp = minp = nums[0];

        for (int i = 1; i < nums.size(); i++)
        {
            int tmax = max(maxp * nums[i], minp * nums[i]);
            int tmin = min(maxp * nums[i], minp * nums[i]);
            maxp = max(tmax, nums[i]);
            minp = min(tmin, nums[i]);
            ret = max(ret, maxp);
        }

        return ret;
    }
};
```

## [173. Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator/)

二叉搜索树的迭代器

## [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)

二叉树的右视图

## [201. Bitwise AND of Numbers Range](https://leetcode.com/problems/bitwise-and-of-numbers-range/)

求区间内所有数的AND值

因为是&运算，所以一旦出现0，那一位上结果就是另。所以找到m,n两数的相同前缀即可。其后面的部分必定是0

```cpp
class Solution
{
public:
    int rangeBitwiseAnd(int m, int n)
    {

        if (m == 0)
            return 0;

        int factor = 0;
        while (m != n)
        {
            m >>= 1;
            n >>= 1;
            factor++;
        }

        return m << factor;
    }
};
```

## [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)

实现前缀树

## [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)

求长度最小的连续数组，满足和>=s

滑动窗口

```cpp
class Solution
{
public:
    int minSubArrayLen(int s, vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        int ret = nums.size() + 1;

        int start = 0, end = 0;
        int value = 0;

        while (end < nums.size() || value >= s)
        {
            if (value >= s)
            {
                ret = min(ret, end - start);
                value -= nums[start++];
            }
            else
            {
                value += nums[end++];
            }
        }

        return ret == (nums.size() + 1) ? 0 : ret;
    }
};
```

## [210. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)

课程安排（拓扑排序）

```cpp
class Solution
{
  public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>> &prerequisites)
    {
        vector<int>ret;
        if (numCourses == 0)
            return ret;
        queue<int> q;
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> adj(numCourses);
        for (int i = 0; i < prerequisites.size(); i++)
        {
            indegree[prerequisites[i].first]++;
            adj[prerequisites[i].second].push_back(prerequisites[i].first);
        }

        for (int i = 0; i < indegree.size(); i++)
        {
            if (indegree[i] == 0)
                q.push(i);
        }
        int count = 0;
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            ret.push_back(v);
            ++count;

            for (int i = 0; i < adj[v].size(); i++)
            {
                if (!(--indegree[adj[v][i]]))
                    q.push(adj[v][i]);
            }
        }
        
        if( count == numCourses)
            return ret;
        else{
            ret.clear();
            return ret;                
        }
            
    }
};
```

## [211. Add and Search Word - Data structure design](https://leetcode.com/problems/add-and-search-word-data-structure-design/)

添加和搜索单词

## [213. House Robber II](https://leetcode.com/problems/house-robber-ii/)

抢劫房子，不能抢劫相邻的房子，切头尾算相邻的房子。求能抢到的最大值

分成两种情况。一种只包括头，一种只包含尾，然后转换成原始rob问题。

ppre表示在上上步时的最大值，pre是上一步最大值。那么对于当前步来说，抢的话就是ppre+nums[i]，不抢就是pre，两者比较取较大值。

```cpp
class Solution
{
public:
    int rob(vector<int> &nums)
    {

        if (nums.size() == 0)
            return 0;

        if (nums.size() == 1)
            return nums[0];

        vector<int> n1(nums.begin() + 1, nums.end());
        vector<int> n2(nums.begin(), nums.end() - 1);

        return max(rob2(n1), rob2(n2));
    }
    int rob2(vector<int> &nums)
    {

        int ppre = 0, pre = 0, cur = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            ppre = pre;
            pre = cur;
            cur = nums[i] + ppre;
            cur = (cur > pre ? cur : pre);
        }
        return cur;
    }
};
```

## [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)

第k大的数

可以利用优先队列（heapsort)，以及快排(partition)

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1, kth;
        while (true) {
            int idx = partition(nums, left, right);
            if (idx == k - 1) {
                kth = nums[idx];
                break;
            }
            if (idx < k - 1) {
                left = idx + 1;
            } else {
                right = idx - 1;
            }
        }
        return kth;
    }
private:
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[left], l = left + 1, r = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot) {
                swap(nums[l++], nums[r--]);
            }
            if (nums[l] >= pivot) {
                l++;
            }
            if (nums[r] <= pivot) {
                r--;
            }
        }
        swap(nums[left], nums[r]);
        return r;
    }
};
```

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        buildMaxHeap(nums);
        for (int i = 0; i < k - 1; i++) {
            swap(nums[0], nums[--heapSize]);
            maxHeapify(nums, 0);
        }
        return nums[0];
    }
private:
    int heapSize;
    
    int left(int i) {
        return (i << 1) + 1;
    }
    
    int right(int i) {
        return (i << 1) + 2;
    }
    
    void maxHeapify(vector<int>& nums, int i) {
        int largest = i, l = left(i), r = right(i);
        if (l < heapSize && nums[l] > nums[largest]) {
            largest = l;
        }
        if (r < heapSize && nums[r] > nums[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(nums[i], nums[largest]);
            maxHeapify(nums, largest);
        }
    }
    
    void buildMaxHeap(vector<int>& nums) {
        heapSize = nums.size();
        for (int i = (heapSize >> 1) - 1; i >= 0; i--) {
            maxHeapify(nums, i);
        }
    }
};
```

## [221. Maximal Square](https://leetcode.com/problems/maximal-square/)

求01矩阵中最大的正方形,dp

```cpp
class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return 0;
        int ret = 0;
        vector<vector<int>> dp(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));

        for (int i = 1; i <= matrix.size(); i++)
        {
            for (int j = 1; j <= matrix[0].size(); j++)
            {
                if (matrix[i - 1][j - 1] == '1')
                {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                    ret = max(ret, dp[i][j]);
                }
            }
        }

        return ret * ret;
    }
};
```

## [222. Count Complete Tree Nodes](https://leetcode.com/problems/count-complete-tree-nodes/)

计算完全二叉树结点个数。利用递归。并判断最左和最右子树是否相同来判断是否是满二叉树快速计算满二叉树的结点个数。

```cpp
class Solution
{

public:
    int countNodes(TreeNode *root)
    {

        if (!root)
            return 0;

        int hl = 0, hr = 0;

        TreeNode *l = root, *r = root;

        while (l)
        {
            hl++;
            l = l->left;
        }

        while (r)
        {
            hr++;
            r = r->right;
        }

        if (hl == hr)
            return pow(2, hl) - 1;

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};
```

## [229. Majority Element II](https://leetcode.com/problems/majority-element-ii/)

给一个数组，求出现次数大于n/3的数

记录出现次数最多的两个数，当遍历到第三个数时，前两个数的技术-1，如果变成0那么就重新确定出现次数>n/3的数。先找到出现次数可能大于n/3的数，再重新准确计数。大于n/3的数加入返回值中。注意可能有0-2个数

```cpp
class Solution
{
public:
    vector<int> majorityElement(vector<int> &nums)
    {

        int n1, n2, c1, c2;
        c1 = c2 = 0;
        for (int i = 0; i < nums.size(); i++)
        {

            if (n1 == nums[i])
                c1++;
            else if (n2 == nums[i])
                c2++;
            else if (c1 == 0)
            {
                n1 = nums[i];
                c1 = 1;
            }
            else if (c2 == 0)
            {
                n2 = nums[i];
                c2 = 1;
            }
            else
            {
                c1--;
                c2--;
            }
        }

        vector<int> ret;

        c1 = c2 = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (n1 == nums[i])
                c1++;
            else if (n2 == nums[i])
                c2++;
        }

        if (c1 > nums.size() / 3)
            ret.push_back(n1);
        if (c2 > nums.size() / 3)
            ret.push_back(n2);
        return ret;
    }
};
```

## [230. Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)

求二叉搜索树中第k小的元素

## [236. Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)

求二叉树两个结点的最小祖先

在两个结点左上方、中间（root）、右上方

```cpp
class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == NULL || p == root || q == root)
            return root;

        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left == NULL && right == NULL)
            return NULL;
        else if (left && right)
            return root;
        else if (left == NULL)
            return right;
        else
            return left;
    }
};
```

## [241. Different Ways to Add Parentheses](https://leetcode.com/problems/different-ways-to-add-parentheses/)

一个计算式，通过不同的方式添加括号，计算能够得到的值。

递归。当当前字符是一个运算符时，考虑其前后两个字符串计算得到的结果，再进行运算。

```cpp
class Solution
{
public:
    vector<int> diffWaysToCompute(string input)
    {
        vector<int> result;
        int size = input.size();
        for (int i = 0; i < size; i++)
        {
            char cur = input[i];
            if (cur == '+' || cur == '-' || cur == '*')
            {
                vector<int> result1 = diffWaysToCompute(input.substr(0, i));
                vector<int> result2 = diffWaysToCompute(input.substr(i + 1));
                for (auto n1 : result1)
                {
                    for (auto n2 : result2)
                    {
                        if (cur == '+')
                            result.push_back(n1 + n2);
                        else if (cur == '-')
                            result.push_back(n1 - n2);
                        else
                            result.push_back(n1 * n2);
                    }
                }
            }
        }
        if (result.empty())
            result.push_back(atoi(input.c_str()));
        return result;
    }
};
```

## [260. Single Number III](https://leetcode.com/problems/single-number-iii/)

一个数列中，只有两个元素出现了一次，求出这两个元素。

设这两个数为a和b。那么，将整个数组异或之后，得到a^b，因为ab不相同，所以异或的结果至少有一位是1.通过diff&=-diff找到最后一个为1的bit。这一位，就可以区分a和b两个数。通过diff将a 和 b分成两组，每一组都是有一个出现一次的元素，其他都是出现两次。

```cpp
class Solution
{
public:
    vector<int> singleNumber(vector<int> &nums)
    {
        // Pass 1 :
        // Get the XOR of the two numbers we need to find
        int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        // Get its last set bit
        diff &= -diff;

        // Pass 2 :
        vector<int> rets = {0, 0}; // this vector stores the two numbers we will return
        for (int num : nums)
        {
            if ((num & diff) == 0) // the bit is not set
            {
                rets[0] ^= num;
            }
            else // the bit is set
            {
                rets[1] ^= num;
            }
        }
        return rets;
    }
};
```

## [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)

n+1个1-n的数中，必定存在重复的数，假设只有一个数出现多次，求这个数

这个数处于1-n之间，使用二分法求解。每次取中，计算数组中<=mid的数的个数。并通过比较count和mid来动态调整low和high的值。

```cpp
int findDuplicate(vector<int> &nums)
{
    int n = nums.size() - 1;
    int low = 1;
    int high = n;
    int mid;
    while (low < high)
    {
        mid = (low + high) / 2;
        int count = 0;
        for (int num : nums)
        {
            if (num <= mid)
                count++;
        }
        if (count > mid)
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}
```

## [289. Game of Life](https://leetcode.com/problems/game-of-life/)

## [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)

最长递增子序列

用res[i]表示长度为i+1的递增子序列的最后一个值

那么，res是一个非递减的的数组，res的长度就是最长子序列的长度。对于一个新的数，有两种情况：比res.back()大，那么就push_back()进res中，表示得到了更长的递增子序列。否则就找到res中第一个大于nums[i]的值，将其修改。

```cpp
int lengthOfLIS(vector<int> &nums)
{
    vector<int> res;
    for (int i = 0; i < nums.size(); i++)
    {
        auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
        if (it == res.end())
            res.push_back(nums[i]);
        else
            *it = nums[i];
    }
    return res.size();
}
```

## [304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/)

二维矩阵的子矩阵和

大矩阵-两个小矩阵+小小矩阵

```cpp
class NumMatrix
{
public:
    vector<vector<int>> sum;

    NumMatrix(vector<vector<int>> matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return;

        sum = vector<vector<int>>(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));

        for (int i = 1; i <= matrix.size(); i++)
        {
            int linesum = 0;

            for (int j = 1; j <= matrix[0].size(); j++)
            {
                linesum += matrix[i - 1][j - 1];
                sum[i][j] = sum[i - 1][j] + linesum;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {

        return sum[row2 + 1][col2 + 1] - sum[row2 + 1][col1] - sum[row1][col2 + 1] + sum[row1][col1];
    }
};
```

## [307. Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/)

连续子数组的和

## [309. Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

有冷却情况下买卖股票的最佳时机

利用DP+状态机求解。

[leetcode 解答](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/discuss/75928/Share-my-DP-solution-(By-State-Machine-Thinking))

```cpp
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {

        if (prices.size() <= 0)
            return 0;
        vector<int> s0(prices.size(), 0);
        vector<int> s1(prices.size(), 0);
        vector<int> s2(prices.size(), 0);

        s1[0] = -prices[0];

        s2[0] = INT_MIN;
        for (int i = 1; i < prices.size(); i++)
        {
            s0[i] = max(s0[i - 1], s2[i - 1]);
            s1[i] = max(s1[i - 1], s0[i - 1] - prices[i]);
            s2[i] = s1[i - 1] + prices[i];
        }
        return max(s0[prices.size() - 1], s2[prices.size() - 1]);
    }
};
```

## [310. Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/)

## [313. Super Ugly Number](https://leetcode.com/problems/super-ugly-number/)

丑数问题

```cpp
class Solution
{
public:
    int nthSuperUglyNumber(int n, vector<int> &primes)
    {

        if (n < 1 || primes.size() == 0)
            return 0;

        vector<int> index(primes.size(), 0);

        vector<int> ret(n, 1);

        for (int i = 1; i < n; i++)
        {
            vector<int> temp(index.size());
            int minval = INT_MAX;
            for (int j = 0; j < index.size(); j++)
            {
                temp[j] = ret[index[j]] * primes[j];
                if (minval > temp[j])
                    minval = temp[j];
            }
            ret[i] = minval;
            for (int j = 0; j < index.size(); j++)
            {
                if (minval == temp[j])
                    index[j]++;
            }
        }

        return ret.back();
    }
};
```

## [318. Maximum Product of Word Lengths](https://leetcode.com/problems/maximum-product-of-word-lengths/)

构成不重复的单词长度最大乘积

用bitmap来判断单词是否有重复字母。

```cpp
class Solution
{
public:
    int maxProduct(vector<string> &words)
    {
        vector<int> mask(words.size());
        int result = 0;
        for (int i = 0; i < words.size(); ++i)
        {
            for (char c : words[i])
                mask[i] |= 1 << (c - 'a');
            for (int j = 0; j < i; ++j)
                if (!(mask[i] & mask[j]))
                    result = max(result, int(words[i].size() * words[j].size()));
        }
        return result;
    }
};
```

## [322. Coin Change](https://leetcode.com/problems/coin-change/)

最少找零问题

DP

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {        
        vector<int> dp(amount+1,amount+1);
        dp[0] = 0;
        for(int i = 1;i<=amount;i++)
        {
            for(int j = 0 ;j<coins.size()  ;j++)
            {
                if(i>=coins[j])
                    dp[i] = min( dp[i],  dp[i-coins[j]]+1);                
            }            
        }        
        return dp[amount]== (amount+1)?-1:dp[amount];
        
    }
};
```


## [328. Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/)

奇偶链表

```cpp
class Solution
{
public:
    ListNode *oddEvenList(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
            return head;

        ListNode *l1 = head, *l2 = head->next, *pp = head->next;
        while (l1 && l2 && l2->next)
        {
            ListNode *temp = l2->next;

            l1->next = temp;
            l2->next = temp->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        l1->next = pp;

        return head;
    }
};
```

## [331. Verify Preorder Serialization of a Binary Tree](https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/)

验证二叉树的先序遍历序列化

## [334. Increasing Triplet Subsequence](https://leetcode.com/problems/increasing-triplet-subsequence/)

数组中是否存在一个长度为3的递增子序列

设置两个数，s1存储当前最小值，s2存储大于s1的值，当第三个大于s2的数出现时，即满足条件。

```cpp
class Solution
{
public:
    bool increasingTriplet(vector<int> &nums)
    {

        int s1 = INT_MAX, s2 = INT_MAX;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] <= s1)
            {
                s1 = nums[i];
            }
            else if (nums[i] <= s2)
            {
                s2 = nums[i];
            }
            else
            {
                return true;
            }
        }

        return false;
    }
};
```

## [337. House Robber III](https://leetcode.com/problems/house-robber-iii/)

## [341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/)

## [343. Integer Break](https://leetcode.com/problems/integer-break/)

将一个数拆分成至少两个正数，求拆分后的最大乘积

x^(n/x) ，求最小值，求导（先取对数再求导）可以得到 x=e时取得最大值。即2个或者3个数。

动态规划。j*(i-j)表示两个数，j*maxArr[i-j]表示三个数

```cpp
class Solution
{
public:
    int integerBreak(int n)
    {

        if (n <= 2)
            return 1;

        vector<int> maxArr(n + 1, 0);
        maxArr[1] = 0;
        maxArr[2] = 1;
        for (int i = 3; i <= n; i++)
        {
            for (int j = 1; j < i; j++)
            {
                maxArr[i] = max(maxArr[i], max(j * (i - j), j * maxArr[i - j]));
            }
        }
        return maxArr[n];
    }
};
```

## [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/)

求数组中最多出现的前K个数

先用map统计各个数的出现次数，再利用桶排序，将数按出现次数排序，返回出现次数最多的k个数。

```cpp
class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {

        unordered_map<int, int> m;

        for (auto num : nums)
            ++m[num];

        vector<vector<int>> buckets(nums.size() + 1);
        for (auto p : m)
            buckets[p.second].push_back(p.first);

        vector<int> ans;
        for (int i = buckets.size() - 1; i >= 0 && ans.size() < k; --i)
        {
            for (int num : buckets[i])
            {
                ans.push_back(num);
                if (ans.size() == k)
                    break;
            }
        }
        return ans;
    }
};
```

## [355. Design Twitter](https://leetcode.com/problems/design-twitter/)

设计twitter

## [368. Largest Divisible Subset](https://leetcode.com/problems/largest-divisible-subset/)

求最大数组，使得每两个元素都能相除

对于一个已经满足条件的数组，如果要往其中添加新的数，那么要么满足能够整除最大数，或者能被最小数整除。先对数组进行排序，然后从大往小开始遍历，用T[i]表示有nums[i]的数组的最大长度。

```cpp
class Solution
{
public:
    vector<int> largestDivisibleSubset(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());

        vector<int> T(nums.size(), 0);
        vector<int> parent(nums.size(), 0);

        int m = 0;
        int mi = 0;

        for (int i = nums.size() - 1; i >= 0; --i)
        {
            for (int j = i; j < nums.size(); ++j)
            {
                if (nums[j] % nums[i] == 0 && T[i] < 1 + T[j])
                {
                    T[i] = 1 + T[j];
                    parent[i] = j;

                    if (T[i] > m)
                    {
                        m = T[i];
                        mi = i;
                    }
                }
            }
        }

        vector<int> ret;

        for (int i = 0; i < m; ++i)
        {
            ret.push_back(nums[mi]);
            mi = parent[mi];
        }

        return ret;
    }
};
```

## [373. Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/)

两个有序集合，从a和b中各取一个数，得到一个pair，求和最小的前K个pairs

```cpp
class Solution
{
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
    {

        vector<int> index(nums1.size(), 0);
        vector<vector<int>> ret;
        if (nums1.size() == 0 || nums2.size() == 0)
            return ret;

        int count = min(k, int(nums1.size() * nums2.size()));
        while (count)
        {
            int t = INT_MAX;
            for (int i = 0; i < nums1.size(); i++)
            {
                if (index[i] == nums2.size())
                    continue;
                t = min(t, nums1[i] + nums2[index[i]]);
            }

            for (int i = 0; i < nums1.size(); i++)
            {
                if (index[i] < nums2.size() && t == (nums1[i] + nums2[index[i]]))
                {
                    vector<int> temp(2, 0);
                    temp[0] = nums1[i];
                    temp[1] = nums2[index[i]];
                    ret.push_back(temp);
                    index[i]++;
                    count--;
                }
                if (count == 0)
                    return ret;
            }
        }

        return ret;
    }
};
```

## [376. Wiggle Subsequence](https://leetcode.com/problems/wiggle-subsequence/)

## [377. Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/)



## [378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)

在一个有序的矩阵中找到第k小的数

可以用类似ugly number的解法，但是复杂度较高。

另外可以用二分搜索，矩阵最小值为left，最大值为right，利用二分法求mid，再用upper_bound求出每一行第一个大于mid的数的位置，进行累加，如果这个累加和小于k，就更新left。否则更新right。

```cpp
class Solution
{
public:
    int kthSmallest(vector<vector<int>> &matrix, int k)
    {
        int n = matrix[0].size();
        int left = matrix[0][0];
        int right = matrix[n - 1][n - 1];

        while (left < right)
        {
            int mid = (left + right) / 2;
            int num = 0;

            for (int i = 0; i < n; i++)
            {
                auto it = upper_bound(matrix[i].begin(), matrix[i].end(), mid);
                num += it - matrix[i].begin();
            }

            if (num < k)
                left = mid + 1;
            else
                right = mid;
        }

        return right;
    }
};
```

```cpp
class Solution
{
public:
    int kthSmallest(vector<vector<int>> &matrix, int k)
    {

        if (matrix.size() == 0 || matrix[0].size() == 0)
            return 0;

        vector<int> index(matrix.size(), 0);

        int count = min(k, int(matrix.size() * matrix[0].size()));
        int val;
        while (count > 0)
        {
            val = INT_MAX;
            for (int i = 0; i < matrix.size(); i++)
            {
                if (index[i] == matrix[0].size())
                    continue;
                val = min(val, matrix[i][index[i]]);
            }

            for (int i = 0; i < matrix.size(); i++)
            {
                if (index[i] < matrix[0].size() && val == matrix[i][index[i]])
                {
                    count--;
                    index[i]++;
                    if (count == 0)
                        return val;
                }
            }
        }

        return val;
    }
};
```

## [380. Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/)

map+vector，vector中记录数值，map记录数值及其对应vecotr中的下标

```cpp
class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (m.find(val) != m.end()) return false;
        nums.push_back(val);
        m[val] = nums.size() - 1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (m.find(val) == m.end()) return false;
        int last = nums.back();
        m[last] = m[val];
        nums[m[val]] = last;
        nums.pop_back();
        m.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return nums[rand() % nums.size()];
    }
private:
    vector<int> nums;
    unordered_map<int, int> m;
};
```

## [382. Linked List Random Node](https://leetcode.com/problems/linked-list-random-node/)

## [384. Shuffle an Array](https://leetcode.com/problems/shuffle-an-array/)

打乱一个数组

随机位置，然后交换

```cpp
class Solution {
public:
    
    vector<int> origin;
    Solution(vector<int>& nums) {
        origin = nums;  
        srand(time(0));
    }
    configuration and return it. */
    vector<int> reset() {
        return origin;        
    }    
    vector<int> shuffle() {        
        vector<int> result(origin);
        for (int i = 0;i < result.size();i++) {
            int pos = rand()%(result.size()-i);
            swap(result[i+pos], result[i]);
        }
        return result;
    }
};
```

## [386. Lexicographical Numbers](https://leetcode.com/problems/lexicographical-numbers/)

返回1-n的字典序

dfs或者直接求解

```cpp
class Solution
{
public:
    vector<int> ret;
    vector<int> lexicalOrder(int n)
    {

        for (int i = 1; i <= 9; i++)
        {
            dfs(n, i);
        }
        return ret;
    }

    void dfs(int n, int t)
    {
        if (t > n)
            return;
        ret.push_back(t);
        t *= 10;
        for (int i = 0; i <= 9; i++)
            if (t + i <= n)
                dfs(n, t + i);
    }
};
```

```cpp
class Solution {
class Solution
{
public:
    vector<int> lexicalOrder(int n)
    {
        vector<int> res(n);
        int cur = 1;
        for (int i = 0; i < n; i++)
        {
            res[i] = cur;
            if (cur * 10 <= n)
                cur *= 10;
            else
            {
                if (cur >= n)
                    cur /= 10;
                cur++;
                while (!(cur % 10))
                    cur /= 10;
            }
        }
        return res;
    }
};
```

## [394. Decode String](https://leetcode.com/problems/decode-string/)

字符串解码

## [395. Longest Substring with At Least K Repeating Characters](https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/)

最长有最少K个重复字符的子串

先统计所有字符的个数，然后找到第一个出现次数少于k次的字符，以该位置为分割点，一分为二，递归求解。

```cpp
class Solution
{
public:
    int longestSubstring(string s, int k)
    {
        if (s.size() == 0 || k > s.size())
            return 0;
        if (k == 0)
            return s.size();

        unordered_map<char, int> Map;
        for (int i = 0; i < s.size(); i++)
        {
            Map[s[i]]++;
        }

        int idx = 0;
        while (idx < s.size() && Map[s[idx]] >= k)
            idx++;
        if (idx == s.size())
            return s.size();

        int left = longestSubstring(s.substr(0, idx), k);

        while (idx < s.size() && Map[s[idx]] < k)
            idx++;
        int right = longestSubstring(s.substr(idx), k);

        return max(left, right);
    }
};
```

## [399. Evaluate Division](https://leetcode.com/problems/evaluate-division/)

并查集（Union-Find）算法

```cpp


```

## [402. Remove K Digits](https://leetcode.com/problems/remove-k-digits/)

删除一个数字的K位，得到的数最小

把string当作stack，对比栈顶和当前遍历到的字符，如果栈顶大，那么就将栈顶删除。注意如果c是'0'且栈顶为空，就不进栈（前导零）

```cpp
class Solution
{
public:
    string removeKdigits(string num, int k)
    {

        string ans = ""; 

        for (char c : num)
        {
            while (ans.length() && ans.back() > c && k)
            {
                ans.pop_back(); 
                k--;            
            }

            if (ans.length() || c != '0')
            {
                ans.push_back(c);
            } 
        }

        while (ans.length() && k--)
        {
            ans.pop_back();
        } 

        return ans.empty() ? "0" : ans;
    }
};
```

## [406. Queue Reconstruction by Height](https://leetcode.com/problems/queue-reconstruction-by-height/)

给定一组<身高,个数>，将其排序，满足个数等于排在自己前面且比自己高的人的个数

先按照身高、位置排序，再依次将人插入返回数组中。

翻译：矮子插队无所谓，反正高个子看不到

```cpp
//网上的api改了
class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
         auto comp = [](const pair<int, int>& p1, const pair<int, int>& p2)
                    { return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second); };
    sort(people.begin(), people.end(), comp);
    vector<pair<int, int>> res;
    for (auto& p : people) 
        res.insert(res.begin() + p.second, p);
    return res;
    }
};
```

## [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)

将数组分成和相等的两部分

可以转化为，求一个子数组，使其和为sum的一半。动态规划。

```cpp
class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {

        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
            sum += nums[i];
        if (sum == 0 || sum & 1 != 0)
            return false;
        sum /= 2;

        vector<int> dp(sum + 1, 0);
        dp[0] = 1;
        for (auto num : nums)
            for (int i = sum; i >= num; i--)
                dp[i] = dp[i] || dp[i - num];

        return dp[sum];
    }
};
```

## [417. Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)

太平洋、大西洋洋流问题

从边上开始dfs，用val表示经过的大洋，并用|运算来记录是否经过了太平洋和大西洋

```cpp
class Solution
{
public:
    vector<pair<int, int>> res;
    vector<vector<int>> visited;
    void dfs(vector<vector<int>> &matrix, int x, int y, int pre, int preval)
    {
        if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size() || matrix[x][y] < pre || (visited[x][y] & preval) == preval)
            return;
        visited[x][y] |= preval;
        if (visited[x][y] == 3)
            res.push_back({x, y});
        dfs(matrix, x + 1, y, matrix[x][y], visited[x][y]);
        dfs(matrix, x - 1, y, matrix[x][y], visited[x][y]);
        dfs(matrix, x, y + 1, matrix[x][y], visited[x][y]);
        dfs(matrix, x, y - 1, matrix[x][y], visited[x][y]);
    }

    vector<pair<int, int>> pacificAtlantic(vector<vector<int>> &matrix)
    {
        if (matrix.empty())
            return res;
        int m = matrix.size(), n = matrix[0].size();
        visited.resize(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++)
        {
            dfs(matrix, i, 0, INT_MIN, 1);
            dfs(matrix, i, n - 1, INT_MIN, 2);
        }
        for (int i = 0; i < n; i++)
        {
            dfs(matrix, 0, i, INT_MIN, 1);
            dfs(matrix, m - 1, i, INT_MIN, 2);
        }
        return res;
    }
};
```

## [421. Maximum XOR of Two Numbers in an Array](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/)

求数组中两个数最大的xor

## [430. Flatten a Multilevel Doubly Linked List](https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/)

## [435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)

求最少需要删去多少个区间后，剩下的区间不重叠

```cpp
class Solution
{
public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {

        auto comp = [](vector<int> &v1, vector<int> &v2) {if(v1[0]==v2[0]) return v1[1]<v2[1];   return v1[0]<v2[0]; };
        sort(intervals.begin(), intervals.end(), comp);
        int ret = 0, pre = 0;
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] < intervals[pre][1])
            {
                ret++;
                if (intervals[i][1] < intervals[pre][1])
                    pre = i;
            }
            else
                pre = i;
        }
        return ret;
    }
};
```

## [436. Find Right Interval](https://leetcode.com/problems/find-right-interval/)

```cpp

```

## [442. Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array/)

找到数组中所有出现两次的数

因为所有数都是1-n，所以将这个数对应的位置的数取反，如果取反后是正数，说明已经取反了两次，就将这个数添加res中。

```cpp
class Solution
{
public:
    vector<int> findDuplicates(vector<int> &nums)
    {
        vector<int> res;
        for (int i = 0; i < nums.size(); i++)
        {
            nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1];
            if (nums[abs(nums[i]) - 1] > 0)
                res.push_back(abs(nums[i]));
        }
        return res;
    }
};
```

## [445. Add Two Numbers II](https://leetcode.com/problems/add-two-numbers-ii/)

链表表示的两个数相加

## [449. Serialize and Deserialize BST](https://leetcode.com/problems/serialize-and-deserialize-bst/)

序列化二叉搜索树

## [450. Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/)

删除二叉搜索树的结点

## [452. Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/)

```cpp
class Solution
{
public:
    int findMinArrowShots(vector<pair<int, int>> &points)
    {
        if (points.size() == 0)
            return 0;

        auto comp = [](pair<int, int> p1, pair<int, int> p2) { return p1.second < p2.second; };
        sort(points.begin(), points.end(), comp);

        int shotcount = 1;
        int shotpos = points[0].second;
        for (int i = 1; i < points.size(); i++)
        {
            if (shotpos < points[i].first)
            {
                shotcount++;
                shotpos = points[i].second;
            }
        }

        return shotcount;
    }
};
```

## [456. 132 Pattern](https://leetcode.com/problems/132-pattern/)

## [462. Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)

求通过让一个数+1或-1，使得所有的数相等，求操作的最少次数

中位数

```CPP
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int m  = nums[ (nums.size()-1)/2];
        int count = 0 ;
        for(int i = 0 ;i<nums.size();i++)
        {
            if(nums[i]<m)
                count+=m-nums[i];
            else
                count+=nums[i]-m;            
        }
        return count;
        
    }
};
```

## [467. Unique Substrings in Wraparound String](https://leetcode.com/problems/unique-substrings-in-wraparound-string/)

## [470. Implement Rand10() Using Rand7()](https://leetcode.com/problems/implement-rand10-using-rand7/)

通过rand7()生成rand10()

注意rand7()是生成1-7

```
class Solution
{
  public:
    int rand10()
    {
        int result = 40;
        while (result >= 40)
        {
            result = 7 * (rand7() - 1) + (rand7() - 1);
        }
        return result % 10 + 1;
    }
};
```

## [473. Matchsticks to Square](https://leetcode.com/problems/matchsticks-to-square/)

## [474. Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/)

给定字符串数组中，有多少个字符能够由最多m个0，n个1组成

```cpp
class Solution
{
public:
    int findMaxForm(vector<string> &strs, int m, int n)
    {

        vector<vector<int>> ret(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i < strs.size(); i++)
        {
            vector<int> c(2, 0);
            for (char ch : strs[i])
                c[ch - '0']++;

            for (int i = m; i >= c[0]; i--)
            {
                for (int j = n; j >= c[1]; j--)
                {
                    ret[i][j] = max(ret[i][j], ret[i - c[0]][j - c[1]] + 1);
                }
            }
        }

        return ret[m][n];
    }
};
```

## [477. Total Hamming Distance](https://leetcode.com/problems/total-hamming-distance/)

求两两汉明距离的总和

```cpp
class Solution
{
public:
    int totalHammingDistance(vector<int> &nums)
    {
        int total = 0;
        for (int j = 0; j < 32; j++)
        {
            int bitCount = 0;
            for (int i = 0; i < nums.size(); i++)
                bitCount += (nums[i] >> j) & 1;
            total += bitCount * (nums.size() - bitCount);
        }
        return total;
    }
};
```

## [486. Predict the Winner](https://leetcode.com/problems/predict-the-winner/)

DP

```cpp
class Solution
{
public:
    bool PredictTheWinner(vector<int> &nums)
    {
        vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), 0));

        for (int i = 0; i < nums.size(); i++)
            dp[i][i] = nums[i];

        for (int l = 1; l < nums.size(); l++)
        {
            for (int i = 0; i < nums.size() - l; i++)
            {
                dp[i][i + l] = max(nums[i + l] - dp[i][i + l - 1], nums[i] - dp[i + 1][i + l]);
            }
        }

        return dp[0][nums.size() - 1] >= 0;
    }
};
```

## [491. Increasing Subsequences](https://leetcode.com/problems/increasing-subsequences/)

求所有递增子串

DFS

```cpp
class Solution
{
public:
	vector<vector<int>> ret;
	vector<vector<int>> findSubsequences(vector<int> &nums)
	{
		vector<int> temp;
		dfs(nums, temp, 0);
		return ret;
	}
	void dfs(vector<int> &nums, vector<int> &temp, int index)
	{
		if (temp.size() > 1)
			ret.push_back(temp);
		unordered_set<int> hash;
		for (int i = index; i < nums.size(); ++i)
		{
			if ((temp.size() == 0 || nums[i] >= temp[temp.size() - 1]) && hash.find(nums[i]) == hash.end())
			{
				temp.push_back(nums[i]);
				dfs(nums, temp, i + 1);
				temp.pop_back();
				hash.insert(nums[i]);
			}
		}
	}
};
```

## [494. Target Sum](https://leetcode.com/problems/target-sum/)

```text
                  sum(P) - sum(N) = target
sum(P) + sum(N) + sum(P) - sum(N) = target + sum(P) + sum(N)
                       2 * sum(P) = target + sum(nums)
```

可以证明，sum(p)必须是sum和target和的一半，这样就能进行转换。

```cpp
class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int s)
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return sum < s || (s + sum) & 1 ? 0 : subsetSum(nums, (s + sum) >> 1);
    }

    int subsetSum(vector<int> &nums, int s)
    {
        int dp[s + 1] = {0};
        dp[0] = 1;
        for (int n : nums)
            for (int i = s; i >= n; i--)
                dp[i] += dp[i - n];
        return dp[s];
    }
};
```

## [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/)

## [508. Most Frequent Subtree Sum](https://leetcode.com/problems/most-frequent-subtree-sum/)

## [513. Find Bottom Left Tree Value](https://leetcode.com/problems/find-bottom-left-tree-value/)

## [515. Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/)

## [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/)

最长回文子序列

## [518. Coin Change 2](https://leetcode.com/problems/coin-change-2/)

求找零方式个数

## [524. Longest Word in Dictionary through Deleting](https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/)

删除一个单词某些字符后，得到的最长在字典中的单词

## [525. Contiguous Array](https://leetcode.com/problems/contiguous-array/)

## [526. Beautiful Arrangement](https://leetcode.com/problems/beautiful-arrangement/)

## [539. Minimum Time Difference](https://leetcode.com/problems/minimum-time-difference/)

## [540. Single Element in a Sorted Array](https://leetcode.com/problems/single-element-in-a-sorted-array/)

## [542. 01 Matrix](https://leetcode.com/problems/01-matrix/)

求每个单位到其最近0的距离

## [547. Friend Circles](https://leetcode.com/problems/friend-circles/)

## [554. Brick Wall](https://leetcode.com/problems/brick-wall/)

## [556. Next Greater Element III](https://leetcode.com/problems/next-greater-element-iii/)

## [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)

求连续子串和为k的子串个数

## [565. Array Nesting](https://leetcode.com/problems/array-nesting/)

## [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/)

查找s2中是否有s1的同构字符串

## [576. Out of Boundary Paths](https://leetcode.com/problems/out-of-boundary-paths/)

## [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/)


