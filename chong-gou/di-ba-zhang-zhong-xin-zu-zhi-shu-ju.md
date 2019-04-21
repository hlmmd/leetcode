# 第八章 重新组织数据

8.1 Self Encapsulate Filed 自封装字段

为字段建立取值/设值函数，并且只以这些函数来访问字段。

8.2 Replace Data Value with Object 以对象取代数据项

新建一个类，申明一个和要替换的数据项相同的字段，并加入取值设值函数，以及构造函数。

8.3 Change Value to Reference 将值对象改为引用对象

8.4 Change Reference to Value 将引用对象改为值对象

8.5 Replace Array with Objects 以对象取代数组

数组中的元素各自代表不同的东西。对数组中每一个元素，以一个字段来表示。

8.9 以字面常量取代魔法数

8.10 Encapsulate Field 封装字段

将public 字段申明为private

