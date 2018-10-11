# LinkList

```cpp


```

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

###  141. Linked List Cycle

判断一个链表中是否有环。要求O\(1\)复杂度

如果链表中有环，那么单凭借一个指针，如果想要做到，需要申请数组，记录指针的地址，查看是否有重复出现的地址，这样空间复杂度达不到要求。所以我们需要用两个指针，一快一慢。如果链表中有环，那么在循环的过程中，快指针一定能够追上慢指针，即二者的值相同。如果快指针值为NULL，表明没有环。

```cpp
class Solution
{
  public:
	bool hasCycle(ListNode *head)
	{
		ListNode *slow = head, *fast = head;
		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (fast == slow)
				return true;
		}
		return false;
	}
};
```



