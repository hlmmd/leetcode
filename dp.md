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

