# leetcode contest

## Weekly Contest 186

2020.4.26 

### [1422. Maximum Score After Splitting a String](https://leetcode.com/problems/maximum-score-after-splitting-a-string/)

把01字符串拆成左右两个字串，让左串的0和右串的1数量和最大

```cpp
class Solution
{
public:
    int maxScore(string s)
    {
        int zeros = 0, ones = 0;
        int maxret = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '1')
                ones++;
        }

        for (int i = 0; i < s.size() - 1; i++)
        {
            s[i] == '0' ? zeros++ : ones--;
            maxret = max(maxret, zeros + ones);
        }

        return maxret;
    }
};
```

### [1423. Maximum Points You Can Obtain from Cards](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/)

题目等同于求最小连续定长子序列的和

```cpp
class Solution
{
public:
    int maxScore(vector<int> &cardPoints, int k)
    {

        int sum = 0;
        for (int i = 0; i < cardPoints.size(); i++)
            sum += cardPoints[i];

        int sublen = cardPoints.size() - k;

        int tempsum = 0;
        for (int i = 0; i < sublen; i++)
            tempsum += cardPoints[i];

        int minsubsum = tempsum;
        for (int i = sublen; i < cardPoints.size(); i++)
        {
            tempsum += cardPoints[i];
            tempsum -= cardPoints[i - sublen];
            minsubsum = min(minsubsum, tempsum);
        }
        return sum - minsubsum;
    }
};
```

### [1424. Diagonal Traverse II](https://leetcode.com/problems/diagonal-traverse-ii/)

遍历矩阵 暴力会超时，学了一手map。因为每一斜行的i+j都是一样的

```cpp
class Solution
{
public:
    vector<int> findDiagonalOrder(vector<vector<int>> &nums)
    {

        map<int, vector<int>> mymap;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = 0; j < nums[i].size(); j++)
            {
                mymap[i + j].push_back(nums[i][j]);
            }
        }

        vector<int> ret;
        for (auto &it : mymap)
        {
            auto vec = it.second;
            for (int i = vec.size() - 1; i >= 0; i--)
            {
                ret.push_back(vec[i]);
            }
        }
        return ret;
    }
};
```

### [1425. Constrained Subsequence Sum](https://leetcode.com/problems/constrained-subsequence-sum)

题都没看 //fix me

## Weekly Contest 187

2020.5.3

### [1436. Destination City](https://leetcode.com/problems/destination-city/)

找出不作为出发点的那一个城市。用set即可

```cpp
class Solution
{
public:
    string destCity(vector<vector<string>> &paths)
    {

        set<string> start;
        for (int i = 0; i < paths.size(); i++)
        {
            start.insert(paths[i][0]);
        }

        for (int i = 0; i < paths.size(); i++)
        {
            if (start.find(paths[i][1]) == start.end())
            {
                return paths[i][1];
            }
        }
        return "";
    }
};
```

### [1437. Check If All 1's Are at Least Length K Places Away](https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away)

straight forward.找出01字符串中1最小间隔

```cpp
class Solution
{
public:
    bool kLengthApart(vector<int> &nums, int k)
    {

        int pre = -1, cur = 0;

        int mindist = nums.size();
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 1)
            {
                cur = i;
                if (pre != -1)
                {
                    mindist = min(mindist, cur - pre - 1);
                }
                pre = cur;
            }
        }

        return mindist >= k;
    }
};
```

### [1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)

吃饭了，没做出来。

其实只需要找到子序列的最大值和最小值就行。

用两个deque

[](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/discuss/609771/JavaC%2B%2BPython-Deques-O(N))

```cpp
int longestSubarray(vector<int> &A, int limit)
{
    deque<int> maxd, mind;
    int i = 0, j;
    for (j = 0; j < A.size(); ++j)
    {
        while (!maxd.empty() && A[j] > maxd.back())
            maxd.pop_back();
        while (!mind.empty() && A[j] < mind.back())
            mind.pop_back();
        maxd.push_back(A[j]);
        mind.push_back(A[j]);
        if (maxd.front() - mind.front() > limit)
        {
            if (maxd.front() == A[i])
                maxd.pop_front();
            if (mind.front() == A[i])
                mind.pop_front();
            ++i;
        }
    }
    return j - i;
}
```

### [1439. Find the Kth Smallest Sum of a Matrix With Sorted Rows](https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/)

一个m*n矩阵，每一行都是有序的，从每行中取一个数，得到一个子序列和。求所有可能取到的子序列和中第k大的数

## 2020.5.10

### [1441. Build an Array With Stack Operations](https://leetcode.com/problems/build-an-array-with-stack-operations/)

因为target是有序的，直接求解就行

```cpp
class Solution
{
public:
    vector<string> buildArray(vector<int> &target, int n)
    {

        int index = 0;
        int arrhead = 1;
        vector<int> temp;
        vector<string> ret;
        while (1)
        {
            if (target == temp)
                break;
            if (target[index] > arrhead)
            {
                ret.push_back("Push");
                ret.push_back("Pop");
                arrhead++;
            }
            else
            {
                ret.push_back("Push");
                temp.push_back(arrhead);
                index++;
                arrhead++;
            }
        }
        return ret;
    }
};
```

