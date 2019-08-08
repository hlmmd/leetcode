# valgrind

安装：sudo apt install valgrind

首先，编译的时候设置-g打开debug，编译优化设置为-O0

执行valgrind ./test

## core dump

使用ulimit -c unlimited 允许产生core文件

gdb ./test core 查看core文件