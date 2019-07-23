# [google-talk-pdf](https://www.openonload.org/openonload-google-talk.pdf)

 [video](https://www.youtube.com/watch?v=1Y8hoznuuuM)

## 传统网络架构

![1](../asset/openonload_1.jpg)

## 将网络协议栈放到用户态中处理的一些问题

* 应用程序退出后，协议栈相关调用还未结束 send exit
* 异步问题
* 可能被销毁 exec
* 协议栈状态被共享 fork exec (SOL_SOCKET/SCM_RIGHT )
* 同步问题（ARP，IP）

* may persist longer than the application (send; exit )
* may require asynchronous advancement (TCP_ACK within TMO)
* may be destroyed (exec)
* may be shared (fork; exec ) (SOL_SOCKET/SCM_RIGHT )
* may need to be synchronized (ARP, IP ROUTE)
* may be modified by a corrupt / malicious application

可能的解决方案：

* push protocol state / processing into the network
* implement strict programming models (RDMA, Matched send/recv)

## OpenOnload Architecture

![openonload](../asset/openonload_2.jpg)

### A fully protected virtualized interface (V-NICS)

网卡硬件设备能提供一个用户安全的接口，将以太网包正确地送给相应的应用程序，基于headers中的流信息。

假设现在负载着许多不同的应用程序，需要一个hardware mapped (虚拟网卡->address space)，保证每个应用安全地收发包。即每个应用都不能DMA到其他人的address。

将这个网卡切分、虚拟化的功能由硬件保证。

Network hardware provides a user-safe interface which can route Ethernet packets to an application context based on flow information contained within headers

### protocol processing

协议栈处理过程既可以在用户态下完成，也可以在内核中进行。

例如当一个应用已经终止，但仍然存在需要处理的内容。

Protocol processing can take place both in the application and kernel context for a given flow

Enables persistent / asynchronous processing

Maintains existing network control-plane

### Protocol state

协议栈状态在用户和内核中通过共享内存进行共享。

因为可以同时在用户态和内核中处理，所以需要同步->共享内存。

Protocol state is shared between the kernel and application contexts through a protected shared memory communications channel

Enables correct handling of protocol state with high-performance

## Openonload Implementation

### 性能指标

#### CPU开销

从用户空间应用程序转入和转出内核是一项高开销的操作：相当于数百或数千条指令。对于传统网络，每次应用程序发送和接收数据时都需要进行转换。

使用Onload，TCP / IP处理可以完全在用户进程内完成，从而消除了应用程序/内核转换，即系统调用。此外，Onload TCP / IP堆栈经过高度调整，可进一步节省开销。 Onload的开销节省意味着更多的CPU计算能力可供应用程序执行有用的工作。

#### 延迟

传统网络应用中，当服务器应用程序准备好处理事务时，它调用OS内核来执行“接收”操作，其中内核将调用线程“休眠”直到请求从网络到达。当这样的请求到达时，网络硬件“中断”内核，内核接收请求并“唤醒”应用程序。所有这些开销都需要CPU周期以及增加缓存和转换后备缓冲区（TLB）占用空间。

使用Onload，应用程序可以保持在用户态，等待请求到达网络适配器并直接处理它们。消除内核态和用户态的转换、中断以及用户态到内核态的转换，这样可以显着减少延迟。简而言之，降低的开销意味着减少延迟。

#### 带宽

因为Onload减少了开销，所以它可以每秒处理更多字节的网络流量。除了`针对10千兆位网络设计的专门调整的缓冲和算法`外，Onload还允许应用程序显着提高带宽。在流量大的时候，带宽决定了延迟。（loss、TCP重传等会大大消耗带宽）

#### 可伸缩性

现代多核系统能够同时运行许多应用程序。但是，当多个内核竞争单个资源（例如内核网络堆栈或设备驱动程序中的锁定）时，优势很快就会丢失。在具有跨多个CPU内核和非统一内存架构的多个高速缓存的现代系统中，这些问题更加复杂。

Onload将网络适配器分区，并且每个分区都由TCP / IP堆栈的独立副本访问。 所以使用Onload，加倍核心的数量就可以加倍吞吐量。

当增加核心、内存、线程、sockets等资源时，开销如何变化？

### 内核协议栈剖析

![3](../asset/openonload_3.jpg)

左边是处在用户态的资源，右边是处于内核中的资源。

用户通过file descriptor table(用户态中通过整数来访问)，映射到内核中相关数据结构。

用户空间通过libc库与内核进行交互。这个库是一个自动加载的动态链接库，用于产生系统调用。

### 用户态协议栈剖析

![4](../asset/openonload_4.jpg)

本质上来说，是将协议栈放入用户空间内。

想要实现Os bypass，需要在用户空间接收发送包，因此协议栈需要能直接访问到网络适配器。这个网卡是虚拟化的接口，即V-NICs（Virtual Network Interface Controllers)。

