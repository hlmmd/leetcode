# Array

## 1. Two Sum

Given an array of integers, return **indices** of the two numbers such that they add up to a specific target.

You may assume that each input would have _**exactly**_ one solution, and you may not use the _same_ element twice.

**Example:**

```text
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```

给出一个数组，和一个目标数字target，在数组中找出两个数，使两数之和为target，返回两个数的下标。（假设有且仅有一解）

要找到两个和为target，即对于数组中任意一个数num，要判断target-num是否存在于数组中。

可以使用unodered\_map进行存储，既能存储Num值使查找复杂度达到O\(1\)，又能存储数组下标，方便return。整体复杂度为O\(n\)

```cpp
class Solution
{
  public:
    vector<int> twoSum(vector<int> &nums, int target)
    {

        unordered_map<int, int> map;
        vector<int> ret;
        for (int i = 0; i < nums.size(); i++)
        {
            if (map.find(target - nums[i]) != map.end())
            {
                ret.push_back(i);
                ret.push_back(map[target - nums[i]]);
                return ret;
            }
            map[nums[i]] = i;
        }
        return ret;
    }
};
```

## 53. Maximum Subarray

Given an integer array `nums`, find the contiguous subarray \(containing at least one number\) which has the largest sum and return its sum.

**Example:**

```text
Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
```

求一个数组的最长连续子串和。

基本思想：贪心算法。最大和maxsum用于保存当前计算得到的最大和，sum表示当前的求和。因为只要sum是大于0的，那么对于求和计算，都是有益的，因而采用贪心算法，只要sum&gt;0 ，就一直累加下去。当sum&lt;0时，重置为0。要注意考虑全部都是负数的情况。

```cpp
class Solution
{
  public:
    int maxSubArray(vector<int> &nums)
    {

        if (nums.size() == 0)
            return 0;
        int maxsum = nums[0];
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            maxsum = sum > maxsum ? sum : maxsum;
            sum = sum >= 0 ? sum : 0;
        }
        return maxsum;
    }
};
```

##   169. Majority Element

Given an array of size n, find the majority element. The majority element is the element that appears **more than** `⌊ n/2 ⌋` times.

You may assume that the array is non-empty and the majority element always exist in the array.

求一个数组中出现次数大于n/2的数（假定必定存在）

因为这个数必定存在，所以可以记录当前数出现的次数，如果下一个数与之不同，则count--，相同则count++，当count==0时，说明之前的数都不一定是最多的数，重新赋值。

如果这个数不一定存在，则不能使用该算法。

参考:**Boyer-Moore Voting Algorithm**

```cpp
class Solution
{
  public:
	int majorityElement(vector<int> &nums)
	{
		int count = 0;
		int val;
		for (auto num : nums)
		{
			val = (count == 0) ? num : val;
			num == val ? count++ : count--;
		}
		return val;
	}
};
```

##  283. Move Zeroes

 Given an array `nums`, write a function to move all `0`'s to the end of it while maintaining the relative order of the non-zero elements.

将一个数组中所有的0移动到最后，剩下的数字保留原顺序。

记录0的个数count，因为0会被移动到后面，所以所有不为0的数nums\[i\]，都会向前移动count个。

```cpp
class Solution
{
  public:
	void moveZeroes(vector<int> &nums)
	{
		int count = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			nums[i - count] = nums[i];
			if (nums[i] == 0)
				count++;
			if (count)
				nums[i] = 0;
		}
	}
};
```

##  350. Intersection of Two Arrays II

Given two arrays, write a function to compute their intersection.

**Example 1:**

```text
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]
```

用一个unordered\_map存储，先统计nums1所有数出现个数，再比较nums2。

```cpp
class Solution
{
public:
	vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
	{
		vector<int> ret;
		unordered_map<int, int> map;
		for (int i = 0; i < nums1.size(); i++)
			map[nums1[i]]++;
		for (int i = 0; i < nums2.size(); i++)
		{
			if (map[nums2[i]] > 0)
			{
				map[nums2[i]]--;
				ret.push_back(nums2[i]);
			}
		}

		return ret;
	}
};

```

##  455. Assign Cookies

