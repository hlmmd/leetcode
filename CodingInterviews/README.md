# 剑指offer题解

## 1 二维数组中的查找

在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

从右上角开始查找即可

```cpp
class Solution
{
  public:
    bool Find(int target, vector<vector<int>> array)
    {
        if (array.size() == 0 || array[0].size() == 0)
            return false;

        int px = 0;
        int py = array[0].size() - 1;

        while (px < array.size() && py >= 0)
        {
            if (array[px][py] > target)
                py--;
            else if (array[px][py] == target)
                return true;
            else
                px++;
        }
        return false;
    }
};
```

## 2 替换空格

请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

```cpp
class Solution
{
  public:
    void replaceSpace(char *str, int length)
    {

        string tempstr = "";
        char *p = str;
        while (*p)
        {
            if (*p == ' ')
                tempstr += "%20";
            else
                tempstr += *p;
            p++;
        }
        strcpy(str, tempstr.c_str());
    }
};

```

## 3 从尾到头打印链表

输入一个链表，按链表值从尾到头的顺序返回一个ArrayList。

```cpp
class Solution
{
  public:
    vector<int> printListFromTailToHead(ListNode *head)
    {
        stack<int> value;
        vector<int> ret;
        if (head == NULL)
            return ret;
        ListNode *p = head;
        while (p)
        {
            value.push(p->val);
            p = p->next;
        }
        while (!value.empty())
        {
            ret.push_back(value.top());
            value.pop();
        }
        return ret;
    }
};
```


## 4 重建二叉树

输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。

基本思路：先从先序遍历找到当前根节点。然后在中序遍历中找到对应的结点位置，其左边的结点都是左子树的结点，右边的结点是右子树的结点，分治递归即可。

```cpp
class Solution
{
  public:
    TreeNode *reConstructBinaryTree(vector<int> pre, vector<int> vin)
    {
        return helper(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
    }
    TreeNode *helper(vector<int> pre, int pl, int pr, vector<int> vin, int vl, int vr)
    {
        if (pl > pr || vl > vr)
            return NULL;
        int val = pre[pl];
        int in_pos = -1;
        for (int i = vl; i <= vr; i++)
        {
            if (vin[i] == val)
            {
                in_pos = i;
                break;
            }
        }
        int len_left = in_pos - vl;
        TreeNode *p = new TreeNode(val);
        p->left = helper(pre, pl + 1, pl + len_left, vin, vl, in_pos - 1);
        p->right = helper(pre, pl + len_left + 1, pr, vin, in_pos + 1, vr);
        return p;
    }
};
```


## 5 用两个栈实现队列

用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。

一个栈用来保存入队数据，另一个栈用来出队。当push时，直接将数字push进stack1中。当要执行出队操作时，先判断stack2是否为空，如果非空，直接栈顶出栈。如果不空，就将所有stack1中的数出栈后再扔进stack2中。这样，stack2中的出栈顺序就是队列的出队顺序了。

```cpp
class Solution
{
  public:
    void push(int node)
    {
        stack1.push(node);
    }

    int pop()
    {

        if (!stack2.empty())
        {
            int ret = stack2.top();
            stack2.pop();
            return ret;
        }

        else if (stack1.empty())
            return -1;

        while (stack1.size() != 1)
        {
            int v = stack1.top();
            stack1.pop();
            stack2.push(v);
        }
        int ret = stack1.top();
        stack1.pop();
        return ret;
    }

  private:
    stack<int> stack1;
    stack<int> stack2;
};
```

## 6 旋转数组的最小数字

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。 输入一个非减排序的数组的一个旋转，输出旋转数组的最小元素。 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。

二分查找。查找到的条件是left\<right， 或者rotateArray[left] < rotateArray[right]，此时直接返回rotateArray[left]。

```cpp
class Solution
{
  public:
    int minNumberInRotateArray(vector<int> rotateArray)
    {
        if (rotateArray.size() == 0)
            return 0;

        int left = 0, right = rotateArray.size() - 1;
        while (left < right)
        {
            if (rotateArray[left] < rotateArray[right])
                return rotateArray[left];
            int mid = (left + right) / 2;
            if (rotateArray[mid] >= rotateArray[left])
                left = mid + 1;
            else if (rotateArray[mid] <= rotateArray[right])
                right = mid;
        }
        return rotateArray[left];
    }
};
```


## 7 斐波那契数列

大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0）。n<=39

```cpp
class Solution
{
  public:
    int Fibonacci(int n)
    {

        long long f[40];
        f[0] = 0, f[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            f[i] = f[i - 1] + f[i - 2];
        }
        return f[n];
    }
};
```


## 8 跳台阶

一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

```cpp
class Solution
{
  public:
    int jumpFloor(int number)
    {

        long long f[40];
        f[0] = 1, f[1] = 1;
        for (int i = 2; i <= number; i++)
        {
            f[i] = f[i - 1] + f[i - 2];
        }
        return f[number];
    }
};
```

## 9 变态跳台阶

一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。

```cpp
class Solution
{
  public:
    int jumpFloorII(int number)
    {
        if (number == 0)
            return 0;
        vector<long long> dp(number + 1, 0);
        dp[1] = 1;
        for (int i = 2; i <= number; i++)
        {
            dp[i] = dp[i - 1] << 1;
        }
        return dp.back();
    }
};
```

## 10 矩阵覆盖

我们可以用2\*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2\*1的小矩形无重叠地覆盖一个2\*n的大矩形，总共有多少种方法？

依然是斐波那契

```cpp
class Solution
{
  public:
    int rectCover(int number)
    {
        if (number == 0)
            return 0;
        int n = number;
        long long f[40];
        f[1] = 1, f[2] = 2;
        for (int i = 3; i <= n; i++)
        {
            f[i] = f[i - 1] + f[i - 2];
        }
        return f[n];
    }
};
```

