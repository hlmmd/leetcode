# preload 实现

## /src/transport/unix/sys.c

注意宏定义`CI_MK_DECL`，代码中给出了多处实现。

syscal_unix.h

syscall.c

sys.c

给出一个定义后，会`# include <onload/declare_syscalls.h.tmpl>`来展开define，分别完成函数指针定义、赋值等操作

## onload/declare_syscalls.h.tmpl

涉及到的函数：

```c
CI_MK_DECL(int           , socket     , (int, int, int));
CI_MK_DECL(int           , bind       , (int, const struct sockaddr*, socklen_t));
CI_MK_DECL(int           , listen     , (int, int));
CI_MK_DECL(int           , shutdown   , (int, int));
CI_MK_DECL(int           , getsockname, (int, struct sockaddr*, socklen_t*));
CI_MK_DECL(int           , getpeername, (int, struct sockaddr*, socklen_t*));
CI_MK_DECL(int           , getsockopt , (int, int, int, void*, socklen_t*));
CI_MK_DECL(int           , setsockopt , (int, int, int, const void*, socklen_t));

CI_MK_DECL(ssize_t       , readv      , (int, const struct iovec*, int));
CI_MK_DECL(ssize_t       , writev     , (int, const struct iovec*, int));

CI_MK_DECL(int           , ioctl      , (int, unsigned long, ...));

CI_MK_DECL(int           , dup        , (int));
CI_MK_DECL(int           , dup2       , (int, int));

CI_MK_DECL(int           , accept     , (int, struct sockaddr*, socklen_t*));

CI_MK_DECL(int           , connect    , (int, const struct sockaddr*, socklen_t));
CI_MK_DECL(ssize_t       , recv       , (int s, void*, size_t, int));
CI_MK_DECL(ssize_t       , recvfrom   , (int, void*, size_t, int,
                                         struct sockaddr*, socklen_t*));

CI_MK_DECL(ssize_t       , recvmsg    , (int, struct msghdr*, int));

CI_MK_DECL(ssize_t       , send       , (int, const void*, size_t, int));
CI_MK_DECL(ssize_t       , sendto     , (int, const void*, size_t, int,
                                         const struct sockaddr*, socklen_t));
CI_MK_DECL(ssize_t       , sendmsg    , (int, const struct msghdr*, int));

CI_MK_DECL(ssize_t       , read       , (int, void*, size_t));

CI_MK_DECL(ssize_t       , write      , (int, const void*, size_t));

CI_MK_DECL(int           , close      , (int));
CI_MK_DECL(int           , fcntl      , (int, int, ...));
CI_MK_DECL(int           , poll       , (struct pollfd *, nfds_t, int));

CI_MK_DECL(int           , select     , (int, fd_set*, fd_set*, fd_set*, struct timeval*));
CI_MK_DECL(int           , pselect    , (int, fd_set*, fd_set*, fd_set*, const struct timespec*, const sigset_t *));

CI_MK_DECL(pid_t         , vfork      , (void));


CI_MK_DECL(int           , open       , (const char*, int, ...));
CI_MK_DECL(int           , creat      , (const char*, mode_t));

CI_MK_DECL(int           , setrlimit  , (__rlimit_resource_t, const struct rlimit *));

CI_MK_DECL(int           , __fxstat   , (int, int, struct stat *));

CI_MK_DECL(int           , open64     , (const char*, int, ...));
CI_MK_DECL(int           , creat64    , (const char*, mode_t));
CI_MK_DECL(int           , setrlimit64, (__rlimit_resource_t, const struct rlimit64 *));
CI_MK_DECL(int           , __fxstat64 , (int, int, struct stat64 *));


CI_MK_DECL(int           , socketpair , (int, int, int, int sv[2]));
CI_MK_DECL(int           , pipe       , (int fd[2]));

CI_MK_DECL(int           , setuid     , (uid_t));
CI_MK_DECL(int           , chroot     , (const char*));

CI_MK_DECL(int           , execve     , (const char*, char* const argv[], char* const envp[]));
CI_MK_DECL(int           , execl      , (const char*, const char*, ...));
CI_MK_DECL(int           , execlp     , (const char*, const char*, ...));
CI_MK_DECL(int           , execle     , (const char*, const char*, ...));
CI_MK_DECL(int           , execv      , (const char*, char *const argv[]));
CI_MK_DECL(int           , execvp     , (const char*, char *const argv[]));


#if CI_CFG_USERSPACE_EPOLL
#include <sys/epoll.h>
CI_MK_DECL(int           , epoll_create, (int));
#ifdef EPOLL_CLOEXEC
CI_MK_DECL(int           , epoll_create1, (int));
#endif
CI_MK_DECL(int           , epoll_ctl, (int, int, int, struct epoll_event *));
CI_MK_DECL(int           , epoll_wait, (int, struct epoll_event *, int, int));
#if CI_LIBC_HAS_epoll_pwait
CI_MK_DECL(int           , epoll_pwait, (int, struct epoll_event *, int, int, const sigset_t *));
#endif
#endif

#if CI_CFG_USERSPACE_SYSCALL
CI_MK_DECL(long          , syscall    , (long, ...));
#endif

```

