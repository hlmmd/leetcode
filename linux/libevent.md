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

event_base的backend:libevent所使用的多路IO复用函数

event_base可以通过event_base_new()获得一个默认的event_base结构体。

如果我们要对event_base进行配置，只需要对event_config进行配置即可。

可以配置拒绝使用某个backend，如select和poll。event_config_avoid_method

三种特性，不同backend支持的特性可以在对应的.c文件中找到。如select支持EV_FEATURE_FDS，而epoll支持EV_FEATURE_ET和EV_FEATURE_O1

```cpp
enum event_method_feature
{
    //支持边沿触发
    EV_FEATURE_ET = 0x01,
    //添加、删除、或者确定哪个事件激活这些动作的时间复杂度都为O(1)
    //select、poll是不能满足这个特征的.epoll则满足
    EV_FEATURE_O1 = 0x02,
    //支持任意的文件描述符,而不能仅仅支持套接字
    EV_FEATURE_FDS = 0x04
};
```

## 跨平台Reactor接口的实现

```cpp
struct event_base
{
    const struct eventop *evsel;
    void *evbase;
    // ...
};
struct eventop
{
    const char *name; //多路IO复用函数的名字
    void *(*init)(struct event_base *);
    int (*add)(struct event_base *, evutil_socket_t fd, short old,
               short events, void *fdinfo);
    int (*del)(struct event_base *, evutil_socket_t fd, short old,
               short events, void *fdinfo);
    int (*dispatch)(struct event_base *, struct timeval *);
    void (*dealloc)(struct event_base *);
    int need_reinit; //是否要重新初始化
    //多路IO复用的特征。参考http://blog.csdn.net/luotuo44/article/detai
    ls / 38443569 enum event_method_feature features;
    size_t fdinfo_len; //额外信息的长度。有些多路IO复用函数需要额外的信息
};
```
   
event_base中，首先有一个eventop结构体指针。

而eventop结构体制中，定义了每个backend方法的名字、初始化、add、del、dispatch等操作。

event_base如何选择自己的backend方法？

通过宏定义先定义当前平台支持的backend的结构体，再通过宏定义定义一个数组，将所有支持的结构体放入其中，效率高的在前。

在选取的时候，从0开始循环，直到找到一个可用的backend。

像select、poll、epoll之类多路IO复用函数在调用时要传入一些数据,比如监听的文件描述符fd,监听的事件有哪些。在Libevent中,这些数据都不是保存在event_base这个结构体中的,而是存放在evbase这个指针指向的一个结构体中。

## libevent工作流程

```cpp
#include <unistd.h>
#include <stdio.h>
#include <event.h>
void cmd_cb(int fd, short events, void *arg)
{
    char buf[1024];
    printf("in the cmd_cb\n");
    read(fd, buf, sizeof(buf));
}
int main()
{
    //使用默认的event_base配置
    struct event_base *base = event_base_new();
    struct event *cmd_ev = event_new(base, STDIN_FILENO,
                                     EV_READ | EV_PERSIST, cmd_cb,
                                     NULL);
    event_add(cmd_ev, NULL); //没有超时
    event_base_dispatch(base);
    return 0;
}
```

创建event_base

event_new创建event，event_new调用event_assign。event不同既监听读写，又监听信号。二者实现方法相斥。

将event加入event_base中，涉及加锁操作。event_add是线程安全的。将event插入到eventqueue队列。

event_base_dispatch进入主循环，开始监听event。该函数在循环外进行加锁。

当监听事件发生后，需要将已激活event插入到激活队列。

以poll为例，当主线程从poll返回时,没有错误的话,就说明有些监听的事件发生了。在函数的后面,它会遍历这个pollfd数组,查看哪个fd是有事件发生。如果事件发生,就调用evmap_io_active(base, event_set[i].fd, res);在这个函数里面会把这个fd对应的event放到event_base的激活event队列中。

evmap_io_active将激活的事件放入事件队列中。

处理激活列表中的event

遍历激活数组队列,把所有激活的event都处理即可。

event_process_active从高优先级遍历队列数组，对与每一个event，调用event_process_active_single_queue


