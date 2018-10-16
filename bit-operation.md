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





