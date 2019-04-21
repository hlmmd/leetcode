# Hard1



##  23. Merge k Sorted Lists

将多个有序的链表合并成一个有序的链表。

用到的数据结构：

优先队列、小根堆

使用优先队列，对链表进行排序，使得在队首的链表的第一个结点的值最小。

这样，每次都直接从优先队列中获取第一个链表的第一个结点，再将剩下的链表放回优先队列中待用。这样每次都保证取出来的结点是最小的结点。

```cpp
class Solution
{
  public:
    struct compare
    {
        bool operator()(const ListNode *l, const ListNode *r)
        {
            return l->val > r->val;
        }
    };
    ListNode *mergeKLists(vector<ListNode *> &lists)
    { //priority_queue
        priority_queue<ListNode *, vector<ListNode *>, compare> q;
        for (auto l : lists)
        {
            if (l)
                q.push(l);
        }
        if (q.empty())
            return NULL;

        ListNode *result = q.top();
        q.pop();
        if (result->next)
            q.push(result->next);
        ListNode *tail = result;
        while (!q.empty())
        {
            tail->next = q.top();
            q.pop();
            tail = tail->next;
            if (tail->next)
                q.push(tail->next);
        }
        return result;
    }
};
```



##  32. Longest Valid Parentheses

求最长合法匹配的括号子串。





## 37.Sudoku Solver

解数独。回溯算法，遍历整个数独，找到空白位置'.'

尝试将1-9分别填入该空中，判断填入后数独是否合法，如果合法就继续往下搜索，如果不合法，就继续尝试。如果1-9均不能满足，说明该层搜索不存在解，将其还原成'.'，往上回溯。

```cpp
class Solution
{
  public:
    bool isValid(vector<vector<char>> &board, int row, int col, char c)
    {
        for (int i = 0; i < 9; i++)
        {
            if (board[i][col] == c)
                return false; //check row
            if (board[row][i] == c)
                return false; //check column
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
                return false; //check 3*3 block
        }
        return true;
    }

    void solveSudoku(vector<vector<char>> &board)
    {
        if (board.size() == 0 || board[0].size() == 0)
            return;
        solve(board);
    }

    bool solve(vector<vector<char>> &board)
    {

        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] == '.')
                {
                    for (char ch = '1'; ch <= '9'; ch++)
                    {

                        if (isValid(board, i, j, ch))
                        {
                            board[i][j] = ch;
                            if (solve(board))
                                return true;
                            else
                                board[i][j] = '.';
                        }
                    }

                    return false;
                }
            }
        }
        return true;
    }
};

```

## 41.First Missing Positive

求出没有出现的最小正整数。

通过将对应的数交换到对应位置来判断。比如1应该被交换到nums\[0\]，2为nums\[1\]，这样比较nums\[i\]和i+1的关系就能得出是缺少哪一个数了。

对每一个处于\[1,n\]之间的数，都是需要做换位操作的。对其进行换位知道找到对应的位置，使得nums\[i\]==nums\[nums\[i\]-1\]。不在这个区间内的数可以忽略不管，没有影响。

```cpp
class Solution
{
  public:
    int firstMissingPositive(vector<int> &nums)
    {

        for (int i = 0; i < nums.size(); i++)
        {
            while (nums[i] >= 1 && nums[i] <= nums.size() &&
             nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != (i + 1))
                return i + 1;
        }

        return nums.size() + 1;
    }
};
```

## 42.Trapping Rain Water

数组给出一组高度，求去由此构成的形状能蓄多少水。如图所示。

![](.gitbook/assets/image%20%281%29.png)

对每一个位置分别计算。对于一个位置来说，其能蓄多少水取决于其左边最大值leftmax和右边最大值rightmax，值为min\(leftmax,rightmax\)-height。

用两个指针分别指向左右两侧，如果左边的值较小，那么此时min\(leftmax,rightmax\)必定是取决于左边，所以只需要考虑左边部分。比较当前指针指向的值height\[left\]和Leftmax的大小，如果leftmax较小，就更新其值，如果leftmax较大，则可以容纳leftmax-height\[left\]。对于右侧同理。