## 11 二进制中1的个数

输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。

每次计算n&(n-1)，相当于把n最后一位1清0。计算这样的清零操作执行了多少次即可

```cpp
class Solution
{
  public:
    int NumberOf1(int n)
    {

        int count = 0;
        while (n)
        {
            count++;
            n = n & (n - 1);
        }

        return count;
    }
};
```

## 12 数值的整数次方

给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。

使用递归。

$$x^n=
\begin{cases}
1& \text{n==0}\\
1/x^{-n}& \text{n<0}\\
x*x^{n-1}& \text{n\%2==1}\\
(x^2)^{n/2} & \text{n\%2==0}
\end{cases}$$

```cpp
class Solution
{
  public:
    double Power(double base, int exponent)
    {
        if (exponent == 0)
            return 1;
        if (exponent < 0)
            return 1.0 / Power(base, -exponent);

        if (exponent % 2 == 1)
            return base * Power(base, exponent - 1);
        else
            return Power(base * base, exponent >> 1);
    }
};
```

## 13 调整数组顺序使奇数位于偶数前面

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。

因为要求稳定，所以不能使用类似快排的思想。可以使用冒泡等稳定排序，或者申请额外空间。

```cpp
class Solution
{
  public:
    void reOrderArray(vector<int> &array)
    {
        // 奇数个数
        int oddCnt = 0;
        for (int val : array)
            if (val % 2 == 1)
                oddCnt++;
        vector<int> copy = array;
        int i = 0, j = oddCnt;
        for (int num : copy)
        {
            if (num % 2 == 1)
                array[i++] = num;
            else
                array[j++] = num;
        }
    }
};
```

## 14 链表中倒数第k个结点

输入一个链表，输出该链表中倒数第k个结点。

使用两个指针。第一个指针先往后跑k次，此时如果没有到底，则剩下n-k个（n为链表长度）

接下来两个指针一起跑，跑n-k次第一个指针为NULL，此时第二个指针跑了n-k次，即为倒数第k个结点。

```cpp
class Solution
{
  public:
    ListNode *FindKthToTail(ListNode *pListHead, unsigned int k)
    {

        ListNode *p1, *p2;
        p1 = p2 = pListHead;

        int x = k;
        while (x && p1)
        {
            x--;
            p1 = p1->next;
        }
        if (p1 == NULL && x != 0)
            return NULL;
        while (p1)
        {
            p2 = p2->next;
            p1 = p1->next;
        }

        return p2;
    }
};
```

## 15 反转链表

输入一个链表，反转链表后，输出新链表的表头。

使用last、cur、next三个指针。

```cpp
class Solution
{
  public:
    ListNode *ReverseList(ListNode *pHead)
    {

        if (pHead == NULL)
            return NULL;
        ListNode *next, *cur = pHead, *last = NULL;
        while (cur)
        {
            next = cur->next;
            cur->next = last;
            last = cur;
            cur = next;
        }

        return last;
    }
};
```

## 16 合并两个排序的链表

输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。

```cpp
class Solution
{
  public:
    ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
    {
        ListNode *dummy = new ListNode(0);
        ListNode *p = dummy;
        ListNode *p1 = pHead1, *p2 = pHead2;

        while (p1 && p2)
        {
            if (p1->val < p2->val)
            {
                p->next = p1;
                p1 = p1->next;
            }
            else
            {
                p->next = p2;
                p2 = p2->next;
            }
            p = p->next;
        }
        p->next = p1 ? p1 : p2;
        return dummy->next;
    }
};
```

## 17 树的子结构

输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）

注意不是子树..一开始以为是子树

```cpp
class Solution
{
  public:
    bool IsSame(TreeNode *root1, TreeNode *root2)
    {
        if (root1 == NULL && root2 == NULL)
            return true;
        if (root1 != NULL && root2 == NULL)
            return true;
        return root1 && root2 && root1->val == root2->val && (IsSame(root1->left, root2->left)) && (IsSame(root1->right, root2->right));
    }

    bool HasSubtree(TreeNode *pRoot1, TreeNode *pRoot2)
    {
        if (pRoot1 == NULL || pRoot2 == NULL)
            return false;
        if (IsSame(pRoot1, pRoot2))
            return true;
        return HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
    }
};
```

## 18 二叉树的镜像

操作给定的二叉树，将其变换为源二叉树的镜像

```cpp
class Solution
{
  public:
    void SwapChildNode(TreeNode *root)
    {
        if (root == NULL)
            return;
        TreeNode *temp = root->right;
        root->right = root->left;
        root->left = temp;
    }

    void Mirror(TreeNode *pRoot)
    {

        if (pRoot == NULL)
            return;
        SwapChildNode(pRoot);
        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }
};
```

## 19 顺时针打印矩阵

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.

```cpp
class Solution
{
  public:
    vector<int> printMatrix(vector<vector<int>> matrix)
    {
        vector<int> ret;
        int m = matrix.size();
        if (m == 0)
            return ret;
        int n = matrix[0].size();

        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};

        int x = 0, y = 0;
        vector<vector<int>> visited(m, vector<int>(n, 0));
        int pos = 0;
        for (int i = 0; i < m * n; i++)
        {
            ret.push_back(matrix[x][y]);
            visited[x][y] = 1;
            int xx = x + dx[pos];
            int yy = y + dy[pos];
            if (xx >= 0 && xx < m && yy >= 0 && yy < n && visited[xx][yy] == 0)
            {
                x = xx;
                y = yy;
            }
            else
            {
                pos = (pos + 1) % 4;
                x = x + dx[pos];
                y = y + dy[pos];
            }
        }
        return ret;
    }
};
```

## 20 包含min函数的栈 

定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间复杂度应为O（1））。

专门用一个栈去存储最小值即可

