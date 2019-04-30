# leetcode Easy

## [28. Implement strStr()](https://leetcode.com/problems/implement-strstr/)

```cpp
class Solution
{
  public:
    int strStr(string haystack, string needle)
    {
        if (needle.length() == 0)
            return 0;

        for (int i = 0; haystack[i]; i++)
        {
            for (int j = 0;; j++)
            {
                if (needle[j] == 0)
                    return i;
                if (haystack[i + j] == 0)
                    return -1;
                if (haystack[i + j] != needle[j])
                    break;
            }
        }

        return -1;
    }
};
```

## [67. Add Binary](https://leetcode.com/problems/add-binary/)

注意i--写在?:表达式中可以防止负数溢出。

```cpp
class Solution
{
  public:
    string addBinary(string a, string b)
    {

        string ret = "";

        int i = a.length() - 1;
        int j = b.length() - 1;
        int c = 0;

        while (i >= 0 || j >= 0 || c > 0)
        {
            c += i >= 0 ? a[i--] - '0' : 0;
            c += j >= 0 ? b[j--] - '0' : 0;
            ret = (char)(c % 2 + '0') + ret;
            c = c / 2;
        }

        return ret;
    }
};
```

## [69. Sqrt(x)](https://leetcode.com/problems/sqrtx/)

牛顿法！

```cpp
class Solution
{
  public:
    int mySqrt(int x)
    {

        if (x == 0)
            return 0;

        double r = x;
        while (r * r > x)
        {
            r = (int)((r * r + x) / 2 / r);
        }

        return (int)r;
    }
};
```

## [204. Count Primes](https://leetcode.com/problems/count-primes/)

```cpp
class Solution
{
  public:
    int countPrimes(int n)
    {
        if (n <= 2)
            return 0;
        int count = 0;

        vector<bool> isprime(n, true);
        for (int i = 2; i < n; i++)
        {
            if (isprime[i])
            {
                count++;
                for (int j = i * 2; j < n; j += i)
                    isprime[j] = false;
            }
        }

        return count;
    }
};
```

## [219. Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/)

```cpp
class Solution
{
  public:
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {

        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {
            if (map.find(nums[i]) == map.end())
                map[nums[i]] = i;
            else if (map[nums[i]] + k >= i)
                return true;
            else
                map[nums[i]] = i;
        }
        return false;
    }
};
```

## [405. Convert a Number to Hexadecimal](https://leetcode.com/problems/convert-a-number-to-hexadecimal)

```cpp
class Solution
{
  public:
    string toHex(int num)
    {

        if (num == 0)
            return "0";
        string ret;
        string map = "0123456789abcdef";
        for (int i = 0; i < 8 && num; i++)
        {
            ret = map[num & 0xf] + ret;
            num >>= 4;
        }

        return ret;
    }
};
```

## [437. Path Sum III](https://leetcode.com/problems/path-sum-iii/)

```cpp
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        if(!root) return 0;
        int ret = sumUp(root,0,sum);
        ret +=pathSum(root->left, sum);
        ret +=pathSum(root->right, sum);
        return ret;
    }
private:
    int sumUp(TreeNode* root, int pre, int& sum){
        if(root==NULL)
            return 0;
        int current = pre + root->val;
        int ret = current==sum;
        ret+=sumUp(root->left, current, sum) ;
        ret+=sumUp(root->right,current,sum);
        return ret;
    }
};
```

## [448. Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/)

O(1)空间，O(n)时间。需要修改数组的值，作为标记。

```cpp
class Solution
{
  public:
    vector<int> findDisappearedNumbers(vector<int> &nums)
    {

        for (int i = 0; i < nums.size(); i++)
        {

            int index = abs(nums[i]) - 1;
            if (nums[index] > 0)
                nums[index] = -nums[index];
        }
        vector<int> ret;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > 0)
                ret.push_back(i + 1);
        }
        return ret;
    }
};
```

## [459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/)

先求字符串长度，然后求其所有的因数，如果是重复样式，那么子串长度一定能整除原字符串长度。

```cpp
class Solution
{
  public:
    bool repeatedSubstringPattern(string s)
    {

        int length = s.length();
        if (length == 0 || length == 1)
            return false;
        for (int i = 1; i <= s.length() / 2; i++)
        {
            if (length % i == 0)
            {
                string sub;
                for (int j = 0; j < length / i; j++)
                {
                    sub += s.substr(0, i);
                }
                if (sub == s)
                    return true;
            }
        }
        return false;
    }
};
```

## [461. Hamming Distance](https://leetcode.com/problems/hamming-distance/)

先将两个数亦或，存在汉明距离的位会被置成1。接下来就是数1的个数（n&(n-1)能将最后一位1变成0）

```cpp
class Solution
{
  public:
    int hammingDistance(int x, int y)
    {

        unsigned int v = x ^ y;

        int ret = 0;
        while (v)
        {
            ret++;
            v &= (v - 1);
        }
        return ret;
    }
};
```

## [476. Number Complement](https://leetcode.com/problems/number-complement/)

先取反，然后通过&运算将前导1置为0。

```cpp
class Solution
{
  public:
    int findComplement(int num)
    {
        unsigned mask = ~0;
        while (num & mask)
            mask <<= 1;
        return ~mask & ~num;
    }
};
```

## [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)

利用最大深度。半径等于左右子树最大深度和+1

```cpp
class Solution
{
  public:
    int ret = 0;

    int diameterOfBinaryTree(TreeNode *root)
    {
        maxDepth(root);
        return ret;
    }

    int maxDepth(TreeNode *root)
    {
        if (root == NULL)
            return 0;

        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        ret = max(ret, left + right);
        return max(left, right) + 1;
    }
};
```

## [581. Shortest Unsorted Continuous Subarray](https://leetcode.com/problems/shortest-unsorted-continuous-subarray/)

## [594. Longest Harmonious Subsequence](https://leetcode.com/problems/longest-harmonious-subsequence/)

## [605. Can Place Flowers](https://leetcode.com/problems/can-place-flowers/)

## [617. Merge Two Binary Trees](https://leetcode.com/problems/merge-two-binary-trees/)

## [665. Non-decreasing Array](https://leetcode.com/problems/non-decreasing-array/)

## [669. Trim a Binary Search Tree](https://leetcode.com/problems/trim-a-binary-search-tree/)

## [706. Design HashMap](https://leetcode.com/problems/design-hashmap/)

## [707. Design Linked List](https://leetcode.com/problems/design-linked-list/)

## [754. Reach a Number](https://leetcode.com/problems/reach-a-number/)

## [766. Toeplitz Matrix](https://leetcode.com/problems/toeplitz-matrix/)
