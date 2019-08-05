# linux 下C语言编程

## 创建守护进程

### 进程组

* 每个进程属于一个进程组
* 每个进程主都有一个进程组号，该号等于该进程组组长的PID号
* 一个进程只能为它自己或子进程设置进程组ID号

### 会话期

会话期(session)是一个或多个进程组的集合。

setsid()函数可以建立一个对话期

如果，调用setsid的进程不是一个进程组的组长，此函数创建一个新的会话期。

1. 此进程变成该对话期的首进程
2. 此进程变成一个新进程组的组长进程。
3. 此进程没有控制终端，如果在调用setsid前，该进程有控制终端，那么与该终端的联系被解除。 如果该进程是一个进程组的组长，此函数返回错误。
4. 先调用fork()然后exit()退出父进程，子进程一定不会是进程组组长，setsid函数一定能成功。

### 创建守护进程所需步骤：

1. 在父进程中执行fork并exit推出；
2. 在子进程中调用setsid函数创建新的会话；
3. 在子进程中调用chdir函数，让根目录 ”/” 成为子进程的工作目录；
4. 在子进程中调用umask函数，设置进程的umask为0；
5. 在子进程中关闭任何不需要的文件描述符

### 守护进程要fork两次的原因：

第一次fork：这里第一次fork的作用就是让shell认为这条命令已经终止，不用挂在终端输入上;再一个是为了后面的setsid服务，因为调用setsid函数的进程不能是进程组组长，如果不fork子进程，那么此时的父进程是进程组组长，无法调用setsid。所以到这里子进程便成为了一个新会话组的组长。

第二次fork：第2次fork不是必须的。也看到很多开源服务没有fork第二次。fork第二次主要目的是。防止进程再次打开一个控制终端。因为打开一个控制终端的前台条件是该进程必须是会话组长。再fork一次，子进程ID != sid（sid是进程父进程的sid）。所以也无法打开新的控制终端。

```c
int daemonize()
{
    int pid;
    pid = fork();
    if (pid > 0)
        exit(0);
    else if (pid < 0)
        exit(1);
    //创建会话期
    setsid();

    //fork 两次
    pid = fork();
    if (pid > 0)
        exit(0);
    else if (pid < 0)
        exit(1);

    //设置工作目录，设置为/tmp保证具有权限
    int ret = chdir("/tmp");
    if (ret != 0)
    {
        printf("chdir失败\n");
        return -1;
    }

    //设置权限掩码
    umask(0);

    //关闭已经打开的文件描述符
    for (int i = 0; i < getdtablesize(); i++)
        close(i);

    //忽略SIGCHLD信号，防止产生僵尸进程
    signal(SIGCHLD, SIG_IGN);
    return 1;
}
```

## 防止一个守护进程运行两次

解用linux fcntl文件锁。第一次运行进程时设置写锁，第二次运行的时候fcntl返回-1。

```c
int open_only_once()
{
    const char filename[] = "/tmp/naiveproxy.pid";
    int fd, val;
    char buf[10];
    //打开控制文件，控制文件打开方式：O_WRONLY | O_CREAT只写创建方式
    //控制文件权限：S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH用户、用户组读写权限
    if ((fd = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
        return -1;
    }
    // try and set a write lock on the entire file
    struct flock lock;
    //建立一个供写入用的锁
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    //以文件开头为锁定的起始位置
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    //结合lock中设置的锁类型，控制文件设置文件锁，此处设置写文件锁
    if (fcntl(fd, F_SETLK, &lock) < 0)
    {
        //如果获取写文件锁成功，则退出当前进程，保留后台进程
        if (errno == EACCES || errno == EAGAIN)
        {
            printf("naiveproxy has already run.\n");
            exit(0); // gracefully exit, daemon is already running
        }
        else
        {
            printf("file being used\n");
            return -1; //如果锁被其他进程占用，返回 -1
        }
    }
    // truncate to zero length, now that we have the lock
    //改变文件大小为0
    if (ftruncate(fd, 0) < 0)
        return -1;
    // and write our process ID
    //获取当前进程pid
    sprintf(buf, "%d\n", getpid());
    //将启动成功的进程pid写入控制文件
    if (write(fd, buf, strlen(buf)) != strlen(buf))
        return -1;
    // set close-on-exec flag for descriptor
    // 获取当前文件描述符close-on-exec标记
    if ((val = fcntl(fd, F_GETFD, 0)) < 0)
        return -1;

    val |= FD_CLOEXEC;
    //关闭进程无用文件描述符
    if (fcntl(fd, F_SETFD, val) < 0)
        return -1;
    // leave file open until we terminate: lock will be held
    return 0;
}
```

## 将二进制文件注册到service命令中。

在/etc/init.d/文件夹下添加文件。如 naiveproxy

修改权限`sudo chmod a+x naiveproxy`

```bash
#!/bin/bash
# naiveproxy
start() 
{
    naiveproxy
}

stop() 
{
    killall -9 $(pidof naiveproxy)	
}

case "$1" in
start)
    start
    ;;

stop)
    stop
    ;;

restart)
    stop
    start
    ;;

*)
    echo "Usage: $0 {start|stop|restart}"
    exit 0
    ;;

esac
exit 0
```

## 零拷贝技术

网络编程中，发送文件内容需要DMA读取硬盘内容到内存中，用户使用read将kernel中的数据读取到用户态buffer缓冲区中，再使用send将数据写入内核socket发送队列，再使用DMA送入网卡。

### mmap

通过mmap跳过用户态、内核态的转换。减少拷贝次数

### sendfile 系统调用

```
#include<sys/sendfile.h>
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
```

out_fd指向套接字，in_fd是一个可以mmap的fd，一般是文件。

不经过用户态，在内核中完成。

不需要将数据copy到socket缓冲区，而是直接从页缓冲区DMA送进网卡

### splice

```cpp
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <fcntl.h>
ssize_t splice(int fd_in, loff_t *off_in, int fd_out, loff_t *off_out, size_t len, unsigned int flags);
```

有一方必须是管道

