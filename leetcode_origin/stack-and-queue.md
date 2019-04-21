# Stack and Queue

## 20. Valid Parentheses

Given a string containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:

1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.

Note that an empty string is also considered valid.

给一串由括号组成的字符串，判断这些括号能否匹配。

用栈解决。如果是左括号，直接进栈。如果是右括号，则查看栈顶的左括号是否与之相匹配，如果不匹配返回false，匹配则出栈，继续检验。如果发现栈为空，则说明缺少左括号，不匹配。当整个字符串都处理过后，如果栈不为空，说明缺少右括号，返回false，为空返回true。

```cpp
class Solution {
public:
    bool isValid( string s )
    {
        stack<char> st;
        for ( int i = 0; s[i]; i++ )
        {
            if ( s[i] == '{' || s[i] == '[' || s[i] == '(' )
                st.push( s[i] );
            else {
                if ( st.empty() )
                    return(false);
                if ( st.top() == '{' && s[i] != '}' || st.top() == '[' && s[i] != ']' || st.top() == '(' && s[i] != ')' )
                    return(false);
                st.pop();
            }
        }

        return(st.empty() );
    }
};
```

##  155. Min Stack

 Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

设计一个栈，能够返回最小值。使用两个栈，一个专门存储最小值。

```cpp
class MinStack
{
  private:
	stack<int> s1;
	stack<int> s2;

  public:
	void push(int x)
	{
		s1.push(x);
		if (s2.empty() || x <= getMin())
			s2.push(x);
	}
	void pop()
	{
		if (s1.top() == getMin())
			s2.pop();
		s1.pop();
	}
	int top()
	{
		return s1.top();
	}
	int getMin()
	{
		return s2.top();
	}
};
```

##  456. 132 Pattern

重点是要找到s3,s3位于S1和S2之间，即第二大的数。使用一个栈来存储s3，从后忘前遍历数组，如果nums\[i\] 大于栈顶，就更新s3的值，如果nums\[i\]&lt;s3，即s1&lt;s3，那么必然存在s1&lt;s3&lt;s2。

```cpp
bool find132pattern(vector<int> &nums)
{
	int s3 = INT_MIN;
	stack<int> st;
	for (int i = nums.size() - 1; i >= 0; i--)
	{
		if (nums[i] < s3)
			return true;
		else
			while (!st.empty() && nums[i] > st.top())
			{
				s3 = st.top();
				st.pop();
			}
		st.push(nums[i]);
	}
	return false;
}
```

##  503. Next Greater Element II

使用堆栈。对于一个数，先将其入栈，下次循环开始时，先判断栈顶的数（即前一个数）是否比当前数num要小，如果小则next\[s.top\(\)\] = num;即num是其下一个数。因为原数组连成一个圈，所以i从0循环到2n，并做模运算。

```cpp
class Solution
{
  public:
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> next(n, -1);
        stack<int> s;
        for (int i = 0; i < n * 2; i++)
        {
            int num = nums[i % n];
            while (!s.empty() && nums[s.top()] < num)
            {
                next[s.top()] = num;
                s.pop();
            }
            if (i < n)
                s.push(i);
        }
        return next;
    }
};
```

##  622. Design Circular Queue

##  641. Design Circular Deque

##  735. Asteroid Collision

在最左边为负的行星和在右边为正的行星永远不会相撞。

使用一个栈来存储返回数组（不会发生碰撞的行星），当栈为空或者栈顶为负数（不管a\[i\]为正或负，都不会碰撞），当a\[i\]为正时，同样也不会碰撞。

只有当栈顶为正，且a\[i\]为负的时候，才会发生碰撞，那么判断碰撞之后留下的行星，或者全部消失，直接pop

```cpp
class Solution
{
  public:
    vector<int> asteroidCollision(vector<int> &a)
    {
        vector<int> s; 
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] > 0 || s.empty() || s.back() < 0)
                s.push_back(a[i]);
            else if (s.back() <= -a[i])
            {
                if (s.back() < -a[i])
                    i--;   
                s.pop_back();
            }                
        }
        return s;
    }
};
```

##  739. Daily Temperatures

ret\[i\]是T\[i\]到第一个T\[j\]满足T\[j\]&gt;T\[i\]的距离。

使用栈来保存下标，当T\[i\]比栈顶大的时候，就出栈找到下标，并赋值。

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
          stack<int> mystack ;
    vector<int> ret(T.size());
    for(int i = 0; i < T.size(); i++) {
        while(!mystack.empty() && T[i] > T[mystack.top()]) {
            int idx = mystack.top();
            mystack.pop();
            ret[idx] = i - idx;
        }
        mystack.push(i);
    }
    return ret;
    }
};
```