## sockcall_intercept.c

具体实现。

```c
# define OO_INTERCEPT(ret, name, args)    ret onload_##name args

# define CI_MK_DECL(ret, fn, args)        strong_alias(onload_##fn, fn)
# include <onload/declare_syscalls.h.tmpl>
```

## 运行库

### 入口函数

程序被加载后，首先运行的不是main函数，在main函数之前有其他代码初始化main的运行环境，main结束后还需进行相应的环境清理工作，这两部分的工作通常是在运行库中的入口函数中完成的。


## /src/transport/unix/startup.c

glibc 初始化入口。_init()和_fini()函数

## internal.h 用于初始化系统调用函数、定义数据结构等

`citp_globals_t`结构体，用于设置startup的顺序

定义enum，定义宏定义，引用头文件，再undef宏定义，以便再次引用startup_order.h

```c
enum {
    CITP_INIT_NONE = 0,
#define STARTUP_ITEM(level, func) level,
#include "startup_order.h"
#undef STARTUP_ITEM
  } init_level;
#define CITP_INIT_ALL   CITP_INIT_PROTO
```

### 初始化顺序：

日志系统，解析ci_sys_*定义，？？，？？，transport，onload extension，fork hook，fdtable，netif，proto (tcp,udp)

```c
/* First of all, allow to use ci_log */
STARTUP_ITEM(CITP_INIT_LOGGING, citp_setup_logging_early)

/* resolve ci_sys_* symbols: now we fake-hanlde the intercepted calls.
 * The only calls we really handle here are exec*() */
STARTUP_ITEM(CITP_INIT_SYSCALLS, citp_syscall_init)

/* We can't easily fake-fandle execl*() functions, so we should prepare
 * to handle them properly ASAP. */
STARTUP_ITEM(CITP_INIT_ENVIRON, citp_environ_init)

/* read efabcfg database */
STARTUP_ITEM(CITP_INIT_CFG, citp_cfg_init)
/* init CITP_OPTS, including CITP_OPTS.log_level:
 * logging fully-functional now. */
STARTUP_ITEM(CITP_INIT_TRANSPORT, citp_transport_init)
/* onload extension library */
STARTUP_ITEM(CITP_INIT_ONLOADEXT, oo_extensions_init)
/* fork hooks should be ready (but disabled) before fdtable and netif */
STARTUP_ITEM(CITP_INIT_FORK_HOOKS, ci_setup_fork)
/* fdtable */
STARTUP_ITEM(CITP_INIT_FDTABLE, citp_fdtable_ctor)

#ifdef ONLOAD_OFE
STARTUP_ITEM(CITP_INIT_OFE, citp_ofe_ctor)
#endif

/* init citp_netif_info */
STARTUP_ITEM(CITP_INIT_NETIF, citp_netif_init_ctor)

/* handle TCP and UDP protocols: now we are going to properly handle all
 * the intercepted functions. */
STARTUP_ITEM(CITP_INIT_PROTO, citp_transport_register)
```