```cpp
class Solution
{
  public:
    stack<int> s1;
    stack<int> s2;

    void push(int x)
    {
        s1.push(x);
        if (s2.empty() || x <= min())
            s2.push(x);
    }
    void pop()
    {
        if (s1.top() == min())
            s2.pop();
        s1.pop();
    }
    int top()
    {
        return s1.top();
    }

    int min()
    {
        return s2.top();
    }
};
```

## 21 栈的压入、弹出

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）

构建一个栈来模拟进栈出栈，每次循环将pushV的内容进栈。并观察popV的数和栈顶是否相同，如果相同就同时出栈（对于popV来说是popindex++)。这样，执行到最后，如果栈是空的，那就是可能的出栈序列。

```cpp
class Solution
{
  public:
    bool IsPopOrder(vector<int> pushV, vector<int> popV)
    {
        stack<int> st;

        int popindex = 0;
        for (int i = 0; i < pushV.size(); i++)
        {
            st.push(pushV[i]);
            while (!st.empty() && popindex < popV.size() && popV[popindex] == st.top())
            {
                popindex++;
                st.pop();
            }
        }
        return st.empty();
    }
};
```

其实第一时间是想用map来做。对于先出栈的数，那么在该数前进栈、比该数后出栈的的数，一定是严格满足先进后出规则的。通过map记住其进栈顺序，进行判断即可。该方法主要是可以不用遍历整个pushV的内容，一旦发现不满足要求的情况，直接返回false。牛客网上这两种方法的时间复杂度差不多（3-5ms)。该方法空间复杂度甚至更低，感觉牛客网判题系统很不靠谱。

```cpp
class Solution
{
  public:
    bool IsPopOrder(vector<int> pushV, vector<int> popV)
    {
        if (pushV.size() != popV.size())
            return false;
        unordered_map<int, int> map1, map2;
        for (int i = 0; i < pushV.size(); i++)
        {
            map1[pushV[i]] = i;
            map2[popV[i]] = i;
        }
        int tempmax = 0;

        for (int i = 0; i < popV.size(); i++)
        {
            if (map1.find(popV[i]) == map1.end())
                return false;
            int pushpos = map1[popV[i]];

            for (int j = tempmax; j < pushpos; j++)
            {
                if (map2[pushV[j]] > map2[pushV[pushpos]] //比该数后出栈
                && map2[pushV[j]] < map2[pushV[j + 1]])  //在该数前进栈才满足
                    return false;
            }
            tempmax = pushpos;
        }
        return true;
    }
};
```

## 22 从上往下打印二叉树

层序遍历，使用队列。

```cpp
class Solution
{
  public:
    vector<int> PrintFromTopToBottom(TreeNode *root)
    {
        vector<int> ret;
        if (root == NULL)
            return ret;
        queue<TreeNode *> treeq;
        treeq.push(root);
        while (!treeq.empty())
        {
            ret.push_back(treeq.front()->val);
            if (treeq.front()->left)
                treeq.push(treeq.front()->left);

            if (treeq.front()->right)
                treeq.push(treeq.front()->right);
            treeq.pop();
        }

        return ret;
    }
};
```

## 23 二叉搜索树的后序遍历

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。

利用二叉搜索树的性质：左<根<右，将数组分成三个部分，最右边的数为根结点的值，作为pivot，将数组分成两个部分，如果不能分成小于pivot和大于pivot的两部分，就返回false，否则继续递归。当left >= right，即叶子结点或者NULL结点的时候，返回true。

```cpp
class Solution
{
  public:
    bool VerifySquenceOfBST(vector<int> sequence)
    {
        if (sequence.size() == 0)
            return false;
        int left = 0, right = sequence.size() - 1;

        return helper(sequence, left, right);
    }

    bool helper(vector<int> &sequence, int left, int right)
    {

        if (left >= right)
            return true;

        int pivot = sequence[right];
        int mid = right;
        for (int i = left; i < right; i++)
        {
            if (sequence[i] > pivot)
            {
                mid = i;
                break;
            }
        }

        for (int i = mid + 1; i < right; i++)
        {
            if (sequence[i] < pivot)
                return false;
        }

        return helper(sequence, left, mid - 1) && helper(sequence, mid, right - 1);
    }
};
```

## 24 二叉树中和为某一值的路径

输入一颗二叉树的跟节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。(注意: 在返回值的list中，数组长度大的数组靠前)

注意是从根结点到叶子结点的路径。在把满足条件的数组压入ret时，需要判断是不是叶子结点。

```cpp
class Solution
{
  public:
    vector<vector<int>> ret;
    vector<vector<int>> FindPath(TreeNode *root, int expectNumber)
    {
        vector<int> temp;
        helper(root, temp, expectNumber);
        auto comp = [](vector<int> v1, vector<int> v2) { return v1.size() > v2.size(); };
        sort(ret.begin(), ret.end(), comp);
        return ret;
    }

    void helper(TreeNode *root, vector<int> &temp, int val)
    {
        if (root == NULL)
            return;

        if (root != NULL && root->left == NULL && root->right == NULL && root->val == val)
        {
            temp.push_back(val);
            ret.push_back(temp);
            temp.pop_back();
            return;
        }
        int tval = val - root->val;
        temp.push_back(root->val);
        helper(root->left, temp, tval);
        helper(root->right, temp, tval);

        temp.pop_back();
    }
};
```

## 25 复杂链表的复制

输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）

分三步：首先，在每个节点后插入一个新节点(next)

第二步：设置好random指针。（注意NULL）

第三步：将两个链表分离。注意指针操作的顺序。写反了就会出现NULL->next的情况。

