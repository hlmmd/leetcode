# mysql技术内幕

## MySQL体系结构和存储引擎

### 数据库和数据库实例

* 数据库：主要指文件，是文件的集合
* 数据库实例：Mysql数据库进程

mysql是单进程、多线程的数据库

Mysql启动后，先读取配置文件，如果没有配置文件，则会按照编译时的默认参数启动

### Mysql体系结构

Mysql由以下几部分组成

* 连接池组件
* 管理服务和工具组件
* SQL接口组件
* 查询分析器组件
* 优化器组件
* 缓冲组件
* 插件式存储引擎
* 物理文件

### Mysql存储引擎

#### InnoDB

面向在线事务处理（OLTP）

特点：支持事务，行锁设计、支持外键、非锁定读、多版本并发控制（MVCC，以获得高并发性）、四种隔离级别

InnoDB采用了聚集方式，每张表的存储都是按主键顺序进行存放的，如果没有显示定义主键，则生成一个6字节的ROWID，作为主键

#### MyISAM 存储引擎

不支持事务，表级锁，支持全文索引，面向OLAP

#### NDB

数据存放在内存中

#### Memory

数据存放在内存，使用哈希索引

### 连接Mysql

TCP/IP

连接时会检查一张权限视图，用来判断客户端IP是否允许连接到Mysql实例。

Unix套接字

主要用于本地连接

## Innodb存储引擎

InnoDB是事务安全的存储引擎，第一个完整支持ACID，行级锁、MVCC、外键、非锁定读。具有高性能、高可用、高可拓展性。

### 后台线程

Master Thread：核心线程，负责将缓冲池中的数据异步刷新到磁盘

IO Thread：使用AIO，提高数据库性能

Purge Thread： 事务提交后，所使用的undolog不再需要，使用PurgeThread来回收。

### 内存

#### 缓冲池

InnoDB是基于磁盘存储的，将其中的记录按照页的方式进行管理。使用缓冲技术来提高性能。

简单来说，缓冲池就是一块内存区域。数据库的修改，会首先修改缓冲池中的页，再以一定的刷新频率刷新到磁盘上。刷新使用checkpoint机制。

InnoDB使用innodb_buffer_pool_size来设置缓冲池的大小。

缓冲池中的数据页类型由索引页、数据页、undo页、插入缓冲等。

缓冲池通过LRU来管理页。并且加入了midpoint位置，即新读取到的页，并不会直接放入LRU列表的首部，而是放入midpoint位置，默认是5/8。

LRU前面部分的页成为热端，如果将新的页直接放入首部，那么很可能将常用的页从LRU列表中删除，而在下一次读取该页的时候，需要重新访问磁盘。InnoDB设置了一个参数，来表示一个页表读取到midpoint多少次后，才会被加入到LRU列表的热端。

压缩页：将原本16KB的页压缩为1-8KB。对于这些压缩过的页，使用unzip_LRU进行管理。unzip_LRU通过**伙伴算法**从缓冲池中分配内存。

在LRU列表中的页被修改后，被称为脏页，即缓冲区的页和磁盘上的页数据不一致。此时会通过checkpoint技术将脏页刷新回磁盘。 Flush列表中保存了脏页。

### checkpoint技术

如果直接将缓冲区的新版本刷新到磁盘上，此时若发生宕机，那么会丢失数据。所以数据库采用了write ahead log策略。当事务提交时，先写重做日志，再修改页。可以通过重做日志恢复数据。

checkpoint主要解决三个问题：
* 缩短数据库恢复时间
* 缓冲池不够用时，将脏页刷新到磁盘
* 重做日志不可用时，刷新脏页

数据库宕机后，只需要重做checkpoint后的日志，缩短恢复时间。

缓冲池不够用时，LRU算法会溢出最少使用的页，如果此页为脏页，那么就强制执行checkpoint

InnoDB通过LSN（log sequence number)来标记版本，是一个8字节的数字。

checkpoint的不同之处有：每次刷新多少页，每次从哪里取脏页，以及什么时间触发checkpoint。

* Sharp Checkpoint：发生在数据库关闭时，将所有的脏页都刷新回磁盘。
* Fuzzy Checkpoint: 运行时使用。只刷新一部分脏页

发生Fuzzy Checkpoint的时刻：

* Master Thread Checkpoint
* FLUSH_LRU_LIST Checkponig
* Aysnc/Sync Flush Checkpoint
* Dirty Page too much Checkpont

Master Thread 会每秒和每十秒定时刷新一定数量的脏页到磁盘。异步操作。

FLUSH_LRU_LIST checkpoint是保证LRU列表中存在100个左右的空闲页可用。

Async/Sync Flush Checkpoint指的是重做日志文件不可用的情况，此时强制将一些页刷新回磁盘。保证重做日志的循环可利用性。

Dirty Page too much是指脏页数量过多，超过75%，会强制执行checkpoint。

### Master Thread工作方式

#### 老版本的Master Thread

Master Thread 具有最高的线程有限级别，其内部包括多个循环：主循环，后台循环，刷新循环，暂停循环。其状态在loop,background loop,flush loop,suspend loop中切换。

Loop是主循环，包括每秒和每十秒的操作。

每秒一次：

* 日志缓冲刷新到磁盘，即使事务还没有提交（总是）
* 合并插入缓冲（可能）
* 至多刷新100个InnoDB的缓冲池中的脏页到磁盘（可能）
* 如果没有用户活动，则切换到background loop（可能）

十秒一次：

* 刷新100个脏页到磁盘（可能的情况下）
* 合并之多5个插入缓冲（总是）
* 将日志缓冲刷新到日志（总是）
* 删除无用的undo页（总是）
* 刷新100个或10个脏页到磁盘（总是）

#### 新版本的Master Thread

旧版InnoDB引擎对IO有限制，在缓冲池向磁盘刷新的时候使用了一定的硬编码，（10，100等），这很大的限制了IO性能。尤其在写入密集的程序中，Master Thread会忙不过来。

### InnoDB关键特性

* 插入缓冲
* 两次写
* 自适应哈希索引
* 异步IO
* 刷新邻接页

#### 插入缓冲

Insert buffer 和数据页一样，是物理页的一个组成部分。

聚集索引和非聚集索引

聚集索引的键值决定了相对应的物理顺序。非聚集索引中逻辑顺序与磁盘上物理顺序不同。

索引的叶节点就是数据结点，而非聚集索引的叶节点仍然是索引结点，通过指针指向数据块。








## 