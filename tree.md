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

