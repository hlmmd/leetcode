# datastructure

首先来本教材[\[数据结构\(C语言版\)\].严蔚敏\_吴伟民.扫描版](https://www.hlmmd.me/wp-content/uploads/2019/02/数据结构C语言版.严蔚敏_吴伟民.扫描版_有目录.pdf)[下载](https://www.hlmmd.me/wp-content/uploads/2019/02/数据结构C语言版.严蔚敏_吴伟民.扫描版_有目录.pdf)

一些链接

[https://cyc2018.github.io/CS-Notes/\#/notes/算法](https://cyc2018.github.io/CS-Notes/#/notes/算法)

### 什么是数据结构

 在计算机科学中，**数据结构**（英语：data structure）**是**计算机中存储、组织**数据**的方式

### 线性表

1. n个元素的有限序列
2. 顺序表示（数组）物理位置相邻，随机存取
3. 链式结构（链表）链式存储，方便插入删除
4. 链表的头结点
5. 单链表、循环链表、双向链表

### 栈和队列

#### 栈

操作限定在表尾的数据结构。表尾叫栈顶，表头叫栈顶。  
先进后出 FILO 、栈与递归

#### 队列

在队尾进行插入，队头删除元素。

先进先出 FIFO

循环队列：队列的顺序表示

### 字符串

零个或多个字符组成的有序序列

子串：字符串中任意个连续字符组成的子序列。

### 树与二叉树

树是由n（n&gt;0）个有限节点组成一个具有层次关系的集合。把它叫做“树”是因为它看起来像一棵倒挂的树，也就是说它是根朝上，而叶朝下的。它具有以下的特点：

* 每个节点有零个或多个子节点；
* 没有父节点的节点称为根节点；
* 每一个非根节点有且只有一个父节点；
* 除了根节点外，每个子节点可以分为多个不相交的子树；
* 树里面没有环路\(cycle\)

#### 二叉树

* 每个结点至多只有两颗子树，且有左右之分，不能颠倒。
* 叶子结点：没有子结点
* 满二叉树：深度为k且有2^k -1个结点。
* 完全二叉树：不看最后一层是一棵满二叉树，最后一层的结点都在最左边。

```text
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lichild,*rchild;
}BiTNode,*BiTree;
```

遍历二叉树

* 先序遍历：根结点，左子树，右子树
* 中序遍历：左子树，根结点，右子树
* 后续遍历：左子树，右子树，根结点

线索二叉树

最优二叉树 哈夫曼树 哈夫曼编码

前缀编码：任意一个字符的编码都不能是另一个字符编码的前缀。

二叉查找树（BST）：任何结点都大于等于左子树中的值，小于等于右子树中的值。

### 图

表示方法：邻接表、邻接矩阵

遍历：

深度优先搜索（DFS）

广度优先搜索（BFS）

拓扑排序：有向图结点线性排序。应用：课程安排

时间复杂度：O\(V+E\)

Dijkstra算法：单源最短路径（权不能为负）

时间复杂度O\(V^2\)

最小生成树：

Prim算法 O\(V^2\)

Kruskal算法 O\(ElogV\)

### 查找

顺序查找

二分查找

二叉查找树

二叉平衡树（AVL）：左右子树都是二叉平衡树，左子树和右子树的深度差不超过1。

B树、B+树

哈希表、处理冲突函数

### 排序

#### 插入排序

每次都将当前元素插入到左侧已经排序的数组中，使得插入之后左侧数组依然有序。

```text
void InsertSort(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); i++)
    {
        int temp = nums[i];
        int j = 0;
        for (j = i - 1; j >= 0 && nums[j] > temp; j--)
            nums[j + 1] = nums[j];
        nums[j + 1] = temp;
    }
}
```

#### 希尔排序

缩小增量排序，先将整个待排序数组分成若干子序列进行插入排序，等到整个序列基本有序后再对整体进行一次插入排序

#### 冒泡排序

交换排序的一种。每次比较相邻两个数的大小，如果左数大于右数，就交换。这样每一轮都可以让最大的数上浮到数组末尾。当一轮循环中没有发生交换的时候，表示已经有序，可以提前退出循环。

```text
void BubbleSort(vector<int> &nums)
{
    bool sorted = false;
    for (int i = 0; i < nums.size() - 1 && !sorted; i++)
    {
        sorted = true;
        for (int j = 1; j < nums.size() - i; j++)
        {
            if (nums[j] < nums[j - 1])
            {
                sorted = false;
                swap(nums[j], nums[j - 1]);
            }
        }
    }
}
```

#### 选择排序

从第i~length-1中选出一个最小的元素，与第i个数交换。

```text
void BubbleSort(vector<int> &nums)
{
    bool sorted = false;
    for (int i = 0; i < nums.size() - 1 && !sorted; i++)
    {
        sorted = true;
        for (int j = 1; j < nums.size() - i; j++)
        {
            if (nums[j] < nums[j - 1])
            {
                sorted = false;
                swap(nums[j], nums[j - 1]);
            }
        }
    }
}
```

#### 归并排序

将数组递归分组，分别进行排序，再归并起来重新排序。

#### 快速排序

快速排序通过一个切分元素将数组分为两个子数组，左子数组小于等于切分元素，右子数组大于等于切分元素，将这两个子数组排序也就将整个数组排序了。

所以算法关键要确定切分元素的位置。

```text
void SelectionSort(vector<int> &nums)
{

    for (int i = 0; i < nums.size() - 1; i++)
    {
        int minpos = i;

        for (int j = i + 1; j < nums.size(); j++)
        {
            if (nums[j] < nums[minpos])
                minpos = j;
        }
        swap(nums[i], nums[minpos]);
    }
}

int partition(vector<int> &nums, int l, int h)
{
    int i = l + 1, j = h;
    int temp = nums[l];
    while (true)
    {
        while (nums[i] < temp && i < h)
            i++;
        while (temp < nums[j] && j > l)
            j--;
        if (i >= j)
            break;
        swap(nums[i], nums[j]);
    }
    swap(nums[l], nums[j]);
    return i;
}
void myqsort(vector<int> &nums, int l, int h)
{
    if (l >= h)
        return;
    int j = partition(nums, l, h);
    myqsort(nums, l, j - 1);
    myqsort(nums, j + 1, h);
}
void QuickSort(vector<int> &nums)
{
    myqsort(nums, 0, nums.size() - 1);
}
```

**算法改进**

切换到插入排序

因为快速排序在小数组中也会递归调用自己，对于小数组，插入排序比快速排序的性能更好，因此在小数组中可以切换到插入排序。

三数取中

最好的情况下是每次都能取数组的中位数作为切分元素，但是计算中位数的代价很高。一种折中方法是取 3 个元素，并将大小居中的元素作为切分元素。

**三段切分**

对于有大量重复元素的数组，可以将数组切分为三部分，分别对应小于、等于和大于切分元素。  
三向切分快速排序对于有大量重复元素的随机数组可以在线性时间内完成排序。

#### 堆排序

堆是一棵完全二叉树，可以用数组来表示。

在堆中，父结点的值比均不大于（或不小于）其左右子树结点的值

上浮和下沉

### 排序算法比较

| 算法 | 稳定性 | 时间复杂度 | 空间复杂度 | 备注 |
| :--- | :--- | :--- | :--- | :--- |
| 选择排序 | × | N2 | 1 |  |
| 冒泡排序 | √ | N2 | 1 |  |
| 插入排序 | √ | N ~ N2 | 1 | 时间复杂度和初始顺序有关 |
| 希尔排序 | × | N 的若干倍乘于递增序列的长度 | 1 | 改进版插入排序 |
| 快速排序 | × | NlogN | logN |  |
| 三向切分快速排序 | × | N ~ NlogN | logN | 适用于有大量重复主键 |
| 归并排序 | √ | NlogN | N |  |
| 堆排序 | × | NlogN | 1 | 无法利用局部性原理 |

快速排序是最快的通用排序算法，它的内循环的指令很少，而且它还能利用缓存，因为它总是顺序地访问数据。它的运行时间近似为 ~cNlogN，这里的 c 比其它线性对数级别的排序算法都要小。

使用三向切分快速排序，实际应用中可能出现的某些分布的输入能够达到线性级别，而其它排序算法仍然需要线性对数时间。

