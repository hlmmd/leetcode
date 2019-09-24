# 编程题

## 2019.3.17 招行

### 修理桌子

```
Arthur最近搬到了新的别墅，别墅特别大，原先的桌子显得比较小，所以他决定换一张新的桌子。他买了一张特别大的桌子，桌子是由很多条桌腿进行支撑的，可是回到家之后他发现桌子不稳，原来是桌子腿长度不太相同。他想要自己把桌子修理好，所以他决定移除掉一些桌腿来让桌子变得平稳。桌子腿总共有n条腿，第i条腿长度为li，Arthur移除第i桌腿要花费代价为di。假设k条腿桌子平稳的条件:超过一半桌腿能够达到桌腿长度的最大值。例如：一条腿的桌子是平稳的，两条腿的桌子腿一样长时是平稳的。请你帮Arthur计算一下是桌子变平稳的最小总代价。

输入描述:
输入:
    第一行数据是一个整数：n (1≤n≤105)，n表示桌腿总数。
    第二行数据是n个整数：l1, l2, ..., ln (1≤li≤105)，表示每条桌腿的长度。
    第三行数据是n个整数：d1, d2, ..., dn (1≤di≤200)，表示移除每条桌腿的代价。

输出描述:
输出:
    输出让桌子变平稳的最小总代价
```

先按腿长排序，从大往小指定腿长。那么最后剩下的，必然是当前腿长，n条，以及n-1条代价最大的小退长。所以，对小于当前腿长的数组按代价降序排列，计算总代价。

```cpp
#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

/*
6
2 2 1 1 3 3
4 3 5 5 2 1

*/

int main()
{

    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    vector<int> len(n);
    vector<int> D(n);
    for (int i = 0; i < n; i++)
        cin >> p[i].first;
    for (int i = 0; i < n; i++)
        cin >> p[i].second;

    auto comp = [](pair<int, int> &p1, pair<int, int> &p2) { return p1.first > p2.first; };
    auto comp2 = [](pair<int, int> &p1, pair<int, int> &p2) { return p1.second > p2.second; };

    sort(p.begin(), p.end(), comp);

    int mind = INT_MAX;

    int d1 = 0;

    int last = 0;
    int templen = p[0].first;
    int bigpart = 0;
    int tempd = 0;
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i].first != templen)
        {
            tempd = 0;
            int len = i - last;
            templen = p[i].first;
            vector<pair<int, int>> remain(p.begin() + i, p.end());
            sort(remain.begin(), remain.end(), comp2);

            for (int i = len - 1; i < remain.size(); i++)
            {
                tempd += remain[i].second;
            }
            tempd += bigpart;

            mind = min(mind, tempd);

            for (int j = last; j < i; j++)
                bigpart += p[j].second;

            last = i;
        }
    }
    cout << mind << endl;

    system("pause");
    return 0;
}
```

## 招行M-geeker初赛

注意：需要用long long int 的一概用long long int

### 第一题

一个整数数组，每次从中选取两个数删除，再将两数的平均数加入数组中，求最后剩下的数的最大值。

先将数组排序，然后每次删掉最小的两个数即可。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main()
{

    int n;
    cin >> n;

    vector<int> nums(n, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());

    double ret = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        ret += nums[i];
        ret /= 2;
    }
    printf("%.4lf\n", ret);
    system("pause");
    return 0;
}
```

### 第二题

一个矩阵（都是正整数），选取两个数，使他们的积最大。这两个数不能在同一行或者同一列。

先求出每一行每一列最大的数和第二大的数，再进行遍历计算，可以将复杂度降到O(n)

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main()
{

    int n, m;
    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(m, 0));

    vector<pair<int, int>> rowmax(n, pair<int, int>(0, 0));
    vector<pair<int, int>> rowmax2(n, pair<int, int>(0, 0));
    vector<pair<int, int>> colmax(m, pair<int, int>(0, 0));
    vector<pair<int, int>> colmax2(m, pair<int, int>(0, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> matrix[i][j];
            if (matrix[i][j] > rowmax[i].first)
            {
                rowmax2[i].first = rowmax[i].first;
                rowmax2[i].second = rowmax[i].second;
                rowmax[i].first = matrix[i][j];
                rowmax[i].second = j;
            }
            else if (matrix[i][j] > rowmax2[i].first)
            {
                rowmax2[i].first = matrix[i][j];
                rowmax2[i].second = j;
            }
        }
    }

    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (matrix[i][j] > colmax[j].first)
            {
                colmax2[j].first = colmax[j].first;
                colmax2[j].second = colmax[j].second;
                colmax[j].first = matrix[i][j];
                colmax[j].second = i;
            }
            else if (matrix[i][j] > colmax2[j].first)
            {
                colmax2[j].first = matrix[i][j];
                colmax2[j].second = i;
            }
        }
    }

    long long int ret = 0;

    for (int i = 0; i < n; i++)
    {
        long long v1 = rowmax[i].first;
        int posj = rowmax[i].second;

        for (int j = 0; j < m; j++)
        {
            if (posj == j)
                continue;
            long long v2 = colmax[j].first;
            if (i == colmax[j].second)
                v2 = colmax2[j].first;
            ret = max(ret, v1 * v2);
        }
    }
    cout << ret << endl;

    system("pause");
    return 0;
}
```

