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

###  160. Intersection of Two Linked Lists

找出两个链表的交点。如果没有交点，则返回NULL

For example, the following two linked lists:

```text
A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
```

begin to intersect at node c1.

假设存在交点，A的链表长度为l1+l3，B的长度为l2+l3 （l3为两个链表的公共部分）。那么，如果我们用两个不同的指针p1，p2 分别遍历链表，并且在p1遍历完A后，接着遍历B链表，p2指针做类似的操作，那么在p1，p2第一次相遇的时候，就是在交点，因为两个指针都移动了l1+l2+l3的距离。如果p1p2都是NULL，说明没有交点。

```cpp
class Solution
{
  public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
	{

		if (headA == NULL || headB == NULL)
			return NULL;
		ListNode *p1 = headA, *p2 = headB;
		while ((p1 || p2) && p1 != p2)
		{
			p1 = p1 ? p1->next : headB;
			p2 = p2 ? p2->next : headA;
		}
		return p1;
	}
};
```

###  203. Remove Linked List Elements

Remove all elements from a linked list of integers that have value **val**.

**Example:**

```text
Input:  1->2->6->3->4->5->6, val = 6
Output: 1->2->3->4->5
```

删除链表中值为val的元素。

要注意处理表头。

```cpp
class Solution
{
  public:
	ListNode *removeElements(ListNode *head, int val)
	{

		while (head && head->val == val)
			head = head->next;

		ListNode *p = head;
		while (p && p->next)
		{
			while (p->next && p->next->val == val)
				p->next = p->next->next;
			p = p->next;
		}
		return head;
	}
};
```

### 206. Reverse Linked List

Reverse a singly linked list.

**Example:**

```text
Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
```

转置一个链表。

需要用到三个指针，一个指向前一个结点，一个指向当前结点，一个指向下一个结点。即pre，cur，next。

对于当前结点，转置之后，cur-&gt;next 应该指向 pre，那么如果不用next指针保存原本的cur-&gt;next值，那就会造成链表丢失。pre值用来记录前一个结点，可以方便直接给cur-&gt;next赋值。当完成一个结点的转置工作后，当前pre变成了cur，cur变成了next。

```cpp
class Solution
{
  public:
	ListNode *reverseList(ListNode *head)
	{
		ListNode *cur = head, *next, *pre = NULL;
		while (cur)
		{
			next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;
		}
		return pre;
	}
};
```

