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