```cpp
class Solution
{
  public:
    RandomListNode *Clone(RandomListNode *pHead)
    {
        if (pHead == NULL)
            return NULL;
        RandomListNode *p = pHead;
        //在每个结点后复制一个新的结点
        while (p)
        {
            RandomListNode *temp = new RandomListNode(p->label);
            temp->next = p->next;
            p->next = temp;
            p = temp->next;
        }
        p = pHead;

        while (p)
        {
            if (p->random)
                p->next->random = p->random->next;
            p = p->next->next;
        }

        p = pHead;
        RandomListNode *ret = pHead, *rHead;
        rHead = p->next;
        while (p)
        {
            ret->next = p->next;
            ret = ret->next;
            p->next = ret->next;
            p = p->next;
        }
        return rHead;
    }
};
```

其实我第一反应是用Map来存random指针的对应关系。编码应该也比较复杂，而且空间复杂度高。

## 26 二叉搜索树与双向链表

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。

使用中序遍历，结合pre指针，用于记录中序遍历中，当前结点的上一个结点。

```cpp
class Solution
{
  public:
    TreeNode *Convert(TreeNode *pRootOfTree)
    {
        pre = NULL;
        head = NULL;
        inorder(pRootOfTree);
        return head;
    }

    TreeNode *pre;
    TreeNode *head;
    void inorder(TreeNode *root)
    {
        if (root == NULL)
            return;
        inorder(root->left);
        root->left = pre;
        if (pre != NULL)
            pre->right = root;

        pre = root;
        if (head == NULL)
            head = root;
        inorder(root->right);
    }
};
```

## 27 字符串的排列

输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。

要注意字符串可能是有重复的，所以在遍历的时候，如果两个字符相同，直接i++，跳过重复的遍历。

```cpp
class Solution
{
  public:
    vector<string> ret;

    void helper(string &str, string &temp, vector<bool> &visited)
    {
        if (temp.size() == str.size())
        {
            ret.push_back(temp);
            return;
        }

        for (int i = 0; i < str.length(); i++)
        {
            if (visited[i])
                continue;
            temp.push_back(str[i]);
            visited[i] = true;
            helper(str, temp, visited);
            visited[i] = false;
            temp.pop_back();

            while (i < str.length() - 1 && str[i] == str[i + 1])
                i++;
        }
    }
    vector<string> Permutation(string str)
    {

        if (str.length() == 0)
            return ret;
        sort(str.begin(), str.end());
        string temp;
        vector<bool> visited(str.length(), false);
        helper(str, temp, visited);

        return ret;
    }
};
```

## 28 数组中出现次数超过一半的数

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。

这道题和leetcode上的区别在于，这个超过一半的数不一定存在，所以需要在最后重新计数、判断一下。

```cpp
class Solution
{
  public:
    int MoreThanHalfNum_Solution(vector<int> numbers)
    {
        if (numbers.size() == 0)
            return 0;
        int ret = numbers[0];
        int count = 1;
        for (int i = 1; i < numbers.size(); i++)
        {
            if (count == 0)
            {
                ret = numbers[i];
                count++;
                continue;
            }
            if (numbers[i] == ret)
                count++;
            else
                count--;
        }
        count = 0;
        for (int val : numbers)
            if (val == ret)
                count++;
        return count > numbers.size() / 2 ? ret : 0;

        return ret;
    }
};
```

## 29 最小的k个数

输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。

使用优先队列。注意边界条件的判断。

```cpp
class Solution
{
  public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k)
    {

        vector<int> ret;
        if (input.size() == 0 || k <= 0 || k > input.size())
            return ret;

        priority_queue<int> q;
        int index = 0;

        while (index < input.size())
        {
            if (q.size() == k && input[index] < q.top())
            {
                q.pop();
            }

            if (q.size() < k && index < input.size())
            {
                q.push(input[index]);
            }
            index++;
        }

        while (!q.empty())
        {
            ret.push_back(q.top());
            q.pop();
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }
};
```

## 30 连续子数组的最大和

HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。给一个数组，返回它的最大连续子序列的和，你会不会被他忽悠住？(子向量的长度至少是1)

注意全是负数的情况。

```cpp
class Solution
{
  public:
    int FindGreatestSumOfSubArray(vector<int> array)
    {

        if (array.size() == 0)
            return 0;

        int ret = array[0];
        int maxval = array[0];
        for (int i = 1; i < array.size(); i++)
        {
            if (ret < 0)
                ret = array[i];
            else
                ret += array[i];
            maxval = max(maxval, ret);
        }
        return maxval;
    }
};
```

## 31 整数中1出现的次数

求出1~13的整数中1出现的次数,并算出100~1300的整数中1出现的次数？为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,但是对于后面问题他就没辙了。ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数（从1 到 n 中1出现的次数）。

```cpp
class Solution
{
  public:
    int NumberOf1Between1AndN_Solution(int n)
    {
        int ones = 0;
        for (long long m = 1; m <= n; m *= 10)
        {
            int a = n / m, b = n % m;
            ones += (a + 8) / 10 * m + (a % 10 == 1) * (b + 1);
        }
        return ones;
    }
};
```

## 32 把数组排成最小的数

输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。

先转成vector\<string\>，再直接排序。

```cpp
class Solution
{
  public:
    string PrintMinNumber(vector<int> numbers)
    {
        if (numbers.size() == 0)
            return "";

        vector<string> numstr;
        for (int i = 0; i < numbers.size(); i++)
            numstr.push_back(to_string(numbers[i]));

        auto comp = [](string s1, string s2) {
            return s1 + s2 < s2 + s1;
        };

        sort(numstr.begin(), numstr.end(), comp);
        string temp;
        for (int i = 0; i < numstr.size(); i++)
        {
            temp += numstr[i];
        }
        if (temp[0] == '0')
            return "0";
        return temp;
    }
};
```

## 33 丑数

把只包含质因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，因为它包含质因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。

这题好克我..第几次了，还是不会做

