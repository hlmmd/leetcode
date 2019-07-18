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

