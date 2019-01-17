# DP

##  198. House Robber

 You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and **it will automatically contact the police if two adjacent houses were broken into on the same night**.

强盗抢劫房子，但是不能抢劫相邻的，问怎样才能抢到最多钱。

动态规划问题，dp\[i\]表示抢劫0-i个房子的最大钱数。

```text
dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
```

因为对于dp\[i\]来说，要么抢劫过nums\[i-1\]房子了，那么对于第i个房子，是不能抢劫的，所以此时dp\[i\]的值与dp\[i-1\]相同。还有可能是没有抢劫过nums\[i-1\]的房子，那么可知，必定会抢劫第i个房子（nums\[i\]的值全部是正数），此时的dp\[i\] = dp\[i-2\]+nums\[i\]，即抢完0~i-2个房子后，又必定会抢劫第i个房子。比较二者大小即可。

```cpp
class Solution
{
  public:
	int rob(vector<int> &nums)
	{

		vector<int> dp(nums.size(), 0);
		if (nums.size() == 0)
			return 0;
		else if (nums.size() == 1)
			return nums[0];
		else if (nums.size() == 2)
			return max(nums[0], nums[1]);

		dp[0] = nums[0];
		dp[1] = max(nums[0], nums[1]);

		for (int i = 2; i < nums.size(); i++)
		{
			dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
		}

		return dp[nums.size() - 1];
	}
};
```

当然，还可以将空间复杂度减少到O（1），操作类似斐波那契数列。

```text
class Solution
{
  public:
	int rob(vector<int> &nums)
	{
		int ppre = 0, pre = 0, cur = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			ppre = pre;
			pre = cur;
			cur = nums[i] + ppre;
			cur = (cur > pre ? cur : pre);
		}
		return cur;
	}
};
```

##  746. Min Cost Climbing Stairs

爬楼梯，一次可以上一层或者两层。每层楼需要花费cost\[i\]，问爬到顶所需要的最小cost。

DP问题，对于任意一层楼梯，它要么从第n-2层爬上来，要么从第n-1层爬上来，取二者中较小的即可。

```cpp
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        
        vector<int> dp(cost.size()+1,0);
        dp[0] = cost[0];
        dp[1] = cost[1];
        for(int i = 2;i<cost.size();i++)
        {
            dp[i] = min(dp[i-2],dp[i-1])+cost[i];
            
        }
        return min( dp[cost.size()-2], dp[cost.size()-1]);
        
    }
};
```

##  139. Word Break

单词拆分，看一个字符串能不能由字典中的字符串组成。

动态规划，只需要确定存不存在一个分割，而不需要求出所有分割，所以不需要递归求解所有的解，只需要用一个数组来表示能不能分割即可。用dp\[i\]表示\[0,i\]子串能否分割。那么在求dp\[i+1\]时，只要考虑\[0,i\]中dp\[i\]为true的作为分割的起点，从字典查找能否构成\[0,i+1\]子串。

因为要多次在字典中查找是否有相应的单词，所以可以将字典存放在unordered\_set中来将查找用时缩减到O\(1\)

```cpp
class Solution
{
  public:
    bool wordBreak(string s, unordered_set<string> &dict)
    {
        if (dict.size() == 0)
            return false;

        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;

        for (int i = 1; i <= s.size(); i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (dp[j])
                {
                    string word = s.substr(j, i - j);
                    if (dict.find(word) != dict.end())
                    {
                        dp[i] = true;
                    }
                }
            }
        }

        return dp[s.size()];
    }

    bool wordBreak(string s, vector<string> &wordDict)
    {

        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return wordBreak(s, dict);
    }
};
```

##  221. Maximal Square

给一个矩阵的1和0（char），找出其中最大的正方形。

很明显要用动态规划。多申请一行一列以便编码，matrix\[i\]\[j\]对应dp\[i+1\]\[j+1\]

如果一个matrix\[i\]\[j\]是0，那么对应的dp必然为0

如果是1，那么dp\[i+1\]\[j+1\]的值要根据其上方、左边、左上方三个点的值来确定。取最小值再加1即可。取最小值保证了加上这个i,j点后，任然是正方形。

即

```cpp
dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
```

```cpp
class Solution
{
  public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return 0;
        int ret = 0;
        vector<vector<int>> dp(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));

        for (int i = 1; i <= matrix.size(); i++)
        {
            for (int j = 1; j <= matrix[0].size(); j++)
            {
                if (matrix[i - 1][j - 1] == '1')
                {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                    ret = max(ret, dp[i][j]);
                }
            }
        }

        return ret * ret;
    }
};
```

##  221. Maximal Square

在一个矩阵的0,1中找到最大的全1正方形。

动态规划，在外围增加1行1列0来方便编写代码。那么matrix\[i-1\]\[j-1\]就对应dp\[i\]\[j\]

如果matrix\[i-1\]\[j-1\]是0，那么dp\[i\]\[j\]就是0。

