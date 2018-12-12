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

