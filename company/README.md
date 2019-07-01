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