分配饼干，有g个小朋友，每个人需要g\[i\]大小的饼干才能满足，饼干s块，每块大小s\[i\]。问怎样分配才能满足最多的人。

贪心算法。将g，s两个数组排序，将最小能满足需求的饼干分配给最小的小朋友。

```cpp
class Solution
{
  public:
	int findContentChildren(vector<int> &g, vector<int> &s)
	{

		std::sort(g.begin(), g.end());
		std::sort(s.begin(), s.end());

		int i = 0, j = 0;
		while (i < g.size() && j < s.size())
		{
			if (g[i] <= s[j])
				i++;
			j++;
		}
		return i;
	}
};
```

##  532. K-diff Pairs in an Array

 Given an array of integers and an integer **k**, you need to find the number of **unique** k-diff pairs in the array. Here a **k-diff** pair is defined as an integer pair \(i, j\), where **i** and **j** are both numbers in the array and their [absolute difference](https://en.wikipedia.org/wiki/Absolute_difference) is **k**.

用set保存pair中较小值，满足unique特性。用unordered\_map保存array，查找有没有相差k的数。

```cpp
class Solution
{
  public:
	int findPairs(vector<int> &nums, int k)
	{
		if (k < 0)
		{
			return 0;
		}
		unordered_set<int> starters;
		unordered_map<int, int> indices;
		for (int i = 0; i < nums.size(); i++)
		{
			if (indices.count(nums[i] - k))
			{
				starters.insert(nums[i] - k);
			}
			if (indices.count(nums[i] + k))
			{
				starters.insert(nums[i]);
			}

			indices[nums[i]] += 1;
		}

		return starters.size();
	}
};
```

##  581. Shortest Unsorted Continuous Subarray

 Given an integer array, you need to find one **continuous subarray** that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.

最直接的方法就是先将数组排序，找到头和尾第一个与排序后结果不相同的数，计算下标差。复杂度O\(n\)。

从左至右遍历，找到最大值和最后一个小于max的数，记为end下标

从右至左遍历，找到最小值和最后一个大于Min的数，记为start下标

再设置合适的初值（数组有序时返回0），使end-start+1=0

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

##  594. Longest Harmonious Subsequence

 We define a harmonious array is an array where the difference between its maximum value and its minimum value is **exactly** 1.

给定一串数字，找出两个相差1的数，使它们的个数和最大。

对每个num计数，再查找有没有num-1，如果有就计算二者的count和，并与返回的最大值比较。

```cpp
class Solution
{
  public:
	int findLHS(vector<int> &nums)
	{

		unordered_map<int, int> map;

		for (int i = 0; i < nums.size(); i++)
			map[nums[i]]++;
		int ret = 0;
		for (auto it : map)
		{
			if (map.count(it.first - 1) > 0)
				ret = max(ret, map[it.first - 1] + it.second);
		}
		return ret;
	}
};
```

##  605. Can Place Flowers

种花问题。保证每朵花都不会与其他的花相邻的前提下，最多能种多少只花。

循环遍历flowerbed，对于每一个为0，即空位，考虑其前后两个位置，都为0时则表明可以种花，将此处赋值为1即可。对头尾两端做特殊处理。

```cpp
class Solution
{
  public:
    bool canPlaceFlowers(vector<int> &flowerbed, int n)
    {
        int count = 0;
        for (int i = 0; i < flowerbed.size(); i++)
        {
            if (flowerbed[i] == 0)
            {
                int pre = i == 0 ? 0 : flowerbed[i - 1];
                int next = i == flowerbed.size() - 1 ? 0 : flowerbed[i + 1];
                if (pre == 0 && next == 0)
                {
                    count++;
                    flowerbed[i] = 1;
                }
            }
        }
        return count >= n;
    }
};
```

##  665. Non-decreasing Array

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

##  674. Longest Continuous Increasing Subsequence

最长递增子序列。

当nums\[i\]&gt;nums\[i-1\]时，len++，否则len重置为1。

```cpp
class Solution
{
  public:
    int findLengthOfLCIS(vector<int> &nums)
    {
        int ret = 0;
        int len = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i == 0)
                ret = len;
            else if (nums[i] > nums[i - 1])
                ret = max(++len, ret);
            else
                len = 1;
        }
        return ret;
    }
};
```

##  766. Toeplitz Matrix

矩阵中每个从左上到右下的斜线上的数值都相等。

判断matrix\[i\]\[j\] 和 matrix\[i+1\]\[j+1\]是否相等即可。

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

##  867. Transpose Matrix

转置矩阵。

```cpp
class Solution
{
  public:
    vector<vector<int>> transpose(vector<vector<int>> &A)
    {

        vector<vector<int>> ret(A[0].size(), vector<int>(A.size(), 0));
        for (int i = 0; i < A.size(); i++)
        {
            for (int j = 0; j < A[0].size(); j++)
            {
                ret[j][i] = A[i][j];
            }
        }

        return ret;
    }
};
```

##  905. Sort Array By Parity

排序，使得偶数在前奇数在后。

```cpp
class Solution
{
  public:
    vector<int> sortArrayByParity(vector<int> &A)
    {
        for (int i = 0, j = 0; i < A.size(); i++)
        {
            if (A[i] % 2 == 0)
            {
                int temp = A[j];
                A[j] = A[i];
                A[i] = temp;
                j++;
            }
        }
        return A;
    }
};
```

## Medium

##  11. Container With Most Water

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

##  179. Largest Number

对一个数列重新排序，使其合并后的值最大

```cpp
class Solution
{
  public:
    static int compare(int a, int b)
    {
        string sa = to_string(a);
        string sb = to_string(b);

        return sa + sb > sb + sa;
    }

    string largestNumber(vector<int> &nums)
    {

        std::sort(nums.begin(), nums.end(), compare);
        if (nums[0] == 0)
            return "0";
        string ret = "";
        for (int i = 0; i < nums.size(); i++)
        {
            ret += to_string(nums[i]);
        }

        return ret;
    }
};
```

##  209. Minimum Size Subarray Sum

长度最小的和大于sum的子串。

两个指针，一头一尾，和到sum时前移头指针，不到sum时后移尾指针。记录最大值。

```cpp
class Solution
{
  public:
    int minSubArrayLen(int s, vector<int> &nums)
    {

        if (nums.size() == 0)
            return 0;

        int i = 0, j = 0, sum = 0, minval = INT_MAX;

        while (j < nums.size())
        {
            sum += nums[j++];

            while (sum >= s)
            {
                minval = min(minval, j - i);
                sum -= nums[i++];
            }
        }

        return minval == INT_MAX ? 0 : minval;

        return 0;
    }
};
```

##  238. Product of Array Except Self

求对一个数组中某一位数字，除了该数字外的所有数的乘积。

  一个数的左边所有数相乘，再乘上右边数相乘。可以减少计算次数

```cpp
class Solution
{
  public:
    vector<int> productExceptSelf(vector<int> &nums)
    {

        vector<int> ret(nums.size(), 1);
        int temp = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            ret[i] = temp;
            temp *= nums[i];
        }
        temp = 1;
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            ret[i] *= temp;
            temp *= nums[i];
        }
        return ret;
    }
};
```

##  240. Search a 2D Matrix II

矩阵的每一行每一列都是有序的。

从右上角开始搜索，如果小于目标就往下查找，大于目标往左查找。

```cpp
class Solution
{
  public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        if (matrix.size() == 0)
            return false;

        int i = 0, j = matrix[0].size() - 1;
        while (i < matrix.size() && j >= 0)
        {
            if (matrix[i][j] == target)
                return true;
            else if (matrix[i][j] > target)
                j--;
            else
                i++;
        }
        return false;
    }
};
```

##  287. Find the Duplicate Number

找到数组中重复出现的数。

利用像找链表中的环一样的方法，使用快慢指针。因为有重复的数（环），所以一定能够使快慢指针所指的值相等，即重复的数。

```cpp
class Solution
{
  public:
	int findDuplicate(vector<int> &nums)
	{
		if (nums.size() > 1)
		{
			int slow = nums[0];
			int fast = nums[nums[0]];
			while (slow != fast)
			{
				slow = nums[slow];
				fast = nums[nums[fast]];
			}

			fast = 0;
			while (fast != slow)
			{
				fast = nums[fast];
				slow = nums[slow];
			}
			return slow;
		}
		return -1;
	}
};
```

##  304. Range Sum Query 2D - Immutable

给一个数组，求一块矩形区域内的所有数的和。

```text
+---------------+   +--------------+   +---------------+   +--------------+   +--------------+
|               |   |         |    |   |   |           |   |         |    |   |   |          |
|   (r1,c1)     |   |         |    |   |   |           |   |         |    |   |   |          |
|   +------+    |   |         |    |   |   |           |   +---------+    |   +---+          |
|   |      |    | = |         |    | - |   |           | - |      (r1,c2) | + |   (r1,c1)    |
|   |      |    |   |         |    |   |   |           |   |              |   |              |
|   +------+    |   +---------+    |   +---+           |   |              |   |              |
|        (r2,c2)|   |       (r2,c2)|   |   (r2,c1)     |   |              |   |              |
+---------------+   +--------------+   +---------------+   +--------------+   +--------------+
```

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

##  307. Range Sum Query - Mutable

##  334. Increasing Triplet Subsequence

长度为3的递增子序列

用c1和c2来记录当前最小和第二小的数，如果两个判断条件都不满足，说明在之前存在两个较小的数，能够组成递增子序列。

```text
bool increasingTriplet(vector<int> &nums)
{
	int c1 = INT_MAX, c2 = INT_MAX;
	for (int x : nums)
	{
		if (x <= c1)
			c1 = x; 
		else if (x <= c2)
			c2 = x; 
		else
			return true; 
	}
	return false;
}
```

##  347. Top K Frequent Elements

求数组中出现次数最多的前K个数。

先运用unordered\_map统计各个元素出现次数，再用桶排序将元素按个数进行排序，最后再讲结果放入数组中返回。

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        
        
        unordered_map<int,int> m ;
        
        
        for (auto num : nums)
            ++m[num];
        
        vector<vector<int>> buckets(nums.size() + 1); 
        for (auto p : m)
            buckets[p.second].push_back(p.first);
        
        vector<int> ans;
        for (int i = buckets.size() - 1; i >= 0 && ans.size() < k; --i) {
            for (int num : buckets[i]) {
                ans.push_back(num);
                if (ans.size() == k)
                    break;
            }
        }
        return ans;
    }
};
```

##  373. Find K Pairs with Smallest Sums

##  380. Insert Delete GetRandom O\(1\)

##  386. Lexicographical Numbers

将1-n按字典序排序。

cur从1开始，每次获取下一个cur。如果cur\*10&lt;=n，那么cur\*10肯定是下一个数，否则，就将cur+1，并且通过/10将其恢复至个位数以满足字典序。此外，要考虑cur超过n的情况，进行处理即可。

```cpp
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