如果是1，那么就是在其上方、左边、左上方选择最小的dp值再加1。

```cpp
class Solution
{
  public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        if (matrix.size() == 0 || matrix[0].size() == 0)
            return 0;
        int ret = 0;
        vector<vector<int>> dp(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));

        for (int i = 1; i <= matrix.size(); i++)
        {
            for (int j = 1; j <= matrix[0].size(); j++)
            {
                if (matrix[i - 1][j - 1] == '1')
                {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
                    ret = max(ret, dp[i][j]);
                }
            }
        }

        return ret * ret;
    }
};
```

##  279. Perfect Squares

将一个数分解成多个完全平方数的和，最小需要多少个数。

```cpp
class Solution
{
  public:
    int numSquares(int n)
    {

        vector<int> ret(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            ret[i] = n;
            for (int j = 1; (i - j * j) >= 0; j++)
                ret[i] = min(ret[i], ret[i - j * j] + 1);
        }
        return ret[n];
    }
};
```

##  300. Longest Increasing Subsequence

最长递增子序列

注意子序列和子串的区别。

动态规划，dp\[i\]表示\[0,i\]子串的最长子序列长度。

对于dp\[i\]，循环遍历0~i-1，如果nums\[j\]&lt;nums\[i\]，即能满足递增条件，就比较dp\[i\]和dp\[j\]的大小，如果dp\[i\] &lt;= dp\[j\]就可以更新dp\[i\]的值。

```cpp
class Solution
{
  public:
	int lengthOfLIS(vector<int> &nums)
	{

		if (nums.size() == 0)
			return 0;

		vector<int> dp(nums.size(), 1);
		int ret = 1;
		for (int i = 1; i < nums.size(); i++)
		{

			for (int j = 0; j < i; j++)
			{
				if (nums[j] < nums[i] && (dp[i] <= dp[j]))
					dp[i] = dp[j] + 1;
			}
			if (ret < dp[i])
				ret = dp[i];
		}

		return ret;
	}
};
```

##  309. Best Time to Buy and Sell Stock with Cooldown

在有冷却的情况下（卖出股票后第二天不能买入）最佳买卖股票的时机。

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/discuss/75928/Share-my-DP-solution-\(By-State-Machine-Thinking\)

动态规划，为了方便理解，引入状态机。S0表示没有购买股票，S1表示购买股票，S2表示卖出股票。

那么有S0\[i\] = S0\[i-1\] \(Rest\)，或者S0\[i\] = S2\[i-1\]\(Cooldown\),取较大值。S1,S2同理

S1\[i\] = max\(S0\[i-1\],S1\[i-1\]-prices\[i\]\)

S2 = S1\[i-1\]+prices\[i\]