### 第三题

做饼干，要求至少做l个饼干，有n个饼干机，限定时间t，和使用饼干机上线k。

每个饼干机每分钟可以做speed[i]个饼干，最多可以做maxout[i]个饼干。

如果能再t分钟内完成任务，则求最短的时间，不能完成任务则求最多能做多少个饼干。

先计算能不能完成任务，再用二分法求最短时间t。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
100 3  7 2
1 10
6 6 
3 5
*/

long long int canfinish(vector<long long int> &speed, vector<long long int> &maxout, int l, int n, int t, int k)
{
    vector<long long int> output_t(n);
    for (int i = 0; i < n; i++)
    {
        long long int temp = speed[i] * t;
        output_t[i] = (temp > maxout[i]) ? maxout[i] : temp;
    }
    sort(output_t.begin(), output_t.end());
    long long number = 0;
    int count = 0;
    for (int i = n - 1; i >= 0 && count < k; i--)
    {
        number += output_t[i];
        count++;
    }
    return number;
}

int main()
{
    int l, n, t, k;
    cin >> l >> n >> t >> k;

    vector<long long int> speed(n);
    vector<long long int> maxout(n);
    vector<long long int> output_t(n);

    for (int i = 0; i < n; i++)
    {
        cin >> speed[i] >> maxout[i];
        long long int temp = speed[i] * t;
        output_t[i] = (temp > maxout[i]) ? maxout[i] : temp;
    }

    long long int maxfinish = canfinish(speed, maxout, l, n, t, k);
    if (maxfinish < l)
    {
        cout << "No" << endl
             << maxfinish << endl;
        return 0;
    }

    int left = 0, right = t;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (canfinish(speed, maxout, l, n, mid, k) >= l)
        {
            right = mid;
        }
        else if (canfinish(speed, maxout, l, n, mid, k) < l)
        {
            left = mid + 1;
        }
    }
    cout << "Yes" << endl
         << right << endl;

    system("pause");
    return 0;
}
```

### 第四题

给定nums[i]，其存在一个最大的连续子序列和。求删除一个连续的子序列后（可以不删），得到的最大的连续子序列和。

不会。

看到牛客网上的一个题解：

第四题(100%): 给定一个序列，可以删除其任意长度的连续子串，求剩下的序列的最大子段和。
解法：其实就是求序列中两个不相交的区间的最大和。从左往右扫一遍求0<=index<=i的最大子段和，记为seq[i];再从右往左一遍，求 n>index>=i的最大子段和,记为rseq[i]；最后从左往右扫一遍，求max(seq[i]+rseq[i+1])。

根据上面这个算法，写了一个答案，但没有测试集，不知道对不对

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
6
100 100 -1000 500 -200 400
*/

int main()
{
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < nums.size(); i++)
	{
		cin >> nums[i];
	}

	vector<long long int> seql(n + 1, 0);
	vector<long long int> seqr(n + 1, 0);

	long long int temp = 0;
	long long int tempmax = 0;

	//求 从左到右，seql[0,i]的最大连续子序列和
	for (int i = 1; i < seql.size(); i++)
	{
		if (nums[i - 1] > 0)
		{
			temp += nums[i - 1];
			tempmax = max(tempmax, temp);
		}
		else if (temp + nums[i - 1] > 0)
		{
			temp += nums[i - 1];
		}
		else
			temp = 0;

		seql[i] = tempmax;
	}

	temp = 0;
	tempmax = 0;
	//求 从右到左，seqr[0,i]的最大连续子序列和
	for (int i = n - 1; i >= 0; i--)
	{
		if (nums[i] > 0)
		{
			temp += nums[i];
			tempmax = max(tempmax, temp);
		}
		else if (temp + nums[i] > 0)
		{
			temp += nums[i];
		}
		else
			temp = 0;

		seqr[i] = tempmax;
	}

	tempmax = 0;
	temp = 0;

	//从0到n选择partition，可将原数组分成两个左右两部分，表示删除之后的左右两部分。

	for (int i = 0; i <= n; i++)
	{
		tempmax = max(tempmax, seql[i] + seqr[i]);
	}
	cout << tempmax << endl;

	return 0;
}
```

