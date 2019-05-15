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

## [18. 4Sum](https://leetcode.com/problems/4sum/)

## [24. Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/)

## [31. Next Permutation](https://leetcode.com/problems/next-permutation/)

## [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

## [36. Valid Sudoku](https://leetcode.com/problems/valid-sudoku/)

## [46. Permutations](https://leetcode.com/problems/permutations/)

## [48. Rotate Image](https://leetcode.com/problems/rotate-image/)

旋转矩阵。

## [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)

合并区间

## [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)

矩阵中两点的最短路径

## [73. Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/)

将矩阵中为0的元素所有行所有列都设置为0，O(1)空间

## [78. Subsets](https://leetcode.com/problems/subsets/)

求一个集合的子集。

## [79. Word Search](https://leetcode.com/problems/word-search/)

二维矩阵中寻找单词

## [92. Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/)

翻转链表一部分

## [95. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/)

不同的二叉搜索树

## [96. Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/)

不同的二叉搜索树个数

## [120. Triangle](https://leetcode.com/problems/triangle/)

## [131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/)

切分字符串，使每个子串都是回文序列

## [137. Single Number II](https://leetcode.com/problems/single-number-ii/)

一个数字出现了一次，其他所有数字都出现了三次

## [139. Word Break](https://leetcode.com/problems/word-break/)

单词拆分

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