```cpp
class Solution
{
  public:
    int GetUglyNumber_Solution(int index)
    {
        if (index == 0)
            return 0;

        vector<int> ret(index, 1);

        vector<int> factor = {2, 3, 5};
        vector<int> seq(3, 0);
        for (int i = 1; i < index; i++)
        {
            vector<int> v(factor.size());
            int minval = INT_MAX;
            for (int j = 0; j < v.size(); j++)
            {
                v[j] = factor[j] * ret[seq[j]];
                minval = min(minval, v[j]);
            }
            ret[i] = minval;
            for (int j = 0; j < v.size(); j++)
            {
                if (v[j] == minval)
                    seq[j]++;
            }
        }
        return ret[index - 1];
    }
};
```

## 34 第一个只出现一次的字符

在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置, 如果没有则返回 -1（需要区分大小写）.

用数组记录所有字符出现的次数即可。

```cpp
class Solution
{
  public:
    int FirstNotRepeatingChar(string str)
    {

        vector<int> count(128, 0);

        for (int i = 0; i < str.length(); i++)
        {
            count[str[i]]++;
        }

        for (int i = 0; i < str.length(); i++)
        {
            if (count[str[i]] == 1)
                return i;
        }
        return -1;
    }
};
```

## 35 数组中的逆序对

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组,求出这个数组中的逆序对的总数P。并将P对1000000007取模的结果输出。 即输出P%1000000007

运用归并排序。

```cpp
class Solution
{
  public:
    long long count;
    void Merge(vector<int> &nums, int l, int m, int h)
    {
        vector<int> temp(nums.begin() + l, nums.begin() + m + 1);
        int i = l, j = m + 1;
        int k = l;

        while (i <= m || j <= h)
        {
            if (i > m)
            {
                nums[k] = nums[j++];
            }
            else if (j > h)
            {
                nums[k] = temp[i++ - l];
            }
            else if (temp[i - l] < nums[j])
            {

                nums[k] = temp[i++ - l];
            }
            else
            {
                nums[k] = nums[j++];
                count += m - i + 1;
            }
            k++;
        }
    }

    void MyMergeSort(vector<int> &nums, int l, int h)
    {
        if (l >= h)
            return;
        int m = (h + l) / 2;
        MyMergeSort(nums, l, m);
        MyMergeSort(nums, m + 1, h);
        Merge(nums, l, m, h);
    }

    void MergeSort(vector<int> &nums)
    {
        MyMergeSort(nums, 0, nums.size() - 1);
    }
    int InversePairs(vector<int> data)
    {
        count = 0;
        MergeSort(data);
        return (int)(count % 1000000007);
    }
};
```

## 36 两个链表的第一个公共结点

输入两个链表，找出它们的第一个公共结点。

```cpp
class Solution
{
  public:
    ListNode *FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2)
    {

        ListNode *p1 = pHead1;
        ListNode *p2 = pHead2;
        while (p1 != p2)
        {
            p1 = (p1 == NULL) ? pHead2 : p1->next;
            p2 = (p2 == NULL) ? pHead1 : p2->next;
        }
        return p1;
    }
};
```

## 37 数字在排序数组中出现的次数

统计一个数字在排序数组中出现的次数。

利用二分搜索，找到>=K的第一个数和>=K+1的第一个数。两个数的下标差就是出现次数。

```cpp
class Solution
{
  public:
    int Getfirstpos(vector<int> &data, int v)
    {
        int left = 0, right = data.size() - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (data[mid] >= v)
                right = mid - 1;
            else if (data[mid] < v)
                left = mid + 1;
        }
        return left;
    }

    int GetNumberOfK(vector<int> data, int k)
    {
        int p1 = Getfirstpos(data, k);
        int p2 = Getfirstpos(data, k + 1);
        if (p1 == data.size() || data[p1] != k)
            return 0;
        else
            return p2 - p1;
    }
};
```

## 38 求二叉树的深度

输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。

```cpp
class Solution
{
  public:
    int TreeDepth(TreeNode *pRoot)
    {
        return (pRoot == NULL) ? 0 : (max(TreeDepth(pRoot->left), TreeDepth(pRoot->right)) + 1);
    }
};
```

## 39 平衡二叉树

输入一棵二叉树，判断该二叉树是否是平衡二叉树。

```cpp
class Solution
{
  public:
    bool flag;
    bool IsBalanced_Solution(TreeNode *pRoot)
    {
        flag = true;
        height(pRoot);
        return flag;
    }
    int height(TreeNode *pRoot)
    {
        if (pRoot == NULL || flag == false)
            return 0;
        int dl = height(pRoot->left);
        int dr = height(pRoot->right);
        if ((dl > dr + 1) || (dl + 1 < dr))
            flag = false;
        return max(dl, dr) + 1;
    }
};
```

## 40 数组中只出现一次的数字

一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。

因为有两个不相同的数字，那么只需要找到这两个数字不相同的某一位，就可以添加条件判断，让他们分别和数组中的其他数字^运算，就能得到这两个数字。diff&=-diff操作可以得到一位是1（最右的一位），其他位是0，可以用来区分。

```cpp
class Solution
{
  public:
    void FindNumsAppearOnce(vector<int> data, int *num1, int *num2)
    {

        int diff = 0;
        for (auto num : data)
            diff ^= num;
        diff &= -diff;
        for (auto num : data)
        {
            if ((diff & num) == 0)
                *num1 ^= num;
            else
                *num2 ^= num;
        }
    }
};
```

## 41 和为S的连续正数序列

小明很喜欢数学,有一天他在做数学作业时,要求计算出9~16的和,他马上就写出了正确答案是100。但是他并不满足于此,他在想究竟有多少种连续的正数序列的和为100(至少包括两个数)。没多久,他就得到另一组连续正数和为100的序列:18,19,20,21,22。现在把问题交给你,你能不能也很快的找出所有和为S的连续正数序列? Good Luck!

