# Tree

##  100. Same Tree

判断两个树是否相同。

递归，相同即 结点的val相同，且左右子树也相同，递归求解即可。

```cpp
class Solution
{
  public:
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        if (p == NULL && q == NULL)
            return true;
        else if (p && q)
            return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        else
            return false;
    }
};
```

##  101. Symmetric Tree

判断一棵树是否是左右对称的。

即要判断左右子树是否是一对镜像。如何判断两颗树是镜像？需要满足两点要求：

1. 根节点的val相同
2. 一棵树的左子树是另一颗树的右子树的镜像

```cpp
class Solution
{
  public:
    bool isMirror(TreeNode *p, TreeNode *q)
    {
        if (p == NULL && q == NULL)
            return true;
        else if (p == NULL || q == NULL)
            return false;
        else
            return p->val == q->val && isMirror(p->left, q->right) && isMirror(p->right, q->left);
    }
    bool isSymmetric(TreeNode *root)
    {
        return isMirror(root, root);
    }
};
```

##  104. Maximum Depth of Binary Tree

求一棵树的最大深度，递归。首先要判断root是否为NULL，然后返回左右子树较大者+1

```cpp
class Solution
{
  public:
    int maxDepth(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};
```

##  107. Binary Tree Level Order Traversal II

求一棵树的层序遍历，并将结果存放在数组中。

层序遍历非递归解法需借助队列。

对于每一层的结点，依次出队列，判断其左右子结点是否为空，不为空则入队，作为下一层需要遍历的结点。要注意队列的size是一直改变的，所以在循环判断时，要提前获取qe的size，表示当前层结点的个数。最后的结果还需要反转。

```cpp
class Solution
{
  public:
    vector<vector<int>> levelOrderBottom(TreeNode *root)
    {
        vector<vector<int>> ret;
        if (root == NULL)
            return ret;
        queue<TreeNode *> qe;
        qe.push(root);
        while (!qe.empty())
        {
            vector<int> t;
            int size = qe.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *p = qe.front();
                qe.pop();
                if (p->left)
                    qe.push(p->left);
                if (p->right)
                    qe.push(p->right);
                t.push_back(p->val);
            }
            ret.push_back(t);
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }
};
```

##  108. Convert Sorted Array to Binary Search Tree

将一个有序数组转化为一棵平衡二叉树。

递归解决，具体方法是：树的root结点应该是数组的中心，这样才能够转化成平衡树，确定了中心点后，将数组划分成两部分，递归解决。

```cpp
class Solution
{
  public:
	TreeNode *helper(int left, int right, vector<int> &nums)
	{
		if (left > right)
			return NULL;
		int mid = (left + right) / 2;
		TreeNode *p = new TreeNode(nums[mid]);

		p->left = helper(left, mid - 1, nums);
		p->right = helper(mid + 1, right, nums);
		return p;
	}

	TreeNode *sortedArrayToBST(vector<int> &nums)
	{
		TreeNode *ret;
		ret = helper(0, nums.size() - 1, nums);
		return ret;
	}
};
```

##  110. Balanced Binary Tree

判断一棵树是否是平衡二叉树。

Depth辅助函数，求出一棵树的高度。判断每个结点的左子树和右子树的差值是否&lt;=1

```cpp
class Solution
{
  public:
	int Depth(TreeNode *root)
	{
		if (root == NULL)
			return 0;
		return 1 + max(Depth(root->left), Depth(root->right));
	}

	bool isBalanced(TreeNode *root)
	{
		if (root == NULL)
			return true;

		int left = Depth(root->left);
		int right = Depth(root->right);

		return abs(left - right) <= 1 && isBalanced(root->left) && isBalanced(root->right);
	}
};
```

##  226. Invert Binary Tree

Invert a binary tree.

**Example:**

Input:

```text
     4
   /   \
  2     7
 / \   / \
1   3 6   9
```

Output:

```text
     4
   /   \
  7     2
 / \   / \
9   6 3   1
```

反转一颗二叉树。使用类似交换整数数值的操作即可。要用一个临时指针用于存储。

```cpp
class Solution
{
  public:
	TreeNode *invertTree(TreeNode *root)
	{

		if (root == NULL)
			return NULL;

		TreeNode *t = root->left;
		root->left = invertTree(root->right);
		root->right = invertTree(t);

		return root;
	}
};
```

##  \#235. Lowest Common Ancestor of a Binary Search Tree

Given a binary search tree \(BST\), find the lowest common ancestor \(LCA\) of two given nodes in the BST.

