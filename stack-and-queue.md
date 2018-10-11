# Stack and Queue



### 20. Valid Parentheses

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

