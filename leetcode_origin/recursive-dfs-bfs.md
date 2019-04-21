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
			if (tx >= 0 && tx < grid.size() && ty >= 0 && ty < grid[0].size()
			 && grid[tx][ty] == 1)
				ret += helper(grid, tx, ty);
			else if (tx < 0 || tx >= grid.size() || ty < 0 || ty >= grid[0].size()
			 || grid[tx][ty] == 0)

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

##  ****_464. Can I Win_

给定一个上限maxChoosableInteger，即只能从\[1,maxChoosableInteger\]中选择，且不能重复。谁先到达&gt;=desiredTotal即可获胜。这是一个可以用DFS解决的问题

因为不能重复使用任何一个数，所以我们用一个整数，用第i个bit位来表示第i个数有没有被使用。每一次往下层DFS时，就遍历所有i个数，如果对应bit位已经被置位1，说明已经使用过该数，则跳过。当累加的数值&gt;=desiredTotal时，即达到了胜利条件，但此时要注意判断是否是自己胜利，如果是自己胜利，那么在这一步之前，对手是无法达到胜利的。最后，用空间换时间，使用一个vector来保存已经访问过的状态，在DFS前先判断是否访问过该状态。

```cpp
class Solution
{
public:
	bool canIWin(int maxChoosableInteger, int desiredTotal)
	{
		if (maxChoosableInteger >= desiredTotal)
			return true;
		int sum = ((maxChoosableInteger + 1) * maxChoosableInteger) >> 1;
		if (sum < desiredTotal)
			return false;
		mp = vector<int>(1 << maxChoosableInteger, -1);
		return canWin(0, maxChoosableInteger, desiredTotal);
	}
	vector<int> mp;
	bool canWin(int used, const int &maxChoosableInteger, int desiredTotal)
	{
		if (mp[used] != -1)
			return mp[used];
		for (int i = maxChoosableInteger, bits = 1 << (maxChoosableInteger - 1);
		 i >= 1; --i, bits >>= 1)
		{
			if ((used & bits) != 0)
				continue;
			if (i >= desiredTotal ||
			 !canWin(used | bits, maxChoosableInteger, desiredTotal - i))
			{
				mp[used] = 1;
				return true;
			}
		}
		mp[used] = 0;
		return false;
	}
};
```

##  473. Matchsticks to Square

用火柴棍拼成一个正方形，要求每一个都使用到。

明显的DFS。

首先，将所有的长度累加，判断是不是4的倍数，并除以4计算得到每条边的边长。然后定义一个数组用于存储4条边的长度，接下来开始对nums数组中每一条边进行DFS递归。

DFS函数中，先进行判断，如果四条边相等且所有火柴棍都被使用了，则返回true。

不满足条件，则一次将当前这根火柴棍加入到各个边中，继续递归。

如果直接这么做，会超时，所以必须要进行一定的优化。首先，对Nums进行从大到小排序。这样在进行DFS时会省去很多时间。

其次，如果当前的边长加上nums\[index\]后超出计算得到的Len,就直接返回，因为不会满足条件。

最后，如果sidesLength\[i\]和之前的sidesLength\[j\]的值相同，那么这两种情况是等价的（四条边是没有区别的）。

```cpp
class Solution
{
	bool dfs(vector<int> &sidesLength, const vector<int> &matches,
	 int index, const int target)
	{
		if (index == matches.size())
			return sidesLength[0] == sidesLength[1] &&
				   sidesLength[1] == sidesLength[2] &&
				   sidesLength[2] == sidesLength[3];
		for (int i = 0; i < 4; ++i)
		{
			if (sidesLength[i] + matches[index] > target) 
				continue;
			int j = i;
			while (--j >= 0)
				if (sidesLength[i] == sidesLength[j])
					break;
			if (j != -1)
				continue;
			sidesLength[i] += matches[index];
			if (dfs(sidesLength, matches, index + 1, target))
				return true;
			sidesLength[i] -= matches[index];
		}
		return false;
	}

  public:
	bool makesquare(vector<int> &nums)
	{
		if (nums.size() < 4)
			return false;
		int sum = 0;
		for (const int val : nums)
		{
			sum += val;
		}
		if (sum % 4 != 0)
			return false;
		auto comp = [](const int &l, const int &r) { return l > r; };
		sort(nums.begin(), nums.end(), comp);
		vector<int> sidesLength(4, 0);
		return dfs(sidesLength, nums, 0, sum / 4);
	}
};
```

##  491. Increasing Subsequences

求一个序列的所有递增子序列。明显DFS。

在DFS时，添加三个判断条件，首先，如果当前序列为空或者Nums\[i\]&gt;=序列最后一个数，即满足递增。其次，这个数之前没有被DFS过，否则在经历了整个DFS过程后，产生的temp序列一定是相同的，会导致重复。所以使用一个set来存储nums\[i\]，判断是否重复。