### [1442. Count Triplets That Can Form Two Arrays of Equal XOR](https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/)

求一段亦或为0的字串。利用前缀亦或，用unoreder_map保存之前的运算结果。

```cpp
class Solution
{
public:
    int countTriplets(vector<int> &arr)
    {
        int ret = 0;
        unordered_map<int, vector<int>> mymap;
        int t = 0;
        mymap[0].push_back(0);
        for (int i = 0; i < arr.size(); i++)
        {
            t ^= arr[i];
            if (mymap.find(t) != mymap.end())
            {
                for (int j = 0; j < mymap[t].size(); j++)
                {
                    ret += i - mymap[t][j];
                }
            }
            mymap[t].push_back(i + 1);
        }
        return ret;
    }
};
```

### [1443. Minimum Time to Collect All Apples in a Tree](https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/)

### [1444. Number of Ways of Cutting a Pizza](https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/)

## 2020.5.17 contest 189

### [1450. Number of Students Doing Homework at a Given Time](https://leetcode.com/problems/number-of-students-doing-homework-at-a-given-time/)

```cpp
class Solution
{
public:
    int busyStudent(vector<int> &startTime, vector<int> &endTime, int queryTime)
    {

        int count = 0;
        for (int i = 0; i < startTime.size(); i++)
        {
            if (startTime[i] <= queryTime && endTime[i] >= queryTime)
                count++;
        }
        return count;
    }
};
```

### [1451. Rearrange Words in a Sentence](https://leetcode.com/problems/rearrange-words-in-a-sentence/)

```cpp
class Solution
{
public:
    string arrangeWords(string text)
    {
        stringstream ss;
        ss << text;
        multimap<size_t, string> maps;
        while (ss >> text)
        {
            transform(text.begin(), text.end(), text.begin(), ::tolower);
            maps.insert({text.length(), text});
        }

        string ret = "";
        for (auto it = maps.begin(); it != maps.end(); ++it)
        {
            ret += it->second + " ";
        }

        ret[0] += 'A' - 'a';

        ret.pop_back();
        return ret;
    }
};
```

### [1452. People Whose List of Favorite Companies Is Not a Subset of Another List](https://leetcode.com/problems/people-whose-list-of-favorite-companies-is-not-a-subset-of-another-list/)

### [1453. Maximum Number of Darts Inside of a Circular Dartboard](https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/)

## 2020.5.24

weekly contest 190

### [1455. Check If a Word Occurs As a Prefix of Any Word in a Sentence](https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/)

又是一个需要split的题，学习python迫在眉睫。

```cpp
class Solution
{
public:
    int isPrefixOfWord(string sentence, string searchWord)
    {
        int flag = false;
        stringstream ss;
        ss << sentence;
        int count = 0;
        while (ss >> sentence)
        {
            count++;
            if (sentence.length() < searchWord.length())
                continue;
            for (int i = 0; i < searchWord.length(); i++)
            {
                if (sentence[i] != searchWord[i])
                {
                    flag = false;
                    break;
                }
                flag = true;
            }
            if (flag)
                return count;
        }

        return -1;
    }
};
```

### [1456. Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)

滑动窗口

```cpp
class Solution
{
public:
    int maxVowels(string s, int k)
    {
        int ret = 0;
        set<char> vowel = {'a', 'e', 'i', 'o', 'u'};
        int count = 0;

        for (int i = 0; i < s.length(); i++)
        {
            if (vowel.find(s[i]) != vowel.end())
            {
                count++;
            }
            if (i >= k && vowel.find(s[i - k]) != vowel.end())
                count--;
            ret = max(ret, count);
        }

        return ret;
    }
};
```

### [1457. Pseudo-Palindromic Paths in a Binary Tree](https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree)

到子节点最多只有一个val出现了奇数次

```cpp
class Solution
{
public:
    unordered_map<int, int> count;
    int ret;
    int pseudoPalindromicPaths(TreeNode *root)
    {
        helper(root);
        return ret;
    }

    void helper(TreeNode *root)
    {
        if (root == NULL)
            return;

        if (count.find(root->val) == count.end())
            count[root->val] = 1;
        else
            count[root->val]++;
        if (root->left == NULL && root->right == NULL)
        {
            int x = 0;
            for (auto it = count.begin(); it != count.end(); it++)
            {
                if (it->second % 2 != 0)
                    x++;
            }
            if (x <= 1)
                ret++;

            count[root->val]--;
            return;
        }

        helper(root->left);
        helper(root->right);

        count[root->val]--;
    }
};
```

### [1458. Max Dot Product of Two Subsequences](https://leetcode.com/problems/max-dot-product-of-two-subsequences/)

最大子序列点积,DP

```cpp
class Solution
{
public:
    int maxDotProduct(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size();
        int n = nums2.size();

        vector<vector<int>> dp(m, vector<int>(n));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dp[i][j] = nums1[i] * nums2[j];
                if (i > 0 && j > 0)
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + max(nums1[i] * nums2[j], 0));
                if (i > 0)
                    dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                if (j > 0)
                    dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
        }

        return dp[m - 1][n - 1];
    }
};
```