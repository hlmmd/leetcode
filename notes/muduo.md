# linux多线程服务端编程

## 线程安全的对象生命期管理

线程安全：

* 多个线程同时访问时，表现出正确行为
* 无论操作系统如何调度这些线程，无论这些线程执行顺序如何交织
* 调用端代码无需额外的同步或其他协调动作

C++标准库里大多数类都不是线程安全的，如string,map,vector等。

