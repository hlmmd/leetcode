# 公司笔试题

## 字节跳动

### 字符串处理

```
我叫王大锤，是一家出版社的编辑。我负责校对投稿来的英文稿件，这份工作非常烦人，因为每天都要去修正无数的拼写错误。但是，优秀的人总能在平凡的工作中发现真理。我发现一个发现拼写错误的捷径：

1. 三个同样的字母连在一起，一定是拼写错误，去掉一个的就好啦：比如 helllo -> hello
2. 两对一样的字母（AABB型）连在一起，一定是拼写错误，去掉第二对的一个字母就好啦：比如 helloo -> hello
3. 上面的规则优先“从左到右”匹配，即如果是AABBCC，虽然AABB和BBCC都是错误拼写，应该优先考虑修复AABB，结果为AABCC
```

```cpp
#include <iostream>
#include <string>

using namespace std;

string Process(string str)
{
    string ret = "";
    if (str == "")
        return ret;
    ret += str[0];
    for (int i = 1; i < str.size(); i++)
    {
        if (str[i] != str[i - 1])
            ret += str[i];
        else
        {
            ret += str[i++];
            while (i < str.size() && str[i] == str[i - 1])
                i++;
            if (i >= str.size())
                return ret;
            ret += str[i++];
            while (i < str.size() && str[i] == str[i - 1])
                i++;
            if (i < str.size())
                ret += str[i];
        }
    }

    return ret;
}

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string str;
        cin >> str;
        cout << Process(str) << endl;
    }
    system("pause");
    return 0;
}
```

### q2

```
我叫王大锤，是一名特工。我刚刚接到任务：在字节跳动大街进行埋伏，抓捕恐怖分子孔连顺。和我一起行动的还有另外两名特工，我提议

1. 我们在字节跳动大街的N个建筑中选定3个埋伏地点。
2. 为了相互照应，我们决定相距最远的两名特工间的距离不超过D。

我特喵是个天才! 经过精密的计算，我们从X种可行的埋伏方案中选择了一种。这个方案万无一失，颤抖吧，孔连顺！
……
万万没想到，计划还是失败了，孔连顺化妆成小龙女，混在cosplay的队伍中逃出了字节跳动大街。只怪他的伪装太成功了，就是杨过本人来了也发现不了的！

请听题：给定N（可选作为埋伏点的建筑物数）、D（相距最远的两名特工间的距离的最大值）以及可选建筑的坐标，计算在这次行动中，大锤的小队有多少种埋伏选择。
注意：
1. 两个特工不能埋伏在同一地点
2. 三个特工是等价的：即同样的位置组合(A, B, C) 只算一种埋伏方法，不能因“特工之间互换位置”而重复使用
```

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int N, D;
    cin >> N >> D;
    if (N < 3)
        return 0;

    unsigned long long count = 0;

    vector<int> pos(N, 0);
    for (int i = 0; i < N; i++)
        cin >> pos[i];

    int left = 0, right = 2;

    while (right < N)
    {
        while (pos[right] - D > pos[left])
            left++;
        long long len = right - left + 1;
        if (len >= 3)
            count += (len - 2) * (len - 1) / 2;
        right++;
    }
    count %= 99997867;

    cout << count << endl;

    system("pause");
    return 0;
}
```

### 麻将胡牌

```
小包最近迷上了一款叫做雀魂的麻将游戏，但是这个游戏规则太复杂，小包玩了几个月了还是输多赢少。
于是生气的小包根据游戏简化了一下规则发明了一种新的麻将，只留下一种花色，并且去除了一些特殊和牌方式（例如七对子等），具体的规则如下：

总共有36张牌，每张牌是1~9。每个数字4张牌。
你手里有其中的14张牌，如果这14张牌满足如下条件，即算作和牌
14张牌中有2张相同数字的牌，称为雀头。
除去上述2张牌，剩下12张牌可以组成4个顺子或刻子。顺子的意思是递增的连续3个数字牌（例如234,567等），刻子的意思是相同数字的3个数字牌（例如111,777）

例如：
1 1 1 2 2 2 6 6 6 7 7 7 9 9 可以组成1,2,6,7的4个刻子和9的雀头，可以和牌
1 1 1 1 2 2 3 3 5 6 7 7 8 9 用1做雀头，组123,123,567,789的四个顺子，可以和牌
1 1 1 2 2 2 3 3 3 5 6 7 7 9 无论用1 2 3 7哪个做雀头，都无法组成和牌的条件。

