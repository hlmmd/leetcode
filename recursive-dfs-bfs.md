# Recursive/DFS/BFS

##  463. Island Perimeter

You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water.

Grid cells are connected horizontally/vertically \(not diagonally\). The grid is completely surrounded by water, and there is exactly one island \(i.e., one or more connected land cells\).

Input: \[\[0,1,0,0\], \[1,1,1,0\], \[0,1,0,0\], \[1,1,0,0\]\]

Output: 16

给一个二位数组，求由所有1构成的图形的周长。

用DFS递归，当值为1的点的相邻是边界或grid值为0的点时，表明这是这个图形的边界，是周长的一部分，如果也是1，则继续递归。为了防止重复递归，在访问过一个点后，将其值赋值为2。用两个数组int dx\[4\] = {1, 0, -1, 0};        int dy\[4\] = {0, 1, 0, -1};来表示上下左右四个方向。

```cpp
class Solution
{
  public:
	int islandPerimeter(vector<vector<int>> &grid)
	{

		int ret = 0;
		if (grid.size() == 0 || grid[0].size() == 0)
			return false;

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid.size(); j++)
			{
				if (grid[i][j] == 1)
					return helper(grid, i, j);
			}
		}
		return ret;
	}
	int helper(vector<vector<int>> &grid, int x, int y)
	{
		int dx[4] = {1, 0, -1, 0};
		int dy[4] = {0, 1, 0, -1};
		int ret = 0;
		grid[x][y] = 2;
		for (int i = 0; i < 4; i++)
		{

			int tx = x + dx[i];
			int ty = y + dy[i];
			if (tx >= 0 && tx < grid.size() && ty >= 0 && ty < grid[0].size() && grid[tx][ty] == 1)
				ret += helper(grid, tx, ty);
			else if (tx < 0 || tx >= grid.size() || ty < 0 || ty >= grid[0].size() || grid[tx][ty] == 0)

				ret++;
		}
		return ret;
	}
};
```

