剑指offer题解

# 1 二维数组中的查找

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

# 2 替换空格

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

# 3 从尾到头打印链表

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


# 4 重建二叉树

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


# 5 用两个栈实现队列

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

# 6 旋转数组的最小数字

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


# 7 斐波那契数列

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


# 8 跳台阶

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

# 9 变态跳台阶

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

# 10 矩阵覆盖

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

# 11 二进制中1的个数

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

# 12 数值的整数次方

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

# 13 调整数组顺序使奇数位于偶数前面

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

# 14 链表中倒数第k个结点

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

# 15 反转链表

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

# 16 合并两个排序的链表

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

# 17 树的子结构

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

# 18 二叉树的镜像

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

# 19 顺时针打印矩阵

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

# 20 包含min函数的栈 

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

# 21 栈的压入、弹出

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

# 22 从上往下打印二叉树

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

# 23 二叉搜索树的后序遍历

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

# 24 二叉树中和为某一值的路径

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

# 25 复杂链表的复制

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

# 26 二叉搜索树与双向链表

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

# 27 字符串的排列

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

# 28 数组中出现次数超过一半的数

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

# 29 最小的k个数

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

# 30 连续子数组的最大和

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

# 31 整数中1出现的次数

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

# 32 把数组排成最小的数

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

# 33 丑数

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

# 34 第一个只出现一次的字符

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

# 35 数组中的逆序对

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

# 36 两个链表的第一个公共结点

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

# 37 数字在排序数组中出现的次数

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

# 38 求二叉树的深度

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

# 39 平衡二叉树

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