滑动窗口。

```cpp
class Solution
{
  public:
    vector<vector<int>> FindContinuousSequence(int sum)
    {
        vector<vector<int>> ret;
        if (sum == 1)
            return ret;
        int l = 1, r = 1;
        int s = 1;

        while (l <= sum / 2)
        {
            if (s < sum)
                s += ++r;
            else if (s == sum)
            {
                vector<int> temp;
                for (int i = l; i <= r; i++)
                    temp.push_back(i);
                ret.push_back(temp);
                s -= l++;
                s += ++r;
            }
            else
                s -= l++;
        }

        return ret;
    }
};
```

## 42 和为S的两个数字

输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。

```cpp
class Solution
{
  public:
    vector<int> FindNumbersWithSum(vector<int> array, int sum)
    {
        vector<int> ret;
        if (array.size() < 2)
            return ret;
        int left = 0, right = array.size() - 1;

        while (left < right)
        {
            if ((array[left] + array[right]) < sum)
                left++;
            else if ((array[left] + array[right]) > sum)
                right--;
            else
            {
                ret.push_back(array[left]);
                ret.push_back(array[right]);
                return ret;
            }
        }
        return ret;
    }
};
```

## 43 左旋转字符串

汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。是不是很简单？OK，搞定它！

如果要求空间复杂度O(1)，就做三次旋转。

```cpp
class Solution
{
  public:
    string LeftRotateString(string str, int n)
    {
        if (str == "")
            return str;
        n = n % str.length();

        string dstr = str + str;
        return dstr.substr(n, str.length());
    }
};
```

## 44 翻转单词顺序列

牛客最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“student. a am I”。后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”。Cat对一一的翻转这些单词顺序可不在行，你能帮助他么？

```cpp
class Solution
{
  public:
    string ReverseSentence(string str)
    {

        int i = 0, j = 0;

        while (j <= str.length())
        {
            if (str[j] == 0 || str[j] == ' ')
            {
                Reverse(str, i, j - 1);
                i = j + 1;
            }
            j++;
        }
        Reverse(str, 0, str.length() - 1);
        return str;
    }

    void Reverse(string &str, int l, int r)
    {
        while (l < r)
        {
            char temp = str[l];
            str[l] = str[r];
            str[r] = temp;
            r--;
            l++;
        }
    }
};
```

## 45 扑克牌顺子

LL今天心情特别好,因为他去买了一副扑克牌,发现里面居然有2个大王,2个小王(一副牌原本是54张^_^)...他随机从中抽出了5张牌,想测测自己的手气,看看能不能抽到顺子,如果抽到的话,他决定去买体育彩票,嘿嘿！！“红心A,黑桃3,小王,大王,方片5”,“Oh My God!”不是顺子.....LL不高兴了,他想了想,决定大\小 王可以看成任何数字,并且A看作1,J为11,Q为12,K为13。上面的5张牌就可以变成“1,2,3,4,5”(大小王分别看作2和4),“So Lucky!”。LL决定去买体育彩票啦。 现在,要求你使用这幅牌模拟上面的过程,然后告诉我们LL的运气如何， 如果牌能组成顺子就输出true，否则就输出false。为了方便起见,你可以认为大小王是0。

```cpp
class Solution
{
  public:
    bool IsContinuous(vector<int> numbers)
    {

        if (numbers.size() != 5)
            return false;

        sort(numbers.begin(), numbers.end());
        if (numbers[4] == 0)
            return false;

        int count = 0;
        for (auto num : numbers)
            if (num == 0)
                count++;

        for (int i = count; i < 4; i++)
        {
            if (numbers[i + 1] == numbers[i])
                return false;
            count -= numbers[i + 1] - numbers[i] - 1;
        }

        return count >= 0;
    }
};
```

## 46 孩子们的游戏（圆圈中最后剩下的数）

每年六一儿童节,牛客都会准备一些小礼物去看望孤儿院的小朋友,今年亦是如此。HF作为牛客的资深元老,自然也准备了一些小游戏。其中,有个游戏是这样的:首先,让小朋友们围成一个大圈。然后,他随机指定一个数m,让编号为0的小朋友开始报数。每次喊到m-1的那个小朋友要出列唱首歌,然后可以在礼品箱中任意的挑选礼物,并且不再回到圈中,从他的下一个小朋友开始,继续0...m-1报数....这样下去....直到剩下最后一个小朋友,可以不用表演,并且拿到牛客名贵的“名侦探柯南”典藏版(名额有限哦!!^_^)。请你试着想下,哪个小朋友会得到这份礼品呢？(注：小朋友的编号是从0到n-1)

```cpp
class Solution
{
  public:
    int LastRemaining_Solution(int n, int m)
    {
        if (n == 0) /* 特殊输入的处理 */
            return -1;
        if (n == 1) /* 递归返回条件 */
            return 0;
        return (LastRemaining_Solution(n - 1, m) + m) % n;
    }
};
```

用循环链表模拟：

```cpp
class Solution
{
  public:
    int LastRemaining_Solution(int n, int m)
    {

        list<int> linklist;
        for (int i = 0; i < n; i++)
            linklist.push_back(i);

        int forward = 0;
        auto it = linklist.begin();
        while (linklist.size() != 1)
        {
            int count = linklist.size();
            forward = m % count;
            if (forward == 0)
                forward = m;
            for (int i = 1; i < forward; i++)
            {
                it++;
                if (it == linklist.end())
                    ++it;
            }
            auto next = it;
            next++;
            if (next == linklist.end())
                next++;
            linklist.erase(it);
            it = next;
        }
        return *it;
    }
};
```

## 47 求1+2+3+...+n

求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

短路运算。或者定义二位数组，返回sizeof。

