# google code jam

## code jam 2018

### Practice Session 2018

#### Number Guessing

给一个范围，猜数字。二分法。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int a, b;
        cin >> a >> b;
        int num;
        cin >> num;
        while (1)
        {
            int guess = (a + b) / 2;
            string res;
            cout << guess << endl;
            cin >> res;
            if (res == "CORRECT")
            {
                break;
            }
            else if (res == "TOO_BIG")
            {
                b = guess - 1;
            }
            else
            {
                a = guess + 1;
            }
        }
    }

    return 0;
}
```

#### Senate Evacuation

疏散议员。要保证剩下的议员中，不会有一个党派超过半数。

主要思想：先排序，找到人数最少的两个党派，最后撤离。计算两者差值，然后撤离出部分人（从第二少的党派和最多的党派中选择），保证最少的两个党派相同。然后将其他的党派撤出（一次撤出一个人即可，优先撤出人数最多的党派中的一人，直到除了最少的两个党派外所有的党派都已经撤出），然后再撤出这最后两个党派。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int N;
        cin >> N;
        vector<pair<int, int>> nums(N);
        for (int i = 0; i < N; i++)
        {
            cin >> nums[i].second;
            nums[i].first = i + 'A';
        }

        string answer = "";
        answer += "Case #";
        answer += to_string((t + 1));
        answer += ": ";

        if (N == 2)
        {

            for (int i = 0; i < nums[0].second; i++)
            {
                answer += "AB ";
            }
        }
        else
        {
            auto comp = [](pair<int, int> &p1, pair<int, int> &p2) {
                return p1.second < p2.second;
            };

            sort(nums.begin(), nums.end(), comp);

            int d = nums[1].second - nums[0].second;

            for (int i = 0; i < d; i++)
            {
                answer += nums[1].first;
                answer += nums.back().first;
                answer += " ";
            }
            nums[1].second -= d;
            nums[N - 1].second -= d;

            while (1)
            {
                int i = N - 1;
                if (nums[i].second == 0)
                    break;
                while (i >= 3 && nums[i].second <= nums[i - 1].second)
                    i--;

                answer += nums[i].first;
                answer += " ";

                nums[i].second--;
            }

            for (int i = 0; i < nums[0].second; i++)
            {
                answer += nums[0].first;
                answer += nums[1].first;
                answer += " ";
            }
        }

        cout << answer << endl;
    }
    //system("pause");
    return 0;
}
```

#### cruise control

一条长为D的路，Annie从0骑马出发，速度恒定为v。路上有很多别的马，位置为pos，速度为speed，处于后方的马不会超过前马，问Annie最大的速度为多少，可以满足不会超过别的马。

只需要找到所有马中最慢的那一匹即可。所有在它西边的马会和它一起到达，所有在它东边的马不受影响。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

int main()
{
	int T;
	cin >> T;

	for (int t = 0; t < T; t++)
	{
		int D, N;
		cin >> D >> N;

		vector<int> pos(N, 0);
		vector<int> speed(N, 0);

		for (int i = 0; i < N; i++)
		{
			cin >> pos[i] >> speed[i];
		}
		double s = (double)D / (D - pos[0]) * speed[0];
		for (int i = 1; i < N; i++)
		{
			double temp = (double)D / (D - pos[i]) * speed[i];
			s = min(temp, s);
		}
		printf("Case #%d: %6lf\n", t + 1, s);
	}

	system("pause");
	return 0;
}
```

#### Bathroom Stalls

主要思想：二分。要得到最大值，肯定是选择最中间的两个位置之一，即(X-1)/2和X/2中的一个。所以，每次把一个大的长度X一分为二，得到两个小的长度x0,x1，大的长度个数count(X)-1，小的长度个数count(x0)+=count(X)。用set保存长度，因为要求最大值,O(1)复杂度。用unordered_map保存个数，用于查询。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>
#include <unordered_map>
using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        long long N, K;
        cin >> N >> K;
        set<long long> S;
        S.insert(N);
        unordered_map<long long, long long> count;
        count[N] = 1;

        long long p = 0;
        for (long long i = 0; i < K; i++)
        {
            long long X = *S.rbegin();

            long long x0 = (X - 1) / 2;
            long long x1 = (X) / 2;

            p += count[X];
            if (p >= K)
            {
                printf("Case #%d: %lld %lld\n", t + 1, x1, x0);
                break;
            }

            S.erase(X);
            S.insert(x0);
            S.insert(x1);
            if (count.find(x0) == count.end())
            {
                count[x0] = count[X];
            }
            else
                count[x0] += count[X];

            if (count.find(x1) == count.end())
            {
                count[x1] = count[X];
            }
            else
                count[x1] += count[X];
        }
    }

    system("pause");
    return 0;
}
```

### Qualification Round

#### Saving The Universe Again

贪心算法。每次交换最右边的CS组合，这样得到的新的字符串对应的值是最小的。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>
#include <unordered_map>
using namespace std;

int cal(string &s)
{
    int ret = 0;
    int v = 1;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'S')
        {
            ret += v;
        }
        else
            v <<= 1;
    }

    return ret;
}