### _init()函数

初始化入口 glibc

先检查pagesize，再调用citp_do_init

### citp_do_init函数

`citp_setup_logging_early`设置日志

**`citp_syscall_init`调用sys.c，获取所有preload的函数， fake-handle？** 

`citp_environ_init`调用environ.c，保存当前环境变量（LD_PRELOAD)

`citp_cfg_init`调用efabcfg.c，读取一些配置信息

**`citp_transport_init`传输层初始化**

`oo_extensions_init`onload拓展功能模块初始化

`ci_setup_fork`初始化fork，netif_init.c中

**`citp_fdtable_ctor`fdtable.c，初始化文件描述符表**

**`citp_netif_init_ctor`初始化netinterface**

**`citp_transport_register`注册tcp和udp协议。**

## preload函数流程

`sys.c` ：使用dlsym查找函数指针

`onload/declare_syscalls.h.tmpl`: 用来定义，声明syscall函数

`sockcall_intercept.c`：实现了preload函数。

`tcp_fd.c`:定义了tcp protocol 结构体，及相关函数


# linux preload

## linux Hook技术

### Linux常见Hook技术对比

| 技术类型         | 生效范围   | 生效时机    | 依赖注入 | 层级 | 安全性 | 稳定性 | 开发运维难度 |
|--------------|--------|---------|------|----|-----|-----|--------|
| 内核模块         | 所有进程   | 加载内核模块后 | 否    | 低  | 最高  | 中   | 极高     |
| Inline Hook  | 当前进程   | hook后   | 是    | 中  | 中   | 中   | 高      |
| Got Hook     | 当前进程模块 | hook后   | 是    | 中  | 低   | 良   | 中      |
| Preload Hook | 所有进程   | hook后   | 否    | 中  | 低   | 优   | 低      |
| 系统文件修改       | 所有进程   | 文件修改后   | 否    | 中  | 高   | 中   | 高      |

1. 依赖注入，代表在使用该技术hook第三方进程前，是否需要先进行注入
2. 层级，代表hook点在整个系统调用的位置，越底层则层级越低
3. 稳定性越低，代表要通过这种技术做到稳定所需要的技术和时间成本较高
4. 安全性，代表该项技术被绕过的难易程度

### 函数调用类型

按函数调用在整个系统所处层级划分，可分为系统调用和库函数调

* 系统调用
  系统调用是指，真正执行逻辑实现于系统内核的库函数，通常是操作系统资源相关的例如文件、内存、进程、线程、网络等函数，如open函数。对这类函数的Hook可以做到较高安全性。/usr/include/bits/syscall.h头文件定义了当前系统支持的所有系统调用
* 库函数
  真正逻辑实现于用户态动态库的函数，除系统调用以外的库函数都算该类，如memcpy函数

按函数调用时机划分，可分为静态调用和动态调用

* 静态调用
  静态调用是指，直接使用函数调用运算符("()")调用自身或外部库导出函数
* 动态调用
  动态调用是指，使用dlopen/dlsym等方式直接获取到函数指针，进行调用的方式

### 内核模块Hook

  通常是从内核源码特殊位置，修改回调、修改中断表；或修改重编译内核，导出内部函数，从而跳转到自定义函数，开发内核模块实现hook。

* 可以拦截到所有应用层系统调用，应用层无法绕过
* 开发调试复杂，测试周期长，升级和卸载内核模块带来稳定性问题

### 应用层Inline Hook

应用层内联hook，即直接修改二进制函数体的汇编指令，修改执行逻辑使其跳转到自定义函数，开发应用层模块实现hook。