## 2019.4.17 华为笔试

给定一个数组，含有6个数字，求这六个数字能组成的最大时间。

```cpp

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> ret;
int retv = -1;
void cal(vector<int> &nums)
{
    int num1 = nums[0] * 10 + nums[1];
    int num2 = nums[2] * 10 + nums[3];
    int num3 = nums[4] * 10 + nums[5];

    if (num1 >= 24 || num2 >= 60 || num3 >= 60)
        return;
    else
    {
        int temp = num1 * 10000 + num2 * 100 + num3;
        if (temp > retv)
        {
            retv = temp;
            ret = nums;
        }
    }
}

void helper(vector<int> &nums, vector<int> &temp, vector<bool> &visited)
{
    if (nums.size() == temp.size())
    {
        cal(temp);
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        if (visited[i] == true)
            continue;
        temp.push_back(nums[i]);
        visited[i] = true;

        helper(nums, temp, visited);
        temp.pop_back();
        visited[i] = false;

        while (i + 1 < nums.size() && nums[i] == nums[i + 1])
            i++;
    }
}

int main()
{
    vector<int> time;

    string str;
    cin >> str;
    int i = 0;
    while (i < str.length())
    {
        string temp = "";
        while (str[i] >= '0' && str[i] <= '9')
        {
            temp += str[i];
            i++;
        }
        if (temp != "")
        {

            int v = stoi(temp);
            time.push_back(v);
        }
        i++;
    }
    for (int i = 0; i < 6; i++)
    {
        if (time[i] > 9)
        {
            cout << "invalid" << endl;
            return 0;
        }
    }

    vector<bool> visited(6, false);

    vector<int> sss;
    helper(time, sss, visited);

    if (retv == -1)
        cout << "invalid" << endl;
    else
    {
        cout << ret[0] << ret[1] << ":" << ret[2] << ret[3] << ":" << ret[4] << ret[5] << endl;       
    }

    system("pause");
    return 0;
}
```

卖水果问题。数组m,n,m表示成本价，n表示卖出价格，在成本有k元的情况下，最多能赚多少钱。每个水果买卖一次。

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> m;
    vector<int> n;

    string str;
    cin >> str;
    int i = 0;
    while (i < str.length())
    {
        string temp = "";
        while (str[i] >= '0' && str[i] <= '9')
        {
            temp += str[i];
            i++;
        }
        if (temp != "")
        {
            int v = stoi(temp);
            m.push_back(v);
        }
        i++;
    }

    cin >> str;
    i = 0;
    while (i < str.length())
    {
        string temp = "";
        while (str[i] >= '0' && str[i] <= '9')
        {
            temp += str[i];
            i++;
        }
        if (temp != "")
        {
            int v = stoi(temp);
            n.push_back(v);
        }
        i++;
    }

    int k;
    cin >> k;

    if (m.size() != n.size())
        return 0;

    vector<pair<int, int>> map(m.size());

    for (int i = 0; i < m.size(); i++)
    {
        map[i].first = m[i];
        map[i].second = n[i];
    }

    auto comp = [](pair<int, int> p1, pair<int, int> p2) { return p1.first < p2.first; };

    sort(map.begin(), map.end(), comp);

    int money = k;

    for (int i = 0; i < map.size(); i++)
    {
        if (map[i].second <= map[i].first)
            continue;
        else if (map[i].first > money)
            break;
        else
        {
            money += map[i].second - map[i].first;
        }
    }

    cout << money << endl;

    system("pause");
    return 0;
}
```

有m个处理器，n个作业，在最短作业优先的方案下，处理完所有作业耗时？

3 5

8 4 3 1 10

输出13

```cpp

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <queue>
using namespace std;

struct compare
{
    bool operator()(const int a, const int b)
    {
        return a > b;
    }
};

