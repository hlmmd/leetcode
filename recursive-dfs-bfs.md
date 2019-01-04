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

## Medium

##  46. Permutations

给出一个元素互不相同的数组的全排列。

递归。每次给temp添加一个不重复的整数，继续递归，在外部再讲这个整数pop出去，来完成一次完整的递归操作。当temp数组和nums数组size相同时，递归达到了边界条件，记录此时的temp并返回。

```cpp
class Solution
{
  public:
    vector<vector<int>> ret;

    void get(vector<int> &temp, vector<int> &nums)
    {
        if (temp.size() == nums.size())
        {
            ret.push_back(temp);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (find(temp.begin(), temp.end(), nums[i]) != temp.end())
                continue;

            temp.push_back(nums[i]);
            get(temp, nums);
            temp.pop_back();
        }
        return;
    }

    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<int> temp;
        get(temp, nums);
        return ret;
    }
};
```

##  131. Palindrome Partitioning

把一个字符串分成由回文串组成的分割。

```cpp
class Solution
{
  public:
    vector<vector<string>> ret;

    vector<vector<string>> partition(string s)
    {
        vector<string> temp;
        helper(s, 0, temp);
        return ret;
    }

    bool IsPalindrome(string s, int left, int right)
    {
        while (left <= right)
        {
            if (s[left] != s[right])
                return false;
            left++;
            right--;
        }
        return true;
    }

    void helper(string s, int start, vector<string> &temp)
    {
        if (start == s.length())
        {
            ret.push_back(temp);
            return;
        }

        for (int i = start; i < s.length(); i++)
        {
            if (IsPalindrome(s, start, i))
            {
                temp.push_back(s.substr(start, i - start + 1));
                helper(s, i + 1, temp);
                temp.pop_back();
            }
        }
    }
};
```

##  241. Different Ways to Add Parentheses

##  417. Pacific Atlantic Water Flow

## 433.Minimum Genetic Mutation

BFS。

首先将基因库bank转换为unordered\_map，以便计数（查看是否存在对应的变异基因）。

使用队列用于BFS，记录下一个循环需要遍历的基因。首先，将start进队，当队列非空的时候，退出循环，并返回-1，表示没找到（在循环内判断是否找到end，直接返回）。

循环内，将队列中的所有元素逐一出队，如果有end就返回dist。不然就进行遍历，找寻当一个基因发生突变后，存在于bank中的基因。遍历操作先将被遍历的基因踢出map中，避免重复遍历，再对基因逐一遍历字符串，再将其修改为AGCT，如果能在map中找到，就进行将其添加到队列中进行遍历。

```cpp
class Solution
{
  public:
	int minMutation(string start, string end, vector<string> &bank)
	{
		queue<string> toVisit;
		unordered_set<string> dict(bank.begin(), bank.end());
		int dist = 0;

		if (!dict.count(end))
			return -1;

		toVisit.push(start);
		while (!toVisit.empty())
		{
			int n = toVisit.size();
			for (int i = 0; i < n; i++)
			{
				string str = toVisit.front();
				toVisit.pop();
				if (str == end)
					return dist;
				addWord(str, dict, toVisit);
			}
			dist++;
		}
		return -1;
	}

	void addWord(string word, unordered_set<string> &dict, queue<string> &toVisit)
	{
		dict.erase(word);
		for (int i = 0; i < word.size(); i++)
		{
			char tmp = word[i];
			for (char c : string("ACGT"))
			{
				word[i] = c;
				if (dict.count(word))
				{
					toVisit.push(word);
				}
			}
			word[i] = tmp;
		}
	}
};
```