```cpp
class Solution
{
  public:
    int Sum_Solution(int n)
    {
        int ret = 0;
        (n > 0) && (ret = Sum_Solution(n - 1) + n);
        return ret;

        bool a[n][n + 1];
        return sizeof(a) >> 1;
    }
};
```

## 48 不用加减乘除做加法

写一个函数，求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号。

^运算可以得到不考虑进位的结果。

&运算可以找到哪里会产生进位(1+1)，进位之后左移一位，即是进位的结果。

将^或结果与进位结果相加，直到没有产生进位，那么此时^得到的值就是两数相加的值。

```cpp
class Solution
{
  public:
    int Add(int num1, int num2)
    {
        int temp;
        while (num2 != 0)
        {
            temp = num1 ^ num2;        //  计算不带进位的情况
            num2 = (num1 & num2) << 1; //  计算带进位的情况
            num1 = temp;
        }

        return num1;
    }
};
```

## 49 把字符串转成整数

将一个字符串转换成一个整数(实现Integer.valueOf(string)的功能，但是string不符合数字要求时返回0)，要求不能使用字符串转换整数的库函数。 数值为0或者字符串不是一个合法的数值则返回0。

```cpp
class Solution
{
  public:
    int StrToInt(string str)
    {
        if (str == "")
            return 0;
        bool negative = false;
        if (str[0] == '-')
            negative = true;
        int ret = 0;
        int i = 0;
        for (int i = 0; str[i]; i++)
        {
            if (i == 0 && (str[i] == '+' || str[i] == '-'))
                continue;
            if (str[i] >= '0' && str[i] <= '9')
                ret = ret * 10 + str[i] - '0';
            else
                return 0;
        }
        return negative ? -ret : ret;
    }
};
```

## 50 数组中重复的数字

在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。

```cpp
class Solution
{
  public:
    bool duplicate(int numbers[], int length, int *duplication)
    {
        vector<int> count(length, 0);
        for (int i = 0; i < length; i++)
        {
            count[numbers[i]]++;
            if (count[numbers[i]] == 2)
            {
                *duplication = numbers[i];
                return true;
            }
        }
        return false;
    }
};
```

## 51 构建乘积数组

给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]\*[1]\*...\*A[i-1]\*A[i+1]\*...\*A[n-1]。不能使用除法。

```cpp
class Solution
{
  public:
    vector<int> multiply(const vector<int> &A)
    {
        vector<int> ret(A.size(), 1);
        if (A.size() <= 1)
            return ret;
        vector<int> left(A.size(), 1);
        vector<int> right(A.size(), 1);
        left[0] = A[0];
        for (int i = 1; i < A.size() - 1; i++)
        {
            left[i] = A[i] * left[i - 1];
        }
        right[A.size() - 1] = A.back();
        for (int i = A.size() - 2; i >= 1; i--)
        {
            right[i] = A[i] * right[i + 1];
        }

        ret[0] = right[1];
        ret[A.size() - 1] = left[A.size() - 2];
        for (int i = 1; i < A.size() - 1; i++)
            ret[i] = left[i - 1] * right[i + 1];
        return ret;
    }
};
```

## 52 正则表达式匹配

```text
请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配
```

注意处理*，以及dp[i][j]对应的字符是str[i-1]和pattern[j-1]

```cpp
class Solution
{
  public:
    bool match(char *str, char *pattern)
    {
        int m = strlen(str);
        int n = strlen(pattern);
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;

        for (int i = 1; i <= m; i++)
            dp[i][0] = false;
        for (int j = 1; j <= n; j++)
            dp[0][j] = j > 1 && pattern[j - 1] == '*' && dp[0][j - 2];

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (str[i - 1] == pattern[j - 1] || pattern[j - 1] == '.')
                    dp[i][j] = dp[i - 1][j - 1];
                else if (pattern[j - 1] == '*')
                    dp[i][j] = dp[i][j - 2] || (dp[i - 1][j] && (str[i - 1] == pattern[j - 2] || pattern[j - 2] == '.'));
            }
        }

        return dp[m][n];
    }
};
```

## 53 表示字符的字符串

请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。

+-号单独考虑，记录e和.只能出现一次。

```cpp
class Solution
{
  public:
    bool isNumeric(char *string)
    {
        if (string == NULL)
            return false;
        char *p = string;
        if (*p == '+' || *p == '-')
            p++;
        if (*p == 0)
            return false;
        bool hase = false, haspoint = false;
        while (*p)
        {
            if (*p >= '0' && *p <= '9')
                p++;
            else if (*p == 'e' || *p == 'E')
            {
                if (hase)
                    return false;
                p++;
                hase = true;
                if (*p == '+' || *p == '-')
                    p++;
                if (*p == 0)
                    return false;
            }
            else if (*p == '.')
            {
                if (haspoint || hase)
                    return false;
                p++;
                haspoint = true;
            }
            else
                return false;
        }
        return true;
    }
};
```

## 54 字符流中第一个不重复的字符

请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。如果当前字符流没有存在出现一次的字符，返回#字符。

用队列来存储字符串的顺序，用count来记录个数。当队头字符的个数达到2时，就出队。

```cpp
class Solution
{
  public:
    //Insert one char from stringstream

    queue<char> q;
    vector<int> count;

    Solution()
    {
        count = vector<int>(256, 0);
    }

    void Insert(char ch)
    {
        count[ch]++;
        q.push(ch);
        while (!q.empty() && count[q.front()] >= 2)
            q.pop();
    }
    //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        return q.empty() ? '#' : q.front();
    }
};
```

## 55 链表中环的入口结点

给一个链表，若其中包含环，请找出该链表的环的入口结点，否则，输出null。

重点是要找到环的入口。容易证明，当快慢指针第一次相遇的时候，fast到入口的距离和头结点到入口的距离是相等的。利用这一性质，即可以找到入口。

