# 第一章

重构第一步：为即将修改的代码建立一套可靠的测试环境。



从代码中找到函数内部的局部变量和参数。

不会被修改的变量可以当做参数传入一个新的函数。

如果只有一个变量发生改变，可以作为返回值。

成员函数放置在其所使用的数据的所属对象内。

尽量去除没有意义的临时变量。

