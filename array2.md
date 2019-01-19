# Array2

##  452. Minimum Number of Arrows to Burst Balloons

射掉气球所需的最少次数。将气球按照x2排序，之后用贪心算法比较当前一次射击位置和下一个气球的x1值，如果x1大，那么就需要再射一箭。

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

##  462. Minimum Moves to Equal Array Elements II

这是一道数学问题。

![](.gitbook/assets/image%20%284%29.png)

答案是中位数。证明如下

![](.gitbook/assets/image%20%283%29.png)

```cpp
class Solution
{
  public:
	int minMoves2(vector<int> &nums)
	{
		sort(nums.begin(), nums.end());
		int m = nums[(nums.size() - 1) / 2];
		int count = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] < m)
				count += m - nums[i];
			else
				count += nums[i] - m;
		}
		return count;
	}
};
```

##  525. Contiguous Array

一个数组由0和1构成，求一个最长子串，0和1的个数相同。

利用求和来简化计算。对于子串\(i,j\)，对于为0的，记为-1，那么如果0和1的个数相同，那么其和为0。

我们一次求出sum\(0,i\)，在计算出其和后，我们寻找之前的和，如果有sum相等的数sum\(0,j\)，那么sum\(i,j\)的值就为0。所以用一个unordered\_map来记录各个和，这样便于查找、存储。

```cpp
class Solution
{
  public:
    int findMaxLength(vector<int> &nums)
    {
        unordered_map<int, int> myMap;

        int sum = 0;
        int maxLen = 0;
        myMap[0] = -1;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += (nums[i] == 0) ? -1 : 1;
            auto it = myMap.find(sum);
            if (it != myMap.end())
                maxLen = max(maxLen, i - it->second);
            else
                myMap[sum] = i;
        }
        return maxLen;
    }
};
```

