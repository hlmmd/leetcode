# Math

###  70. Climbing Stairs

You are climbing a stair case. It takes _n_ steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

爬楼梯问题，实际上就是斐波那契数列。因为爬到第n阶楼梯只有两种爬法：从第n-1阶爬1层或者从第n-2阶爬两层。即f\(n\) = f\(n-1\) + f\(n-2\)

```cpp
class Solution
{
  public:
	int climbStairs(int n)
	{

		if (n == 0 || n == 1)
			return 1;

		int f1 = 1, f2 = 1, ret;
		for (int i = 2; i <= n; i++)
		{
			ret = f1 + f2;
			f2 = f1;
			f1 = ret;
		}

		return ret;
	}
};
```

