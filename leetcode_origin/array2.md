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

![](.gitbook/assets/image%20%289%29.png)

答案是中位数。证明如下

![](.gitbook/assets/image%20%287%29.png)

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

##  540. Single Element in a Sorted Array

一个有序的数组中，有一个数出现了一次，其他都出现了两次。找出这个数。要求O\(logn\)

使用二分法，但要注意在确定上下界的时候，一定要去掉重复的两个数，否则留下一个数会导致子序列中出现两个只出现一次的数，导致出错。

```cpp
class Solution
{
  public:
    int singleNonDuplicate(vector<int> &nums)
    {

        int n = nums.size(), left = 0, right = n - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (mid % 2 == 0)
            {
                if (nums[mid] == nums[mid - 1])
                    right = mid - 2;
                else if (nums[mid] == nums[mid + 1])
                    left = mid + 2;
                else
                    return nums[mid];
            }
            else
            {
                if (nums[mid] == nums[mid - 1])
                    left = mid + 1;
                else if (nums[mid] == nums[mid + 1])
                    right = mid - 1;
            }
        }
        return nums[left];
    }
};
```

##  554. Brick Wall

砖墙，切一条线，要求横穿的砖要最少，不考虑头尾。

对每一行砖进行求和，并用map来保存各个和的值，map\[sum\]有多少，说明在sum处有多少砖重合，切一刀穿过的砖头只有wall.size\(\)-map\[sum\]。

```cpp
class Solution
{
  public:
	int leastBricks(vector<vector<int>> &wall)
	{
		unordered_map<int, int> edges;
		auto min_bricks = wall.size();
		for (auto row : wall)
			for (auto i = 0, width = 0; i < row.size() - 1; ++i) // skip last brick
				min_bricks = min(min_bricks, wall.size() - (++edges[width += row[i]]));
		return min_bricks;
	}
};
```

##  560. Subarray Sum Equals K

求有多少个子串和为K。

用Unordered\_map记录sum\(0,i-1\)的值，在计算出新的sum\(0,i\)后，查找map中是否有和为sum-k的数，如果有。那么sum\(i,j\)为K。

```cpp
class Solution
{
  public:
	int subarraySum(vector<int> &nums, int k)
	{

		unordered_map<int, int> map;
		int sum = 0, ret = 0;
		map[0] = 1;
		for (int i = 0; i < nums.size(); i++)
		{
			sum += nums[i];
			if (map.find(sum - k) != map.end())
				ret += map[sum - k];
			map[sum]++;
		}
		return ret;
	}
};
```

##  565. Array Nesting

数组会形成多个圈，求一个最大的圈中元素个数。那么，对于所有访问过的结点，值为-1作为标记（下标不会为负数），再统计最大值。

```cpp
class Solution
{
  public:
	int arrayNesting(vector<int> &a)
	{
		int maxsize = 0;
		for (int i = 0; i < a.size(); i++)
		{
			int size = 0;
			for (int k = i; a[k] >= 0; size++)
			{
				int ak = a[k];
				a[k] = -1;
				k = ak;
			}
			maxsize = max(maxsize, size);
		}

		return maxsize;
	}
};
```

##  646. Maximum Length of Pair Chain

首先，将所有的组合按第二个数的大小排序，然后使用贪心算法即可。

```cpp
class Solution
{
  public:
    int findLongestChain(vector<vector<int>> &pairs)
    {
        int ret = 0;
        auto comp = [](vector<int> p1, vector<int> p2) { return p1[1] < p2[1]; };
        sort(pairs.begin(), pairs.end(), comp);
        for (int i = 0, pre = 0; i < pairs.size(); i++)
        {
            if (i == 0 || pairs[pre][1] < pairs[i][0])
            {
                ret++;
                pre = i;
            }
        }

        return ret;
    }
};
```

##  659. Split Array into Consecutive Subsequences

贪心算法。先对数组中所有的数进行计数。

再用tails来记录当前序列中末尾为num的序列个数。

对于一个数num，如果能够够成为一个序列的末尾，那么即tails\[num-1\]不为0。一定会接在序列后面，而不会作为新序列的开始，否则组成的这个新序列能够接在前一个数组上。

如果tails\[num-1\]为0，那么这个数只能作为一个新序列的开头，那么cnt\[num+1\],cnt\[num+2\]就不能为0，否则构不成连续的序列。算法中要注意cnt和tails的加减运算。

```cpp
class Solution
{
  public:
	bool isPossible(vector<int> &nums)
	{
		unordered_map<int, int> cnt, tails;
		for (int &i : nums)
			cnt[i]++;
		for (int &i : nums)
		{
			if (!cnt[i])
				continue;
			cnt[i]--;
			if (tails[i - 1] > 0)
			{
				tails[i - 1]--;
				tails[i]++;
			}
			else if (cnt[i + 1] && cnt[i + 2])
			{
				cnt[i + 1]--;
				cnt[i + 2]--;
				tails[i + 2]++;
			}
			else
				return false;
		}
		return true;
	}
};
```

##  713. Subarray Product Less Than K

滑动窗口，当窗口往右扩大一格后，乘积仍然小于K，则cnt += 窗口大小，如果大于等于K，那么久将左边也右移，缩小窗口。

```cpp
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k == 0) return 0;
        int cnt = 0;
        int pro = 1;
        for (int i = 0, j = 0; j < nums.size(); j++) {
            pro *= nums[j];
            while (i <= j && pro >= k) {
                pro /= nums[i++];
            }
            cnt += j - i + 1;
        }
        return cnt;
    }
};
```

##  714. Best Time to Buy and Sell Stock with Transaction Fee

在收交易费的情况下如何买卖股票。依然使用类似状态机的解法，s0表示手上没有股票，s1表示有股票，则s0-&gt;s1需要买入股票并支付交易费，s1-&gt;s0则卖出股票。

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int s0 = 0, s1 = INT_MIN; 
        for(int p:prices) {
            int tmp = s0;
            s0 = max(s0, s1+p);
            s1 = max(s1, tmp-p-fee);
        }
        return s0;
    }
};
```

##  763. Partition Labels

先遍历一遍，找到各个字母最后一次出现的下标。

再遍历一次，记录当前遍历到的字母最大下标，如果i ==idx，那么就可以产生一个分割。

```cpp
class Solution
{
  public:
    vector<int> partitionLabels(string S)
    {
        vector<int> res, pos(26, 0);
        for (auto i = 0; i < S.size(); ++i)
            pos[S[i] - 'a'] = i;
        for (auto i = 0, idx = INT_MIN, last_i = 0; i < S.size(); ++i)
        {
            idx = max(idx, pos[S[i] - 'a']);
            if (idx == i)
                res.push_back(i - exchange(last_i, i + 1) + 1);
        }
        return res;
    }
};
```

