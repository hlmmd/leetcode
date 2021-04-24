## 根据难度&like和dislike的比例筛选了一些题目

### [990 Medium. Satisfiability of Equality Equations](https://leetcode.com/problems/satisfiability-of-equality-equations)

首先假定a-z对应0-25，每个等号修改其指向的值。核心是理解find()函数，即字母指向的真实值

```cpp
class Solution
{
public:
    vector<int> value;

    bool equationsPossible(vector<string>& equations)
    {
        value.resize(26);
        for (int i = 0; i < value.size(); i++)
            value[i] = i;

        for (auto& equation : equations)
        {
            if (equation[1] == '=')
                value[find((equation[3] - 'a'))] = find(equation[0] - 'a');
        }

        for (auto& equation : equations)
        {
            if (equation[1] == '!' && find(equation[3] - 'a') == find(equation[0] - 'a'))
                return false;
        }
        return true;
    }

    int find(int x)
    {
        if (x != value[x])
            return find(value[x]);
        return x;
    }
};
```

### [958 Medium. Check Completeness of a Binary Tree](https://leetcode.com/problems/check-completeness-of-a-binary-tree)

判断是否是完全二叉树

```cpp
class Solution
{
public:
    bool isCompleteTree(TreeNode* root)
    {
        vector<TreeNode*> bfs;
        bfs.push_back(root);
        int i = 0;
        while (i < bfs.size() && bfs[i])
        {
            bfs.push_back(bfs[i]->left);
            bfs.push_back(bfs[i]->right);
            i++;
        }
        while (i < bfs.size() && !bfs[i])
            i++;
        return i == bfs.size();
    }
};
```

### [1546 Medium. Maximum Number of Non-Overlapping Subarrays With Sum Equals Target](https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target)

求所有的子数组，不重叠，其和为target

需要用map来保存[0,i]的sum，每得到一个新的sum [0,j]，查找是否存在sum-target。如果存在，那么[i,j]的和就是target。由贪心可知，下一段target的起始index一定小于j，所以用了一个变量start来去掉那些会发生重叠的子数组。

```cpp
class Solution
{
public:
    int maxNonOverlapping(vector<int> &nums, int target)
    {
        int sum = 0;
        map<int, int> summap;
        summap[0] = -1;
        int start = -1;
        int ret = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            if (summap.find(sum - target) != summap.end())
            {
                int left = summap[sum - target];
                if (start <= left)
                {
                    start = i;
                    ret++;
                }
            }
            summap[sum] = i;
        }

        return ret;
    }
};
```