* 可以拦截到系统调用和普通库函数
* 由于linux系统本身具有多个发行版本及指令集，不容易做到通用
* 可以通过自定义实现底层函数或恢复模块内存方式绕过

### Got表

  当在程序中引用某个共享库中的符号时，编译链接阶段并不知道这个符号的具体位置，只有等到动态链接器将所需要的共享库加载时进内存后，符号的地址才会最终确定。因此，需要有一个数据结构来保存符号的绝对地址。编译器在编译C/C++程序时，会根据代码中对外部库函数的静态调用情况构造成一个符号索引表，使代码中外部库函数的调用暂时指向每个索引，在程序运行时进程加载器(进程加载器的概念)会将每个索引表项指向真正的函数地址，从而完成外部库函数调用。这种方式实现了在编译期时处理(动态加载模块的)函数调用问题。

  在Windows系统中，可执行程序为PE结构，该表为import table(俗称导入表)，对应.idata段；Linux/Android系统中，可执行程序为ELF结构，该表即为got(Global Offset Table)表，对应.got段；MacOS/iOS系统中，可执行程序为MachO格式，该表对应为__nl_symbol_ptr和__la_symbol_ptr段。在本文中统称导入表。

### 应用层Got Hook

  应用层got表hook，即在运行阶段修改程序本身got表，这样调用api的逻辑，就会相应的跳转到用户自定义函数中。

* 可以拦截系统调用和普通库函数
* 由于只需要考虑ELF格式因此实现难度较为简单
* 可以通过自定义实现底层函数或恢复got表内存方式绕过

### 应用层Preload Hook

Preload Hook是指利用系统支持的preload能力，将模块自动注入进程实现hook。可以通过以下手段使用Preload技术：一种是环境变量配置(LD_PRELOAD)；另一种是文件配置：(/etc/ld.so.preload)。

* 若使用命令行指定LD_PRELOAD则只影响该新进程及子进程；
* 若写入全局环境变量则LD_PRELOAD对所有新进程生效；
* 父进程可以控制子进程的环境变量从而取消preload
* 文件preload方式影响所有新进程且无法被取消
* 可以拦截到系统调用和普通库函数
* 实现和操作最为简单，只需要编写同名系统调用函数即可实现hook
* 可以使用动态调用方式或自定义实现方式绕过

## preload 技术

### 进程模块表的链状结构

```c
// from glibc/elf/link.h                for Linux
struct link_map     
{
    /* These first few members are part of the protocol with the debugger.
       This is the same format used in SVR4.  */
    ElfW(Addr) l_addr;        /* Difference between the address in the ELF
                   file and the addresses in memory.  */
    char *l_name;        /* Absolute file name object was found in.  */
    ElfW(Dyn) *l_ld;        /* Dynamic section of the shared object.  */
    struct link_map *l_next, *l_prev; /* 这里为链表结构.  */
};  
struct link_map _dl_loaded; // 全局模块表头
```

### 进程加载器的概念

属于操作系统的一部分，用于加载程序和动态库。加载器是执行程序和代码必不可少的组件，是一种用户态的模块，用户在shell中启动进程后，首先加载的是进程加载器模块，它负责将进程文件从文件形态映射到内存中、加载相应的依赖模块、初始化可执行模块、初始化进程所需的环境，最后调用程序入口点(main)执行真正的工作。加载器在模块表中的位置总是最前。下表是常见系统的进程加载器：

| Bit | Linux                       | Android              | MacOS/iOS     | Windows                         |
|-----|-----------------------------|----------------------|---------------|---------------------------------|
| 64  | /lib64/ld-linux-x86-64.so.2 | /system/bin/linker64 | /usr/lib/dyld | %SYSTEMROOT%\system32\ntdll.dll |
| 32  | /lib/ld-linux.so.2          | /system/bin/linker   | /usr/lib/dyld | %SYSTEMROOT%\system32\ntdll.dll |