现在，小包从36张牌中抽取了13张牌，他想知道在剩下的23张牌中，再取一张牌，取到哪几种数字牌可以和牌。
```

用递归，先找两个一样的，再找三个一样的，再找顺子

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool helper(vector<int> nums)
{
    for (int i = 1; i <= 9; i++)
    {

        if (nums[i] < 0)
            return false;

        if (nums[i] >= 3)
        {
            nums[i] -= 3;
            if (helper(nums))
                return true;
            nums[i] += 3;
        }

        if (nums[i] >= 1 && i <= 7)
        {
            nums[i] -= 1;
            nums[i + 1] -= 1;
            nums[i + 2] -= 1;
            if (helper(nums))
                return true;
            else
                return false;
        }
        else if (nums[i] >= 1 && i > 7)
            return false;
    }

    return true;
}

bool Try(vector<int> nums)
{
    for (int i = 1; i <= 9; i++)
    {
        if (nums[i] >= 2)
        {
            nums[i] -= 2;
            if (helper(nums))
                return true;
            nums[i] += 2;
        }
    }
    return false;
}

int main()
{

    vector<int> cards(13, 0);
    for (int i = 0; i < 13; i++)
        cin >> cards[i];

    vector<int> nums(10, 0);

    bool flag = false;

    for (int i = 0; i < cards.size(); i++)
    {
        nums[cards[i]]++;
    }

    for (int i = 1; i <= 9; i++)
    {
        if (nums[i] == 4)
            continue;
        auto temp = nums;
        temp[i]++;
        if (Try(temp))
        {
            flag = true;
            cout << i << " ";
        }
    }
    if (flag == false)
        cout << 0 << endl;

    system("pause");
    return 0;
}
```

### 特征提取

```
 小明是一名算法工程师，同时也是一名铲屎官。某天，他突发奇想，想从猫咪的视频里挖掘一些猫咪的运动信息。为了提取运动信息，他需要从视频的每一帧提取“猫咪特征”。一个猫咪特征是一个两维的vector<x, y>。如果x_1=x_2 and y_1=y_2，那么这俩是同一个特征。
       因此，如果喵咪特征连续一致，可以认为喵咪在运动。也就是说，如果特征<a, b>在持续帧里出现，那么它将构成特征运动。比如，特征<a, b>在第2/3/4/7/8帧出现，那么该特征将形成两个特征运动2-3-4 和7-8。
现在，给定每一帧的特征，特征的数量可能不一样。小明期望能找到最长的特征运动。
```

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int M;
        cin >> M;
        int out = 0;
        //key为frame，value 为 index和length对，分别表示上一个index的值和当前的长度
        //注意，unordered_map需要传入一个hash函数，才能将pair作为键值，而map是通过比较，所以不需要
        map<pair<int, int>, pair<int, int>> map;
        for (int j = 0; j < M; j++)
        {
            int count;
            cin >> count;
            for (int k = 0; k < count; k++)
            {
                if (out == 0)
                    out = 1;
                pair<int, int> frame;
                cin >> frame.first >> frame.second;

                auto it = map.find(frame);

                if (it == map.end())
                    map[frame] = pair<int, int>(j, 1);
                else
                {
                    //如果和上一帧连续，就++length，并更新out，否则将length重置为1，再更新index
                    if ((it->second.first + 1) == j)
                    {
                        it->second.second++;
                        out = max(out, it->second.second);
                    }
                    else
                    {
                        it->second.second = 1;
                    }

                    it->second.first = j;
                }
            }
        }
        cout << out << endl;
    }
    return 0;
}
```

### 机器人能量

逆推。或者用二分法

```
机器人正在玩一个古老的基于DOS的游戏。游戏中有N+1座建筑——从0到N编号，从左到右排列。编号为0的建筑高度为0个单位，编号为i的建筑的高度为H(i)个单位。 

起初， 机器人在编号为0的建筑处。每一步，它跳到下一个（右边）建筑。假设机器人在第k个建筑，且它现在的能量值是E, 下一步它将跳到第个k+1建筑。它将会得到或者失去正比于与H(k+1)与E之差的能量。如果 H(k+1) > E 那么机器人就失去 H(k+1) - E 的能量值，否则它将得到 E - H(k+1) 的能量值。

游戏目标是到达第个N建筑，在这个过程中，能量值不能为负数个单位。现在的问题是机器人以多少能量值开始游戏，才可以保证成功完成游戏？
```

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	int N;
	cin >> N;

	vector<int> height(N, 0);
	for (int i = 0; i < height.size(); i++)
		cin >> height[i];
	vector<int>dp(N + 1, 0);
	for (int i = N - 1; i >= 0; i--)
	{
		dp[i] = (height[i] + dp[i + 1] + 1) / 2;
	}
	cout << dp[0] << endl;
	return 0;
}
```

### 京东 紧急疏散