![&#x72B6;&#x6001;&#x673A;&#x793A;&#x610F;&#x56FE;](.gitbook/assets/image%20%282%29.png)

最后的结果必然在S0（没有买股票）和S2（刚卖出股票）二者之间，取较大值即可。

```cpp
class Solution
{
  public:
	int maxProfit(vector<int> &prices)
	{

		if (prices.size() <= 0)
			return 0;
		vector<int> s0(prices.size(), 0);
		vector<int> s1(prices.size(), 0);
		vector<int> s2(prices.size(), 0);

		s1[0] = -prices[0];
		s2[0] = INT_MIN;
		for (int i = 1; i < prices.size(); i++)
		{
			s0[i] = max(s0[i - 1], s2[i - 1]);
			s1[i] = max(s1[i - 1], s0[i - 1] - prices[i]);
			s2[i] = s1[i - 1] + prices[i];
		}
		return max(s0[prices.size() - 1], s2[prices.size() - 1]);
	}
};
```

##  322. Coin Change

硬币找零问题。给定硬币面值，求最少用多少个硬币能够达到amount

动态规划，dp\[i\]表示i个找零需要最少硬币数。初值设为amount+1，不要设为INT\_MAX，测试时会有边界值故意引发溢出问题。dp\[i\] = min\( dp\[i\], dp\[i-coins\[j\]\]+1\)

```cpp
class Solution
{
  public:
	int coinChange(vector<int> &coins, int amount)
	{
		vector<int> dp(amount + 1, amount + 1);
		dp[0] = 0;
		for (int i = 1; i <= amount; i++)
		{
			for (int j = 0; j < coins.size(); j++)
			{
				if (i >= coins[j])
					dp[i] = min(dp[i], dp[i - coins[j]] + 1);
			}
		}
		return dp[amount] == (amount + 1) ? -1 : dp[amount];
	}
};
```

##  368. Largest Divisible Subset

##  377. Combination Sum IV

给一个target和一个数组nums，使用nums中的数对target进行拆分，求拆分的个数。不同的顺序算作不同的拆分。

动态规划，dp\[i\]表示对i的拆分的个数。对于一个i，遍历nums中的数，如果num==i，那么dp\[i\]++，因为存在一个个数为1，数值为i的拆分。如果Num&gt;i，那么拆分不存在。如果num&lt;i，那么我们将num作为拆分的最后一个数，则前面只需要满足是i-num的拆分即可，存在dp\[i-num\]个。对每个num累加即可。

```cpp
class Solution
{
  public:
	int combinationSum4(vector<int> &nums, int target)
	{

		vector<int> dp(target + 1, 0);

		for (int i = 1; i < dp.size(); i++)
		{
			for (auto num : nums)
			{
				if (num == i)
					dp[i]++;
				else if (num < i)
					dp[i] += dp[i - num];
			}
		}

		return dp[target];
	}
};
```

##  416. Partition Equal Subset Sum

给一组数，问能否将其拆分为两个和相等的集合。即存不存在一个子集，和为sum的一半。

可以使用DFS、DP、Bit op等方法来解决。

DFS代码会运行超时，不符合要求。

DP：dp\[i\]表示是否存在一个子集的和为i。那么dp\[i\] = dp\[i\] \|\| dp\[i-num\]，注意要先对nums进行循环，因为是子集，元素不能重复使用。i要从sum开始递减遍历，否则会对结果产生影响

```cpp
class Solution
{
  public:
	bool ret = false;
	bool canPartition(vector<int> &nums)
	{

		int sum = 0;
		for (int i = 0; i < nums.size(); i++)
			sum += nums[i];
		if (sum == 0 || sum & 1 != 0)
			return false;
		sum /= 2;

		vector<int> dp(sum + 1, 0);
		dp[0] = 1;
		for (auto num : nums)
			for (int i = sum; i >= num; i--)
				dp[i] = dp[i] || dp[i - num];
		return dp[sum];
	}
};
```

BIT:

 bits的第i位为1的话表示此数组里面存在组合使得该组合的和为i。  
此处采用归纳法简单的分析下算法：  
1.假设n之前的子列里面存在1~m,k~L……之间和的组合  
2.填加了数字n之后，将会存在\(1+n\)~\(m+n\),\(k+n\)~\(L+n\)……之间和的组合（只要在上面的组合里面添加当前的元素n即可），在标记bits里面相当于将bits向左边移动n位，即bits &lt;&lt; n  
3.故目前为止，存在1~m,k~L……以及\(1+n\)~\(m+n\),\(k+n\)~\(L+n\)……之间和的组合  
4.故bits \|= bits &lt;&lt; n

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        bitset<10001> bits(1);
        int sum = accumulate(nums.begin(), nums.end(), 0);
        for (auto n : nums) bits |= bits << n;
        return !(sum & 1) && bits[sum >> 1];
    }
};
```

##  474. Ones and Zeroes

给定一些0，1字符串组和m个0，n个1，求由这些01能构成最多多少个字符串组中的字符串。

动态规划，用dp\[i\]\[j\]表示i个0，j个1能够构成的字符串个数。要注意要从上往下递归，否则之前的运算的结果会影响后面的递归运算值。dp\[i\]\[j\] = max\(dp\[i\]\[j\], dp\[i - c\[0\]\]\[j - c\[1\]\] + 1\);即当前ij最大值要么不变，要么是去掉0、1个数后+1

```cpp
class Solution
{
  public:
	int findMaxForm(vector<string> &strs, int m, int n)
	{

		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

		for (int i = 0; i < strs.size(); i++)
		{
			vector<int> c(2, 0);
			for (char ch : strs[i])
				c[ch - '0']++;

			for (int i = m; i >= c[0]; i--)
			{
				for (int j = n; j >= c[1]; j--)
				{
					dp[i][j] = max(dp[i][j], dp[i - c[0]][j - c[1]] + 1);
				}
			}
		}

		return dp[m][n];
	}
};
```

##  486. Predict the Winner

##  494. Target Sum

将这个问题进行等价转换再分析。即将数组分成两个集合，P和N，他们的和分别记为sum\(P\)和sum\(N\)。

那么问题就转换成了

sum\(P\)-sum\(N\) = target

两边加上sum\(P\)+sum\(N\) ，即数组累加和sum，得到

2\*sum\(p\) = target+ sum

所以，只需要求一个集合P，使得sum\(p\) = \(target+sum\)/2。

那么问题就转化为类似将数组分为相同的两个集合\(416. Partition Equal Subset Sum\)

```cpp
class Solution
{
  public:
    int findTargetSumWays(vector<int> &nums, int s)
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return sum < s || (s + sum) & 1 ? 0 : subsetSum(nums, (s + sum) >> 1);
    }

    int subsetSum(vector<int> &nums, int s)
    {
        int dp[s + 1] = {0};
        dp[0] = 1;
        for (int n : nums)
            for (int i = s; i >= n; i--)
                dp[i] += dp[i - n];
        return dp[s];
    }
};
```



