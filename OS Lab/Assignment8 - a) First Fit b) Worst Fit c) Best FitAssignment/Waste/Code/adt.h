#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct node
{
	int start;
	int end;
	int size;
	char status[3];
	struct node *next;
};

struct node *newNode(int start, int end);			  // returns a newnode
int insert(struct node *temp, struct node **head);	  // inserts after a certain node
struct node *insertEnd(struct node *, struct node *); // inserts at the end
struct node *clone(struct node *list);				  // returns a clone of the list
struct node *merge(struct node *h1, struct node *h2); // in-place sorted merging of 2 sorted lists

struct node *newNode(int start, int end)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	strcpy(temp->status, "H");
	temp->end = end;
	temp->start = start;
	temp->size = temp->end - temp->start;
	temp->next = NULL;
	return temp;
}

struct node *insertEnd(struct node *p, struct node *temp)
{
	struct node *ptr = p;
	if (!ptr)
	{
		p = temp;
		p->next = NULL;
	}
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = temp;
		temp->next = NULL;
	}
	return p;
}

int insert(struct node *temp, struct node **head)
{
	if (!temp)
		return 0;
	struct node *ptr = *head;
	if (!*head)
	{
		*head = insertEnd(*head, temp);
		return 1;
	}
	if (temp->start < ptr->start)
	{
		temp->next = *head;
		*head = temp;
		return 1;
	}
	while (ptr->next && temp->start > ptr->next->start)
		ptr = ptr->next;
	temp->next = ptr->next;
	ptr->next = temp;
	return 1;
}

struct node *clone(struct node *list)
{
	if (!list)
		return NULL;

	struct node *result = (struct node *)malloc(sizeof(struct node));
	result->start = list->start;
	result->end = list->end;
	result->size = list->size;
	strcpy(result->status, list->status);
	result->next = clone(list->next);
	return result;
}

struct node *merge(struct node *h1, struct node *h2)
{
	if (!h1)
		return h2;
	if (!h2)
		return h1;
	if (h1->start < h2->start)
	{
		h1->next = merge(h1->next, h2);
		return h1;
	}
	else
	{
		h2->next = merge(h1, h2->next);
		return h2;
	}
}
