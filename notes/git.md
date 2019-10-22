# [git](https://github.com/521xueweihan/git-tips)

* 本地版本控制系统
* 集中化的版本控制系统
* 分布式版本控制系统

##  起步

git直接记录快照，而非比较差异

git大部分的操作都是本地执行，本地上存储了项目的完整历史

Git完整性校验

存储前会计算校验和，使用SHA-1散列

git一般只添加数据

### 三种状态

* 已提交(commit):数据已经安全的保存在本地数据库中。
* 已修改（modified）:修改了文件，但还没保存到数据库中。
* 已暂存（staged）:对一个已修改文件的当前版本做了标记，使之包含在下次提交的快照中。

三个工作区：git 仓库、工作目录、暂存区域

Git 仓库目录是 Git 用来保存项目的元数据和对象数据库的地方。这是 Git 中最重要的部分，从其它计算机克隆仓库时，拷贝的就是这里的数据。

工作目录是对项目的某个版本独立提取出来的内容。这些从 Git 仓库的压缩数据库中提取出来的文件，放在磁盘上供你使用或修改。

暂存区域是一个文件，保存了下次将提交的文件列表信息，一般在 Git 仓库目录中。有时候也被称作`‘索引’'，不过一般说法还是叫暂存区域。

基本的 Git 工作流程如下：
1. 在工作目录中修改文件。
2. 暂存文件，将文件的快照放入暂存区域。
3. 提交更新，找到暂存区域的文件，将快照永久性存储到 Git 仓库目录。

## git 基础

获取git 仓库

初始化仓库

git init 

克隆远程仓库

git clone

检查当前文件状态

git status

untracked unmodified modified staged

跟踪文件

git add

提交

git commit -a -m

日志

git log

撤销操作

git commit --amend

推送到远程仓库

git push

git pull = git fetch + git merge

打标签

git tag

附注标签： git tag -a v1.4 -m''

查看标签

git show

轻量标签

git 别名

## git 分支

分支查看 

git branch

分支创建

git branch new

分支切换

git checkout new

分支创建并切换

git checkout -b new

git 通过HEAD指针来获取当前处于哪一个分支。

分支合并

git merge

当两个分支对同一文件相同地方进行了修改时，需要手动进行合并

分支管理

git branch -v 查看每个分支最后一次提交

git branch --merged

git branch --no-merged

查看已经合并或者尚未合并的分支

分支开发工作流

* 长期分支
* 特性分支 
* 远程分支

跟踪分支

拉取

git pull = git fetch + git merge

变基

git 中整合不同分支的主要修改方法有两种：merge和rebase

rebase命令将某一分支上的修改都移动到另一分支上。