```cpp
class Solution
{
  public:
    ListNode *EntryNodeOfLoop(ListNode *pHead)
    {
        if (pHead == NULL)
            return NULL;
        ListNode *fast = pHead, *slow = pHead;
        do
        {
            if (fast == NULL || fast->next == NULL)
                return NULL;
            fast = fast->next->next;
            slow = slow->next;
        } while (fast != slow);
        slow = pHead;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }

        return slow;
    }
};
```

## 56 删除链表中重复的结点

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5

申请一个dummy结点。

```cpp
class Solution
{
  public:
    ListNode *deleteDuplication(ListNode *pHead)
    {
        ListNode *dummy = new ListNode(INT_MAX);
        dummy->next = pHead;
        ListNode *last = dummy;
        ListNode *temp = pHead;
        while (temp && temp->next)
        {
            if (temp->val != temp->next->val)
            {
                last = temp;
                temp = temp->next;

                continue;
            }
            while (temp && temp->next && temp->val == temp->next->val)
            {
                temp->next = temp->next->next;
            }
            last->next = temp->next;
            temp = temp->next;
        }

        return dummy->next;
    }
};
```

## 57 二叉树的下一个结点

给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。

分情况，如果有右子树，那么就找到右子树最左的结点。如果没有右子树，就往上找，直到当前结点是父节点的左子树或NULL时，返回。

```cpp
class Solution
{
  public:
    TreeLinkNode *GetNext(TreeLinkNode *pNode)
    {
        if (pNode == NULL)
            return NULL;
        if (pNode->right)
        {
            TreeLinkNode *p = pNode->right;
            while (p->left)
                p = p->left;
            return p;
        }
        else
        {
            TreeLinkNode *p = pNode;
            while (p->next && (p->next->right == p))
                p = p->next;
            return p->next;
        }
    }
};
```

## 58 对称的二叉树

请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。

```cpp
class Solution
{
  public:
    bool isSymmetrical(TreeNode *pRoot)
    {
        return isMirror(pRoot, pRoot);
    }

    bool isMirror(TreeNode *root1, TreeNode *root2)
    {
        if (root1 == NULL && root2 == NULL)
            return true;
        else if (root1 == NULL || root2 == NULL)
            return false;
        if (root1->val != root2->val)
            return false;
        return isMirror(root1->left, root2->right) && isMirror(root1->right, root2->left);
    }
};
```

## 59 按之字形顺序打印二叉树

请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。

使用两个栈保存。一个栈保存奇数层，一个栈保存偶数层。左右子树按照不同的顺序进栈。

```cpp
class Solution
{
  public:
    vector<vector<int>> Print(TreeNode *pRoot)
    {
        vector<vector<int>> ret;
        if (pRoot == NULL)
            return ret;
        stack<TreeNode *> q;
        stack<TreeNode *> s;
        q.push(pRoot);
        int level = 1;
        while (!q.empty() || !s.empty())
        {
            vector<int> temp;
            if (!q.empty())
            {
                while (!q.empty())
                {
                    TreeNode *p = q.top();
                    temp.push_back(p->val);
                    q.pop();
                    if (p->left)
                        s.push(p->left);
                    if (p->right)
                        s.push(p->right);
                }
            }
            else
            {
                while (!s.empty())
                {
                    TreeNode *p = s.top();
                    temp.push_back(p->val);
                    s.pop();
                    if (p->right)
                        q.push(p->right);
                    if (p->left)
                        q.push(p->left);
                }
            }
            ret.push_back(temp);
        }
        return ret;
    }
};
```

## 60 把二叉树打印成多行

从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。

```cpp
class Solution
{
  public:
    vector<vector<int>> Print(TreeNode *pRoot)
    {
        vector<vector<int>> ret;
        if (pRoot == NULL)
            return ret;
        queue<TreeNode *> q;
        q.push(pRoot);
        while (!q.empty())
        {
            int count = q.size();
            vector<int> temp;
            for (int i = 0; i < count; i++)
            {
                TreeNode *p = q.front();
                temp.push_back(p->val);
                q.pop();
                if (p->left)
                    q.push(p->left);
                if (p->right)
                    q.push(p->right);
            }

            ret.push_back(temp);
        }
        return ret;
    }
};
```

## 61 序列化二叉树

请实现两个函数，分别用来序列化和反序列化二叉树

```cpp
class Solution
{
  public:
    char a[100000];
    char *Serialize(TreeNode *root)
    {
        ostringstream out;
        serialize(root, out);
        strcpy(a, out.str().c_str());
        return a;
    }
    TreeNode *Deserialize(char *str)
    {
        string data = str;
        istringstream in(data);
        return deserialize(in);
    }

  private:
    void serialize(TreeNode *root, ostringstream &out)
    {
        if (root)
        {
            out << root->val << ' ';
            serialize(root->left, out);
            serialize(root->right, out);
        }
        else
        {
            out << "# ";
        }
    }

    TreeNode *deserialize(istringstream &in)
    {
        string val;
        in >> val;
        if (val == "#")
            return nullptr;
        TreeNode *root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};
```

## 62 二叉搜索树的第k个结点

给定一棵二叉搜索树，请找出其中的第k小的结点。例如， （5，3，7，2，4，6，8）    中，按结点数值大小顺序第三小结点的值为4。

```cpp
class Solution
{
  public:
    int count;
    TreeNode *ans;
    TreeNode *KthNode(TreeNode *pRoot, int k)
    {
        count = 0;
        ans = NULL;
        Inorder(pRoot, k);
        return ans;
    }

    void Inorder(TreeNode *pRoot, int k)
    {
        if (pRoot == NULL || count >= k)
            return;
        Inorder(pRoot->left, k);
        count++;
        if (count == k)
        {
            ans = pRoot;
            return;
        }
        Inorder(pRoot->right, k);
    }
};
```