直接使用dfs，方法简单易懂，但复杂度较高

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

##  390. Elimination Game

在进行了第一次消除后，全部只剩偶数，除2后，得到1-n/2的序列。

那么，从右往左消除的时候，得到的就是从左到右消除的镜像操作。

即得到 1+n/2 - lastRemaining\(n / 2\)

再乘以2回复原来的数值。

```cpp
class Solution
{
  public:
	int lastRemaining(int n)
	{
		return n == 1 ? 1 : 2 * (1 + n / 2 - lastRemaining(n / 2));
	}
};
```

##   406. Queue Reconstruction by Height

##  435. Non-overlapping Intervals

求有多少个不重复的集合。首先将集合按照start的大小排序，然后比较相邻的两个集合。如果后一个的start小于前一个的end，说明有重叠，计数+1，再判断end的大小。取较大的作为pre

```cpp
class Solution
{
  public:
	int eraseOverlapIntervals(vector<Interval> &intervals)
	{
		auto comp = [](const Interval &i1, const Interval &i2) { return i1.start < i2.start; };
		sort(intervals.begin(), intervals.end(), comp);
		int res = 0, pre = 0;
		for (int i = 1; i < intervals.size(); i++)
		{
			if (intervals[i].start < intervals[pre].end)
			{
				res++;
				if (intervals[i].end < intervals[pre].end)
					pre = i;
			}
			else
				pre = i;
		}
		return res;
	}
};
```

