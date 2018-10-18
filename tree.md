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

