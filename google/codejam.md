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