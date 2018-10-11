# Math

### 70. Climbing Stairs

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

###  118. Pascal's Triangle

杨辉三角问题。也可以通过组合来求解。

```cpp
class Solution {
public:
	vector<vector<int> > generate( int numRows )
	{
		vector<vector<int> > ret;
		for ( int i = 0; i < numRows; i++ )
		{
			vector<int> temp( i + 1, 1 );
			for ( int j = 1; j <= i - 1; j++ )
				temp[j] = ret[i - 1][j - 1] + ret[i - 1][j];
			ret.push_back( temp );
		}
		return(ret);
	}
};
```

###  119. Pascal's Triangle II

只求一行，要求空间复杂度O\(k\)

注意在循环求下一行的值时，从右往左求即可，否则值会被覆盖。

当然用组合公式也可以。

```cpp
class Solution
{
  public:
	vector<int> getRow(int rowIndex)
	{
		vector<int> ret(rowIndex + 1, 0);
		ret[0] = 1;
		for (int i = 1; i <= rowIndex; i++)
		{
			for (int j = i; j > 0; j--)
			{
				ret[j] = ret[j] + ret[j - 1];
			}
		}
		return ret;
	}
};
```

###  121. Best Time to Buy and Sell Stock

买入、出售股票的最好时机（至多只有一次机会）

记住股票的最低点即可。如果价格低于最低点，则刷新最低点，如果高于最低点，那么求出利润，并与最大利润相比较即可。

```cpp
class Solution
{
  public:
	int maxProfit(vector<int> &prices)
	{
		if (prices.size() == 0)
			return 0;
		int minval = prices[0];
		int ret = 0;
		for (int i = 1; i < prices.size(); i++)
		{
			if (prices[i] <= minval)
				minval = prices[i];
			else
				ret = prices[i] - minval > ret ? prices[i] - minval : ret;
		}
		return ret;
	}
};
```

###  171. Excel Sheet Column Number

将数字转化为excel表格的列。即从A到Z再到AA，ZZ……

```cpp
class Solution {
public:
	string convertToTitle( int n )
	{
		string ret = "";
		while ( n )
		{
			n--;
			char temp = n % 26 + 'A';
			ret	= temp + ret;
			n	/= 26;
		}

		return(ret);
	}
};
```

