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

