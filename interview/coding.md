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