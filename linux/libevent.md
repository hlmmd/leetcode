# libevent 库学习笔记

[github](https://github.com/libevent/libevent)

[官网地址](http://libevent.org/)

安装：

```bash
bash autogen.sh
./configure
make
sudo make install
sudo ldconfig
```

源代码分析版本：2.1.10

## event-config.h.cmake

定义了许多宏定义以达到跨平台的目的。

## 日志系统

event_warn、event_msgx、event_err等函数记录了一些出错的情况。

可用户自定义，通过回调函数实现

## 内存分配

libevent默认使用C语言的标准内存分配函数malloc/free等，用户可以自行定义，使用诸如内存池等。

## 多线程、锁、条件变量

定义在thead.h中。

libevent默认不开启多线程。但是用户可以自己定义。当libevent开启了多线程，libevent中的函数就变成了线程安全的。

libevent允许用户自定义锁结构，提供普通锁、递归锁、读写锁。

## queue.h

在compat/sys目录下，queue.h中定义了一些数据结构

TAILQ_QUEUE队列结构

链式存储结构，包括队头、队尾

每个结点都有一个next指针和一个pre指针。

```cpp
#define TAILQ_HEAD(name, type)						\
struct name {								\
	struct type *tqh_first;	/* first element */			\
	struct type **tqh_last;	/* addr of last next element */		\
}

#define TAILQ_HEAD_INITIALIZER(head)					\
	{ NULL, &(head).tqh_first }

#define TAILQ_ENTRY(type)						\
struct {								\
	struct type *tqe_next;	/* next element */			\
	struct type **tqe_prev;	/* address of previous next element */	\
}
```

## event_io_map哈希表

链地址法解决冲突。

只有在windows系统中会用到哈希表。因为其socket不是连续的。而posix的fd都是从0开始，连续的fd。

哈希函数：`h += (h >> 2) | (h << 30);`再%哈希表大小。

在使用event_add将event添加到event_base中，使用hash表

## event_signal_map

指针数组

signal类型很少POSIX只有32种，windows只有6种

实现比较简单

## event_bse




