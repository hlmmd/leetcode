# Problems

# 剑指offers

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

# leetcode Easy

## [28. Implement strStr()](https://leetcode.com/problems/implement-strstr/)

## [67. Add Binary](https://leetcode.com/problems/add-binary/)

## [69. Sqrt(x)](https://leetcode.com/problems/sqrtx/)

## [204. Count Primes](https://leetcode.com/problems/count-primes/)

## [219. Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/)

## [405. Convert a Number to Hexadecimal](https://leetcode.com/problems/convert-a-number-to-hexadecimal)

## [437. Path Sum III](https://leetcode.com/problems/path-sum-iii/)

## [448. Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/)

## [459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/)

## [461. Hamming Distance](https://leetcode.com/problems/hamming-distance/)

## [463. Island Perimeter](https://leetcode.com/problems/island-perimeter/)

## [476. Number Complement](https://leetcode.com/problems/number-complement/)

## [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)

## [572. Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/)

## [581. Shortest Unsorted Continuous Subarray](https://leetcode.com/problems/shortest-unsorted-continuous-subarray/)

## [594. Longest Harmonious Subsequence](https://leetcode.com/problems/longest-harmonious-subsequence/)

## [605. Can Place Flowers](https://leetcode.com/problems/can-place-flowers/)

## [617. Merge Two Binary Trees](https://leetcode.com/problems/merge-two-binary-trees/)

## [665. Non-decreasing Array](https://leetcode.com/problems/non-decreasing-array/)

## [669. Trim a Binary Search Tree](https://leetcode.com/problems/trim-a-binary-search-tree/)

## [706. Design HashMap](https://leetcode.com/problems/design-hashmap/)

## [707. Design Linked List](https://leetcode.com/problems/design-linked-list/)

## [754. Reach a Number](https://leetcode.com/problems/reach-a-number/)

## [766. Toeplitz Matrix](https://leetcode.com/problems/toeplitz-matrix/)

# leetcode Medium

## [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

## [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)

## [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/)

## [15. 3Sum](https://leetcode.com/problems/3sum/)

## [18. 4Sum](https://leetcode.com/problems/4sum/)

## [24. Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/)

## [31. Next Permutation](https://leetcode.com/problems/next-permutation/)

## [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

# leetcode Hard