int main()
{
    int m, n;
    cin >> m >> n;
    vector<int> time(n);
    for (int i = 0; i < n; i++)
        cin >> time[i];

    sort(time.begin(), time.end());

    priority_queue<int, vector<int>, compare> qu;
    int ret = 0;
    int index = 0;

    if (m >= n)
    {
        cout << time.back() << endl;
        return 0;
    }

    while (index < time.size())
    {
        while (qu.size() < m && (index < time.size()))
        {
            //	cout << time[index] + ret << endl;
            qu.push(time[index] + ret);
            index++;
        }
        //3 5 8 4 3 1 10
        if (index >= time.size())
        {
            //	cout << time.back() + ret << endl;
            ret = time.back() + ret;
            break;
        }
        int top = qu.top();
        while (!qu.empty() && qu.top() == top)
        {
            qu.pop();
        }
        ret = top;
    }

    cout << ret << endl;

    system("pause");
    return 0;
}
```

## 2019.8.9 依图

N个人，每个人说M个兴趣，如果两个人有K个相同的兴趣，则可以做朋友。求朋友最多的人的朋友个数

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;


/*
3 3 2 
sing jump rap
sing basketball rap
code basketball rap

*/

void calfriend(int p1, int p2, vector<int> &counters, vector< vector<int>> &strs,int K)
{
	int count = 0;
	auto s1 = strs[p1];
	auto s2 = strs[p2];
	for (auto ss : s1)
	{
		for (auto ss2 : s2)
		{
			if (ss == ss2)
			{
				count++;
				if (count >= K)
				{
					counters[p1]++;
					counters[p2]++;
					return;
				}
				break;
			}
		}
	}
}

int main() 
{
	int N, M, K;
	cin >> N >> M >> K;
	vector<int> counters(N, 0);
	vector< vector<int>> strs(N,vector<int>(M));

	unordered_map<string, int> mmap;
	int mapcount = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			string temp;
			cin >> temp;
			if (mmap.find(temp) == mmap.end())
			{
				mmap[temp] = mapcount;
				mapcount++;
			}
			strs[i][j] = mmap[temp];
		}
	}

	for (int i = 0; i < N - 1; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			calfriend(i, j, counters, strs, K);
		}
	}
	
	int ret = 0;
	for (int i = 0; i < N; i++)
	{
		ret = max(ret, counters[i]);
	}

	cout << ret << endl;
	system("pause");
	return 0;
}
```

## 2019.8.17 腾讯

### 解析字符串，同leetcode 394

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;
//HG[3|B[2|CA]]F
string decoding(string s)
{
    if (s.length() == 0)
        return "";
    string ret;
    int i = 0;
    while (s[i] >= 'A' && s[i] <= 'Z')
        ret += s[i++];
    if (s[i] == 0)
        return ret;
    string temp;
    int count = 1;
    while (s[i] >= '0' && s[i] <= '9')
    {
        temp += s[i++];
    }

    count = atoi(temp.c_str());
    if (s[i] == 0)
        return ret;
    int start = i, end;
    int c = 1;
    if (s[i] == '[')
    {
        while (c != 0 && s[i++])
        {
            if (s[i] == '[')
                c++;
            else if (s[i] == ']')
                c--;
        }
        end = i;
    }
    else
    {
        end = s.length();
    }

    string ds = decoding(s.substr(start + 1, end - start - 1));
    //cout << count <<ds<< endl;
    for (int i = 0; i < count - 1; i++)
        ret += ds;
    ret += ds;
    if (end < s.length())
        ret += decoding(s.substr(end + 1));

    return ret;
}
```

### 最少休息多少天

n天的时间，play[i]为1表示当天能去健身，work[i]为1表示当天能去工作。不能连续工作或者健身。问最少休息多少天。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <set>
using namespace std;

/*
4
1 1 0 0
0 1 1 0
4
0 0 0 0
1 1 0 1
*/

int main()
{
    int n;
    cin >> n;
    vector<int> work(n, 0);
    vector<int> play(n, 0);

    int dp1, dp2, lp1, lp2;
    dp1 = dp2 = lp1 = lp2 = 0;

    for (int i = 0; i < n; i++)
        cin >> work[i];
    for (int i = 0; i < n; i++)
        cin >> play[i];
    for (int i = 0; i < n; i++)
    {
        lp1 = dp1;
        lp2 = dp2;
        if (work[i] == 0 && play[i] == 0)
        {
            dp2 = dp1 = max(lp1, lp2);
        }
        else if (work[i] == 1 && play[i] == 1)
        {
            dp1 = max(lp1, lp2 + 1);
            dp2 = max(lp2, lp1 + 1);
        }
        else if (work[i] == 1)
        {
            dp2 = max(lp1, lp2);
            dp1 = max(lp1, lp2 + 1);
        }
        else
        {
            dp1 = max(lp1, lp2);
            dp2 = max(lp2, lp1 + 1);
        }
    }
    cout << n - max(dp1, dp2) << endl;
    system("pause");
    return 0;
}
```

### 能看到多少楼

n个楼拍成一列，每个楼高度为h(n)，对于每一座楼，求在这个楼上能看到多少楼。分自身、从左向右、从右向左。前面的楼高度>=后面的楼，则后面的楼会被遮住。

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
6
4 5 7 3 4 6
*/

