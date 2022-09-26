#include "os8.h"

// merges actual holes
void combine(struct node **p)
{
	struct node *ptr = *p, *temp;
	while (ptr)
	{
		temp = ptr;
		while (temp->next && temp->end == temp->next->start && temp->id == temp->next->id) // remove the last id conditon to achieve full coalescing
			temp = temp->next;
		ptr->next = temp->next;
		ptr->end = temp->end;
		ptr->size = ptr->end - ptr->start;
		ptr = ptr->next;
	}
}

// merges all the adjacent holes
void combineall(struct node **p)
{
	struct node *ptr = *p, *temp;
	while (ptr)
	{
		temp = ptr;
		while (temp->next && temp->end == temp->next->start) // remove the last id conditon to achieve full coalescing
			temp = temp->next;
		ptr->next = temp->next;
		ptr->end = temp->end;
		ptr->size = ptr->end - ptr->start;
		ptr = ptr->next;
	}
}

// finds process node from alloc list and returns it
struct node *deallocate(struct node **p, char *pid)
{
	struct node *ptr = *p, *prev;
	if (ptr && strcmp(ptr->status, pid) == 0)
	{
		*p = ptr->next;
		strcpy(ptr->status, "H");
		return ptr;
	}
	while (ptr && strcmp(ptr->status, pid))
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (!ptr)
		return NULL;
	strcpy(ptr->status, "H");
	prev->next = ptr->next;
	return ptr;
}

// output chart
void table(struct node *p, char str[])
{
	struct node *ptr = p;
	if (!ptr)
	{
		printf("NULL\n\n");
		return;
	}
	for (int i = 0; i < strlen(str); i++) // top line
	{
		printf("%c", str[i] == '|' ? '+' : str[i] == '-' ? ' ' : '-');
	}

	printf("\n%s\n", str); // chart

	for (int i = 0; i < strlen(str); i++)
	{
		printf("%c", str[i] == '|' ? '+' : str[i] == '-' ? ' '
														 : '-');
	} // bottom line
	printf("\n");

	int end, s;
	end = ptr->end;
	s = strlen(ptr->status);

	while (ptr) // mem add
	{
		if (!ptr->next || ptr->end == ptr->next->start)
			printf("%-*d", 9 + strlen(ptr->status), ptr->start);
		else
			printf("%-*d%-*d", 9 + strlen(ptr->status), ptr->start, 9, ptr->end);
		end = ptr->end;
		s = strlen(ptr->status);
		ptr = ptr->next;
	}
	printf("%d", end);
	printf("\n\n\n");
}

// prints process node sequence
void disp(struct node *p)
{
	char buf[100], mem[1000];
	struct node *ptr = p;
	strcpy(mem, "|");
	while (ptr)
	{
		if (!ptr->next || ptr->end == ptr->next->start)
		{
			sprintf(buf, "    %s    |", ptr->status);
		}
		else if (ptr->end != ptr->next->start)
		{
			sprintf(buf, "    %s    |---------|", ptr->status);
		}
		strcat(mem, buf);
		ptr = ptr->next;
	}
	table(p, mem);
}

// helper function for disp
void display(struct node *p, struct node *q)
{
	printf("\nAlloc>\n\n");
	disp(p);
	printf("Free>\n\n");
	disp(q);
	struct node *r = merge(clone(p), clone(q));
	printf("Phy>\n\n");
	disp(r);
	free(r);
}

// returns size of the first-fit node
int first(struct node *f, int size)
{
	struct node *ptr = f;
	while (ptr && !(ptr->size >= size))
	{
		ptr = ptr->next;
	}
	if (!ptr)
		return -1;
	return ptr->size;
}

// returns size of the best-fit node
int best(struct node *f, int size)
{
	struct node *ptr = f;
	int min = INT_MAX;
	while (ptr)
	{
		if (ptr->size - size >= 0 && min > ptr->size - size)
			min = ptr->size - size;
		ptr = ptr->next;
	}
	if (min == INT_MAX)
		return -1;
	return min + size;
}

// returns size of the worst-fit node
int worst(struct node *f, int size)
{
	struct node *ptr = f;
	int max = INT_MIN;
	while (ptr)
	{
		if (ptr->size - size >= 0 && max < ptr->size - size)
			max = ptr->size - size;
		ptr = ptr->next;
	}
	// if(max==INT_MIN)
	//	return -1;
	return max + size;
}