体育场突然着火了，现场需要紧急疏散，但是过道真的是太窄了，同时只能容许一个人通过。现在知道了体育场的所有座位分布，座位分布图是一棵树，已知每个座位上都坐了一个人，安全出口在树的根部，也就是1号结点的位置上。其他节点上的人每秒都能向树根部前进一个结点，但是除了安全出口以外，没有任何一个结点可以同时容纳两个及以上的人，这就需要一种策略，来使得人群尽快疏散，问在采取最优策略的情况下，体育场最快可以在多长时间内疏散完成。

输入描述:
第一行包含一个正整数n，即树的结点数量（1<=n<=100000）。 接下来有n-1行，每行有两个正整数x，y，表示在x和y结点之间存在一条边。(1<=x，y<=n)

输出描述:
输出仅包含一个正整数，表示所需要的最短时间

输入例子1:

6

2 1

3 2

4 3

5 2

6 1

输出例子1:

4

起始就是求根节点最大的子树结点个数。使用vector<list<int>> 来存储所有的边，再使用dfs进行遍历，求每一个结点的子树结点个数。在dfs时传入parent，避免重复遍历。

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


int dfs(vector<list<int>> &edge ,int node ,int parent)
{
	int ret = 1;

	for (auto it = edge[node].begin(); it != edge[node].end(); it++)
	{
		if (*it != parent)
		{
			ret += dfs(edge, *it, node);
		}
	}

	return ret;
}


int main()
{
	int N;
	cin >> N;

	vector<list<int>> edge(N+1, list<int>());

	for (int i = 0; i < N-1; i++)
	{
		int a, b;
		cin >> a >> b;
		edge[a].push_front(b);
		edge[b].push_front(a);
	}

	int ret = 0;
	for (auto it = edge[1].begin(); it != edge[1].end(); it++)
	{
		ret = max(ret, dfs(edge, *it,1));
	}

	cout << ret << endl;
	
	system("pause");
	return 0;
}
```

### 京东 寻找子串

给出m个字符串S1，S2，...，Sm和一个单独的字符串T。请在T中选出尽可能多的子串同时满足：  1）这些子串在T中互不相交。  2）这些子串都是S1，S2，...，Sm中的某个串。  问最多能选出多少个子串。

输入描述:

第一行一个数m（1≤m≤10），接下来m行，每行一个串。最后一行输入一个串T。输入中所有单个串的长度不超过100000，串中只会出现小写字母。

输出描述:

输出一个数，最多能选出多少串。

```
输入例子1:
3
aa
b
ac
bbaac

输出例子1:
3
```

贪心算法。先将s1-sm按照字符串的长度排序，优先找短的子串。在找到后，将s中的子串替换为"0"，再继续寻找即可。

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<string> strs(n);
    for (int i = 0; i < n; i++)
        cin >> strs[i];
    string s;
    cin >> s;
    auto comp = [](const string &s1, const string &s2) { return s1.size() < s2.size(); };
    sort(strs.begin(), strs.end(), comp);
    int count = 0;
    for (int i = 0; i < strs.size(); i++)
    {
        int pos = 0;
        while ((pos = s.find(strs[i], pos)) != -1)
        {
            count++;
            s.replace(pos, strs[i].size(), "0");
        }
    }
    cout << count << endl;
    system("pause");
    return 0;
}
```

### 招行 爱吃猫粮的小招喵

```
小招喵喜欢吃喵粮。这里有 N 堆喵粮，第 i 堆中有 p[i] 粒喵粮。喵主人离开了，将在 H 小时后回来。

小招喵可以决定她吃喵粮的速度 K （单位：粒/小时）。每个小时，她将会选择一堆喵粮，从中吃掉 K 粒。如果这堆喵粮少于 K 粒，她将吃掉这堆的所有喵粮，然后这一小时内不会再吃更多的喵粮。  

小招喵喜欢慢慢吃，但仍然想在喵主人回来前吃掉所有的喵粮。

返回她可以在 H 小时内吃掉所有喵粮的最小速度 K（K 为整数）。


输入描述:
第一行输入为喵粮数组，以空格分隔的N个整数

第二行输入为H小时数


输出描述:
最小速度K
示例1
输入
3 6 7 11
8
输出
4
```

最小可能值：猫粮总数/H，最大可能值：最大的一堆猫粮。确定了上下限后用二分进行查找

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <list>
#include <algorithm>
#include <string>
using namespace std;

bool helper(vector<int> &nums, int H, int v)
{
    int count = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        count += (nums[i] / v + ((nums[i] % v) != 0));
    }
    return count <= H;
}

int main()
{
    vector<int> nums;
    int n;
    while (cin >> n)
    {
        nums.push_back(n);
    }

    int H = nums.back();
    nums.pop_back();

    int sum = 0, m = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
        m = max(nums[i], m);
    }

    int m2 = sum / H;
    int l = m2, r = m;
    while (l < r)
    {
        int mid = (l + r) / 2;
        if (helper(nums, H, mid))
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << l << endl;

    system("pause");
    return 0;
}
```

### 网易 被3整除

```
小Q得到一个神奇的数列: 1, 12, 123,...12345678910,1234567891011...。