According to the [definition of LCA on Wikipedia](https://en.wikipedia.org/wiki/Lowest_common_ancestor): “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants \(where we allow **a node to be a descendant of itself**\).”

给定一棵二叉搜索树和两个结点，求它们的最小公共祖先。

两个结点的先祖结点，值必定是介于二者之间，因此会有

```cpp
(root->val - p->val) * (root->val - q->val) <= 0
```



```cpp
class Solution {
public:
	TreeNode* lowestCommonAncestor( TreeNode* root, TreeNode* p, TreeNode* q )
	{
		while ( (root->val - p->val) * (root->val - q->val) > 0 )
			root = p->val < root->val ? root->left : root->right;
		return(root);
	}
};
```

##  404. Sum of Left Leaves

求所有左叶子结点的和。

首先，肯定要通过递归遍历整颗数。然后，要判断是不是一个左叶子结点，如果是，就加上val

```cpp

class Solution
{
  public:
	int sumOfLeftLeaves(TreeNode *root)
	{

		int ret = 0;

		if (root == NULL)
			return 0;
		if (root->left && root->left->left == NULL && root->left->right == NULL)
			ret += root->left->val;
		else
			ret += sumOfLeftLeaves(root->left);

		ret += sumOfLeftLeaves(root->right);
		return ret;
	}
};
```

##  530. Minimum Absolute Difference in BST

二叉搜索树结点最小绝对值差。利用中序遍历可以得到一个有序的数列，而最小的差一定是两个相邻数的差，所以采用中序遍历，每一次记录上一个结点的值pre和最小差值min\_dif，再用当前结点值减去上一个结点值，得到一个可能的min\_dif，用min进行比较。

```cpp
class Solution
{
  public:
	int min_dif = INT_MAX;
	int pre = -1;
	int getMinimumDifference(TreeNode *root)
	{
		if (root->left)
			getMinimumDifference(root->left);

		if (pre != -1)
			min_dif = min(min_dif, abs(root->val - pre));
		pre = root->val;

		if (root->right)
			getMinimumDifference(root->right);

		return min_dif;
	}
};
```

##  538. Convert BST to Greater Tree

Given a Binary Search Tree \(BST\), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

把二叉搜索树的所有结点加上比该结点大的所有结点值。

递归，按右子树、根节点、左子树的顺序，记录sum。

```cpp
class Solution
{
  public:
	int sum = 0;
	TreeNode *convertBST(TreeNode *root)
	{
		if (!root)
			return root;
		if (root->right)
			convertBST(root->right);

		root->val += sum;
		sum = root->val;
		if (root->left)
			convertBST(root->left);

		return root;
	}
};
```

##  543. Diameter of Binary Tree

 Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the **longest**path between any two nodes in a tree. This path may or may not pass through the root.

求二叉树的半径。

通过一个结点的最长路径值等于 左字数的最大深度+ 右字数的最大深度+1

可以递归求每个结点最大深度，并计算半径，得到max

```cpp
class Solution
{
  public:
	int ret = 0;

	int diameterOfBinaryTree(TreeNode *root)
	{
		maxDepth(root);
		return ret;
	}

	int maxDepth(TreeNode *root)
	{
		if (root == NULL)
			return 0;

		int left = maxDepth(root->left);
		int right = maxDepth(root->right);

		ret = max(ret, left + right);

		return max(left, right) + 1;
	}
};
```

##  606. Construct String from Binary Tree

通过一个二叉树构造字符串。递归，注意处理空的左子树不能全部忽略即可。

```cpp
class Solution {
public:

	string str = "";
	string tree2str( TreeNode* t )
	{
		if ( t == NULL )
			return(str);

		str += to_string( t->val );
		if ( t->left || t->right )
		{
			str += "(";
			if ( t->left )
				tree2str( t->left );
			str += ")";
		}
		if ( t->right )
		{
			str += "(";
			tree2str( t->right );
			str += ")";
		}

		return(str);
	}
};
```

##  617. Merge Two Binary Trees

合并两个二叉树。

```cpp
class Solution {
public:
	TreeNode* mergeTrees( TreeNode* t1, TreeNode* t2 )
	{
		if ( t2 == NULL )
			return(t1);
		else if ( t1 == NULL )
			return(t2);

		t1->val		= t1->val + t2->val;
		t1->left	= mergeTrees( t1->left, t2->left );
		t1->right	= mergeTrees( t1->right, t2->right );
		return(t1);
	}
};
```

##  669. Trim a Binary Search Tree

给一颗二叉搜索树，将其按一定的区间\[L,R\]进行修剪。判断当前结点的值，如果为NULL，返回NULL。如果小于新区间的最小值，则返回右子树的修剪。大于区间的最大值，则返回左子树的修剪。如果在区间内，则该结点不变，修改遍历修剪左右子树。

```cpp
class Solution
{
public:
	TreeNode *trimBST(TreeNode *root, int L, int R)
	{
		if (root == NULL)
			return NULL;
		if (root->val < L)
			return trimBST(root->right, L, R);
		if (root->val > R)
			return trimBST(root->left, L, R);
		root->left = trimBST(root->left, L, R);
		root->right = trimBST(root->right, L, R);
		return root;
	}
};
```

##  872. Leaf-Similar Trees

二叉树的叶子结点从左到右组成一个序列，如果两颗树的序列相同，返回true，否则返回false。

```cpp
class Solution
{
  public:
    bool leafSimilar(TreeNode *root1, TreeNode *root2)
    {

        vector<int> ret1;
        vector<int> ret2;
        Getleaf(root1, ret1);
        Getleaf(root2, ret2);
        if (ret1 == ret2)
            return true;
        else
            return false;
    }

    void Getleaf(TreeNode *root, vector<int> &leaf)
    {
        if (root == NULL)
            return;
        if (root->left == NULL && root->right == NULL)
        {
            leaf.push_back(root->val);
            return;
        }

        Getleaf(root->left, leaf);
        Getleaf(root->right, leaf);
    }
};
```

## Medium

##  199. Binary Tree Right Side View

二叉树的右视图，即每一层从右往左看能看到的第一个结点值构成的序列。

递归整个树（根-&gt;右-&gt;左），将第一个结点的值放入返回值中。通过返回数组大小和层数来判断是不是最右边的结点。

```cpp
class Solution {
public:
    void recursion(TreeNode *root, int level, vector<int> &res)
    {
        if(root==NULL) return ;
        if(res.size()<level) res.push_back(root->val);
        recursion(root->right, level+1, res);
        recursion(root->left, level+1, res);
    }
    
    vector<int> rightSideView(TreeNode *root) {
        vector<int> res;
        recursion(root, 1, res);
        return res;
    }
};
```

##  208. Implement Trie \(Prefix Tree\)

##  211. Add and Search Word - Data structure design

##  230. Kth Smallest Element in a BST

##  236. Lowest Common Ancestor of a Binary Tree

##  331. Verify Preorder Serialization of a Binary Tree

##  337. House Robber III