// helper function to choose fit
int whichfit(struct node *f, int size, int ch)
{
	if (ch == 1)
		return first(f, size);
	if (ch == 2)
		return best(f, size);
	if (ch == 3)
		return worst(f, size);
}

// finds the node in freepool and retruns the allocated node
struct node *allocate(struct node **f, char *pid, int size, int ptrsize)
{
	if (ptrsize < 0)
		return NULL;
	struct node *ptr = *f, *prev;

	if (ptr->size == ptrsize)
	{
		if (ptr && ptr->size >= size)
		{
			if (ptr->size == size)
			{
				*f = ptr->next;
				strcpy(ptr->status, pid);
				// free(ptr);
				return ptr;
			}
			else
			{
				struct node *temp1 = newNode(ptr->start, ptr->start + size, ptr->id);
				struct node *temp2 = newNode(ptr->start + size, ptr->end, ptr->id);
				*f = temp2;
				temp2->next = ptr->next;
				strcpy(temp1->status, pid);
				free(ptr);
				return temp1;
			}
		}
	}

	while (ptr && !(ptr->size == ptrsize))
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (!ptr)
		return NULL;
	if (ptr->size == size)
	{
		prev->next = ptr->next;
		strcpy(ptr->status, pid);
		return ptr;
	}
	else
	{
		struct node *temp1 = newNode(ptr->start, ptr->start + size, ptr->id);
		struct node *temp2 = newNode(ptr->start + size, ptr->end, ptr->id);
		prev->next = temp2;
		temp2->next = ptr->next;
		strcpy(temp1->status, pid);
		free(ptr);
		return temp1;
	}
}

int main()
{
	int ch, n, start, end;
	printf("\nEnter the Memory Representation:");
	printf("\nEnter the no.of partitions in memory: ");
	scanf("%d", &n);
	struct node *fpool = NULL, *alloc = NULL, *temp = NULL;
	for (int i = 0; i < n; i++)
	{
		printf("Enter Starting and ending address of partition %d: ", i + 1);
		scanf("%d%d", &start, &end);
		if (start >= end || i && temp->end != start)
		{
			i--;
			printf("Invalid entry,enter again\n");
		}
		else
		{
			temp = newNode(start, end, i + 1);
			fpool = insertEnd(fpool, temp);
		}
	}

	display(alloc, fpool);

	int ch1, size;
	char pid[3];
	char fits[3][15] = {"First Fit", "Best Fit", "Worst Fit"};
	do
	{
		printf("\n1. First Fit\n2. Best Fit \n3. Worst Fit \n4. Exit \nEnter your choice: ");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
		case 2:
		case 3:
			break;
		case 4:
			printf("Exiting...\n");
			return 0;
			break;
		default:
			printf("\nInvalid Input!\n");
		}
		do
		{
			printf("\n\t\t%s Memory Allocation Algorithm\n\n1. Entry / Allocate\n2. Exit / Deallocate \n3. Display \n4. Coalescing of Holes \n5. Back to Algorithm \n6. Exit\nEnter your choice: ", fits[ch - 1]);
			scanf("%d", &ch1);
			switch (ch1)
			{
			case 1:
				printf("\nEnter process id : ");
				scanf("%s", pid);
				printf("Enter size needed : ");
				scanf("%d", &size);
				if (size <= 0)
				{
					printf("\nInvalid size!\n");
					break;
				}
				if (!insert(allocate(&fpool, pid, size, whichfit(fpool, size, ch)), &alloc))
				{
					printf("\nCouldn't allocate memory to %s!\n", pid);
					break;
				}
				else
					printf("\nMemory is allocted to %s\n", pid);
				display(alloc, fpool);
				break;
			case 2:
				printf("\nEnter process id : ");
				scanf("%s", pid);
				if (!insert(deallocate(&alloc, pid), &fpool))
				{
					printf("\nProcess %s is not there!\n", pid);
					break;
				}
				else
					printf("\n%s's memory is deallocted\n", pid);
				combine(&fpool);
				display(alloc, fpool);
				break;
			case 3:
				display(alloc, fpool);
				break;
			case 4:
				combineall(&fpool);
				display(alloc, fpool);
				break;
			case 5:
				break;
			case 6:
				printf("Exiting...\n");
				return 0;
				break;
			default:
				printf("\nInavlid Input!\n");
			}
		} while (!(ch1 == 5 || ch1 == 6));
	} while (ch != 4);
	return 0;
}
