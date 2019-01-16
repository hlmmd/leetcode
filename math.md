# Math

## 70. Climbing Stairs

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

##  118. Pascal's Triangle

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

##  119. Pascal's Triangle II

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

##  121. Best Time to Buy and Sell Stock

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

##  171. Excel Sheet Column Number

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

##  202. Happy Number

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 \(where it will stay\), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

**Example:** 

```text
Input: 19
Output: true
Explanation: 
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
```

给出一个数计算出该数各个位的平方和，循环该操作，直到获得1，返回true。如果不能，直接返回false。

因为可能有死循环，要判断是否存在循环，可以使用判断链表是否有环的相同方法，使用一快一慢两指针。

```cpp
class Solution
{
  public:
	int process(int n)
	{
		int sum = 0;
		while (n)
		{
			sum += (n % 10) * (n % 10);
			n /= 10;
		}
		return sum;
	}

	bool isHappy(int n)
	{

		int fast = n, slow = n;

		while (fast != 1)
		{
			fast = process(fast);
			fast = process(fast);
			slow = process(slow);
			if (fast == slow && fast != 1)
				return false;
		}

		return true;
	}
};
```

##  204. Count Primes

 Count the number of prime numbers less than a non-negative number, **n**.

计算小于n的素数个数。

先假定每一个数都是素数，再用排除法。从2开始，2是素数，但之后所有2的倍数都不是素数，可以一一排除。接着排除3的倍数、5的倍数，这样就排除了所有的合数，只留下素数。

```cpp
class Solution
{
  public:
	int countPrimes(int n)
	{
		int count = 0;
		vector<bool> IsPrime(n, true);

		for (int i = 2; i < n; i++)
		{
			if (IsPrime[i])
			{
				count++;
				for (int j = i + i; j < n; j += i)
					IsPrime[j] = false;
			}
		}
		return count;
	}
};
```

##  303. Range Sum Query - Immutable

Given an integer array nums, find the sum of the elements between indices i and j \(i ≤ j\), inclusive.

**Example:**  


```text
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
```

利用 a\[i\]+a\[i+1\]+...+a\[j\] = a\[0\]+...+a\[j\]-\(a\[0\]+...+a\[i-1\]\)=s\[j\]-s\[i-1\]

可以在初始化的时候保存从0-size的累加和。

```cpp
class NumArray
{
  private:
	vector<int> sum;

  public:
	NumArray(vector<int> nums)
	{

		sum.push_back(0);
		int temp = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			temp += nums[i];
			sum.push_back(temp);
		}
	}

	int sumRange(int i, int j)
	{

		return sum[j + 1] - sum[i];
	}
};
```

##  367. Valid Perfect Square

求一个数是否是平方数。牛顿法。

```cpp
class Solution
{
  public:
	bool isPerfectSquare(int num)
	{

		long x = num;
		while (x * x > num)
		{
			x = (x + num / x) >> 1;
		}
		return x * x == num;
	}
};
```

## 400. Nth Digit

 Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

1~num的数列，求第n个数字（10分为两个数字，1和0）。

先要确定第n的数字对应的num是一个几位数。根据1位数有 9 \*1 ，2位数有 2\* 90,n位数有n\*9\*10^\(n-1\)个数，可以确定是一个几位数。然后再确定是哪一个数，根据\(n-1\)/base的值加上n位数第一个数，就可以得到结果。然后再通过\(n-1\)%base可以得到是这个数的哪一位。

```cpp
class Solution
{
  public:
	int findNthDigit(int n)
	{
		long long base = 1;
		long long ten = 1;
		while (9 * base * ten < n)
		{
			n -= 9 * base * ten;
			base++;
			ten *= 10;
		}
		int num = ten;
		num += (n - 1) / base;
		string temp = to_string(num);
		return temp[(n - 1) % base] - '0';
	}
};
```

##  458. Poor Pigs

 There are 1000 buckets, one and only one of them contains poison, the rest are filled with water. They all look the same. If a pig drinks that poison it will die within 15 minutes. What is the minimum amount of pigs you need to figure out which bucket contains the poison within one hour.

有1000个水桶，其中只有一桶水是有毒的。一只猪会在喝了水之后的15分钟死亡，问最少需要多少头猪能够在1小时之内找到有毒的水桶。

这可以看成一个编码问题，给定的测试时间和猪的死亡时间确定了编码的维度，本题是60/15+1 = 5。而多少头猪则代表码长，水桶数量是要表示的数。5^4&lt;1000 &lt; 5^5，所以至少需要5头猪。

```cpp
class Solution
{
  public:
	int poorPigs(int buckets, int minutesToDie, int minutesToTest)
	{
		int pigs = 0;
		int base = (minutesToTest / minutesToDie + 1);
		int count = 1;
		while (count < buckets)
		{
			count *= base;
			pigs++;
		}

		return pigs;
	}
};
```

## 633. Sum of Square Numbers

判断一个整数c能否拆分成两个数的平方和。

设两个数为left，right且left&lt;=right。left为最小值0，right为最大数sqrt\(c\)+1。