int change(string &str)
{
    if (str.length() <= 1)
        return 0;
    for (int i = str.length() - 2; i >= 0; i--)
    {
        if (str[i] == 'C' && str[i + 1] == 'S')
        {
            swap(str[i], str[i + 1]);
            return 1;
        }
    }
    return 0;
}
int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int D;
        cin >> D;
        string P;
        cin >> P;

        int temp = cal(P);
        int step = 0;
        while (temp > D)
        {
            if (change(P))
            {
                temp = cal(P);
                step++;
            }
            else
                break;
        }
        if (temp <= D)
            cout << step << endl;
        else
        {
            cout << "IMPOSSIBLE" << endl;
        }
    }
    system("pause");
    return 0;
}
```

#### Trouble sort

trouble排序，每次隔一个数进行交换，得到一个非递减序列。

但是这个排序存在bug，如果排序完后序列未有序，则输出下标。

将数组按下表的奇偶分成两个数组，分别排序，再合并起来判断。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>
#include <unordered_map>
using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int n;
        cin >> n;

        vector<int> n1;
        vector<int> n2;

        for (int i = 0; i < n; i++)
        {
            int t;
            cin >> t;
            if (i % 2 == 0)
            {
                n1.push_back(t);
            }
            else
                n2.push_back(t);
        }

        sort(n1.begin(), n1.end());
        sort(n2.begin(), n2.end());

        vector<int> nums(n);
        for (int i = 0; i < nums.size(); i++)
        {
            if (i % 2 == 0)
                nums[i] = n1[i / 2];
            else
                nums[i] = n2[(i - 1) / 2];
        }

        int index = -1;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (nums[i] > nums[i + 1])
            {
                index = i;
                break;
            }
        }

        printf("Case #%d: ", t + 1);
        if (index == -1)
            cout << "OK" << endl;
        else
            cout << index << endl;
    }
    system("pause");
    return 0;
}
```

#### Go, Gopher!

交互性题目，每次输出一个坐标，然后系统随机在这个点的一圈范围内选择一个点进行挖洞，当洞成一个矩形，且面积大于A后，返回0，0表示成功。

将矩形固定为3*x 的形状，选取中间的点作为中心进行随机即可。如下所示，只选择\*作为中心点进行随机即可。

```
xxxxxxxxx
x*xx*xx*x
xxxxxxxxx
```

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>
#include <unordered_map>
using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        int a;
        cin >> a;

        vector<vector<int>> board(1001, vector<int>(1001, 0));

        int len = a / 3 + (a % 3 != 0);

        len -= 2;

        vector<int> pos;
        for (int i = 1; i <= len; i += 3)
        {
            pos.push_back(i + 1);
        }
        if (len % 3 != 1)
            pos.push_back(len + 1);

        int dx[] = {-1, 0, 1};
        int dy[] = {-1, 0, 1};

        int i = 0;
        while (i < pos.size())
        {
            int y = 2;
            int x = pos[i];
            bool found = false;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (board[dx[j] + x][dy[k] + y] == 0)
                    {
                        found = true;
                        break;
                    }
                }
            }

            if (found == false)
            {
                i++;
                continue;
            }

            cout << x << " " << y << endl;
            cin >> x >> y;
            if (x == 0 && y == 0)
                break;
            else if (x == -1 && y == -1)
                exit(0);

            board[x][y] = 1;
        }
    }
    system("pause");
    return 0;
}
```

#### Cubic UFO

数学问题

### round A

#### Waffle Choppers 

切华夫饼。横着切H刀，竖着切V刀，使每一块上面的@个数相同。

先只考虑横着切，每一块相同，可以求出一个横着切的解。同理求出竖着的解。这是**必要不充分**条件，所以需要再检查一下每块是不是都是total/((H+1)*(V+1))


```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <set>
#include <unordered_map>
using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int t = 0; t < T; t++)
    {

        int R, C, H, V;
        cin >> R >> C >> H >> V;
        vector<string> waffle(R);

        vector<int> line(R, 0);
        vector<int> col(C, 0);

        int total = 0;

        for (int i = 0; i < R; i++)
        {
            cin >> waffle[i];
            for (int j = 0; j < C; j++)
            {
                if (waffle[i][j] == '@')
                {
                    total++;
                    line[i]++;
                    col[j]++;
                }
            }
        }
        printf("Case #%d: ", t + 1);

        if (total == 0)
        {
            cout << "POSSIBLE" << endl;
            continue;
        }

        int f = (H + 1) * (V + 1);
        if (total % f != 0)
        {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }

        int rowall = total / (H + 1);
        int colall = total / (V + 1);

        vector<int> rr;

        vector<int> cc;

        int temp = 0;
        for (int i = 0; i < R; i++)
        {
            if (temp + line[i] <= rowall)
            {
                temp += line[i];
            }
            else if (temp == rowall)
            {
                rr.push_back(i);
                temp = line[i];
            }
            else
            {
                break;
            }
        }

        if (rr.size() != H)
        {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }

        temp = 0;
        for (int i = 0; i < C; i++)
        {
            if (temp + col[i] <= colall)
            {
                temp += col[i];
            }
            else if (temp == colall)
            {
                cc.push_back(i);
                temp = col[i];
            }
            else
            {
                break;
            }
        }

        if (cc.size() != V)
        {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }

        rr.push_back(R);
        cc.push_back(C);
        for (int i = 0; i < rr.size(); i++)
        {
            for (int j = 0; j < cc.size(); j++)
            {
                int rs, re, cs, ce;
                rs = (i == 0) ? 0 : rr[i - 1];
                re = rr[i];
                cs = (j == 0) ? 0 : cc[j - 1];
                ce = cc[j];
                int count = 0;
                for (int x1 = rs; x1 < re; x1++)
                {
                    for (int x2 = cs; x2 < ce; x2++)
                    {
                        count += waffle[x1][x2] == '@';
                    }
                }
                if (count != (total / f))
                {
                    goto end;
                }
            }
        }

        cout << "POSSIBLE" << endl;
        continue;
    end:
        cout << "IMPOSSIBLE" << endl;
    }
    system("pause");
    return 0;
}
```
