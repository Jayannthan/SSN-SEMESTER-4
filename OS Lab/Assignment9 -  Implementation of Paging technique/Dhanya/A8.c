#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
typedef struct process
{
	char pid[3];
	int start;
	int end;
	int size;
	int alloc;
} process;
typedef struct partition
{
	int num;
	process pro_arr[MAX];
	int start;
	int end;
	int size;
	int free;
} partition;
void firstfit(int n, partition blocks[])
{
	printf("Enter process id: ");
	char name[3];
	scanf("%s", name);
	printf("Enter size needed: ");
	int size_need;
	scanf("%d", &size_need);
	int flag = 0;
	for (int i = 0; i < n; i++)
		if (blocks[i].free != 0 && blocks[i].free >= size_need)
		{
			blocks[i].num += 1;
			strcpy(blocks[i].pro_arr[blocks[i].num].pid, name);
			blocks[i].pro_arr[blocks[i].num].start =
				blocks[i].start + blocks[i].size - blocks[i].free;
			blocks[i].pro_arr[blocks[i].num].size = size_need;
			blocks[i].pro_arr[blocks[i].num].end = blocks[i].pro_arr[blocks[i].num].start + blocks[i].pro_arr[blocks[i].num].size;
			blocks[i].free -= size_need;
			flag = 1;
			break;
		}
	if (flag == 1)
		printf("Memory allocation successful\n");
	else
		printf("Memory allocation unsuccessful\n");
}
void bestfit(int n, partition blocks[])
{
	printf("Enter process id: ");
	char name[3];
	scanf("%s", name);
	printf("Enter size needed: ");
	int size_need;
	scanf("%d", &size_need);
	int flag = -1;
	for (int i = 0; i < n; i++)
		if (blocks[i].free >= size_need)
		{
			if (flag == -1)
				flag = i;
			else if (blocks[flag].free > blocks[i].free)
				flag = i;
		}
	if (flag != -1)
	{
		printf("Memory allocation successful\n");
		blocks[flag].num += 1;
		strcpy(blocks[flag].pro_arr[blocks[flag].num].pid, name);
		blocks[flag].pro_arr[blocks[flag].num].start = blocks[flag].start + blocks[flag].size - blocks[flag].free;
		blocks[flag].pro_arr[blocks[flag].num].size = size_need;
		blocks[flag].pro_arr[blocks[flag].num].end = blocks[flag].pro_arr[blocks[flag].num].start + blocks[flag].pro_arr[blocks[flag].num].size;
		blocks[flag].free -= size_need;
	}
	else
		printf("Memory allocation unsuccessful\n");
}
void worstfit(int n, partition blocks[])
{
	printf("Enter process id: ");
	char name[3];
	scanf("%s", name);
	printf("Enter size needed: ");
	int size_need;
	scanf("%d", &size_need);
	int flag = -1;
	for (int i = 0; i < n; i++)
		if (blocks[i].free >= size_need)
		{
			if (flag == -1)
				flag = i;
			else if (blocks[flag].free < blocks[i].free)
				flag = i;
		}
	if (flag != -1)
	{
		printf("Memory allocation successful\n");
		blocks[flag].num += 1;
		strcpy(blocks[flag].pro_arr[blocks[flag].num].pid, name);
		blocks[flag].pro_arr[blocks[flag].num].start = blocks[flag].start + blocks[flag].size - blocks[flag].free;
		blocks[flag].pro_arr[blocks[flag].num].size = size_need;
		blocks[flag].pro_arr[blocks[flag].num].end = blocks[flag].pro_arr[blocks[flag].num].start + blocks[flag].pro_arr[blocks[flag].num].size;
		blocks[flag].free -= size_need;
	}
	else
		printf("Memory allocation unsuccessful\n");
}
void deallocate(int n, partition blocks[])
{
	printf("Enter process id: ");
	char name[3];
	scanf("%s", name);
	int flag = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (!strcmp(name, blocks[i].pro_arr[j].pid))
			{
				blocks[i].free += blocks[i].pro_arr[j].size;
				blocks[i].pro_arr[j].start = -1;
				blocks[i].pro_arr[j].size = -1;
				blocks[i].pro_arr[j].end = -1;
				blocks[i].num -= 1;
				flag = 1;
			}
	if (flag == 1)
		printf("Memory deallocation successful\n");
	else
		printf("Memory deallocation unsuccessful\n");
}
void coalesce(int n, partition blocks[])
{
	printf(" ");
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= blocks[i].num; j++)
			printf("------- ");
	printf("------- ");
	printf("\n|");
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= blocks[i].num; j++)
			printf("   %s  |", blocks[i].pro_arr[j].pid);
	printf("   H  |");
	printf("\n ");
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= blocks[i].num; j++)
			printf("------- ");
	printf("------- ");
	printf("\n");
	int pro = 100;
	printf("%d     ", pro);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= blocks[i].num; j++)
		{
			pro += blocks[i].pro_arr[j].size;
			printf("%d     ", pro);
		}
		if (i == n - 1)
			printf("%d", blocks[i].end);
	}
	printf("\n");
}
void display_free(int n, partition blocks[])
{
	printf(" ");
	for (int i = 0; i < n; i++)
		printf("------- ");
	printf("\n|");
	for (int i = 0; i < n; i++)
	{
		if (blocks[i].free != 0)
			printf("   %d   |", blocks[i].free);
		else
			printf("   0   |");
	}
	printf("\n ");
	for (int i = 0; i < n; i++)
		printf("------- ");
	printf("\n");
	printf("%d     ", blocks[0].start);
	for (int i = 0; i < n; i++)
		printf("%d     ", blocks[i].end);
	printf("\n");
}
void display_allocated(int n, partition blocks[])
{
	printf(" ");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= blocks[i].num; j++)
			printf("------- ");
		if (blocks[i].free != 0)
			printf("------- ");
	}
	printf("\n|");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= blocks[i].num; j++)
			printf("   %s  |", blocks[i].pro_arr[j].pid);
		if (blocks[i].free != 0)
			printf("   H   |");
	}
	printf("\n ");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= blocks[i].num; j++)
			printf("------- ");
		if (blocks[i].free != 0)
			printf("------- ");
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= blocks[i].num; j++)
			printf("%d     ", blocks[i].pro_arr[j].start);
		if (blocks[i].free != 0)
			printf("%d     ", blocks[i].start + blocks[i].size - blocks[i].free);
		if (i == n - 1)
			printf("%d", blocks[i].end);
	}
	printf("\n");
}
void display(int n, partition blocks[])
{
	printf("\nPhysical Memory:\n");
	display_allocated(n, blocks);
	printf("\nFree Pool:\n");
	display_free(n, blocks);
}
int main()
{
	printf("\n----------------------\n");
	printf("\nMEMORY REPRESENTATION\n");
	printf("\n----------------------\n");
	printf("Enter the no. of partitions in memory: ");
	int num_parts;
	scanf("%d", &num_parts);
	partition blocks[num_parts];
	int temp_block[num_parts];
	for (int i = 0; i < num_parts; i++)
	{
		printf("Starting and ending address of partition %d: ", i + 1);
		scanf("%d %d", &blocks[i].start, &blocks[i].end);
		blocks[i].size = blocks[i].end - blocks[i].start;
		temp_block[i] = blocks[i].free = blocks[i].size;
		blocks[i].num = -1;
	}
	display(num_parts, blocks);
	int choice = 0;
	do
	{
		printf("\nMemory Allocation Algorithm\n");
		printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		if (choice == 1)
		{
			int select = 0;
			do
			{
				printf("\n\t\tFirst Fit Memory Allocation Algorithm\n");
				printf("\n1. Entry/Allocate\n2. Exit/Deallocate\n3. Display\n4. Coalescing of Holes\n5. Back to algorithm\n\n");
				printf("Enter choice: ");
				scanf("%d", &select);
				if (select == 1)
					firstfit(num_parts, blocks);
				else if (select == 2)
					deallocate(num_parts, blocks);
				else if (select == 3)
					display(num_parts, blocks);
				else if (select == 4)
					coalesce(num_parts, blocks);
			} while (select != 5);
		}
		if (choice == 2)
		{
			int select = 0;
			do
			{
				printf("\n\t\tBest Fit Memory Allocation Algorithm\n");
				printf("\n1. Entry/Allocate\n2. Exit/Deallocate\n3. Display\n4. Coalescing of Holes\n5. Back to algorithm\n\n");
				printf("Enter choice: ");
				scanf("%d", &select);
				if (select == 1)
					bestfit(num_parts, blocks);
				else if (select == 2)
					deallocate(num_parts, blocks);
				else if (select == 3)
					display(num_parts, blocks);
				else if (select == 4)
					coalesce(num_parts, blocks);
			} while (select != 5);
		}
		if (choice == 3)
		{
			int select = 0;
			do
			{
				printf("\n\t\tWorst Fit Memory Allocation Algorithm\n");
				printf("\n1. Entry/Allocate\n2. Exit/Deallocate\n3. Display\n4. Coalescing of Holes\n5. Back to algorithm\n\n");
				printf("Enter choice: ");
				scanf("%d", &select);
				if (select == 1)
					worstfit(num_parts, blocks);
				else if (select == 2)
					deallocate(num_parts, blocks);
				else if (select == 3)
					display(num_parts, blocks);
				else if (select == 4)
					coalesce(num_parts, blocks);
			} while (select != 5);
		}
	} while (choice != 4);
	return 0;
}
