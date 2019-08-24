# 编程题

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