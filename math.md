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