int main()
{
    int n;
    cin >> n;
    vector<int> height(n);
    for (int i = 0; i < n; i++)
        cin >> height[i];

    vector<int> left(n, 0);
    vector<int> right(n, 0);

    stack<int> s;

    s.push(height[0]);
    for (int i = 1; i < n; i++)
    {
        left[i] = s.size();
        while (!s.empty() && s.top() < height[i])
        {
            s.pop();
        }
        s.push(height[i]);
    }

    while (!s.empty())
    {
        s.pop();
    }

    s.push(height[n - 1]);
    for (int i = n - 2; i >= 0; i--)
    {
        right[i] = s.size();
        while (!s.empty() && s.top() < height[i])
        {
            s.pop();
        }
        s.push(height[i]);
    }

    for (int i = 0; i < n; i++)
        cout << left[i] + right[i] + 1 << " ";
    cout << endl;
    system("pause");

    return 0;
}
```

## 2019.8.22 m美团点评

### 骑手包裹

[Leetcode 763. Partition Labels](https://leetcode.com/problems/partition-labels/)

### 求字典序

给一系列单词，他们是以一个重定义后的字典序排列的，求对应的字典序。如果不存在，输出invalid

leetcode 269

## 2019.8.31 360

### 寻找子串

求出现次数最多的子串的出现次数。

就是统计字符个数。

### 散步问题

起点随机，走过M次后，可能到达的终点个数

DFS即可。且只需要遍历一半，另一半利用对称性。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
/*
10 3
5
2
6
*/

void dfs(vector<int> &dp, vector<int> &D, int start, int pos, int N)
{
    if (start == D.size())
    {
        dp[pos] = 1;
        return;
    }
    if ((pos + D[start]) < N)
    {
        dfs(dp, D, start + 1, pos + D[start], N);
    }

    if ((pos - D[start]) >= 0)
    {
        dfs(dp, D, start + 1, pos - D[start], N);
    }
}

int main()
{
    int N, M;
    cin >> N;
    cin >> M;
    vector<int> D(M, 0);
    for (int i = 0; i < M; i++)
        cin >> D[i];
    vector<int> dp(N, 0);
    for (int i = 0; i < N / 2 + 1; i++)
    {
        dfs(dp, D, 0, i, N);
    }

    for (int i = 0; i < N / 2 + 1; i++)
    {
        if (dp[i] == 1)
        {
            dp[N - i - 1] = 1;
        }
    }
    int ret = 0;

    for (int i = 0; i < N; i++)
    {
        if (dp[i] == 1)
            ret++;
    }

    cout << ret << endl;

    //	system("pause");
    return 0;
}
```

## 2019.9.1 腾讯

### 宝箱问题

计算两个奇偶数的值,取较小值相加即可

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    vector<long long> b(m);

    int a1, a2, b1, b2;
    a1 = a2 = b1 = b2 = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] % 2 == 0)
            a2++;
        else
            a1++;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
        if (b[i] % 2 == 0)
            b2++;
        else
            b1++;
    }

    int ret = min(a1, b2) + min(a2, b1);
    cout << ret << endl;

    system("pause");
    return 0;
}
```

### 排队

n个员工排队喝咖啡，有两个属性值a,b。排在第i位的员工满意度为`a[i]*i+b[i]*(n-i+1)`

重新安排顺序，求总满意度最高的序列。

对b-a进行排序。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

/*
3 
1 3
1 1 
4 1
*/

int main()
{	
	int n;
	cin >> n;

	vector<pair<long long , long long >> nums(n);

	for (int i = 0; i < n; i++)
	{
		cin >> nums[i].first >> nums[i].second;
	}
	auto comp = [](const pair<long long , long long > &p1, const pair<long long, long long > &p2) {		
		return (p1.second-p1.first)< (p2.second - p2.first);
	};

	sort(nums.begin(), nums.end(),comp);

	long long ret = 0;
	for (int i = 0; i < n; i++)
	{
		ret += nums[i].first*(i)+nums[i].second*(n - i - 1);
	}
	cout << ret << endl;

	system("pause");
	return 0;
}
```

### 搬箱子

这题太难了，完全不会

1-n，n个位置，每个位置有a[i]个箱子。有m个工人，初始位置是0。

每一秒，一个工人可以：走到下一位置，或者搬走当前位置一个箱子。

求搬完所有的箱子要多少秒。

### 期末总结

数组nums，求 max( min(i,j) * sum(i,j)  );

min(i,j)为[i,j]的最小值，sum[i,j]为[i,j]的和。