### Preload技术

  Preload技术是Linux系统自身支持的模块预加载技术，这意味着进程加载器在加载进程时，会在模块表中首先插入指定的预加载模块，然后再插入进程所依赖的其他模块，预加载模块在模块表的位置总是位于加载器之后。Linux系统中，ELF格式的导入表只存储了符号(包括导出的全局对象、全局变量以及全局函数)名，因此在进程加载器初始化外部符号时，从模块链表头开始按模块搜索直到遇到该符号名。这点不同于Windows的PE格式，后者的导入表同时存储了符号名以及对应的模块名，这样进程加载器在初始化外部符号时已经确知需要加载哪个模块，若不存在则直接报错异常退出。ELF进程加载器这样的搜索顺序便会影响调用库函数时产生的符号查找的结果，具体会影响下面几点：

#### 静态调用的函数

  这类函数出现于编译得到二进制文件的导入表中，在被进程加载器映射到内存并初始化相关结构之后，导入表会被真实函数地址填充，而进程加载器正是通过模块链为导入表分配地址。假设两个包含相同符号/函数名的模块分别先后加载，那么先加载的处于链表靠前位置，进而会被进程加载器选中而当做真实函数地址。

#### 动态调用的函数，且不指定模块

  如果dlsym函数第一个参数被指定为RTLD_DEFAULT时，dlsym函数会匹配模块链中第一个包含该符号的模块，进而会被进程加载器选中而当做真实符号地址；若第一个参数指定的是RTLD_NEXT，dlsym函数会按模块链搜索下一个包含该符号的模块，并将该地址选为符号地址。(注：导出符号为导出函数或导出变量或常量)

  如前述，Linux/Android系统支持环境变量和文件方式的Preload；MacOS/iOS系统则提供了环境变量DYLD_INSERT_LIBRARIES用于Preload，同时提供__interpose结构用于Hook；Windows系统未提供环境变量方式的Preload，而提供了注册表方式注入。

## Preload特点

  Preload技术有自身的作用范围，如果将Preload环境变量到全局环境(/etc/profile)或使用Preload文件时，Preload便在所有在此(配置)时间节点之后运行的进程生效，而无法影响已经在运行的进程；若将Preload环境变量作为启动进程的环境变量(如shell中执行LD_PREOAD=/lib64/inject.so ./myprocess)，则Preload只对当前进程生效。默认情况下进程创建的子进程也会继承Preload环境变量，而父进程可以在子进程初始化前修改子进程的环境变量，从而避免往子代传播。Preload具体使用方式如下：

* LD_PRELOAD环境变量  指定动态库全路径，触发时机：启动时
* /etc/ld.so.preload  指定动态库全路径，触发时机：启动时

进程在启动后，会按照一定顺序加载动态库：

* 加载环境变量LD_PRELOAD指定的动态库
* 加载文件/etc/ld.so.preload指定的动态库
* 搜索环境变量LD_LIBRARY_PATH指定的动态库搜索路径
* 搜索路径/lib64下的动态库文件

  如前述，模块通过Preload技术添加到模块链后，进程加载器在解析导入表时，会按照链表顺序依次查找符号，因此如果在Preload动态库中实现并导出了同名(而不是C++修饰名)库函数，即可实现Hook。

```c
// inject.c
#include <stdio.h>
#include <sys/socket.h>
 __attribute__ ((visibility("default"))) int socket(int family, int type, int protocol) {
    printf("detect socket call\n");
    return -1;
}
__attribute__((constructor)) void main() {
    printf("module inject success\n");
}
/* 
    gcc inject.c --shared -fPIC -o inject.so
    LD_PRELOAD=$PWD/inject.so ping 127.0.0.1
    module inject success
    detect socket call
*/
```

## 应用Preload 存在的问题和解决方案

