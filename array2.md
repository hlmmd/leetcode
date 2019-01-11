# Array2

##  452. Minimum Number of Arrows to Burst Balloons

射掉气球所需的最少次数。将气球按照x2排序，之后用贪心算法比较当前一次射击位置和下一个气球的x1值，如果x1大，那么就需要再射一箭。

```cpp
class Solution
{
  public:
	int findMinArrowShots(vector<pair<int, int>> &points)
	{
		if (points.size() == 0)
			return 0;

		auto comp = [](pair<int, int> p1, pair<int, int> p2) { return p1.second < p2.second; };
		sort(points.begin(), points.end(), comp);

		int shotcount = 1;
		int shotpos = points[0].second;
		for (int i = 1; i < points.size(); i++)
		{
			if (shotpos < points[i].first)
			{
				shotcount++;
				shotpos = points[i].second;
			}
		}

		return shotcount;
	}
};
```

