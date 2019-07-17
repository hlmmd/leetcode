# socket 编程笔记

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