### Preload是否能作用于动态加载(dlopen/dlsym)的函数？

  这里和静态引用函数相比较，如前述，若preload模块已经导出同名函数，进程启动时需要借助进程加载器处理静态引用函数，从模块链中按模块加载顺序查找，直到遇到匹配的函数指针，这个函数此时位于preload模块中。而在动态调用过程中，指定动态库名及符号名的动态调用会在查找时匹配动态库名，再在该动态库符号表中查找符号名，因此会返回原始函数指针。

### Preload是否能作用于子进程(fork/vfork/clone)(execve/system/popen/...)？
 
 由于preload是进程加载器的行为，因此如果能触发进程加载器就能触发preload。对于第一类函数(fork/vfork/clone)，由于没有对进程进行重新初始化的操作，而仅仅是对进程空间的复制行为，因此不能触发preload；对于第二类函数(execve/system/popen/...)，其首先要调用fork产生一个子进程，然后需要使用新的可执行文件对子进程的进程空间重新初始化，这个过程势必会触发preload过程。
  
另外一个重要的考虑因素是，Preload只在部署之后对新进程生效，因此需要作为一个独立服务的可启动项，考虑系统其他服务启动顺序和时机。

### 对Docker / Chroot的支持？
  Paas容器技术提供了和宿主隔离的独立环境，在这种环境下文件系统是相互隔离的，而Preload技术则基于文件系统(ld.so.preload)，因此不存在一个绝对完美的方法提供对容器类场景的支持。下面提供一些特殊方式来解决该需求，对于Docker 分2种情况讨论：

若容器提供了文件映射机制(如docker run -v)，在这种情况下至少要求映射/etc/ld.so.preload及Preload动态库以实现基本的Preload机制，而这本身又需要宿主系统和容器系统相近，保证系统稳定性。
若容器系统和宿主系统相差较大，则需要考虑在容器系统内全新部署Preload相关组件。

  对于类似于使用chroot机制进行文件隔离的场景，需要针对性的修改chroot环境中对应的Preload配置文件及部署拦截模块进行Preload。

### 如何拦截动态加载的符号？

  如前述，Preload是进程加载器的行为，因此对于静态引用的符号生效；这里暂且将动态调用限制在仅使用dlopen/dlsym函数上，对于明确指定了动态库路径和符号名的dlopen/dlsym的动态调用，必然要对dlsym本身进行hook，这样引发的问题是怎样得到原始的dlopen/dlsym及其他符号名，因为通常我们会在hook函数执行前/后，执行一次原始函数，而这个原始函数指针按常规方式需要由dlsym来获取。如果静态使用dlopen/dlsym则会调用hook模块中的自定义dlopen/dlsym中去，从而产生死循环。要解开这个循环必须要使用更底层的方式来做。一种选择是手动解析/proc/pid/map中的模块导出表，从而获取函数基址。更通用的方式则是使用GNU提供的dl_iterate_phdr，此函数存在于进程加载器linker中。所以一个典型的preload hook过程如下：

* 使用dl_iterate_phdr迭代出所有需要进行hook的函数地址，保存为原始函数
* 实现同名函数，在执行hook逻辑前/后，执行原始函数调用
* 在自定义dlopen/dlsym，若匹配到hook函数名，则返回hook模块本身的同名函数，以实现hook动态调用函数的目的

### 如何更安全的部署preload模块？
  
由于preload函数会影响所有新启动的进程，若preload模块存在缺陷，最差的情况是无法执行任何命令(execve/system/popen/...)；此种情况下若进行重启，重启所创建的任何进程均会无法正确执行而导致系统无法使用，从而陷入死循环，这种情况极难处理。这里提供的解决方式是使用mount命令，其特点是，在删除源文件或重启后失效，利用这个特点，首先将ld.preload.so拷贝为ld.preload.so.new，然后使用mount将ld.preload.so.new绑定到ld.preload.so上。此时若preload模块存在缺陷，只需要重启即可去除preload。



