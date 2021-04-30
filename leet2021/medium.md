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

### [208 Medium. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree)

前缀树。需要一个bool来表示当前结点是否存了一个单词。用一个size为26的vector<Trie*>来检索单词。 注：没写析构函数

```cpp
class Trie
{
private:
    //Trie * child;
    std::vector<Trie *> children;
    bool ends;

public:
    /** Initialize your data structure here. */
    Trie()
    {
        children.resize(26, nullptr);
        ends = false;
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    {
        Trie *p = this;
        for (auto ch : word)
        {
            if (p->children[ch - 'a'] == nullptr)
            {
                p->children[ch - 'a'] = new Trie();
            }
            p = p->children[ch - 'a'];
        }
        p->ends = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    {
        Trie *p = this;
        for (auto ch : word)
        {
            if (p->children[ch - 'a'] == nullptr)
            {
                return false;
            }
            p = p->children[ch - 'a'];
        }
        return p->ends;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {

        Trie *p = this;
        for (auto ch : prefix)
        {
            if (p->children[ch - 'a'] == nullptr)
            {
                return false;
            }
            p = p->children[ch - 'a'];
        }
        return true;
    }
};
```

### [337 Medium. House Robber III](https://leetcode.com/problems/house-robber-iii)

对于一个node，有rob和not rob两种情况，当rob当前结点的时候，其两个子结点不能rob，只能rob其孙结点，递归调用其四个孙结点即可。

如果不rob当前结点，那么就可以递归调用其两个子结点

```cpp
class Solution
{
public:
    std::unordered_map<TreeNode *, int> mmap;

    int rob(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        if (mmap.count(root))
            return mmap.at(root);

        int v1 = rob(root->left) + rob(root->right);
        int v2 = root->val;
        if (root->left)
            v2 += rob(root->left->left) + rob(root->left->right);
        if (root->right)
            v2 += rob(root->right->left) + rob(root->right->right);
        int value = max(v1, v2);
        mmap[root] = value;
        return value;
    }
};
```


### [1530 Medium. Number of Good Leaf Nodes Pairs](https://leetcode.com/problems/number-of-good-leaf-nodes-pairs)

核心是返回一个`vector<int>` 来保存当前结点到所有叶子结点的距离。
    
两个叶子结点的距离，等于他们最近祖先到两个叶子结点的距离。

递归思路：一个结点到其所有叶子结点的距离，可以等于其所有子树的距离之和+2

```cpp
class Solution
{
public:
    int countPairs(TreeNode *root, int distance)
    {
        ans = 0;
        dfs(root, distance);
        return ans;
    }
    int ans = 0;
    vector<int> dfs(TreeNode *root, int distance)
    {
        vector<int> ret;
        if (root == NULL)
            return ret;

        auto v1 = dfs(root->left, distance);
        auto v2 = dfs(root->right, distance);
        if (v1.size() == 0 && v2.size() == 0)
        {
            ret.push_back(0);
            return ret;
        }

        for (int i = 0; i < v1.size(); i++)
        {
            for (int j = 0; j < v2.size(); j++)
            {
                if (v1[i] + v2[j] + 2 <= distance)
                    ans++;
            }
        }

        for (int i = 0; i < v1.size(); i++)
        {
            v1[i]++;
            ret.push_back(v1[i]);
        }

        for (int i = 0; i < v2.size(); i++)
        {
            v2[i]++;
            ret.push_back(v2[i]);
        }

        return ret;
    }
};
```

### [64 Medium. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum)

经典dp

```cpp
class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < grid.size(); i++)
        {
            dp[i][0] = grid[i][0] + dp[i - 1][0];
        }
        for (int i = 1; i < n; i++)
        {
            dp[0][i] = grid[0][i] + dp[0][i - 1];
        }

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[m - 1][n - 1];
    }
};
```

### [1493 Medium. Longest Subarray of 1's After Deleting One Element](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element)

一个0,1数组，将其中一个0改成1之后，最长连续1的长度。

没看懂lee的解答。自己的解法太菜。

### [1319 Medium. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected)

union-find 计算出有多少个不连通的结点，再-1。这里nums[i]=i表示这是一个单独的结点

```cpp
class Solution
{
public:
    vector<int> nums;
    int makeConnected(int n, vector<vector<int>> &connections)
    {
        if (n - 1 > connections.size())
        {
            return -1;
        }
        nums.resize(n);
        for (int i = 0; i < nums.size(); i++)
        {
            nums[i] = i;
        }

        for (auto connection : connections)
        {
            int v1 = find(connection[0]);
            int v2 = find(connection[1]);
            if (v1 != v2)
                nums[v1] = v2;
        }
        int count = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == i)
                count++;
        }
        return count - 1;
    }

    int find(int x)
    {
        if (x != nums[x])
            return find(nums[x]);
        return x;
    }
};
```

### [240 Medium. Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii)

经典题目，从左下角或者右上角开始搜索。
    
### [106 Medium. Construct Binary Tree from Inorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal)

还是递归。宗旨是，后序遍历的最后一个是根节点，利用map找到根节点在中序遍历中的位置，这样可以获得中序遍历的左右两棵子树，以及结点个数。根据个数，可以推出来后续遍历的子树起始点和结束点。

```cpp
class Solution
{
public:
    std::map<int, int> inMap;
    TreeNode *helper(vector<int> &inorder, vector<int> &postorder, int l1, int r1, int l2, int r2)
    {
        if (l1 > r1 || l2 > r2)
            return NULL;

        // 根节点是后序遍历的最后一个结点
        int rootValue = postorder[r2];
        int posRootInOrder = inMap[rootValue];
        // 左右子树的中序遍历结点
        int leftl1 = l1, leftr1 = posRootInOrder - 1;
        int rightl1 = posRootInOrder + 1, rightr1 = r1;

        // 右子树可以根据左子树算出节点个数
        int leftl2 = l2, leftr2 = leftl2 + leftr1 - leftl1;
        int rightl2 = leftr2 + 1, rightr2 = r2 - 1;

        TreeNode *left = helper(inorder, postorder, leftl1, leftr1, leftl2, leftr2);
        TreeNode *right = helper(inorder, postorder, rightl1, rightr1, rightl2, rightr2);
        TreeNode *root = new TreeNode(rootValue, left, right);
        return root;
    }

    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        for (int i = 0; i < inorder.size(); i++)
            inMap[inorder[i]] = i;

        return helper(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
    }
};
```

### [1372 Medium. Longest ZigZag Path in a Binary Tree](https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree)

ZigZag 核心还是递归，dfs。lee的答案太牛了

```cpp
class Solution
{
public:
    int longestZigZag(TreeNode *root)
    {
        return dfs(root)[2];
    }

    vector<int> dfs(TreeNode *root)
    {
        if (!root)
            return {-1, -1, -1};
        vector<int> left = dfs(root->left), right = dfs(root->right);
        int res = max(max(left[1], right[0]) + 1, max(left[2], right[2]));
        return {left[1] + 1, right[0] + 1, res};
    }
};
```