当Left和right的平方和为c，返回true，如果小于c，则增加较小的数left，如果大于c，就减小较大的数。

```cpp
bool judgeSquareSum(int c)
{

	int left, right;

	left = 0;
	right = sqrt(c) + 1;
	while (left <= right)
	{
		if (left * left + right * right == c)
			return true;
		if (left * left + right * right < c)
			left++;
		else
			right--;
	}

	return false;
}
```

##  836. Rectangle Overlap

判断两个矩形是否重叠。注意等号（点或者边重合的情况）

```cpp
class Solution
{
  public:
    bool isRectangleOverlap(vector<int> &rec1, vector<int> &rec2)
    {

        if (rec1[3] <= rec2[1] || rec1[2] <= rec2[0] || rec1[0] >= rec2[2] || rec1[1] >= rec2[3])
            return false;
        else
            return true;
    }
};
```

## Medium

##  36. Valid Sudoku

判断一个数独是否合法。即每一行，每一列，和9个九宫格里面1-9都不重复。

定义三个数组分别来记录这三种情况。读入一个数后，就将对应的三个条件的used数组置为1，表示该数字已经出现过了，如果之后再出出现，就发生了重复，不满足要求，返回false。

```cpp
class Solution
{
  public:
    bool isValidSudoku(vector<vector<char>> &board)
    {

        vector<vector<int>> used1(9, vector<int>(9, 0));
        vector<vector<int>> used2(9, vector<int>(9, 0));
        vector<vector<int>> used3(9, vector<int>(9, 0));

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '1';
                    int pos = i / 3 * 3 + j / 3;

                    if (used1[i][num] || used2[j][num] || used3[pos][num])
                        return false;

                    used1[i][num] = used2[j][num] = used3[pos][num] = 1;
                }
            }
        }

        return true;
    }
};
```

##  223. Rectangle Area

给定两个矩形（左下、右上坐标），计算重叠后的面积。

计算重叠部分面积，如果为0那么直接相加两个矩形面积，如果不为0，再减去重叠部分面积。

```cpp
class Solution
{
  public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H)
    {

        int x1 = max(A, E);
        int x2 = min(C, G);
        int y1 = max(B, F);
        int y2 = min(D, H);
        if (x1 >= x2 || y1 >= y2)
            return (C - A) * (D - B) + (G - E) * (H - F);
        else
            return (C - A) * (D - B) + (G - E) * (H - F) - (x2 - x1) * (y2 - y1);
    }
};
```

##  264. Ugly Number II

所有由2，3，5构成的数组成的递增序列。

```cpp
class Solution
{
  public:
    int nthUglyNumber(int n)
    {

        vector<int> ugly(3, 0);
        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++)
        {
            int v2 = dp[ugly[0]] * 2;
            int v3 = dp[ugly[1]] * 3;
            int v5 = dp[ugly[2]] * 5;
            int v = min(v2, min(v3, v5));
            dp[i] = v;
            if (v == v2)
                ugly[0]++;
            if (v == v3)
                ugly[1]++;
            if (v == v5)
                ugly[2]++;
        }

        return dp[n - 1];
    }
};
```

##  396. Rotate Function

运用数学公式，可以将复杂度降低至O\(n\)

dp\(i\) = dp\(i-1\) + sum - nA\[i-1\]

```cpp
class Solution
{
  public:
	int maxRotateFunction(vector<int> &A)
	{
		if (A.size() == 0)
			return 0;
		vector<int> dp(A.size(), 0);
		int sum = 0;
		for (int i = 0; i < A.size(); i++)
		{
			sum += A[i];
			dp[0] += i * A[i];
		}
		int ret = dp[0];
		for (int i = 1; i < A.size(); i++)
		{
			dp[i] = dp[i - 1] - A.size() * A[A.size() - i] + sum;
			if (dp[i] > ret)
				ret = dp[i];
		}
		return ret;
	}
};
```

##  413. Arithmetic Slices

求一个数列中有多少个等差数列子列。

找到一个等差数列，求其长度，就能够算出有多少个子列。

```cpp
class Solution
{
  public:
	int numberOfArithmeticSlices(vector<int> &A)
	{
		if (A.size() <= 2)
			return 0;
		int ret = 0;
		int length = 2;
		for (int i = 0; i < A.size() - 2; i++)
		{
			if (A[i + 2] - A[i + 1] == A[i + 1] - A[i])
			{
				length++;
			}
			else
			{
				ret += (length - 2) * (length - 1) / 2;

				length = 2;
			}
		}

		return ret + (length - 2) * (length - 1) / 2;
		;
	}
};
```

##  470. Implement Rand10\(\) Using Rand7\(\)

如何用rand7\(\)得到rand10\(\)。通过rand7可以得到rand49。对于rand49，我们进行判断，只取0-39，这样得到的是rand40，而rand40%4即可得到0-9，再加1即是rand10\(\)。

```cpp
class Solution
{
public:
	int rand10()
	{
		int result = 40;
		while (result >= 40)
		{
			result = 7 * (rand7() - 1) + (rand7() - 1);
		}
		return result % 10 + 1;
	}
};
```