需要intercept socket (用户调用的BSD socket API)，并要抢在系统的libc库之前完成。

在UNIX系统中，存在LD_PRELOAD功能，即优先加载指定的链接库，在所有其他的库之前。同时，设置的环境变量(export)是dominant的。这个库包含了read、write、send等所有标准的系统调用函数，同时将它们实现成用户空间协议栈。

需要对kernel files、sockets进行处理，所以有一个fd table。在这个例子中，有一个用户态的socket，其他的fd(0,1,2)仍然由内核处理。

### Direct & safe hardware access

![5](../asset/openonload_5.jpg)

如何实现安全的用户态网络硬件访问？

标准的NICs是无法实现该功能的。这个设备称为V-nics，需要完成接受、发送包并通知对应的应用程序。

并不是所有的包都会由用户态协议栈进行处理。

通过filters对包进行过滤，并找到对应的V-nics。

NIC可以实现多个V-nics，进而支持多个应用。

特别的，一些特殊的V-nics用被专门提供给kernel使用，用于处理标准协议栈。

descriptor rings包含了buffers的address(虚拟地址)，该地址是一种页表page table，进而解析这个地址，获得buffer在应用程序中的实际地址。

当包到达时，发送一个通知到notificaton queue，告知应用程序发生了什么。

收到包->filter->送到V-nic->descriptor rings->地址解析->notification queue->应用得知消息

发包的过程与收包相反（地址解析过程等）

doorbells用来实现通知硬件，在RX、TX环中加入了新的fd。

## Challenges for user-level networking

### exec()

系统调用exec是以新的进程去代替原来的进程，但进程的PID保持不变。因此，可以这样认为，exec系统调用并没有创建新的进程，只是替换了原来进程上下文的内容。原进程的代码段，数据段，堆栈段被新的进程所代替。

传统架构中，exec后内核中的所有内容不会消失，新加载的应用程序能够使用之前的fd，一切正常。

而对于user-level协议栈，不仅协议栈、socket、lib会丢失，而且即使重建了协议栈、libc、fd table等结构，也能重新建立和V-nics的连接，我们也无法获得之前的fd、协议栈状态该。

### fork()

 使用fork函数得到的子进程从父进程的继承了整个进程的地址空间，包括：进程上下文、进程堆栈、内存信息、打开的文件描述符、信号控制设置、进程优先级、进程组号、当前工作目录、根目录、资源限制、控制终端等。

 传统架构只需要复制一份指针，指向之前的socket，就能够实现共享socket。

 user-level协议栈会得到两份socket，两份protocol state，指向同一个V-nics。但这样两个进程是无法协作的，不知道互相的状态。

### 其他问题

* 文件描述符可以通过UNIX套接字传递给其他进程
* 当用户进程结束的时候，剩下的TCP链接能够被顺利shutdown(保证已经送至消息队列的数据被发送)
* 当进程不会频繁调用协议栈时（比如进程没有被调度或者当前没有任何网络操作），也需要能够及时地对网络事件作出响应。

* File descriptors (including sockets) can be passed through a UNIX domain socket to another process
* When a process exits, any remaining TCP connections must be shutdown gracefully
  * queued data must reach the receiver
