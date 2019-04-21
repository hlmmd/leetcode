# SQL基础

[https://cyc2018.github.io/CS-Notes/#/notes/SQL](https://cyc2018.github.io/CS-Notes/#/notes/SQL)

## 注释符：三种方式。

```sql
# 注释
SELECT *
FROM mytable; -- 注释
/* 注释1
   注释2 */
```

## 数据库创建与使用：

```sql
CREATE DATABASE test;
USE test;
```

## 创建表

```sql
CREATE TABLE mytable (
  id INT NOT NULL AUTO_INCREMENT,
  col1 INT NOT NULL DEFAULT 1,
  col2 VARCHAR(45) NULL,
  col3 DATE NULL,
  PRIMARY KEY (`id`));
```

## 修改表

```sql
#添加列
ALTER TABLE mytable
ADD col CHAR(20);
#删除列
ALTER TABLE mytable
DROP COLUMN col;
#删除表
DROP TABLE mytable;
```

## 插入

```sql
#普通插入
INSERT INTO mytable(col1, col2)
VALUES(val1, val2);
#插入检索出来的数据

INSERT INTO mytable1(col1, col2)
SELECT col1, col2
FROM mytable2;
#将一个表的内容插入到一个新表

CREATE TABLE newtable AS
SELECT * FROM mytable;
```

## 更新

```sql
UPDATE mytable
SET col = val
WHERE id = 1;
```

## 删除

```sql
DELETE FROM mytable
WHERE id = 1;

#TRUNCATE TABLE 可以清空表，也就是删除所有行。
TRUNCATE TABLE mytable;
```

## 查询

### DISTINCT

相同值只会出现一次。它作用于所有列，也就是说所有列的值都相同才算相同。

```sql
SELECT DISTINCT col1, col2
FROM mytable;
```

### LIMIT

限制返回的行数。可以有两个参数，第一个参数为起始行，从 0 开始；第二个参数为返回的总行数。

```sql
#返回前 5 行：
SELECT *
FROM mytable
LIMIT 5;

SELECT *
FROM mytable
LIMIT 0, 5;
Copy to clipboardErrorCopied

#返回第 3 ~ 5 行：

SELECT *
FROM mytable
LIMIT 2, 3;
```

## 排序

* ASC ：升序（默认）
* DESC ：降序

可以按多个列进行排序，并且为每个列指定不同的排序方式

```sql
SELECT *
FROM mytable
ORDER BY col1 DESC, col2 ASC;
```

## 过滤

不进行过滤的数据非常大，导致通过网络传输了多余的数据，从而浪费了网络带宽。因此尽量使用 SQL 语句来过滤不必要的数据，而不是传输所有的数据到客户端中然后由客户端进行过滤。

```sql
SELECT *
FROM mytable
WHERE col IS NULL;
```

 WHERE 子句可用的操作符

| 操作符     | 说明       |
|---------|----------|
| =       | 等于       |
| <       | 小于       |
| >       | 大于       |
| <> !=   | 不等于      |
| <= !>   | 小于等于     |
| >= !<   | 大于等于     |
| BETWEEN | 在两个值之间   |
| IS NULL | 为 NULL 值 |

AND 和 OR 用于连接多个过滤条件。优先处理 AND，当一个过滤表达式涉及到多个 AND 和 OR 时，可以使用 () 来决定优先级，使得优先级关系更清晰。

IN 操作符用于匹配一组值，其后也可以接一个 SELECT 子句，从而匹配子查询得到的一组值。

NOT 操作符用于否定一个条件。

## 通配符

通配符也是用在过滤语句中，但它只能用于文本字段。

* % 匹配 >=0 个任意字符；
* _ 匹配 ==1 个任意字符；
* \[ \] 可以匹配集合内的字符，例如 [ab] 将匹配字符 a 或者 b。用脱字符 ^ 可以对其进行否定，也就是不匹配集合内的字符。

使用 Like 来进行通配符匹配。

```sql
SELECT *
FROM mytable
WHERE col LIKE '[^AB]%'; -- 不以 A 和 B 开头的任意文本
```

## 计算字段

在数据库服务器上完成数据的转换和格式化的工作往往比客户端上快得多，并且转换和格式化后的数据量更少的话可以减少网络通信量。

计算字段通常需要使用 AS 来取别名，否则输出的时候字段名为计算表达式。

```sql
SELECT col1 * col2 AS alias
FROM mytable;
```

CONCAT() 用于连接两个字段。许多数据库会使用空格把一个值填充为列宽，因此连接的结果会出现一些不必要的空格，使用 TRIM() 可以去除首尾空格。

```sql
SELECT CONCAT(TRIM(col1), '(', TRIM(col2), ')') AS concat_col
FROM mytable;
```

## 函数

| 函 数     | 说 明      |
|---------|----------|
| AVG()   | 返回某列的平均值 |
| COUNT() | 返回某列的行数  |
| MAX()   | 返回某列的最大值 |
| MIN()   | 返回某列的最小值 |
| SUM()   | 返回某列值之和  |

AVG() 会忽略 NULL 行。

使用 DISTINCT 可以让汇总函数值汇总不同的值。

```sql
SELECT AVG(DISTINCT col1) AS avg_col
FROM mytable;
```

### 文本处理

| 函数        | 说明      |
|-----------|---------|
| LEFT()    | 左边的字符   |
| RIGHT()   | 右边的字符   |
| LOWER()   | 转换为小写字符 |
| UPPER()   | 转换为大写字符 |
| LTRIM()   | 去除左边的空格 |
| RTRIM()   | 去除右边的空格 |
| LENGTH()  | 长度      |
| SOUNDEX() | 转换为语音值  |

### 日期和时间处理

| 函 数           | 说 明             |
|---------------|-----------------|
| AddDate()     | 增加一个日期（天、周等）    |
| AddTime()     | 增加一个时间（时、分等）    |
| CurDate()     | 返回当前日期          |
| CurTime()     | 返回当前时间          |
| Date()        | 返回日期时间的日期部分     |
| DateDiff()    | 计算两个日期之差        |
| Date_Add()    | 高度灵活的日期运算函数     |
| Date_Format() | 返回一个格式化的日期或时间串  |
| Day()         | 返回一个日期的天数部分     |
| DayOfWeek()   | 对于一个日期，返回对应的星期几 |
| Hour()        | 返回一个时间的小时部分     |
| Minute()      | 返回一个时间的分钟部分     |
| Month()       | 返回一个日期的月份部分     |
| Now()         | 返回当前日期和时间       |
| Second()      | 返回一个时间的秒部分      |
| Time()        | 返回一个日期时间的时间部分   |
| Year()        | 返回一个日期的年份部分     |

### 数值处理

| 函数     | 说明  |
|--------|-----|
| SIN()  | 正弦  |
| COS()  | 余弦  |
| TAN()  | 正切  |
| ABS()  | 绝对值 |
| SQRT() | 平方根 |
| MOD()  | 余数  |
| EXP()  | 指数  |
| PI()   | 圆周率 |
| RAND() | 随机数 |

## 分组

分组就是把具有相同的数据值的行放在同一组中。

可以对同一分组数据使用汇总函数进行处理，例如求分组数据的平均值等。

指定的分组字段除了能按该字段进行分组，也会自动按该字段进行排序。

```sql
SELECT col, COUNT(*) AS num
FROM mytable
GROUP BY col;
```

GROUP BY 自动按分组字段进行排序，ORDER BY 也可以按汇总字段来进行排序。

```sql
SELECT col, COUNT(*) AS num
FROM mytable
GROUP BY col
ORDER BY num;
```

WHERE 过滤行，HAVING 过滤分组，行过滤应当先于分组过滤。

```sql
SELECT col, COUNT(*) AS num
FROM mytable
WHERE col > 2
GROUP BY col
HAVING num >= 2;
```

分组规定：

* GROUP BY 子句出现在 WHERE 子句之后，ORDER BY 子句之前；
* 除了汇总字段外，SELECT 语句中的每一字段都必须在 GROUP BY 子句中给出；
* NULL 的行会单独分为一组；
* 大多数 SQL 实现不支持 GROUP BY 列具有可变长度的数据类型。

## 子查询

子查询中只能返回一个字段的数据。

可以将子查询的结果作为 WHRER 语句的过滤条件：

```sql
SELECT *
FROM mytable1
WHERE col1 IN (SELECT col2
               FROM mytable2);
```

下面的语句可以检索出客户的订单数量，子查询语句会对第一个查询检索出的每个客户执行一次：

```sql
SELECT cust_name, (SELECT COUNT(*)
                   FROM Orders
                   WHERE Orders.cust_id = Customers.cust_id)
                   AS orders_num
FROM Customers
ORDER BY cust_name;
```

# 连接

连接用于连接多个表，实现多个表查询操作，使用 JOIN 关键字，并且条件语句使用 ON 而不是 WHERE。

连接可以替换子查询，并且比子查询的效率一般会更快。

可以用 AS 给列名、计算字段和表名取别名，给表名取别名是为了简化 SQL 语句以及连接相同表。

## 内连接

 使用比较运算符（包括=、>、<、<>、>=、<=、!>和!<）进行表间的比较操作，查询与连接条件相匹配的数据。根据比较运算符不同，内连接分为等值连接和不等连接两种。使用 INNER JOIN 关键字。

```sql
SELECT A.value, B.value
FROM tablea AS A INNER JOIN tableb AS B
ON A.key = B.key;
```

可以不明确使用 INNER JOIN，而使用普通查询并在 WHERE 中将两个表中要连接的列用等值方法连接起来。

```sql
SELECT A.value, B.value
FROM tablea AS A, tableb AS B
WHERE A.key = B.key;
```

### 自连接
自连接可以看成内连接的一种，只是连接的表是自身而已。

一张员工表，包含员工姓名和员工所属部门，要找出与 Jim 处在同一部门的所有员工姓名。

子查询版本

```sql
SELECT name
FROM employee
WHERE department = (
      SELECT department
      FROM employee
      WHERE name = "Jim");
```

自连接版本

```sql
SELECT e1.name
FROM employee AS e1 INNER JOIN employee AS e2
ON e1.department = e2.department
      AND e2.name = "Jim";
```

### 自然连接

自然连接是把同名列通过等值测试连接起来的，同名列可以有多个。

内连接和自然连接的区别：内连接提供连接的列，而自然连接自动连接所有同名列。

```sql
SELECT A.value, B.value
FROM tablea AS A NATURAL JOIN tableb AS B;
```

## 外连接

分为左连接(left join)、右连接(right join)、全连接(full join)。

左连接：返回左表中的所有行，如果左表中行在右表中没有匹配行，则结果中右表中的列返回空值。

检索所有顾客的订单信息，包括还没有订单信息的顾客。

```sql
SELECT Customers.cust_id, Orders.order_num
FROM Customers LEFT OUTER JOIN Orders
ON Customers.cust_id = Orders.cust_id;
```

customers 表：

| cust_id | cust_name |
|---------|-----------|
| 1       | a         |
| 2       | b         |
| 3       | c         |

orders 表：

| order_id | cust_id |
|----------|---------|
| 1        | 1       |
| 2        | 1       |
| 3        | 3       |
| 4        | 3       |

结果：

| cust_id | cust_name | order_id |
|---------|-----------|----------|
| 1       | a         | 1        |
| 1       | a         | 2        |
| 3       | c         | 3        |
| 3       | c         | 4        |
| 2       | b         | NULL     |

全连接：返回左表和右表中的所有行。当某行在另一表中没有匹配行，则另一表中的列返回空值

### 交叉连接（CROSS JOIN）

也称迪卡尔积。后接WHERE，而不是ON

概念：不带WHERE条件子句，它将会返回被连接的两个表的笛卡尔积，返回结果的行数等于两个表行数的乘积（例如：T_student和T_class，返回4*4=16条记录），如果带where，返回或显示的是匹配的行数。

有where子句，往往会先生成两个表行数乘积的数据表，然后才根据where条件从中选择。

## 组合查询

使用 UNION 来组合两个查询，如果第一个查询返回 M 行，第二个查询返回 N 行，那么组合查询的结果一般为 M+N 行。

每个查询必须包含相同的列、表达式和聚集函数。

默认会去除相同行，如果需要保留相同行，使用 UNION ALL。

只能包含一个 ORDER BY 子句，并且必须位于语句的最后。

```sql
SELECT col
FROM mytable
WHERE col = 1
UNION
SELECT col
FROM mytable
WHERE col =2;
```

## 视图

视图是虚拟的表，本身不包含数据，也就不能对其进行索引操作。

对视图的操作和对普通表的操作一样。

视图具有如下好处：

* 简化复杂的 SQL 操作，比如复杂的连接；
* 只使用实际表的一部分数据；
* 通过只给用户访问视图的权限，保证数据的安全性；
* 更改数据格式和表示。

```sql
CREATE VIEW myview AS
SELECT Concat(col1, col2) AS concat_col, col3*col4 AS compute_col
FROM mytable
WHERE col5 = val;
```

## 存储过程

存储过程可以看成是对一系列 SQL 操作的批处理。

使用存储过程的好处：

* 代码封装，保证了一定的安全性；
* 代码复用；
* 由于是预先编译，因此具有很高的性能。

命令行中创建存储过程需要自定义分隔符，因为命令行是以 ; 为结束符，而存储过程中也包含了分号，因此会错误把这部分分号当成是结束符，造成语法错误。

包含 in、out 和 inout 三种参数。

给变量赋值都需要用 select into 语句。

每次只能给一个变量赋值，不支持集合的操作。

```sql
DELIMITER //
CREATE PROCEDURE myprocedure(OUT ret INT)
    BEGIN
        DECLARE y INT;
        SELECT SUM(col1)
        FROM mytable
        INTO y;
        SELECT y*y INTO ret;
    END //
DELIMITER ;

CALL myprocedure(@ret);
SELECT @ret;
```

## 游标

在存储过程中使用游标可以对一个结果集进行移动遍历。

游标主要用于交互式应用，其中用户需要对数据集中的任意行进行浏览和修改。

使用游标的四个步骤：

* 声明游标，这个过程没有实际检索出数据；
* 打开游标；
* 取出数据；
* 关闭游标；

```sql
DELIMITER //
CREATE PROCEDURE myprocedure(OUT ret INT)
    BEGIN
        DECLARE done BOOLEAN DEFAULT 0;

        DECLARE mycursor CURSOR
        FOR
        SELECT col1 FROM mytable;
        # 定义了一个 continue handler，当 sqlstate '02000' 这个条件出现时，会执行 set done = 1
        DECLARE CONTINUE HANDLER FOR sqlstate '02000' SET done = 1;

        OPEN mycursor;

        REPEAT
            FETCH mycursor INTO ret;
            SELECT ret;
        UNTIL done END REPEAT;

        CLOSE mycursor;
    END //
DELIMITER ;
```

## 触发器

触发器会在某个表执行以下语句时而自动执行：DELETE、INSERT、UPDATE。

触发器必须指定在语句执行之前还是之后自动执行，之前执行使用 BEFORE 关键字，之后执行使用 AFTER 关键字。BEFORE 用于数据验证和净化，AFTER 用于审计跟踪，将修改记录到另外一张表中。

INSERT 触发器包含一个名为 NEW 的虚拟表。

```sql
CREATE TRIGGER mytrigger AFTER INSERT ON mytable
FOR EACH ROW SELECT NEW.col into @result;

SELECT @result; -- 获取结果
```

DELETE 触发器包含一个名为 OLD 的虚拟表，并且是只读的。

UPDATE 触发器包含一个名为 NEW 和一个名为 OLD 的虚拟表，其中 NEW 是可以被修改的，而 OLD 是只读的。

MySQL 不允许在触发器中使用 CALL 语句，也就是不能调用存储过程。

## 事务管理

基本术语：

* 事务（transaction）指一组 SQL 语句；
* 回退（rollback）指撤销指定 SQL 语句的过程；
* 提交（commit）指将未存储的 SQL 语句结果写入数据库表；
* 保留点（savepoint）指事务处理中设置的临时占位符（placeholder），你可以对它发布回退（与回退整个事务处理不同）。

不能回退 SELECT 语句，回退 SELECT 语句也没意义；也不能回退 CREATE 和 DROP 语句。

MySQL 的事务提交默认是隐式提交，每执行一条语句就把这条语句当成一个事务然后进行提交。当出现 START TRANSACTION 语句时，会关闭隐式提交；当 COMMIT 或 ROLLBACK 语句执行后，事务会自动关闭，重新恢复隐式提交。

通过设置 autocommit 为 0 可以取消自动提交；autocommit 标记是针对每个连接而不是针对服务器的。

如果没有设置保留点，ROLLBACK 会回退到 START TRANSACTION 语句处；如果设置了保留点，并且在 ROLLBACK 中指定该保留点，则会回退到该保留点。

## 字符集

基本术语：

* 字符集为字母和符号的集合；
* 编码为某个字符集成员的内部表示；
* 校对字符指定如何比较，主要用于排序和分组。

除了给表指定字符集和校对外，也可以给列指定：

```sql
CREATE TABLE mytable
(col VARCHAR(10) CHARACTER SET latin COLLATE latin1_general_ci )
DEFAULT CHARACTER SET hebrew COLLATE hebrew_general_ci;
```

可以在排序、分组时指定校对：

```sql
SELECT *
FROM mytable
ORDER BY col COLLATE latin1_general_ci;
```

## 权限管理

MySQL 的账户信息保存在 mysql 这个数据库中。

```sql
USE mysql;
SELECT user FROM user;
```

### 创建账户

新创建的账户没有任何权限。

```sql
CREATE USER myuser IDENTIFIED BY 'mypassword';
```

### 修改账户名

```sql
RENAME myuser TO newuser;
```

### 删除账户

```sql
DROP USER myuser;
```

### 查看权限

```sql
SHOW GRANTS FOR myuser;
```

### 授予权限

账户用 username@host 的形式定义，username@% 使用的是默认主机名。

```sql
GRANT SELECT, INSERT ON mydatabase.* TO myuser;
```

### 删除权限

GRANT 和 REVOKE 可在几个层次上控制访问权限：

* 整个服务器，使用 GRANT ALL 和 REVOKE ALL；
* 整个数据库，使用 ON database.*；
* 特定的表，使用 ON database.table；
* 特定的列；
* 特定的存储过程。

```sql
REVOKE SELECT, INSERT ON mydatabase.* FROM myuser;
```

### 更改密码

必须使用 Password() 函数

```sql
SET PASSWROD FOR myuser = Password('new_password');
```

