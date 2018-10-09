# Tree

###  100. Same Tree

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

###  101. Symmetric Tree

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

###  104. Maximum Depth of Binary Tree

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