之前面字节跳动被问过类似的题，当时用的二分法，超时了

poj 2796

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

vector<long long> sum;
int getminpos(vector<int> &w, int l, int r, int &v)
{
    int m = 100000, pos = l;
    for (int i = l; i <= r; i++)
    {
        if (w[i] <= m)
        {
            m = w[i];
            pos = i;
        }
    }
    v = m;
    return pos;
}

long long cal(vector<int> &w, int l, int r)
{
    if (l > r)
        return 0;
    int minv = 0;
    int pos = getminpos(w, l, r, minv);
    long long value = 0;
    if (l > 0)
        value = minv * (sum[r] - sum[l - 1]);
    else
        value = minv * (sum[r]);

    long long v1 = cal(w, l, pos - 1);
    long long v2 = cal(w, pos + 1, r);

    return max(max(v1, v2), value);
}
/*
5
7 2 4 6 5
*/

int main()
{
    int n;
    cin >> n;
    vector<int> w(n, 0);
    for (int i = 0; i < n; i++)
        cin >> w[i];

    sum.resize(n);
    sum[0] = w[0];
    for (int i = 1; i < n; i++)
        sum[i] = sum[i - 1] + w[i];

    int l = 0, r = w.size() - 1;
    long long ret = 0;
    int minv = 0;

    cout << cal(w, l, r) << endl;

    system("pause");
    return 0;
}
```

这是一个单调栈的题目。poj 2796

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

/*
6
3 1 6 4 5 2
*/

int main()
{
    int n;
    cin >> n;
    vector<int> w(n, 0);
    vector<long long> sum(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> w[i];
        sum[i + 1] = w[i] + sum[i];
    }

    vector<int> left(n, 0);
    vector<int> right(n, 0);

    long long ret = 0;
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && w[st.top()] >= w[i])
            st.pop();

        left[i] = st.empty() ? 0 : st.top() + 1;
        st.push(i);
    }

    while (!st.empty())
        st.pop();

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && w[st.top()] >= w[i])
            st.pop();
        right[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    for (int i = 0; i < n; i++)
    {
        ret = max(ret, (sum[right[i]] - sum[left[i]]) * w[i]);
    }

    cout << ret << endl;

    system("pause");
    return 0;
}
```

### 种花

白花和红花，一个数k。给他们排列的时候，白花必须是k的整数倍（可以为0），输入一个区间[a,b]，表示在种[a,b]朵花的时候，一共能有多少种种法。

递推公式：`f[i] = f[i-1]+f[i-k]`

只能过50%，答案错误.

题目忘写取模了，中途给了提示没看到..血亏50%

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

/*
3 2
1 3
2 3
4 4

*/

int main()
{
	int t, k;
	cin >> t;
	cin >> k;
	vector<unsigned long long> dp(100001, 0);

	vector<int>va(t);
	vector<int>vb(t);
	int m1 = 100001, m2 = 0;
	for (int n = 0; n < t; n++)
	{
		cin >> va[n] >> vb[n];
		if (k == 0) {
			cout << vb[n] - va[n] + 1 << endl;
			continue;
		}

		if (va[n] < m1)
			m1 = va[n];
		if (vb[n] > m2)
			m2 = vb[n];
	}
	if (k == 0)
		return 0;

	for (int i = 0; i < k; i++)
		dp[i] = 1;
	for (int i = k; i <= m2; i++)
		dp[i] = dp[i - 1] + dp[i - k];

	//	vector<long long > sum(100001, 0);
	//	for (int i = 1; i <= m2; i++)
	//		sum[i] = sum[i - 1] + dp[i];
	int a, b;
	for (int n = 0; n < t; n++)
	{
		if (k == 0) {
			cout << 1 << endl;
			continue;
		}
		unsigned long long ret = 0;
		for (int i = va[n]; i <= vb[n]; i++)
			ret += dp[i];
		cout << ret << endl;
	}

	system("pause");
	return 0;
}
```

### 2019.9.3 英特尔

两道题，要求C语言

第一题实现一个循环队列，第二题类似leetcode 670

### 2019.9.16 英伟达

题目类似Leetcode，只需要写一个类中的函数即可

#### 棋子翻转

很简单，考察基本逻辑

int型参数不加&，一是int型拷贝开销小，二是可以让函数调用是，可以传x-1这种右值。

```cpp
class Flip
{
public:
    int m, n;
    bool FF(vector<vector<int>> &A, int x, int y)
    {
        if (x < 0 || y < 0 || x >= m || y >= n)
            return false;
        A[x][y] = A[x][y] == 1 ? 0 : 1;
        return true;
    }

