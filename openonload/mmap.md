# mmap原理及libonload中mmap操作

## mmap原理

内存映射，简而言之就是将用户空间的一段内存区域映射到内核空间，映射成功后，用户对这段内存区域的修改可以直接反映到内核空间，同样，内核空间对这段区域的修改也直接反映用户空间。那么对于内核空间<---->用户空间两者之间需要大量数据传输等操作的话效率是非常高的。

### 函数定义及参数

```c
void * mmap(void *start, size_t length, int prot , int flags, int fd, off_t offset)
```

* start：要映射到的内存区域的起始地址，通常都是用NULL（NULL即为0）。NULL表示由内核来指定该内存地址
* length：要映射的内存区域的大小
* prot：期望的内存保护标志，不能与文件的打开模式冲突。是以下的某个值，可以通过or运算合理地组合在一起
  * PROT_EXEC //页内容可以被执行
  * PROT_READ  //页内容可以被读取
  * PROT_WRITE //页可以被写入
  * PROT_NONE  //页不可访问
* flags：指定映射对象的类型，映射选项和映射页是否可以共享。它的值可以是一个或者多个以下位的组合体
```text
MAP_FIXED ：使用指定的映射起始地址，如果由start和len参数指定的内存区重叠于现存的映射空间，重叠部分将会被丢弃。如果指定的起始地址不可用，操作将会失败。并且起始地址必须落在页的边界上。
MAP_SHARED ：对映射区域的写入数据会复制回文件内, 而且允许其他映射该文件的进程共享。
MAP_PRIVATE ：建立一个写入时拷贝的私有映射。内存区域的写入不会影响到原文件。这个标志和以上标志是互斥的，只能使用其中一个。
MAP_DENYWRITE ：这个标志被忽略。
MAP_EXECUTABLE ：同上
MAP_NORESERVE ：不要为这个映射保留交换空间。当交换空间被保留，对映射区修改的可能会得到保证。当交换空间不被保留，同时内存不足，对映射区的修改会引起段违例信号。
MAP_LOCKED ：锁定映射区的页面，从而防止页面被交换出内存。
MAP_GROWSDOWN ：用于堆栈，告诉内核VM系统，映射区可以向下扩展。
MAP_ANONYMOUS ：匿名映射，映射区不与任何文件关联。
MAP_ANON ：MAP_ANONYMOUS的别称，不再被使用。
MAP_FILE ：兼容标志，被忽略。
MAP_32BIT ：将映射区放在进程地址空间的低2GB，MAP_FIXED指定时会被忽略。当前这个标志只在x86-64平台上得到支持。
MAP_POPULATE ：为文件映射通过预读的方式准备好页表。随后对映射区的访问不会被页违例阻塞。
MAP_NONBLOCK ：仅和MAP_POPULATE一起使用时才有意义。不执行预读，只为已存在于内存中的页面建立页表入口。
```
* fd：文件描述符（由open函数返回）
* offset：表示被映射对象（即文件）从那里开始对映，通常都是用0。 该值应该为大小为PAGE_SIZE的整数倍

成功执行时，mmap()返回被映射区的指针，munmap()返回0。

失败时，mmap()返回MAP_FAILED[其值为(void *)-1]，munmap返回-1。errno被设为以下的某个值   

```text
EACCES：访问出错
EAGAIN：文件已被锁定，或者太多的内存已被锁定
EBADF：fd不是有效的文件描述词
EINVAL：一个或者多个参数无效
ENFILE：已达到系统对打开文件的限制
ENODEV：指定文件所在的文件系统不支持内存映射
ENOMEM：内存不足，或者进程已超出最大内存映射数量
EPERM：权能不足，操作不允许
ETXTBSY：已写的方式打开文件，同时指定MAP_DENYWRITE标志
SIGSEGV：试着向只读区写入
SIGBUS：试着访问不属于进程的内存区
```

```c
int munmap(void *start, size_t length)
```

* start：要取消映射的内存区域的起始地址
* length：要取消映射的内存区域的大小。

```c
int msync(const void *start, size_t length, int flags); 
```

对映射内存的内容的更改并不会立即更新到文件中，而是有一段时间的延迟，你可以调用msync()来显式同步一下, 这样你内存的更新就能立即保存到文件里

* start：要进行同步的映射的内存区域的起始地址。
* length：要同步的内存区域的大小
* flag:flags可以为以下三个值之一： 
  * MS_ASYNC : 请Kernel快将资料写入。 
  * MS_SYNC : 在msync结束返回前，将资料写入。 
  * MS_INVALIDATE : 让核心自行决定是否写入，仅在特殊状况下使用

