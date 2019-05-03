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

最直接的方法就是先将数组排序，找到头和尾第一个与排序后结果不相同的数，计算下标差。复杂度O\(n\)。

从左至右遍历，找到最大值和最后一个小于max的数，记为end下标

从右至左遍历，找到最小值和最后一个大于Min的数，记为start下标

再设置合适的初值（数组有序时返回0），使end-start+1=0

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

遍历数组，记录最大最小值及其下标。最小值从右往左，最大值从左往右。

```cpp
class Solution
{
  public:
    int findUnsortedSubarray(vector<int> &nums)
    {

        int maxnum = nums[0];
        int minnum = nums[nums.size() - 1];
        int end = -1, start = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            maxnum = max(maxnum, nums[i]);
            if (maxnum > nums[i])
                end = i;
            minnum = min(minnum, nums[nums.size() - 1 - i]);
            if (minnum < nums[nums.size() - 1 - i])
                start = nums.size() - 1 - i;
        }
        return end - start + 1;
    }
};
```

## [594. Longest Harmonious Subsequence](https://leetcode.com/problems/longest-harmonious-subsequence/)

给定一串数字，找出两个相差1的数，使它们的个数和最大。

对每个num计数，再查找有没有num-1，如果有就计算二者的count和，并与返回的最大值比较。

```cpp
class Solution
{
  public:
    int findLHS(vector<int> &nums)
    {

        unordered_map<int, int> map;
        for (auto num : nums)
            map[num]++;
        int ret = 0;
        for (auto it = map.begin(); it != map.end(); it++)
        {
            int pre = it->first - 1;
            if (map.find(pre) != map.end())
            {
                ret = max(ret, map[pre] + it->second);
            }
        }

        return ret;
    }
};
```

## [665. Non-decreasing Array](https://leetcode.com/problems/non-decreasing-array/)

对于一个数组，能否修改&lt;=1个数能够使数组变成非减数组。nums\[i\]&lt;=nums\[i+1\]

当出现nums\[i\]&gt;nums\[i+1\]时，标志位置1，再次出现则返回false。

对于i==0时，可以不修改num\[i+1\]的值（对后续判断无影响）

i&gt;=1时，将nums\[i+1\]置为最小满足要求的值，即Num\[i\]。

```cpp
class Solution
{
  public:
    bool checkPossibility(vector<int> &nums)
    {
        if (nums.size() == 0)
            return true;
        bool adj = false;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (nums[i] > nums[i + 1])
            {
                if (i >= 1 && nums[i + 1] <= nums[i - 1])
                    nums[i + 1] = nums[i];
                if (adj)
                    return false;
                adj = true;
            }
        }
        return true;
    }
};
```

## [669. Trim a Binary Search Tree](https://leetcode.com/problems/trim-a-binary-search-tree/)

递归，如果值比L小，就返回右子树的递归，大就返回左子树。

如果在LR中间，就向下递归左右子树。

```cpp
class Solution
{
  public:
    TreeNode *trimBST(TreeNode *root, int L, int R)
    {
        if (root == NULL)
            return NULL;
        if (root->val < L)
            return trimBST(root->right, L, R);
        if (root->val > R)
            return trimBST(root->left, L, R);
        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);
        return root;
    }
};
```

## [706. Design HashMap](https://leetcode.com/problems/design-hashmap/)

链地址法解决冲突。注意在**remove** list中的数时，需要注意it指针。直接it++会引发错误，因为it已经被erase掉了。

```cpp
class MyHashMap
{
  public:
    int size = 10000;

    vector<list<pair<int, int>>> map;

    /** Initialize your data structure here. */
    MyHashMap()
    {
        map.resize(size);
    }

    /** value will always be non-negative. */
    void put(int key, int value)
    {

        int pos = key % size;

        for (auto it = map[pos].begin(); it != map[pos].end(); it++)
        {
            if (it->first == key)
            {
                it->second = value;
                return;
            }
        }
        map[pos].push_back(pair<int, int>(key, value));
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key)
    {
        int pos = key % size;
        for (auto it = map[pos].begin(); it != map[pos].end(); it++)
        {
            if (it->first == key)
            {
                return it->second;
            }
        }
        return -1;
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key)
    {

        int pos = key % size;

        for (auto it = map[pos].begin(); it != map[pos].end();)
        {

            if (it->first == key)
            {
                map[pos].erase(it++);
            }
            else
                it++;
        }
    }
};
```

## [707. Design Linked List](https://leetcode.com/problems/design-linked-list/)

测试样例在index为负数时有bug。

```cpp
class MyLinkedList
{

  public:
    class LinkNode
    {
      public:
        int val;
        LinkNode *next;
        LinkNode() { ; }
    };

    LinkNode *head;
    LinkNode *tail;
    int size;

    /** Initialize your data structure here. */
    MyLinkedList()
    {
        head = new LinkNode();
        head->next = NULL;
        tail = head;
        size = 0;
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index)
    {
        if (index >= size || index < 0)
            return -1;

        LinkNode *p = head->next;
        for (int i = 0; i < index; i++)
            p = p->next;
        return p->val;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val)
    {
        LinkNode *temp = new LinkNode();
        temp->val = val;
        temp->next = head->next;
        head->next = temp;
        if (size == 0)
            tail = head->next;
        size++;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val)
    {
        LinkNode *temp = new LinkNode();
        temp->val = val;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
        size++;
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val)
    {
        if (index < 0)
        {
            addAtHead(val);
            return;
        }

        if (index < 0 || index > size)
            return;
        LinkNode *p = head;
        for (int i = 0; i < index; i++)
        {
            p = p->next;
        }
        LinkNode *temp = new LinkNode();
        temp->val = val;
        temp->next = p->next;
        p->next = temp;

        if (index == size)
            tail = temp;

        size++;
    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index)
    {

        if (index < 0 || index >= size)
            return;
        LinkNode *p = head;
        for (int i = 0; i < index; i++)
        {
            p = p->next;
        }
        p->next = p->next->next;

        if (size == index + 1)
        {
            tail = p;
        }

        size--;
    }
};
```

## [754. Reach a Number](https://leetcode.com/problems/reach-a-number/)

数学问题。分类讨论

```cpp
class Solution {
public:
    int reachNumber(int target) {
        target = abs(target);
        long long n = ceil((-1.0 + sqrt(1+8.0*target)) / 2);
        long long sum = n * (n+1) / 2;
        if (sum == target) return n;
        long long res = sum - target;
        if ((res&1) == 0) 
            return n;
        else 
            return n+((n&1) ? 2 : 1);
        
    }
};
```

## [766. Toeplitz Matrix](https://leetcode.com/problems/toeplitz-matrix/)

```cpp
class Solution
{
  public:
    bool isToeplitzMatrix(vector<vector<int>> &matrix)
    {

        for (int i = 0; i < matrix.size() - 1; i++)
        {
            for (int j = 0; j < matrix[0].size() - 1; j++)

            {
                if (matrix[i][j] != matrix[i + 1][j + 1])
                    return false;
            }
        }
        return true;
    }
};
```