    vector<vector<int>> flipChess(vector<vector<int>> A, vector<vector<int>> f)
    {
        // write code here
        m = A.size();
        n = A[0].size();
        for (int i = 0; i < f.size(); i++)
        {
            int x = f[i][0] - 1;
            int y = f[i][1] - 1;
            FF(A, x - 1, y);
            FF(A, x + 1, y);
            FF(A, x, y - 1);
            FF(A, x, y + 1);
        }

        return A;
    }
};
```

### 单词最短距离

一篇文章有n个单词，求单词x单词y之间的最短距离。数据量<1000，直接记录下标，然后循环比较即可。

```cpp

class Distance
{
public:
    int getDistance(vector<string> article, int n, string x, string y)
    {
        // write code here

        vector<int> posx;
        vector<int> posy;

        for (int i = 0; i < n; i++)
        {
            if (article[i] == x)
            {
                posx.push_back(i);
            }
            else if (article[i] == y)
            {
                posy.push_back(i);
            }
        }

        int m = 1001;

        for (int i = 0; i < posx.size(); i++)
        {
            for (int j = 0; j < posy.size(); j++)
            {
                m = min(m, abs(posx[i] - posy[j]));
            }
        }
        return m;
    }
};
```

### 黑白二叉树 最长单色路径

对于一棵由黑白点组成的二叉树，我们需要找到其中最长的单色简单路径，其中简单路径的定义是从树上的某点开始沿树边走不重复的点到树上的另一点结束而形成的路径，而路径的长度就是经过的点的数量(包括起点和终点)。而这里我们所说的单色路径自然就是只经过一种颜色的点的路径。你需要找到这棵树上最长的单色路径。

给定一棵二叉树的根节点(树的点数小于等于300，请做到O(n)的复杂度)，请返回最长单色路径的长度。这里的节点颜色由点上的权值表示，权值为1的是黑点，为0的是白点。

```cpp
class LongestPath
{
public:
    int findPath(TreeNode *root)
    {
        maxlen(root);
        return ret;
    }
    int ret = 0;

    int maxlen(TreeNode *root)
    {
        if (root == NULL)
            return 0;

        int r = 1;

        int left = 0, right = 0;
        if (root->left)
        {
            if (root->left->val == root->val)
            {
                left = maxlen(root->left);
            }
            else
            {
                maxlen(root->left);
            }
        }
        if (root->right)
        {
            if (root->right->val == root->val)
            {
                right = maxlen(root->right);
            }
            else
            {
                maxlen(root->right);
            }
        }
        ret = max(ret, left + right + 1);

        return max(left, right) + 1;
    }
};
```

## 2019.9.20 腾讯

### 电话号码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
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

        int len = 0;
        for (; len < str.length(); len++)
        {
            if (str[len] == '8')
                break;
        }
        int remain = str.length() - len;
        if (remain >= 11)
        {
            cout << "YES" << endl;
        }
        else
            cout << "NO" << endl;
    }

    system("pause");
    return 0;
}
```

### 分工

排序，贪心。

```cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

/*
3
1 8
2 5
1 2 
*/

int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> dp(n);
    for (int i = 0; i < n; i++)
    {
        cin >> dp[i].first >> dp[i].second;
    }

    auto comp = [](pair<int, int> &p1, pair<int, int> &p2) { return p1.second < p2.second; };
    sort(dp.begin(), dp.end(), comp);

    long long maxtime = 0;

    int left = 0, right = dp.size() - 1;
    while (left <= right)
    {
        long long temp = dp[left].second + dp[right].second;
        maxtime = max(temp, maxtime);
        dp[left].first--;
        if (dp[left].first == 0)
            left++;
        dp[right].first--;
        if (dp[right].first == 0)
            right--;
    }
    cout << maxtime << endl;

    system("pause");
    return 0;
}
```

### 最小数

每次找出最小数x，然后其他所有不为0的数-x，再

```cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

/*
7 5
5 8 10 3 6  10 8
*/

int main()
{

    int n, k;
    cin >> n >> k;
    vector<int> value(n);
    for (int i = 0; i < n; i++)
        cin >> value[i];

    sort(value.begin(), value.end());

    int index = 0;
    int last = 0;

    for (int i = 0; i < k; i++)
    {
        if (index >= n)
        {
            cout << 0 << endl;
            continue;
        }
        cout << value[index] - last << endl;
        last = value[index];
        while (index < value.size() && value[index] == last)
            index++;
    }

    system("pause");
    return 0;
}
```

### 亦或运算

两个大小为n的数组，两两求和，得到n^2个数，求这些数的亦或值。

[解答](https://blog.csdn.net/hypHuangYanPing/article/details/80612781
)

