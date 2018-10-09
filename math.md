# Array

###  1. Two Sum

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

###  53. Maximum Subarray

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

