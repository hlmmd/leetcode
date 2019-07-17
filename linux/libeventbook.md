# libevent手册

## libevent manual

[官方手册](http://www.wangafu.net/~nickm/libevent-book/)

[手册github](https://github.com/nmathewson/libevent-book)

### 手册安装

```bash
# 源代码下载
git clone https://github.com/nmathewson/libevent-book
# 安装依赖
sudo apt install asciidoc
# 生成pdf文件
make LibeventBook.pdf
```

### Introduction

异步(asynchronous)IO引入

如果IO调用是同步(synchronous)的，调用时会阻塞直到该操作完成，或者等待了足够长的时间。比如在建立TCP连接时，调用connect进行三次握手，会给server发送SYN包请求连接，此时connect会阻塞到收到ACK+SYN包，或者等待足够长的时间才决定放弃。

下面是一个阻塞IO的示例。连接www.baidu.com并发送简单http请求，并打印相应。

```cpp
/* For sockaddr_in */
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>
/* For gethostbyname */
#include <netdb.h>

#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int c, char **v)
{
    const char query[] =
        "GET / HTTP/1.0\r\n"
        "Host: www.baidu.com\r\n"
        "\r\n";
    const char hostname[] = "www.baidu.com";
    struct sockaddr_in sin;
    struct hostent *h;
    const char *cp;
    int fd;
    ssize_t n_written, remaining;
    char buf[1024];

    /* Look up the IP address for the hostname.   Watch out; this isn't
       threadsafe on most platforms. */
    h = gethostbyname(hostname);
    if (!h) {
        fprintf(stderr, "Couldn't lookup %s: %s", hostname, hstrerror(h_errno));
        return 1;
    }
    if (h->h_addrtype != AF_INET) {
        fprintf(stderr, "No ipv6 support, sorry.");
        return 1;
    }

    /* Allocate a new socket */
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket");
        return 1;
    }

    /* Connect to the remote host. */
    sin.sin_family = AF_INET;
    sin.sin_port = htons(80);
    sin.sin_addr = *(struct in_addr*)h->h_addr;
    if (connect(fd, (struct sockaddr*) &sin, sizeof(sin))) {
        perror("connect");
        close(fd);
        return 1;
    }

    /* Write the query. */
    /* XXX Can send succeed partially? */
    cp = query;
    remaining = strlen(query);
    while (remaining) {
      n_written = send(fd, cp, remaining, 0);
      if (n_written <= 0) {
        perror("send");
        return 1;
      }
      remaining -= n_written;
      cp += n_written;
    }

    /* Get an answer back. */
    while (1) {
        ssize_t result = recv(fd, buf, sizeof(buf), 0);
        if (result == 0) {
            break;
        } else if (result < 0) {
            perror("recv");
            close(fd);
            return 1;
        }
        fwrite(buf, 1, result, stdout);
    }

    close(fd);
    return 0;
}
```

以上代码的所有调用都是阻塞的。在单用户单线程的情况下，这样并没有什么问题，但是如果需要读取两个输入，就不知道哪个输入会先获得输入，引起阻塞。

```cpp
/* This won't work. */
char buf[1024];
int i, n;
while (i_still_want_to_read())
{
    for (i = 0; i < n_sockets; ++i)
    {
        n = recv(fd[i], buf, sizeof(buf), 0);
        if (n == 0)
            handle_close(fd[i]);
        else if (n < 0)
            handle_error(fd[i], errno);
        else
            handle_input(fd[i], buf, n);
    }
}
```

上面这段代码并不起作用，因为如果fd[2]先收到消息，此时程序也会阻塞地等待fd[0]和fd[1]的消息直到完成。

可以用多线程来解决这个问题，为每个连接建立一个线程，这样阻塞就不会影响其他连接。

下面是一个基于fork的多进程程序。

```cpp
/* For sockaddr_in */
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 16384

char rot13_char(char c)
{
    /* We don't want to use isalpha here; setting the locale would change
     * which characters are considered alphabetical. */
    if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
        return c + 13;
    else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
        return c - 13;
    else
        return c;
}

void child(int fd)
{
    char outbuf[MAX_LINE + 1];
    size_t outbuf_used = 0;
    ssize_t result;

    while (1)
    {
        char ch;
        result = recv(fd, &ch, 1, 0);
        if (result == 0)
        {
            break;
        }
        else if (result == -1)
        {
            perror("read");
            break;
        }

        /* We do this test to keep the user from overflowing the buffer. */
        if (outbuf_used < sizeof(outbuf))
        {
            outbuf[outbuf_used++] = rot13_char(ch);
        }

        if (ch == '\n')
        {
            send(fd, outbuf, outbuf_used, 0);
            outbuf_used = 0;
            continue;
        }
    }
}

void run(void)
{
    int listener;
    struct sockaddr_in sin;

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(40713);

    listener = socket(AF_INET, SOCK_STREAM, 0);

#ifndef WIN32
    {
        int one = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif

    if (bind(listener, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("bind");
        return;
    }

    if (listen(listener, 16) < 0)
    {
        perror("listen");
        return;
    }

    while (1)
    {
        struct sockaddr_storage ss;
        socklen_t slen = sizeof(ss);
        int fd = accept(listener, (struct sockaddr *)&ss, &slen);
        if (fd < 0)
        {
            perror("accept");
        }
        else
        {
            if (fork() == 0)
            {
                child(fd);
                exit(0);
            }
        }
    }
}

int main(int c, char **v)
{
    run();
    return 0;
}
```

这个解决方案存在问题。创建进程（甚至线程）的代价是很大的，当然实际场景中会使用线程池来消除创建进程带来的系统开销，但是当程序需要同时处理成千上万个连接时，多线程的效率就很低了。

在unix系统中，可以通过非阻塞socket来实现IO复用。

```cpp
fcntl(fd, F_SETFL, O_NONBLOCK);
```

非阻塞socket调用时，将会立即执行或者返回一个错误码，告知当前该事件还不能完成。

```cpp
/* This will work, but the performance will be unforgivably bad. */
int i, n;
char buf[1024];
for (i = 0; i < n_sockets; ++i)
    fcntl(fd[i], F_SETFL, O_NONBLOCK);
while (i_still_want_to_read())
{
    for (i = 0; i < n_sockets; ++i)
    {
        n = recv(fd[i], buf, sizeof(buf), 0);
        if (n == 0)
        {
            handle_close(fd[i]);
        }
        else if (n < 0)
        {
            if (errno == EAGAIN)
                ; /* The kernel didn't have any data for us to read. */
            else
                handle_error(fd[i], errno);
        }
        else
        {
            handle_input(fd[i], buf, n);
        }
    }
}
```

以上程序能够满足异步处理各个连接，但是其性能很差。因为每次循环会进行系统调用，即使socket没有消息。所以，我们需要知道socket上是否有事件产生，然后再进行处理。

select是最早用于解决这一个问题的调用。select()会检测三个集合，可读、可写、异常。select会等待直到set中的某个socket就绪，然后set中的socket只包含这个就绪的socket。

```cpp
/* If you only have a couple dozen fds, this version won't be awful */
fd_set readset;
int i, n;
char buf[1024];
while (i_still_want_to_read())
{
    int maxfd = -1;
    FD_ZERO(&readset);
    /* Add all of the interesting fds to readset */
    for (i = 0; i < n_sockets; ++i)
    {
        if (fd[i] > maxfd)
            maxfd = fd[i];
        FD_SET(fd[i], &readset);
    }
    /* Wait until one or more fds are ready to read */
    select(maxfd + 1, &readset, NULL, NULL, NULL);
    /* Process all of the fds that are still set in readset */
    for (i = 0; i < n_sockets; ++i)
    {
        if (FD_ISSET(fd[i], &readset))
        {
            n = recv(fd[i], buf, sizeof(buf), 0);
            if (n == 0)
            {
                handle_close(fd[i]);
            }
            else if (n < 0)
            {
                if (errno == EAGAIN)
                    ; /* The kernel didn't have any data for us to read. */
                else
                    handle_error(fd[i], errno);
            }
            else
            {
                handle_input(fd[i], buf, n);
            }
        }
    }
}
```

基于select的ROT13

```cpp
/* For sockaddr_in */
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>
/* For fcntl */
#include <fcntl.h>
/* for select */
#include <sys/select.h>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MAX_LINE 16384

char rot13_char(char c)
{
    /* We don't want to use isalpha here; setting the locale would change
     * which characters are considered alphabetical. */
    if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
        return c + 13;
    else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
        return c - 13;
    else
        return c;
}

struct fd_state
{
    char buffer[MAX_LINE];
    size_t buffer_used;

    int writing;
    size_t n_written;
    size_t write_upto;
};

struct fd_state *
alloc_fd_state(void)
{
    struct fd_state *state = malloc(sizeof(struct fd_state));
    if (!state)
        return NULL;
    state->buffer_used = state->n_written = state->writing =
        state->write_upto = 0;
    return state;
}

void free_fd_state(struct fd_state *state)
{
    free(state);
}

void make_nonblocking(int fd)
{
    fcntl(fd, F_SETFL, O_NONBLOCK);
}

int do_read(int fd, struct fd_state *state)
{
    char buf[1024];
    int i;
    ssize_t result;
    while (1)
    {
        result = recv(fd, buf, sizeof(buf), 0);
        if (result <= 0)
            break;

        for (i = 0; i < result; ++i)
        {
            if (state->buffer_used < sizeof(state->buffer))
                state->buffer[state->buffer_used++] = rot13_char(buf[i]);
            if (buf[i] == '\n')
            {
                state->writing = 1;
                state->write_upto = state->buffer_used;
            }
        }
    }

    if (result == 0)
    {
        return 1;
    }
    else if (result < 0)
    {
        if (errno == EAGAIN)
            return 0;
        return -1;
    }

    return 0;
}

int do_write(int fd, struct fd_state *state)
{
    while (state->n_written < state->write_upto)
    {
        ssize_t result = send(fd, state->buffer + state->n_written,
                              state->write_upto - state->n_written, 0);
        if (result < 0)
        {
            if (errno == EAGAIN)
                return 0;
            return -1;
        }
        assert(result != 0);

        state->n_written += result;
    }

    if (state->n_written == state->buffer_used)
        state->n_written = state->write_upto = state->buffer_used = 0;

    state->writing = 0;

    return 0;
}

void run(void)
{
    int listener;
    struct fd_state *state[FD_SETSIZE];
    struct sockaddr_in sin;
    int i, maxfd;
    fd_set readset, writeset, exset;

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(40713);

    for (i = 0; i < FD_SETSIZE; ++i)
        state[i] = NULL;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    make_nonblocking(listener);

#ifndef WIN32
    {
        int one = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif

    if (bind(listener, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("bind");
        return;
    }

    if (listen(listener, 16) < 0)
    {
        perror("listen");
        return;
    }

    FD_ZERO(&readset);
    FD_ZERO(&writeset);
    FD_ZERO(&exset);

    while (1)
    {
        maxfd = listener;

        FD_ZERO(&readset);
        FD_ZERO(&writeset);
        FD_ZERO(&exset);

        FD_SET(listener, &readset);

        for (i = 0; i < FD_SETSIZE; ++i)
        {
            if (state[i])
            {
                if (i > maxfd)
                    maxfd = i;
                FD_SET(i, &readset);
                if (state[i]->writing)
                {
                    FD_SET(i, &writeset);
                }
            }
        }

        if (select(maxfd + 1, &readset, &writeset, &exset, NULL) < 0)
        {
            perror("select");
            return;
        }

        if (FD_ISSET(listener, &readset))
        {
            struct sockaddr_storage ss;
            socklen_t slen = sizeof(ss);
            int fd = accept(listener, (struct sockaddr *)&ss, &slen);
            if (fd < 0)
            {
                perror("accept");
            }
            else if (fd > FD_SETSIZE)
            {
                close(fd);
            }
            else
            {
                make_nonblocking(fd);
                state[fd] = alloc_fd_state();
                assert(state[fd]); /*XXX*/
            }
        }

        for (i = 0; i < maxfd + 1; ++i)
        {
            int r = 0;
            if (i == listener)
                continue;

            if (FD_ISSET(i, &readset))
            {
                r = do_read(i, state[i]);
            }
            if (r == 0 && FD_ISSET(i, &writeset))
            {
                r = do_write(i, state[i]);
            }
            if (r)
            {
                free_fd_state(state[i]);
                state[i] = NULL;
                close(i);
            }
        }
    }
}

int main(int c, char **v)
{
    setvbuf(stdout, NULL, _IONBF, 0);

    run();
    return 0;
}
```

select函数对socketfd有数量限制，默认1024。当socket过多时，遍历socket带来了非常大的开销，因为其操作复杂度是O(n)。

为了解决select存在的这一限制，不同操作系统有不同的解决方案，包括poll()，epoll()，kqueue()，evports,/dev/poll。除了poll之外，其他函数添加socket、删除socket、通知程序socket就绪都是O(1)复杂度。然而这些系统调用并不统一，在linux中，我们使用epoll，BSDs使用kqueue，等等。而libevent则为用户封装了接口，使其能够再不同的操作系统、平台下实现高性能IO。

下面利用libevent实现ROT13的server

```cpp
/* For sockaddr_in */
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>
/* For fcntl */
#include <fcntl.h>

#include <event2/event.h>

#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MAX_LINE 16384

void do_read(evutil_socket_t fd, short events, void *arg);
void do_write(evutil_socket_t fd, short events, void *arg);

char rot13_char(char c)
{
    /* We don't want to use isalpha here; setting the locale would change
     * which characters are considered alphabetical. */
    if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
        return c + 13;
    else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
        return c - 13;
    else
        return c;
}

struct fd_state
{
    char buffer[MAX_LINE];
    size_t buffer_used;

    size_t n_written;
    size_t write_upto;

    struct event *read_event;
    struct event *write_event;
};

struct fd_state *
alloc_fd_state(struct event_base *base, evutil_socket_t fd)
{
    struct fd_state *state = (struct fd_state *)malloc(sizeof(struct fd_state));
    if (!state)
        return NULL;
    state->read_event = event_new(base, fd, EV_READ | EV_PERSIST, do_read, state);
    if (!state->read_event)
    {
        free(state);
        return NULL;
    }
    state->write_event =
        event_new(base, fd, EV_WRITE | EV_PERSIST, do_write, state);

    if (!state->write_event)
    {
        event_free(state->read_event);
        free(state);
        return NULL;
    }

    state->buffer_used = state->n_written = state->write_upto = 0;

    assert(state->write_event);
    return state;
}

void free_fd_state(struct fd_state *state)
{
    event_free(state->read_event);
    event_free(state->write_event);
    free(state);
}

void do_read(evutil_socket_t fd, short events, void *arg)
{
    struct fd_state *state = (struct fd_state *)arg;
    char buf[1024];
    int i;
    ssize_t result;
    while (1)
    {
        assert(state->write_event);
        result = recv(fd, buf, sizeof(buf), 0);
        if (result <= 0)
            break;

        for (i = 0; i < result; ++i)
        {
            if (state->buffer_used < sizeof(state->buffer))
                state->buffer[state->buffer_used++] = rot13_char(buf[i]);
            if (buf[i] == '\n')
            {
                assert(state->write_event);
                event_add(state->write_event, NULL);
                state->write_upto = state->buffer_used;
            }
        }
    }

    if (result == 0)
    {
        free_fd_state(state);
    }
    else if (result < 0)
    {
        if (errno == EAGAIN) // XXXX use evutil macro
            return;
        perror("recv");
        free_fd_state(state);
    }
}

void do_write(evutil_socket_t fd, short events, void *arg)
{
    struct fd_state *state = (struct fd_state *)arg;

    while (state->n_written < state->write_upto)
    {
        ssize_t result = send(fd, state->buffer + state->n_written,
                              state->write_upto - state->n_written, 0);
        if (result < 0)
        {
            if (errno == EAGAIN) // XXX use evutil macro
                return;
            free_fd_state(state);
            return;
        }
        assert(result != 0);

        state->n_written += result;
    }

    if (state->n_written == state->buffer_used)
        state->n_written = state->write_upto = state->buffer_used = 1;

    event_del(state->write_event);
}

void do_accept(evutil_socket_t listener, short event, void *arg)
{
    struct event_base *base = (struct event_base *)arg;
    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);
    int fd = accept(listener, (struct sockaddr *)&ss, &slen);
    if (fd < 0)
    { // XXXX eagain??
        perror("accept");
    }
    else if (fd > FD_SETSIZE)
    {
        close(fd); // XXX replace all closes with EVUTIL_CLOSESOCKET */
    }
    else
    {
        struct fd_state *state;
        evutil_make_socket_nonblocking(fd);
        state = alloc_fd_state(base, fd);
        assert(state); /*XXX err*/
        assert(state->write_event);
        event_add(state->read_event, NULL);
    }
}

void run(void)
{
    evutil_socket_t listener;
    struct sockaddr_in sin;
    struct event_base *base;
    struct event *listener_event;

    base = event_base_new();
    if (!base)
        return; /*XXXerr*/

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(40713);

    listener = socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_socket_nonblocking(listener);

#ifndef WIN32
    {
        int one = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif

    if (bind(listener, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("bind");
        return;
    }

    if (listen(listener, 16) < 0)
    {
        perror("listen");
        return;
    }

    listener_event = event_new(base, listener, EV_READ | EV_PERSIST, do_accept, (void *)base);
    /*XXX check it */
    event_add(listener_event, NULL);

    event_base_dispatch(base);
}

int main(int c, char **v)
{
    setvbuf(stdout, NULL, _IONBF, 0);

    run();
    return 0;
}
```

### Preliminaries

libevent特性：

* Portability：可移植性
* Speed：快速、非阻塞的socket通信
* Scalability：支持成千上万的并发连接
* Convenience：编程简单、健壮性高

libevent构成：

* evutil:封装各个平台网络编程接口
* event and event_base: 提供用户编程API
* bufferevent: 读写事件通知
* evbuffer: bufferevent的buffer
* evhttp/evdns/evrpc: 简单的http/dns/rpc实现

### 创建event_base

每个event_base都会有一个方法，包括：

select、poll、epoll、kqueue、devpoll、evport、win32

event_base会选择当前平台支持的最快的方法。

当我们想对event_base进行设置时，需要使用event_config结构，通过event_base_new_with_config()函数修改当前的config。设置完成后调用event_config_free释放config结构体。

检查当前系统和libevent支持的函数类型：

```cpp
#include <stdio.h>
#include <event2/event.h>

int main()
{

    int i;
    const char **methods = event_get_supported_methods();
    printf("Starting Libevent %s. Available methods are:\n", event_get_version());
    for (i = 0; methods[i] != NULL; ++i)
    {
        printf("%s\n", methods[i]);
    }

    return 0;
}
```

检查当前系统和livevent支持的特性（ET模式、O(1)事件通知复杂度、FD type支持(不仅仅是socket))

```cpp
#include <stdio.h>
#include <event2/event.h>

int main()
{
    struct event_base *base;
    enum event_method_feature f;
    base = event_base_new();
    if (!base)
    {
        puts("Couldn't get an event_base!");
    }
    else
    {
        printf("Using Libevent with backend method %s.",
               event_base_get_method(base));
        f = (event_method_feature)event_base_get_features(base);
        if ((f & EV_FEATURE_ET))
            printf(" Edge-triggered events are supported.");
        if ((f & EV_FEATURE_O1))
            printf(" O(1) event notification is supported.");
        if ((f & EV_FEATURE_FDS))
            printf(" All FD types are supported.");
        puts("");
    }

    return 0;
}
```

### event loop

在初始化好了event_base并注册了一些events，开启事件循环。

```cpp
#define EVLOOP_ONCE
0x01
#define EVLOOP_NONBLOCK
0x02
#define EVLOOP_NO_EXIT_ON_EMPTY 0x04
int event_base_loop(struct event_base *base, int flags);
```

### event

libevent的基本单元是event。每个event包括：

* 一个等待读取或写入的fd
* 一个等待读取或写入的fd(仅用于ET模式)
* 计时器
* 信号
* user-triggered event

使用event_new创建一个新的event

```cpp
/*事件超时后激活*/
#define EV_TIMEOUT 0x01
/*可读事件激活*/
#define EV_READ 0x02
/*可写事件激活*/
#define EV_WRITE 0x04
/*检测信号*/
#define EV_SIGNAL 0x08
/*事件响应后不会被移除，不需要event_add*/
#define EV_PERSIST 0x10
/*ET 模式*/
#define EV_ET 0x20

typedef void (*event_callback_fn)(evutil_socket_t, short, void *);
struct event *event_new(struct event_base *base, evutil_socket_t fd,
                        short what, event_callback_fn cb,
                        void *arg);
void event_free(struct event *event);
```

* event_base: 新申请的event都会注册到event_base上
* evutil_socket_t fd:socketfd
* short what: 宏定义
* event_callback_fn cb:当事件发生时的回调函数
* void *arg:回调函数的参数

当事件响应后，需要使用event_add重新添加对该事件的监听。或者设置EV_PERSIST。

对于一些timeout-only的event，提供了一些宏定义

```cpp
#define evtimer_new(base, callback, arg) \
event_new((base), -1, 0, (callback), (arg))
#define evtimer_add(ev, tv) \
event_add((ev),(tv))
#define evtimer_del(ev) \
event_del(ev)
#define evtimer_pending(ev, tv_out) \
event_pending((ev), EV_TIMEOUT, (tv_out))
```

### 常用的函数和数据类型

#### evutil_socket_t

除了windows系统，所有的操作系统中socket都是一个int型。

```cpp
#ifdef WIN32
#define evutil_socket_t intptr_t
#else
#define evutil_socket_t int
#endif
```

#### 跨平台的timer函数

提供了获取系统时间、比较大小、重置等操作

```cpp
#define evutil_timercmp(tvp, uvp, cmp)
#define evutil_timerclear(tvp) /* ... */
#define evutil_timerisset(tvp) /* ... */
#define evutil_timeradd(tvp, uvp, vvp) /* ... */
#define evutil_timersub(tvp, uvp, vvp) /* ... */
int evutil_gettimeofday(struct timeval *tv, struct timezone *tz);
```

socket API 操作

string操作

随机数生成器

### bufferevent

传统socket通信的步骤包括：

* 我们将要写入socket的数据放入一个buffer中
* 等待连接可写
* 尽可能多地写数据
* 记录写过了多少数据，以及还有多少仍需要写入的，等到下一次可写就绪

bufferevent会在读取或者写入足够的数据后引发回调函数，而不是可写或者可读

### Evbuffer

libevent的evbuffer通过队列实现，在队尾添加数据，从队头取数据。

evbuffer不是线程安全的。