```cpp
class Solution
{
public:
	vector<vector<int>> ret;
	vector<vector<int>> findSubsequences(vector<int> &nums)
	{
		vector<int> temp;
		dfs(nums, temp, 0);
		return ret;
	}
	void dfs(vector<int> &nums, vector<int> &temp, int index)
	{
		if (temp.size() > 1)
			ret.push_back(temp);
		unordered_set<int> hash;
		for (int i = index; i < nums.size(); ++i)
		{
			if ((temp.size() == 0 || nums[i] >= temp[temp.size() - 1])
			 && hash.find(nums[i]) == hash.end())
			{
				temp.push_back(nums[i]);
				dfs(nums, temp, i + 1);
				temp.pop_back();
				hash.insert(nums[i]);
			}
		}
	}
};
```

##  542. 01 Matrix

一个01矩阵，求1到其最近的0需要多少步。

BFS。初始化时，将所有的0的点的坐标加入队列等待遍历，将所有的1设为INT\_MAX表示无限大，以方便之后的计算。

在循环中，不许要一个used数组之类的来记录结点是否被遍历过，只要比较结点当前值是否比周围的值+1要大，如果大就更新更新这个值，持续这样的操作，最后才能得到正确的结果。

```cpp
class Solution
{
  public:
    vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<vector<int>> updateMatrix(vector<vector<int>> &matrix)
    {
        if (matrix.empty())
            return matrix;
        int m = matrix.size();
        int n = matrix[0].size();
        queue<pair<int, int>> q;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == 0)
                {
                    q.push({i, j});
                }
                else
                {
                    matrix[i][j] = INT_MAX;
                }
            }
        }
        while (!q.empty())
        {
            auto xy = q.front();
            q.pop();
            int i = xy.first, j = xy.second;
            for (auto d : dir)
            {
                int ii = i + d.first, jj = j + d.second;
                if (ii < m && ii >= 0 && jj < n && jj >= 0)
                {
                    if (matrix[ii][jj] >= matrix[i][j] + 1)
                    {
                        matrix[ii][jj] = matrix[i][j] + 1;
                        q.push({ii, jj});
                    }
                }
            }
        }
        return matrix;
    }
};
```

##  547. Friend Circles

如果A和B是朋友，B和C是朋友，那么A和C就是间接朋友，属于一个朋友圈

先给出所有人的关系，求有多少个朋友圈。

DFS，一次遍历每一个人，并用visited数组来记录是否访问过某人的信息，只要有朋友关系且之前没有访问过，就展开递归。

```cpp
class Solution
{
  public:
	int findCircleNum(vector<vector<int>> &M)
	{
		if (M.empty())
			return 0;
		int n = M.size();
		vector<bool> visited(n, false);
		int groups = 0;
		for (int i = 0; i < visited.size(); i++)
		{
			groups += !visited[i] ? dfs(i, M, visited), 1 : 0;
		}
		return groups;
	}

  private:
	void dfs(int i, vector<vector<int>> &M, vector<bool> &visited)
	{
		visited[i] = true;
		for (int j = 0; j < visited.size(); j++)
		{
			if (i != j && M[i][j] && !visited[j])
			{
				dfs(j, M, visited);
			}
		}
	}
};
```

##  698. Partition to K Equal Sum Subsets

将数组分成K等分。解题思路同473. Matchsticks to Square，473是k为4的特殊情况

```cpp
class Solution
{
  public:
	bool canPartitionKSubsets(vector<int> &nums, int k)
	{
		int sum = 0;
		for (int num : nums)
			sum += num;
		if (k <= 0 || sum % k != 0)
			return false;
		vector<int> visited(nums.size(), 0);
		return canPartition(nums, visited, 0, k, 0, 0, sum / k);
	}

	bool canPartition(vector<int> &nums, vector<int> &visited, 
	int start_index, int k, int cur_sum, int cur_num, int target)
	{
		if (k == 1)
			return true;
		if (cur_sum == target && cur_num > 0)
			return canPartition(nums, visited, 0, k - 1, 0, 0, target);
		for (int i = start_index; i < nums.size(); i++)
		{
			if (!visited[i])
			{
				visited[i] = 1;
				if (canPartition(nums, visited, i + 1, k, 
				cur_sum + nums[i], cur_num++, target))
					return true;
				visited[i] = 0;
			}
		}
		return false;
	}
};
```

##  752. Open the Lock

##  785. Is Graph Bipartite?

判断一个图是不是二分图，即可以将定点分为两组，所有的边的两个定点分别在这两组中。

```cpp
class Solution
{
  public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<int> colors(n, 0);

        for (int i = 0; i < n; i++)
        {
            if (colors[i] != 0)
                continue;
            queue<int> q;
            q.push(i);
            colors[i] = 1;

            while (!(q.empty()))
            {
                int cur = q.front();
                q.pop();
                for (auto next : graph[cur])
                {
                    if (colors[next] == 0)
                    {
                        colors[next] = -colors[cur];
                        q.push(next);
                    }
                    else if (colors[next] != -colors[cur])
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};
```

