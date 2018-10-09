# LinkList

###  21. Merge Two Sorted Lists

合并两个有序的链表。

要注意的点：给出的链表和返回的链表都是不带头结点的。

```cpp
class Solution {
public:
	ListNode* mergeTwoLists( ListNode* l1, ListNode* l2 )
	{
		ListNode * l = new ListNode( 0 );

		ListNode *ret = l;
		while ( l1 || l2 )
		{
			int	v1	= l1 ? l1->val : INT_MAX;
			int	v2	= l2 ? l2->val : INT_MAX;
			if ( v1 < v2 )
			{
				l->next = new ListNode( v1 );
				l1	= l1->next;
			}else  {
				l->next = new ListNode( v2 );
				l2	= l2->next;
			}
			l = l->next;
		}


		l->next = NULL;
		return(ret->next);
	}
};
```

###  83. Remove Duplicates from Sorted List

 Given a sorted linked list, delete all duplicates such that each element appear only _once_.

给定一个有序的链表，删除其中重复的元素。

比较当前结点和下一结点的val即可，如果相同则跳过下一结点。

```cpp
class Solution
{
  public:
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *p1 = head;
        while (p1 && p1->next)
        {
            if (p1->val == p1->next->val)
                p1->next = p1->next->next;
            else
                p1 = p1->next;
        }
        return head;
    }
};
```

