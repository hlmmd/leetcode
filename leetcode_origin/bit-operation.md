# Bit operation

##  136. Single Number

 Given a **non-empty** array of integers, every element appears _twice_ except for one. Find that single one.

一串数字中只有一个数出现了1次，其他出现了2次，求这个出现1次的数。

运用异或运算的特性。

$$
(a⊕b)⊕b = a⊕(b⊕b) = a⊕0 = a
$$

将数组中所有的数异或，最终结果就是出现1次的数。

```cpp
class Solution
{
  public:
	int singleNumber(vector<int> &nums)
	{
		int ret = 0;
		for (auto num : nums)
			ret ^= num;
		return ret;
	}
};
```

##  231. Power of Two

运用结论 \(n&\(n-1\)\)==0

```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n>0 && (n&(n-1))==0;
    }
};
```

##  371. Sum of Two Integers

 Calculate the sum of two integers a and b, but you are **not allowed** to use the operator `+` and `-`.

不用+ - 运算符实现两数相加。

[https://leetcode.com/problems/sum-of-two-integers/discuss/84278/A-summary:-how-to-use-bit-manipulation-to-solve-problems-easily-and-efficiently](https://leetcode.com/problems/sum-of-two-integers/discuss/84278/A-summary:-how-to-use-bit-manipulation-to-solve-problems-easily-and-efficiently)

先不考虑进位，直接相加。比特位的相加就是异或^，然后再计算进位，因为只有两个1相加，才会产生进位，所以用&运算符，并左移一位，再重复一遍相加的过程，直到不再产生进位为止。

```cpp
class Solution
{
  public:
	int getSum(int a, int b)
	{
		int sum = a;

		while (b != 0)
		{
			sum = a ^ b;	  
			b = (a & b) << 1; 
			a = sum;		 
		}

		return sum;
	}
};
```

##  405. Convert a Number to Hexadecimal

将十进制转换成十六进制。

从比特位考虑，每4个比特位对应一个16进制数，所以用0xf与上num，就能得到末位的16进制数，然后再将num右移，可以得到倒数第二位，以此类推，直到Num为0或者全部转换。

```cpp

class Solution
{
  public:
	const string HEX = "0123456789abcdef";
	string toHex(int num)
	{
		if (num == 0)
			return "0";
		string result;
		int count = 0;
		while (num && count++ < 8)
		{
			result = HEX[(num & 0xf)] + result;
			num >>= 4;
		}
		return result;
	}
};
```

##  461. Hamming Distance

求汉明距离。

```cpp
class Solution
{
  public:
	int hammingDistance(int x, int y)
	{

		int ret = 0;
		int v = x ^ y;
		for (int i = 0; i < 32; i++)
		{
			ret += v & 1;
			v >>= 1;
		}
		return ret;
	}
};
```

##  476. Number Complement

 Given a positive integer, output its complement number. The complement strategy is to flip the bits of its binary representation.

给一个正整数，求它的complement number（不考虑前导零）

 5 is 101 \(no leading zero bits\), and its complement is 010. 

先要求出有多少个前导零，用全1（~0）作为mask，mask&num如果不为零，说明num中存在1，将mask左移，即mask前半部分都是1，后半部分都是0，如果mask&num为0，说明mask中1的个数与num前导零的个数相同。最后，在将mask和num求反，二者相与即可得到答案。

```cpp
class Solution
{
  public:
	int findComplement(int num)
	{

		int mask = ~0;

		while (mask & num)
			mask <<= 1;

		return ~mask & ~num;
	}
};
```

##  693. Binary Number with Alternating Bits

一个数的二进制是0、1相间的。

如果满足条件，那么这个数n ，和n右移一位n&gt;&gt;1的异或结果应该是前几位全0之后全1，即00000...1111...

满足这个条件的数又满足 t&\(t+1\)==0

```cpp
class Solution
{
  public:
	bool hasAlternatingBits(int n)
	{
		int t = n ^ n >> 1;
		return !(t & (t + 1));
	}
};
```

## 696. Count Binary Substrings

数字符串的子串中，01个数相同的子串个数，且是连续的0和连续的1。

```cpp
class Solution
{
  public:
	int countBinarySubstrings(string s)
	{
		int ret = 0;
		int pre = 0, len = 1;
		for (int i = 0; i < s.length(); i++)
		{
			if (i < s.length() - 1 && s[i + 1] == s[i])
				len++;
			else
			{
				ret += min(pre, len);
				pre = len;
				len = 1;
			}
		}

		return ret;
	}
};
```

## Medium

##  201. Bitwise AND of Numbers Range

当m和n不同时，连续AND操作一定会最后一位变成0。

所以我们持续将m n 右移，直到mn相等，此时AND的结果就是m，再将m左移回原来的数值。

```cpp
class Solution
{
  public:
    int rangeBitwiseAnd(int m, int n)
    {

        if (m == 0)
            return 0;

        int factor = 1;
        while (m != n)
        {
            m >>= 1;
            n >>= 1;
            factor <<= 1;
        }

        return m * factor;
    }
};
```

##  338. Counting Bits

数0-n所有数的二进制表示中1的个数。

```cpp
class Solution
{
  public:
	vector<int> countBits(int num)
	{

		vector<int> ret(num + 1, 0);

		for (int i = 1; i <= num; i++)
		{
			ret[i] = ret[i >> 1] + i % 2;
		}
		return ret;
	}
};
```

##  421. Maximum XOR of Two Numbers in an Array