并且小Q对于能否被3整除这个性质很感兴趣。

小Q现在希望你能帮他计算一下从数列的第l个到第r个(包含端点)有多少个数可以被3整除。


输入描述:
输入包括两个整数l和r(1 <= l <= r <= 1e9), 表示要求解的区间两端。

输出描述:
输出一个整数, 表示区间内能被3整除的数字个数。

输入例子1:
2 5

输出例子1:
3

例子说明1:
12, 123, 1234, 12345...
其中12, 123, 12345能被3整除。
```

以3为一个循环。i%3==1则不可以，否则可以。对[i,j]进行计数即可。

```cpp
#include <iostream>
using namespace std;

int main()
{

    int l, r;
    cin >> l >> r;
    int ret = 0;
    ret += 2 * ((r - l + 1) / 3);
    int mod = (r - l + 1) % 3;

    if (mod == 1)
    {
        int k = l % 3;
        ret += (k != 1);
    }
    else if (mod == 2)
    {
        int k = l % 3;
        if (k == 2)
            ret += 2;
        else
            ret += 1;
    }

    cout << ret << endl;

    system("pause");
    return 0;
}
```

### 网易 安置路灯

```
小Q正在给一条长度为n的道路设计路灯安置方案。

为了让问题更简单,小Q把道路视为n个方格,需要照亮的地方用'.'表示, 不需要照亮的障碍物格子用'X'表示。

小Q现在要在道路上设置一些路灯, 对于安置在pos位置的路灯, 这盏路灯可以照亮pos - 1, pos, pos + 1这三个位置。

小Q希望能安置尽量少的路灯照亮所有'.'区域, 希望你能帮他计算一下最少需要多少盏路灯。


输入描述:
输入的第一行包含一个正整数t(1 <= t <= 1000), 表示测试用例数
接下来每两行一个测试数据, 第一行一个正整数n(1 <= n <= 1000),表示道路的长度。
第二行一个字符串s表示道路的构造,只包含'.'和'X'。

输出描述:
对于每个测试用例, 输出一个正整数表示最少需要多少盏路灯。

输入例子1:
2
3
.X.
11
...XX....XX

输出例子1:
1
3
```

贪心算法即可。每遍历到一个. 就+1，然后指针后移3（在这个.的下一位置放路灯）

```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int x = 0; x < t; x++)
    {
        int n;
        cin >> n;
        string str;
        cin >> str;
        int ret = 0;

        for (int i = 0; i < str.length();)
        {
            if (str[i] == '.')
            {
                ret++;
                i += 3;
            }
            else
                i++;
        }

        cout << ret << endl;
    }
    system("pause");
    return 0;
}
```

### 网易 牛牛的背包问题

```
牛牛准备参加学校组织的春游, 出发前牛牛准备往背包里装入一些零食, 牛牛的背包容量为w。
牛牛家里一共有n袋零食, 第i袋零食体积为v[i]。
牛牛想知道在总体积不超过背包容量的情况下,他一共有多少种零食放法(总体积为0也算一种放法)。

输入描述:
输入包括两行
第一行为两个正整数n和w(1 <= n <= 30, 1 <= w <= 2 * 10^9),表示零食的数量和背包的容量。
第二行n个正整数v[i](0 <= v[i] <= 10^9),表示每袋零食的体积。

输出描述:
输出一个正整数, 表示牛牛一共有多少种零食放法。

输入例子1:
3 10
1 2 4

输出例子1:
8

例子说明1:
三种零食总体积小于10,于是每种零食有放入和不放入两种情况，一共有2*2*2 = 8种情况。
```

dfs，注意在背包中所有的重量和小于w时，可以简化计算。另外不要用pow.

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <list>
#include <algorithm>
#include <string>
using namespace std;

int helper(vector<int> &nums, int start, int w)
{
    int ret = 1;

    for (int i = start; i < nums.size(); i++)
    {
        if (nums[i] > w)
        {
            return ret;
        }
        ret += helper(nums, i + 1, w - nums[i]);
    }
    return ret;
}

int main()
{
    int n;
    int w;
    cin >> n >> w;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    sort(nums.begin(), nums.end());
    long long sum = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
    }
    if (sum <= w)
    {
        int ans = 1;
        for (int i = 0; i < nums.size(); i++)
            ans *= 2;
        cout << ans << endl;
        return 0;
    }

    int ret = helper(nums, 0, w);
    cout << ret << endl;

    system("pause");
    return 0;
}

```