### mmap程序示例

首先在驱动程序分配一页大小的内存，然后用户进程通过mmap()将用户空间中大小也为一页的内存映射到内核空间这页内存上。映射完成后，驱动程序往这段内存写10个字节数据，用户进程将这些数据显示出来。

#### 驱动代码mymap.c

```c
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <linux/gpio.h>

#define DEVICE_NAME "mymap"

static unsigned char array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static unsigned char *buffer;

static int my_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int my_map(struct file *filp, struct vm_area_struct *vma)
{
    unsigned long page;
    unsigned char i;
    unsigned long start = (unsigned long)vma->vm_start;
    //unsigned long end =  (unsigned long)vma->vm_end;
    unsigned long size = (unsigned long)(vma->vm_end - vma->vm_start);

    //得到物理地址
    page = virt_to_phys(buffer);
    //将用户空间的一个vma虚拟内存区映射到以page开始的一段连续物理页面上
    if (remap_pfn_range(vma, start, page >> PAGE_SHIFT, size, PAGE_SHARED)) //第三个参数是页帧号，由物理地址右移PAGE_SHIFT得到
        return -1;

    //往该内存写10字节数据
    for (i = 0; i < 10; i++)
        buffer[i] = array[i];

    return 0;
}

static struct file_operations dev_fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .mmap = my_map,
};

static struct miscdevice misc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &dev_fops,
};

static int __init dev_init(void)
{
    int ret;

    //注册混杂设备
    ret = misc_register(&misc);
    //内存分配
    buffer = (unsigned char *)kmalloc(PAGE_SIZE, GFP_KERNEL);
    //将该段内存设置为保留
    SetPageReserved(virt_to_page(buffer));

    return ret;
}

static void __exit dev_exit(void)
{
    //注销设备
    misc_deregister(&misc);
    //清除保留
    ClearPageReserved(virt_to_page(buffer));
    //释放内存
    kfree(buffer);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("LKN@SCUT");
```

#### 用户代码test.c

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#define PAGE_SIZE 4096

int main(int argc, char *argv[])
{
    int fd;
    int i;
    unsigned char *p_map;

    //打开设备
    fd = open("/dev/mymap", O_RDWR);
    if (fd < 0)
    {
        printf("open fail\n");
        exit(1);
    }

    //内存映射
    p_map = (unsigned char *)mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p_map == MAP_FAILED)
    {
        printf("mmap fail\n");
        goto here;
    }

    //打印映射后的内存中的前10个字节内容
    for (i = 0; i < 10; i++)
        printf("%d\n", p_map[i]);

here:
    munmap(p_map, PAGE_SIZE);
    return 0;
}
```

#### Makefile

```bash
obj-m := mymap.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	make -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules && gcc -o test test.c

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean  && rm test
```

#### 加载模块及运行

先执行make进行编译

再加载mymap模块至内核

最后执行test读取数据

```bash
make 
sudo insmod mymap.ko
sudo ./test
```

卸载模块及清理

```bash
sudo rmmod mymap
make clean
```

## libonload中的mmap

### 使用mmap获取pkt地址空间

src\include\onload\unix_intf.h

```c
ci_inline int
oo_resource_mmap(ci_fd_t fp, ci_uint8 map_type, unsigned long map_id,
                 unsigned bytes, int flags, void** p_out)
{
  int mmap_prot = PROT_READ;
  int mmap_flags = MAP_SHARED;
  int saved_errno = errno;

  off_t offset = map_id << OO_MMAP_ID_SHIFT;
  offset |= ((off_t) map_type) << OO_MMAP_TYPE_SHIFT;
#ifndef OO_MMAP_TYPE_DSHM
  ci_assert_equal(map_type, OO_MMAP_TYPE_NETIF);
#endif

  if( ! (flags & OO_MMAP_FLAG_READONLY) )
    mmap_prot |= PROT_WRITE;
  if( flags & OO_MMAP_FLAG_FIXED )
    mmap_flags |= MAP_FIXED;
  if( flags & OO_MMAP_FLAG_POPULATE )
    mmap_flags |= MAP_POPULATE;
  *p_out = mmap((flags & OO_MMAP_FLAG_FIXED) ? *p_out : (void*) 0, bytes,
                mmap_prot, mmap_flags, fp, offset);
  if( *p_out == MAP_FAILED ) {
    int rc = -errno;
    errno = saved_errno;
    return rc;
  }
  return 0;
}
```