* The process may not invoke the stack frequently  (because it is not scheduled, or just not doing any networking at the moment) but we must still respond to network events in a timely fashion

## implement requirements

* A user-level stack’s state must live outside the user-level
process
  * in order to survive exec()
  * so that sockets survive exit()
* Sockets must be represented in the kernel’s fdtable
  * to avoid clashes in the descriptor space
* State must be shareable
  * to support fork()
  * and passing sockets to other processes

## The openonload architecture

![6](../asset/openonload_6.jpg)

协议栈依然放在内核中。

分成两部分：

trust stack state: 只对内核可见
shared stack state: 用户态程序中能直接访问的部分

用户态可以通过mapping访问到shared stack state。

在trust stack state中，有由kernel fd table存放的socket，这是一个标准的内核结构体(file)，它拥有一个指向user-level socket的指针。

同时，用户态的FD table当然能直接找到user-level socket(这就是我们实现Intercept的地方)

### 解决fork()

![7](../asset/openonload_7.jpg)

### 解决exec()

stat() fd table : 判断出不是一个普通文件，也不是socekt，而是onload file。

mmap映射

## 协议栈共享的内容

Includes everything needed for the data-path:

* sockets
* packet buffers
* v-nic state
* demux table
* timers (retransmit, zwin-probes, keep-alive etc.)
* free resources
* statistics
* configuration

## Address spaces

```text
The shared state is mapped into the kernel and potentially multiple independent process address spaces
– so all ‘pointers’ are indirect
– packet buffers and sockets are identified by index
– more generally fields are identified by offset
• useful for complex data-structures such as timer wheels
 Untrusted user-space code may corrupt the state in arbitrary ways
– processes that share a stack must trust one-another
• if they can’t, then they mustn’t share a stack
Code running in the kernel must be careful when accessing shared state
```

## Protecting the kernel

```text
Trusted state – kernel only
– pointers to base of shared memory regions
– various dimensions and masks
– resources (wait-queues, demux filter etc.)
Protecting memory accesses
– pointers computed using inputs from shared state are made safe by
bounds checking or masking
Avoiding excessive resource consumption
– loops are bounded (using bounds from trusted state)
```

## Control plane

```text
ARP table, routing table and interface table
– single copy shared by all stacks
– mapped read-only into user-space
– protected with generation counters
– TCP sockets cache their route and layer-2 headers
• validation is just a single compare of a generation counter in the ARP
table (no bus-locked instructions)
– any updates cause generation counters of potentially affected entries
in the ARP table to be bumped
• which pushes potentially affected parties to do a full lookup
– synchronised with Linux via netlink sockets
```

## parallel stack

* 一开始并不知道我们会使用哪一个接口去创建socket直到bound或者connected
  * 这个interface可能不是onload enabled的网卡
  * interface 可能改变
* 监听TCP sockets必须能够accept来自任何interface的连接
  * 不仅仅是支持onload的网卡
  * 包括loopback网卡
* UDP socket需要能够在多种设备上接收和发送
  * 包括loopback

```text
We don’t initially know which interface a socket will use until it is bound
or connected
– it might not be an interface that is “onload enabled”
– the interface can change
 Listening TCP sockets must be able to accept connections from any and
all interfaces
– not just those that are “onload enabled”
– including the loopback interface, even if bound to a specific IP
UDP sockets need to send and receive over multiple interfaces
– including loopback
```

## We need an O/S socket

为了支持以上特性，我们需要一个kernel socket

## Handling network events

```text
 The network controller sends and receives packets and delivers
notifications asynchronously
 In the traditional architecture, an interrupt is raised which invokes
the device driver, which processes notifications and passes
received packets to the stack
 Received data is queued at a socket, or copied into a user buffer
 Threads that are blocked waiting for received data (or buffer
space) may be woken
 The handling of network events is asynchronous with respect to
the behaviour of the application
```

## Handling network events in onload

```text
By default, interrupts are not enabled
Notifications are delivered to the notification queue,and ignored until…
stack_poll() {
reprime_hw_timer();
handle_network_events();
refill_rx_ring();
refill_tx_ring();
process_timers();
}
```