### 分组问题

n个人，分成两组，要求两组人数差不超过1。并且两个组的战斗力差值最小。

思路是先从大到小排序，然后dfs，当到达size()/2时，计算一次结果，取差值最小值。

**然而20%**

没注意题目是不是给定n>=2

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <stack>
using namespace std;

/*
2
4
5 9 4 7
11
9 13 18 18 12 4 18 3 22 19 20000
*/

#define BIG 100005

int sum = 0;
int mindist = BIG;

int result = 0;

void dfs(vector<int> &nums, int count, int index, int total)
{
	if (mindist == 0)
		return;

	if (nums.size() / 2 == count)
	{
		int dist = abs((sum - total) - total);
		if (dist < mindist)
		{
			result = min(total, sum - total);
			mindist = dist;
		}

		return;
	}

	if (total > sum / 2)
		return;

	for (int i = index; i < nums.size(); i++)
	{
		dfs(nums, count + 1, i + 1, total + nums[i]);
	}

}


int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		int n;
		cin >> n;
		vector<int> nums(n);
		sum = 0;
		mindist = BIG;
		for (int i = 0; i < n; i++)
		{
			cin >> nums[i];
			sum += nums[i];
		}

		auto comp = [](int &a, int &b) {return a > b; };
		sort(nums.begin(), nums.end(), comp);

		result = 0;
		dfs(nums, 0, 0, 0);
		cout << result << " " << sum - result << endl;

	}

	system("pause");
	return 0;
}
```

## 2019.9.22 微软

### 不同字符串

定义两个字符串s1,s2，如果s1交换i,j位两个字符，并且ij满足i+j%2==0，那么s1和s2相同。求一组字符串中不同字符串的个数。

将每个字符串按奇偶拆分成两个子字符串，然后排序，放到一个pair中，再把pair放入set中，返回set的size即可。

```cpp
int func(int input1, const char *input2[])
{
    set<pair<string, string>> ss;
    for (int n = 0; n < input1; n++)
    {
        vector<char> s1;
        vector<char> s2;
        for (int i = 0; input2[n][i]; i++)
        {
            if (i % 2 == 0)
                s1.push_back(input2[n][i]);
            else
                s2.push_back(input2[n][i]);
        }
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());

        pair<string, string> p;
        for (int i = 0; i < s1.size(); i++)
            p.first += s1[i];
        for (int i = 0; i < s2.size(); i++)
            p.second += s2[i];

        ss.insert(p);
    }
    return ss.size();
}
```

### 熟练度问题

一开始熟练度为0，给一个数组表示锻炼，长度为K，每个元素是素数，如[2,3,5,7...]，求最少需要锻炼多少次，能够到达刚好N熟练度，如果不能实现，返回-1

同leetcode 322找零问题，加了一个求质数

```cpp
int minDays(int input1, int input2)
{
    vector<int> prime;
    int n = 2;
    while (1)
    {
        if (prime.size() >= input2)
            break;
        bool flag = false;
        for (int i = 2; i <= n / 2; i++)
        {
            if (n % i == 0)
            {
                flag = true;
                break;
            }
        }
        if (flag == false)
            prime.push_back(n);
        n++;
    }

    vector<int> dp(input1 + 1, input1);
    dp[0] = 0;
    for (int i = 1; i <= input1; i++)
    {
        for (int j = 0; j < prime.size(); j++)
        {
            if (i < prime[j])
                break;
            dp[i] = min(dp[i], dp[i - prime[j]] + 1);
        }
    }

    return dp[input1] == input1 ? -1 : dp[input1];
}
```

### 特殊的数

如果一个数能够拆成两个数的和，且n2 = reverse(n1)，那么这是一个特殊的数

求数组中有多少个特殊的数。

只会暴力求解。

非暴力求解目前能想到考虑某一位能够由哪两个数相加得到，以及是否产生进位等。如

6 = [0,6],[1,5],[2,4],[3,3],[7,9],[8,8]

```cpp
int is_special(const char *input1[], int input2)
{
    vector<int> nums(input2);
    for (int i = 0; i < input2; i++)
    {
        nums[i] = atoi(input1[i]);
    }
    int count = 0;

    for (int i = 0; i < input2; i++)
    {
        if (nums[i] == 0)
        {
            count++;
            break;
        }

        for (int n = 1 ; n <= nums[i]; n++)
        {
            string sr = "";
            int temp = n;
            while (temp)
            {
                sr += temp % 10 + '0';
                temp /= 10;
            }
            if (atoi(sr.c_str()) + n == nums[i])
            {
                count++;
                break;
            }
        }
    }
    return count;
}
```