```cpp
class Solution
{
  public:
    int trap(vector<int> &height)
    {

        int left = 0, right = height.size() - 1;
        int leftmax = 0, rightmax = 0;
        int ret = 0;
        while (left <= right)
        {
            if (height[left] < height[right])
            {
                if (height[left] > leftmax)
                    leftmax = height[left];
                else
                    ret += leftmax - height[left];
                left++;
            }
            else
            {
                if (height[right] > rightmax)
                    rightmax = height[right];
                else
                    ret += rightmax - height[right];
                right--;
            }
        }
        return ret;
    }
};
```

## 44.Wildcard Matching

类似正则表达式的字符串匹配。动态规划。dp\[i\]\[j\]表示s的前i个字符和p前j个字符是否匹配。注意dp\[i\]\[j\]和s\[i-1\]\[s\[j-1\]对应。

首先dp\[0\]\[0\]=true，因为两个空串是匹配的。然后，给dp\[0\]\[j\]赋值，当p\[j-1\]为'\*'才能和空串匹配。而对于dp\[i\]\[0\]，s非空而p为空，必定不匹配。

处理了为0的下标后，不用考虑i-1、j-1越界的情况，方便编写代码。

如果p\[j-1\]是'\*'，那么可以匹配s的最后一个字符，所以dp\[i\]\[j\] = dp\[i-1\]\[j\]。或者\*匹配空串，dp\[i\]\[j\] = dp\[i\]\[j-1\]。二者满足一个即可，所以用或运算。

如果p\[j-1\]是'?'，则可以和s\[i-1\]匹配。或者s\[i-1\]==p\[j-1\]，直接匹配。此时dp\[i\]\[j\] = dp\[i-1\]\[j-1\]

其他情况均不匹配，dp\[i\]\[j\]保持false，不需要赋值。

```cpp
class Solution
{
  public:
    bool isMatch(string s, string p)
    {

        vector<vector<bool>> dp(s.length() + 1,
         vector<bool>(p.length() + 1, false));
        dp[0][0] = true;

        for (int j = 1; j <= p.length(); j++)
        {
            dp[0][j] = dp[0][j - 1] && p[j - 1] == '*';
        }

        for (int i = 1; i <= s.length(); i++)
        {
            for (int j = 1; j <= p.length(); j++)
            {
                if (p[j - 1] == '*')
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                else if (p[j - 1] == '?' || p[j - 1] == s[i - 1])
                    dp[i][j] = dp[i - 1][j - 1];
            }
        }
        return dp[s.length()][p.length()];
    }
};
```

还可以直接利用多指针直接解析，判断能否匹配。

i,j分别表示当前s、p的字符。先判断是否相同，p\[j\]是否是'?'。然后如果p\[j\]是'\*'，就用starindex来记录这个\*的下标，用si来记录此时i指针的值，用于回溯。记录后j++，因为'\*'可以当作空处理。如果之后不匹配再回退。当两个条件都不满足时，需要回退，重新匹配'\*'，用starindex找到上一个\*的位置，将j仍然赋值为其后一位。并将i也赋值为si（即之前i值）的后一位，这样表示用'\*'匹配了s中的第i个字符。

```cpp
class Solution
{
  public:
    bool isMatch(string s, string p)
    {
        int i = 0, j = 0;
        int si;
        int starindex = -1;
        while (s[i])
        {
            if (s[i] == p[j] || p[j] == '?')
            {
                i++;
                j++;
            }
            else if (p[j] == '*')
            {
                starindex = j;
                j++;
                si = i;
            }
            else if (starindex != -1)
            {
                j = starindex + 1;
                i = ++si;
            }
            else
                return false;
        }

        while (p[j] == '*')
            j++;
        return p[j] == 0;
    }
};
```

## 45.Jump Game II

从0开始跳，最少多少步能跳到末尾。nums\[i\]表示能跳的步数。

BFS。每一层遍历时求出最大能跳到的地方，如果满足就直接返回。

```cpp
class Solution
{
  public:
    int jump(vector<int> &nums)
    {

        if (nums.size() <= 1)
            return 0;
        int level = 0, currentMax = 0, i = 0, nextMax = 0;

        while (i < nums.size() && (currentMax - i + 1 > 0))
        {
            level++;
            for (; i <= currentMax; i++)
            {
                nextMax = max(nextMax, A[i] + i);
                if (nextMax >= n - 1)
                    return level;
            }
            currentMax = nextMax;
        }
        return 0;
    }
};
```

第一时间想到的解法是DP..

```cpp
class Solution
{
  public:
    int jump(vector<int> &nums)
    {

        vector<int> dp(nums.size() + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (j + nums[j] >= i)
                    dp[i] = min(dp[i], dp[j] + 1);
            }
        }
        return dp[nums.size() - 1];
    }
};
```

## 51.N-Queens

N皇后问题。求出所有解。

第一次做的时候，是将整个map全部遍历一次，但实际上因为每一行不能出现相同的皇后，所以每次只要安排第row行的皇后即可。这样只需要遍历n次，并安排合理的col值即可。

此外，在判断两条斜线方向是否有冲突的时候，只需要判断上半部分即可。因为从上往下遍历，下面在没有遍历到的情况下全是'.' 当row==n时表示完成遍历，得到一个解，将其放入ret中返回。

```cpp
class Solution
{
  public:
    vector<vector<string>> ret;

    vector<vector<string>> solveNQueens(int n)
    {
        string temp(n, '.');
        vector<string> solution(n, temp);
        helper(solution, 0, n);
        return ret;
    }

    void helper(vector<string> &map, int row, int n)
    {
        if (row == n){
            ret.push_back(map);
            return ;
        }
        for (int col = 0; col < n; col++)
        {
            if (IsValid(map, row, col, n))
            {
                map[row][col] = 'Q';
                helper(map, row + 1, n);
                map[row][col] = '.';
            }
        }
    }

    bool IsValid(vector<string> &map, int row, int col, int n)
    {
        for (int i = 0; i <= row; i++)
        {
            if (map[i][col] == 'Q')
                return false;
        }

        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
            if (map[i][j] == 'Q')
                return false;
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
            if (map[i][j] == 'Q')
                return false;
        return true;
    }
};
```

## 57.Insert Interval

合并区间。

```cpp
class Solution
{
  public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
    {
        auto comp = [](Interval &I1, Interval &I2) {
            return I1.start < I2.start;
        };
        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end(), comp);
        vector<Interval> ret;
        int pre = 0;
        ret.push_back(intervals[pre]);
        for (int i = 1; i < intervals.size(); i++)
        {

            if (ret[pre].end < intervals[i].start)
            {
                ret.push_back(intervals[i]);
                pre++;
            }
            else if (ret[pre].end < intervals[i].end)
                ret[pre].end = intervals[i].end;
        }

        return ret;
    }
};
```

## 72.Edit Distance

字符串编辑距离。word1可以通过三种操作：插入一个字符、删除一个字符、替换一个字符来变成word2。求从word1到word2的最小操作数。

动态规划，用dp\[i\]\[j\]表示字符串word1\[0,i\)到word2\[0,j\)的编辑距离。注意，dp\[i\]\[j\]对应word1\[i-1\]和word2\[j-1\]

如果word1\[i-1\]==word2\[j-1\]那么不需要进行修改，仍能保持相同，所以此时dp\[i\]\[j\] = dp\[i-1\]\[j-1\]。

如果word1\[i-1\]!=word2\[j-1\]，此时可能需要三种操作。

1：直接将word2\[j-1\]替换为word1\[i-1\]，此时dp\[i\]\[j\] = dp\[i-1\]\[j-1\]+1

2: word1\[0,i-1\)能编辑成word2\[0,j\)，那么word1\[0,i\)只需要删除word1\[i-1\]即可，dp\[i\]\[j\] = dp\[i-1\]\[j\]+1

3: word2直接添加一个字符，此时dp\[i\]\[j\] = dp\[i\]\[j-1\]+1

以上三种情况取最小值即可。

```cpp
class Solution
{
  public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; i++)
        {
            dp[i][0] = i;
        }
        for (int j = 1; j <= n; j++)
        {
            dp[0][j] = j;
        }
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
                }
            }
        }
        return dp[m][n];
    }
};
```

## 76.Minimum Window Substring

s包含t的最小子串。

滑动窗口。用一个map来记录t中字符出现次数。count用来表示出现次数复合要求的个数，当count==t.size\(\)的时候，s中的字符串包含t

设定begin和end两个指针，先移动end指针，将map对应的值+1，当s\[end\]在t中时，判断此时map\[s\[end\]\]的值是否小于等于0，如果满足，就将count++。当counter==t.size\(\)时，先判断此时的字符串长度d，并更新d和head（用来记录子串起始位置）。然后移动head指针，如果map\[s\[begin\]\]&lt;0，说明此时的窗口内的字符串已经不能包含t了，count--，跳出循环，继续往后移动end。

```cpp
class Solution
{
  public:
    string minWindow(string s, string t)
    {
        vector<int> map(128, 0);
        for (auto c : t)
            map[c]--;
        int counter = 0, begin = 0, end = 0, d = INT_MAX, head = 0;
        while (end < s.size())
        {
            map[s[end]]++;
            if (map[s[end]] <= 0)
                counter++;
            end++;

            while (counter == t.size())
            {
                if (end - begin < d)
                {
                    d = end - begin;
                    head = begin;
                }

                map[s[begin]]--;
                if (map[s[begin]] < 0)
                    counter--;

                begin++;
            }
        }

        return d == INT_MAX ? "" : s.substr(head, d);
    }
};
```



## 84.Largest Rectangle in Histogram

求面积最大的长方形。

用一个栈来存储高度的下标，当栈顶的高度比当前高度小的时候，直接进栈，所以栈内的高度是从底向顶递增的。如果栈顶比当前高度高，那么出栈，作为长方形的高。然后计算宽，通过当前下标i和最大高度的下标计算出长度。

```cpp
  class Solution {
    public:
        int largestRectangleArea(vector<int> &height) {
            
            int ret = 0;
            height.push_back(0);
            vector<int> index;
            
            for(int i = 0; i < height.size(); i++)
            {
                while(index.size() > 0 && height[index.back()] >= height[i])
                {
                    int h = height[index.back()];
                    index.pop_back();
                    
                    int sidx = index.size() > 0 ? index.back() : -1;
                    if(h * (i-sidx-1) > ret)
                        ret = h * (i-sidx-1);
                }
                index.push_back(i);
            }
            
            return ret;
        }
    };
```

## 85.Maximal Rectangle

## 97. [Interleaving String](https://leetcode.com/problems/interleaving-string)

判断字符串s1,s2能否组成s3。

dp

```cpp
class Solution
{
  public:
    bool isInterleave(string s1, string s2, string s3)
    {
        if (s3.length() != s1.length() + s2.length())
            return false;

        bool table[s1.length() + 1][s2.length() + 1];

        for (int i = 0; i < s1.length() + 1; i++)
            for (int j = 0; j < s2.length() + 1; j++)
            {
                if (i == 0 && j == 0)
                    table[i][j] = true;
                else if (i == 0)
                    table[i][j] = (table[i][j - 1] && 
                    s2[j - 1] == s3[i + j - 1]);
                else if (j == 0)
                    table[i][j] = (table[i - 1][j] && 
                    s1[i - 1] == s3[i + j - 1]);
                else
                    table[i][j] = (table[i - 1][j] && 
                    s1[i - 1] == s3[i + j - 1]) ||
                     (table[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
            }

        return table[s1.length()][s2.length()];
    }
};
```

## 132. Palindrome Partitioning II

求一个字符串最少分成多少个子串，使得所有子串都是回文序列。

动态规划，对于0-i子串，假设需要dp[i]次分割。那么对于dp[i+1]，考虑以s[i]作为中心的回文序列，求min(dp[i+j+1],dp[i-j]+1)，其中j为到字符s[i]的距离。

```cpp
class Solution
{
  public:
    int minCut(string s)
    {
        int n = s.size();
        vector<int> dp( n+1,0);

        //s的(0,i)子串最大切分数目为i-1，即全部分成单个字符，注意，要将字符串为0赋值为-1
        for(int i = 0;i<dp.size();i++)
            dp[i]=i-1;
        for(int i = 0;i<n;i++)
        {
            //分奇偶两种情况。j表示到i的距离。如果从i-j到i+j都是回文串，
            //那么对 dp[i+j+1]，可以将[i-j]到[i+j]作为一个分割。
            //其值是dp[i-j]+1，与原值比较取较小值即可
            for(int j = 0;j<=i && i+j<n && s[i-j]==s[i+j];j++)
                dp[i+j+1] = min(dp[i+j+1],dp[i-j]+1);
            for(int j = 1;j<=i+1 && i+j<n && s[i+1-j]==s[i+j];j++)
                dp[i+j+1] = min(dp[i+j+1],dp[i+1-j]+1);


        }
        return dp[n];
    }
};
```

## 146. LRU Cache

实现一个LRU，使get()获取一个页面put()添加一个页面的时间复杂度均为O(1)

使用哈希表+双向链表。

Cachelist是一个list，用来实现O(1)时间内删除结点。当一个结点被touch(put或者get时)，将其从原链表中删除，再插入表头。如果发生缺页，没有命中，那么直接删除表尾，将新的页面加入表头。

```cpp
class LRUCache
{
  public:
    int cap;
    list<int> Cachelist;
    unordered_map<int, list<int>::iterator> pos_dict;
    unordered_map<int, int> value_dict;

    LRUCache(int capacity)
    {
        cap = capacity;
    }

    int get(int key)
    {
        if (value_dict.find(key) == value_dict.end())
            return -1;
        touch(key);
        return value_dict[key];
    }
    int touch(int key)
    {

        auto pos = pos_dict.find(key);
        if (pos == pos_dict.end() && Cachelist.size() == cap)
        {
            int old = Cachelist.back();
            Cachelist.pop_back();
            value_dict.erase(old);
            pos_dict.erase(old);
        }
        else if (pos != pos_dict.end())
        {
            Cachelist.erase(pos[key]);
        }

        Cachelist.push_front(key);
        pos_dict[key] = Cachelist.begin();

        return 0;
    }
    void put(int key, int value)
    {

        touch(key);
        cache[key] = value;
    }
};

```

## 164. Maximum Gap

一个未排序的数组，求当数组有序后，相邻两个数的最大差值。要求时间复杂度O(n)

最简单就是直接排序，但是时间复杂度不满足。需要使用桶排序。

将数组分组。因为最大的gap不会小于 (maxV - minV) / (nums.size() - 1)，所以将数组分成(maxV - minV) / bucketsize + 1个桶，每个桶内的两个数必定不会复合要求，因为其差值小于bucketsize。所以gap的值一定是在两个桶之间取得的。用下一个桶的最小值减去上一个桶的最大值，就能获得一个gap，取最大值即可。

```cpp
class Solution
{
  public:
    int maximumGap(vector<int> &nums)
    {

        if (nums.size() <= 1)
            return 0;

        int minV = INT_MAX;
        int maxV = INT_MIN;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > maxV)
                maxV = nums[i];
            if (nums[i] < minV)
                minV = nums[i];
        }

        int bucketsize = (maxV - minV) / (nums.size() - 1);

        if (bucketsize < 1)
            bucketsize = 1;
        int bucketnum = (maxV - minV) / bucketsize + 1;

        vector<int> minbucket(bucketnum, INT_MAX);
        vector<int> maxbucket(bucketnum, INT_MIN);

        for (auto num : nums)
        {
            int pos = (num - minV) / bucketsize;
            minbucket[pos] = min(num, minbucket[pos]);
            maxbucket[pos] = max(num, maxbucket[pos]);
        }

        int i = 0, j;
        int gap = maxbucket[0] - minbucket[0];
        while (i < bucketnum)
        {
            j = i + 1;
            while (j < bucketnum && minbucket[j] == INT_MAX && maxbucket[j] == INT_MIN)
                j++;
            if (j == bucketnum)
                break;
            gap = max(gap, minbucket[j] - maxbucket[i]);
            i = j;
        }
        return gap;
    }
};
```

## 174. Dungeon Game

打怪游戏。最少需要多少初始血量才能救到公主。主要难点是必须保证每一步的血量都不低于1。

依然是动态规划，不过是在底部和右侧添加dummy，并从右下角往左上角遍历。当需要的血量>0时，记为1.

```cpp
class Solution
{
  public:
    int calculateMinimumHP(vector<vector<int>> &dungeon)
    {
        int M = dungeon.size();
        int N = dungeon[0].size();
        vector<vector<int>> hp(M + 1, vector<int>(N + 1, INT_MAX));
        hp[M][N - 1] = 1;
        for (int i = M - 1; i >= 0; i--)
        {
            for (int j = N - 1; j >= 0; j--)
            {
                int need = min(hp[i + 1][j], hp[i][j + 1]) - dungeon[i][j];
                hp[i][j] = need <= 0 ? 1 : need;
            }
        }
        return hp[0][0];
    }
};
```

## 188. Best Time to Buy and Sell Stock IV

买卖股票的时机。当有至多k次交易机会时，最大能够获利多少？

当k的值比较大的时候，可以简单计算，因为交易次数充足。

当k较小时，使用动态规划，dp[k][len]表示股票[0,len]序列在最多k次交易的情况下能够获得的最大利润。

动态规划基本公式：

```cpp
    dp[k, i] = max(dp[k, i-1], prices[i] - prices[j] + dp[k-1, j-1]), j=[0..i-1]
```

先对k循环，再对len循环。tmpmin用来记录当前最小的买入值。用price[j]-tmpmin能够获取当前的最大利润。对于股票prices[j]，如果没有使用，那么dp[i][j]=dp[i][j-1]，如果使用了，那么dp[i][j] = prices[j]-tmpmin。

tmpmin则可以`prices[j] - dp[i - 1][j - 1]`计算得来。即在prices[j]的基础上减去之前计算的结果，求一个最小值。

```cpp
class Solution
{
  public:
    int maxProfit(int k, vector<int> &prices)
    {
        int len = prices.size();
        if (k >= len / 2)
        {
            int ret = 0;
            for (int i = 1; i < len; i++)
                //当交易次数充足时，只要是递增的相邻两数，都可以获利
                if (prices[i] > prices[i - 1])
                    ret += prices[i] - prices[i - 1];
            return ret;
        }

        vector<vector<int>> dp(k + 1, vector<int>(len, 0));
        for (int i = 1; i <= k; i++)
        {
            int tmpmin = prices[0];
            for (int j = 1; j < len; j++)
            {
                tmpmin = min(tmpmin, prices[j] - dp[i - 1][j - 1]);
                dp[i][j] = max(dp[i][j - 1], prices[j] - tmpmin);
            }
        }

        return dp[k][len - 1];
    }
};
```

## 212. Word Search II

先建立字典树存储所有的单词，并用is_end来表示单词的结尾。

然后使用DFS来遍历整个board，当遍历到is_end的单词节点时，将该单词添加到result中。

```cpp
class TrieNode
{
  public:
    bool is_end;
    vector<TrieNode *> children;
    TrieNode()
    {
        is_end = false;
        children = vector<TrieNode *>(26, NULL);
    }
};

class Trie
{
  public:
    TrieNode *getRoot() { return root; }
    Trie(vector<string> &words)
    {
        root = new TrieNode();
        for (int i = 0; i < words.size(); ++i)
            addWord(words[i]);
    }
    void addWord(const string &word)
    {
        TrieNode *cur = root;
        for (int i = 0; i < word.size(); ++i)
        {
            int index = word[i] - 'a';
            if (cur->children[index] == NULL)
                cur->children[index] = new TrieNode();
            cur = cur->children[index];
        }
        cur->is_end = true;
    }

  private:
    TrieNode *root;
};

class Solution
{
  public:
    vector<string> findWords(vector<vector<char>> &board, vector<string> &words)
    {
        Trie *trie = new Trie(words);
        TrieNode *root = trie->getRoot();
        set<string> result_set;
        for (int x = 0; x < board.size(); ++x)
            for (int y = 0; y < board[0].size(); ++y)
                findWords(board, x, y, root, "", result_set);

        vector<string> result;
        for (auto it : result_set)
            result.push_back(it);
        return result;
    }

  private:
    void findWords(vector<vector<char>> &board, int x, int y, TrieNode *root, string word, set<string> &result)
    {
        if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size() || board[x][y] == ' ')
            return;

        if (root->children[board[x][y] - 'a'] != NULL)
        {
            word = word + board[x][y];
            root = root->children[board[x][y] - 'a'];
            if (root->is_end)
                result.insert(word);
            char c = board[x][y];
            board[x][y] = ' ';
            findWords(board, x + 1, y, root, word, result);
            findWords(board, x - 1, y, root, word, result);
            findWords(board, x, y + 1, root, word, result);
            findWords(board, x, y - 1, root, word, result);
            board[x][y] = c;
        }
    }
};
```

## 224. Basic Calculator

实现一个简单的加减括号计算器。

```cpp
class Solution
{
  public:
    int calculate(string s)
    {
        long long  total = 0;
        vector<int> signs(2, 1);
        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            if (c >= '0')
            {
                long long number = 0;
                while (i < s.size() && s[i] >= '0')
                    number = 10 * number + s[i++] - '0';
                total += signs.back() * number;
                signs.pop_back();
                i--;
            }
            else if (c == ')')
                signs.pop_back();
            else if (c != ' ')
                signs.push_back(signs.back() * (c == '-' ? -1 : 1));
        }
        return total;
    }
};
```

## 239. Sliding Window Maximum

给定一个数组，求所有长度为k的每一个滑动窗口中的最大值。

使用deque(双向队列)，队列中的数保持递减、个数小于k。这样既能满足滑动窗口大小的要求，又能在需要求最大值的时候，直接取队头。而且当窗口大小到达k时，可以直接把队头pop掉。

```cpp
class Solution
{
  public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {

        deque<int> dq;
        vector<int> ret;
        for (int i = 0; i < nums.size(); i++)
        {
            //当滑动窗口的大小大于k时，将第一个数出队列。
            if (!dq.empty() && dq.front() == i - k)
                dq.pop_front();
            //比较队尾和Nums[i]的关系，如果比nums[i]小，
            //这些值一定不能成为最终选用的值，不考虑，直接出队即可。
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();

            dq.push_back(i);

            //从k-1下表开始，开始写入答案，队头即最大值。
            if (i >= k - 1)
                ret.push_back(nums[dq.front()]);
        }
        return ret;
    }
};
```

## 297. Serialize and Deserialize Binary Tree

如何序列化一个二叉树并恢复。

给出 先序（递归）、层序（队列）两种方法。

```cpp
class Codec
{
  public:
    string serialize(TreeNode *root)
    {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    TreeNode *deserialize(string data)
    {
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

class Codec
{
  public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root) const
    {
        if (!root)
            return "[]";

        ostringstream os;
        os << "[" << root->val;
        int null_count = 0;
        queue<TreeNode *> q({root->left, root->right});
        while (!q.empty())
        {
            auto node = q.front();
            q.pop();
            if (node)
            {
                os << ',' << node->val;
                if (null_count > 0)
                {
                    os << ":" << null_count;
                    null_count = 0;
                }
                q.push(node->left);
                q.push(node->right);
            }
            else
            {
                ++null_count;
            }
        }

        os << "]";
        return os.str();
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data) const
    {
        istringstream is(data);
        TreeNode *root = nullptr;
        queue<TreeNode **> q({&root});

        int value, null_count;
        char sep;
        is >> sep >> value;
        while (is)
        {
            if (is.peek() == ':')
            {
                is >> sep >> null_count;
                for (int i = 0; i < null_count; ++i)
                    q.pop();
            }

            TreeNode *node = new TreeNode(value);
            q.push(&node->left);
            q.push(&node->right);
            *(q.front()) = node;
            q.pop();

            is >> sep >> value;
        }
        return root;
    }
};
```


