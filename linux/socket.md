# socket 编程笔记

基于ubuntu18.04

## 设置非阻塞socket

先用fcntl读出原来的opt值，用|运算修改，加上O_NONBLOCK属性，再用fcntl设置。

```cpp
int setnonblocking(int fd)
{
    int old_opt = fcntl(fd, F_GETFL);
    int new_opt = old_opt | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_opt);
    return old_opt;
}
```

## select

每次select返回后，set中的描述符只剩下需要相应的socket，所以在select前，需要把所有要监听的socket重新添加到set中。

在server中，需要accept新的connection并同时相应用户的数据，此时可以将listenfd和userfd同时加入select中，当listenfd可读时，说明有新的连接。然后再遍历除了listenfd的所有socket，相应用户数据。

## recv

recv非阻塞的socket的时候，当没有数据可读的时候，返回值<0时并且(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)的情况下认为连接是正常的，继续接收。

可以利用这一特性保证socket中的数据已经读完。

```cpp
while (1)
{
    memset(buf, 0, BUFFER_SIZE);
    int ret = recv(sockfd, buf, BUFFER_SIZE, 0);
    if (ret < 0)
    {
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
        {
            printf("read later\n");
            break;
        }
        close(sockfd);
        break;
    }
    else if (ret == 0)
    {
        close(sockfd);
    }
    else
    {
        printf("get %d bytes of content: %s\n", ret, buf);
    }
}
```

## epoll ET 模式下 accept的问题

多个连接同时到达，服务器的TCP就绪队列瞬间积累多个就绪连接，由于是边缘触发模式，epoll只会通知一次，accept只处理一个连接，导致TCP就绪队列中剩下的连接都得不到处理。

解决办法: 用while循环抱住accept调用，处理完TCP就绪队列中的所有连接后再退出循环。如何知道是否处理完就绪队列中的所有连接呢？accept返回-1并且errno设置为EAGAIN就表示所有连接都处理完。综合以上两种情况，服务器应该使用非阻塞地accept，accept在ET模式下的正确使用方式为：

```cpp
while (1)
{
    int connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlength);
    if (connfd < 0 && (errno == EAGAIN || errno == ECONNABORTED || errno == EPROTO || errno == EINTR))
        break;
    addfd(epollfd, connfd, true);
}
```

## 系统/进程打开最大文件数

ulimit -n 可以查看单个进程打开的最大描述符个数

在/etc/security/limits.conf 中修改

```bash
sudo vi /etc/security/limits.conf 
#添加：
* soft nofile 3000000
* hard nofile 3000000

sudo vi /etc/pam.d/common-session
#添加：
session required pam_limits.so

sudo gedit /etc/systemd/system.conf 
#设置
DefaultLimitNOFILE=3000000
```

/proc/sys/fs/file-max 中保存再系统所有进程总计可以打开的文件描述符数量

在/etc/sysctl.conf中修改

```bash
sudo vim /etc/sysctl.conf
加入以下内容，重启生效
fs.file-max=30000000
net.nf_conntrack_max = 30000000
net.netfilter.nf_conntrack_max = 30000000
```

## epoll内部数据结构

一块mmap区域，用于与内核交互

红黑树，存储event,O(logn)插入复杂度

链表，就绪句柄链表

## epoll压力测试

在使用epoll作为客户端进行压力测试时，由于客户端端口数限制，需要设置多个虚拟IP进行绑定，否则连接最多只能到达28230。


## shutdown() 与 close()

### close()函数

```c
#include<unistd.h>
int close(int sockfd);     //返回成功为0，出错为-1.
```

close 一个套接字的默认行为是把套接字标记为已关闭，然后立即返回到调用进程，该套接字描述符不能再由调用进程使用，也就是说它不能再作为read或write的第一个参数。**然而TCP将尝试发送已排队等待发送到对端的任何数据，发送完毕后发生的是正常的TCP连接终止序列。**

在多进程并发服务器中，父子进程共享着套接字，套接字描述符引用计数记录着共享着的进程个数，当父进程或某一子进程close掉套接字时，描述符引用计数会相应的减一，**当引用计数仍大于零时，这个close调用就不会引发TCP的四路握手断连过程。**


### shutdown()函数

```c
#include<sys/socket.h>
int shutdown(int sockfd,int howto);  //返回成功为0，出错为-1.
```

该函数的行为依赖于howto的值

1. SHUT_RD：值为0，关闭连接的读这一半。
2. SHUT_WR：值为1，关闭连接的写这一半。
3. SHUT_RDWR：值为2，连接的读和写都关闭。

终止网络连接的通用方法是调用close函数。但使用shutdown能更好的控制断连过程（使用第二个参数）。

### 两函数的区别

close与shutdown的区别主要表现在：

* close函数会关闭套接字ID，如果有其他的进程共享着这个套接字，那么它仍然是打开的，这个连接仍然可以用来读和写，并且有时候这是非常重要的 ，特别是对于多进程并发服务器来说。

* 而shutdown会切断进程共享的套接字的所有连接，不管这个套接字的引用计数是否为零，那些试图读得进程将会接收到EOF标识，那些试图写的进程将会检测到SIGPIPE信号，同时可利用shutdown的第二个参数选择断连的方式。

## inet_ntoa函数

用于将点分十进制转换成整数。

这个函数内部使用静态变量进行存储，是不可重的。例如当printf函数打印中调用了两次inet_ntoa，其结果会是一样的。

## linux 多进程文件锁

目前遇到一个问题：多个进程对同一个文件进行写操作，如何避免冲突。研究了一下，做个小结。

对于多进程写文件，主要有以下两种处理方式：

1.类似于Linux日志文件服务

启动一个logger进程，其他进程向logger发消息，即把数据发送给logger，由logger来写文件，这种方法最安全，但是实现上相对复杂

2.采用文件锁

对当前读写文件进行加锁处理，简单说下两种加锁方式：

flock()：文件级别的锁，针对整个文件进行加锁

fcntl()函数：段级别的锁，能够针对文件的某个部分进行加锁

另外，对于读写相对不很频繁，每次写入数据量比较小的这种情况，不加锁也可以接受，但打开文件操作时，必须启用O_APPEND选项，以免造成多个进程相互覆盖写入的情况。

在O_APPEND模式下，文件写入操作是这样的一个原子操作：将位置指针移动至文件末尾，写入数据。

## send返回-1的问题

可能是写缓冲区满了。也可能是非阻塞socket connect后，tcp连接尚未建立的情况下send