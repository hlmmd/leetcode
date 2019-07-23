# linux下驱动编写简介

## 实现一个最简单的内核驱动 helloworld

## 编写hello.c，用于生成模块hello.ko

```c
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");
static int hello_init(void)
{
    printk(KERN_ALERT "Hello, world\n");
    return 0;
}
static void hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
}
module_init(hello_init);
module_exit(hello_exit);
```

模块构造函数：module_init()

* 执行insmod或modprobe指令加载内核模块时会调用的初始化函数，括号内是函数指针

模块析构函数：module_exit()

执行rmmod指令卸载模块时调用的函数。

模块许可声明：MODULE_LICENSE("Dual BSD/GPL");

函数原使用的许可证，不然在加载时它会提示该模块污染内核。一般会写GPL。

头文件module.h，必须包含此文件；

头文件kernel.h，包含常用的内核函数；

头文件init.h包含宏_init和_exit，允许释放内核占用的内存。

## 编写Makefile

```bash
obj-m:=hello.o
PWD:=$(shell pwd)
BUILDSYSTEM_DIR:=/lib/modules/$(shell uname -r)/build

all:
    $(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules

clean:
    $(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) clean
```

obj-m：后面接要编译的文件名.o，CURRENT_PATH是当前路径，LINUX_KERNEL_PATH是前面查到的所使用内核的路径，

make -C $(LINUX_KERNEL_PATH) 指明跳转到内核源码目录下读取那里的Makefile，

M=$(CURRENT_PATH) 表明返回到当前目录继续执行当前的Makefile。

## 编译与安装

执行make，会生成hello.ko文件

用insmod命令安装模块

dmesg查看输出消息

rmmod卸载模块

```bash
make
sudo insmod hello.ko
dmesg
sudo rmmod hello.ko
```

可以看到输出：

```bash
[12725.717058] Hello, world
[12752.068475] Goodbye, cruel world
```

## 一个简单的虚拟网卡示例 virnet.c

```c
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");

// 网络设备对象
static struct net_device *sg_dev;

// 有数据帧要发送时，kernel会调用该函数
static int virnet_send_packet(struct sk_buff *skb,struct net_device *dev)
{
    // 统计已发送的数据包
    dev->stats.tx_packets++;
    // 统计已发送的字节
    dev->stats.tx_bytes+=skb->len;
    // 释放数据帧
    dev_kfree_skb(skb);
    return 0;
}

// 驱动程序支持的操作
static struct net_device_ops sg_ops=
{
    // 发送数据帧
    .ndo_start_xmit=virnet_send_packet,
};

// 驱动程序初始化
static int virnet_init(void)
{
    // 创建一个网络设备，名为“virnet%d"，kernel会自动填写%d为网卡编号
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,4,1)
    // kernel 4.4.0-97上需要四个参数如下
    sg_dev=alloc_netdev(0,"virnet%d", NET_NAME_UNKNOWN, ether_setup);
#else
    sg_dev=alloc_netdev(0,"virnet%d",ether_setup);
#endif
    
    // 该网络设备的操作集
    sg_dev->netdev_ops=&sg_ops;
    // MAC地址是01:02:03:04:05:06
    memcpy(sg_dev->dev_addr,"\x01\x02\x03\x04\x05\x06",6);
    // 注册网络设备
    register_netdev(sg_dev);
    return 0;
}

// 驱动程序销毁
static void virnet_exit(void)
{
    // 注销网络设备
    unregister_netdev(sg_dev);
    // 释放对象
    free_netdev(sg_dev);
}

module_init(virnet_init);
module_exit(virnet_exit);
```

Makefile:

```bash
obj-m := virnet.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	make -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
```