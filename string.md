# String

### 28. Implement strStr\(\)

实现 strstr\(\)函数

当needle字符串为空的时候，返回0。

基本解法：brute force 滑动窗口。

```cpp
class Solution {
public:
	int strStr( string haystack, string needle )
	{
		if ( needle.length() == 0 )
			return(0);

		for ( int i = 0; haystack[i]; i++ )
		{
			for ( int j = 0;; j++ )
			{
				if ( needle[j] == 0 )
					return(i);
				if ( haystack[i + j] == 0 )
					return(-1);
				if ( haystack[i + j] != needle[j] )
					break;
			}
		}

		return -1;
	}
};
```

此外还有KMP算法、BM算法、Sunday算法用于解决该问题。

