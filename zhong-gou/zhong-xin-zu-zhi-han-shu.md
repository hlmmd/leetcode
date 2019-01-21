# 重新组织函数

## 6.1 Extract Method（提炼函数）

 把一段代码从原先函数中提取出来

动机：过长函数，一段需要注释才能看懂的代码

做法：创造一个新函数，并根据其用途来命名。

处理临时变量、局部变量。设置参数，返回值。

## 6.2 Inline Method 把一个函数调用替换为函数本体

## 6.3 Inline Temp 内联临时变量

去除临时变量

## 6.4 Replace Temp with Query以查询取代临时变量

将一个表达式提炼到一个独立的函数中去

## 6.5 Introduce Explaining Variable 引入解释性变量

## 6.6分解临时变量

不要对临时变量赋值多次。（循环、计算结果等除外）

临时变量应该根据其用途而命名、赋值，不要身兼多职。

## 6.7 Remove Assignments to Parameters 移除对参数的赋值

不要对参数的值做出修改。建立临时变量并赋值

## 6.8 Replace Method with Method Object 以函数对象取代函数

## 6.9 替换算法





