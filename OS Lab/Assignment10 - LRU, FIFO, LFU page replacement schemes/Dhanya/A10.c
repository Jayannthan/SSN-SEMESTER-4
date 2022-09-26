#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#define ROW 10
#define COL 20
void putTable(int table[ROW][COL], int n_frames, int n_updates)
{
	printf("\n ");
	for (int i = 0; i < n_updates; i++)
	{
		printf("+----");
	}
	printf("+\n ");
	for (int i = 0; i < n_frames; i++)
	{
		for (int j = 0; j < n_updates; j++)
		{
			if (table[i][j] == -1)
			{
				printf("| -  ");
			}
			else
			{
				printf("| %-2d ", table[i][j]);
			}
		}
		printf("|\n ");
	}
	for (int i = 0; i < n_updates; i++)
		printf("+----");
	printf("+\n ");
}
void insertTable(List tmp, int table[ROW][COL], int n_frames, int faults)
{
	for (int i = 0; i < n_frames; i++)
	{
		if (tmp)
		{
			table[i][faults] = tmp->d;
			tmp = tmp->next;
		}
		else
		{
			table[i][faults] = -1;
		}
	}
}
void FIFO(int seq[], int len, int n_frames)
{
	int size = 0;
	int faults = 0;
	int table[ROW][COL];
	List alloc = createEmptyList();
	Node *oldest;
	printf("\n");
	printf("   Frame ->        In Memory      -> Faults \n\n");
	for (int i = 0; i < len; i++)
	{
		printf("     %-2d  ->", seq[i]);
		Node *isFound = search(alloc, seq[i]);
		Node *tmp;
		if (!isFound)
		{
			if (size < n_frames)
			{
				insertLast(alloc, seq[i]);
				size++;
				if (size == 1)
				{
					oldest = alloc->next;
				}
			}
			else
			{
				oldest->d = seq[i];
				if (oldest->next)
				{
					oldest = oldest->next;
				}
				else
				{
					oldest = alloc->next;
				}
			}
			insertTable(alloc->next, table, n_frames, faults);
			faults++;
		}
		display(alloc);
		for (int i = length(alloc) * 3; i <= 22; i++)
			printf(" ");
		printf("->    %-2d   \n", faults);
	}
	putTable(table, n_frames, faults);
}
void optimal(int *seq, int len, int n_frames)
{
	int size = 0;
	int faults = 0;
	int distance;
	int flag;
	int table[ROW][COL];
	List alloc = createEmptyList();
	Node *farthest = NULL, *tmp;
	printf("\n");
	printf("   Frame ->        In Memory      -> Faults \n\n");
	int val = 0;
	int i = 0;
	for (int i = 0; i < len; i++)
	{
		printf("     %-2d  ->", seq[i]);
		Node *isFound = search(alloc, seq[i]);
		if (!isFound)
		{
			if (size < n_frames)
			{
				insertLast(alloc, seq[i]);
				size++;
			}
			else
			{
				tmp = alloc->next;
				distance = 0;
				while (tmp)
				{
					flag = 0;
					for (int j = i + 1; j < len; j++)
						if (seq[j] == tmp->d)
						{
							flag = 1;
							if (j - i > distance)
							{
								distance = (j - i);
								farthest = tmp;
							}
							break;
						}
					if (!flag)
					{
						farthest = tmp;
						break;
					}
					tmp = tmp->next;
				}
				farthest->d = seq[i];
			}
			insertTable(alloc->next, table, n_frames, faults);
			faults++;
		}
		display(alloc);
		for (int i = length(alloc) * 3; i <= 22; i++)
			printf(" ");
		printf("->   %-2d   \n", faults);
	}
	putTable(table, n_frames, faults);
}
void LRU(int *seq, int len, int n_frames)
{
	int size = 0;
	int faults = 0;
	int distance;
	int table[ROW][COL];
	List alloc = createEmptyList();
	Node *least_recent = NULL, *tmp;
	printf("\n");
	printf("   Frame ->        In Memory      -> Faults \n\n");
	int val = 0;
	int i = 0;
	for (int i = 0; i < len; i++)
	{
		printf("     %-2d  ->", seq[i]);
		Node *isFound = search(alloc, seq[i]);
		if (!isFound)
		{
			if (size < n_frames)
			{
				insertLast(alloc, seq[i]);
				size++;
			}
			else
			{
				tmp = alloc->next;
				distance = 0;
				while (tmp)
				{
					for (int j = i - 1; j >= 0; j--)
						if (seq[j] == tmp->d)
						{
							if (i - j > distance)
							{
								distance = (i - j);
								least_recent = tmp;
							}
							break;
						}
					tmp = tmp->next;
				}
				least_recent->d = seq[i];
			}
			insertTable(alloc->next, table, n_frames, faults);
			faults++;
		}
		display(alloc);
		for (int i = length(alloc) * 3; i <= 22; i++)
			printf(" ");
		printf("->   %-2d   \n", faults);
	}
	putTable(table, n_frames, faults);
}
void LFU(int *seq, int len, int n_frames)
{
	int size = 0;
	int faults = 0;
	int frequency;
	int table[ROW][COL];
	List alloc = createEmptyList();
	Node *least_frequent = NULL, *tmp;
	printf("\n");
	printf("   Frame ->        In Memory      -> Faults \n\n");
	int val = 0;
	int i = 0;
	for (int i = 0; i < len; i++)
	{
		printf("     %-2d  ->", seq[i]);
		Node *isFound = search(alloc, seq[i]);
		if (!isFound)
		{
			if (size < n_frames)
			{
				insertLast(alloc, seq[i]);
				size++;
			}
			else
			{
				tmp = alloc->next;
				frequency = 99;
				while (tmp)
				{
					if (tmp->freq < frequency)
					{
						frequency = tmp->freq;
						least_frequent = tmp;
					}
					tmp = tmp->next;
				}
				least_frequent->d = seq[i];
				least_frequent->freq = 1;
			}
			insertTable(alloc->next, table, n_frames, faults);
			faults++;
		}
		else
			isFound->next->freq++;
		display(alloc);
		for (int i = length(alloc) * 3; i <= 22; i++)
			printf(" ");
		printf("->   %-2d   \n", faults);
	}
	putTable(table, n_frames, faults);
}
int main()
{
	int n_free_frames = -1;
	int n_reqd_frames = -1;
	int sequence[20];
	int index = 0;
	int choice = -1;
	printf("\t\t-------------------------\n\n");
	printf("\t\tPAGE REPLACEMENT TECHNIQUES\n\n");
	printf("\t\t-------------------------\n\n");
	printf("1. Read Input\n");
	printf("2. FIFO\n");
	printf("3. Optimal\n");
	printf("4. LRU\n");
	printf("5. LFU\n");
	printf("6. Exit\n\n");
	while (1)
	{
		printf(" Enter your option: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf(" Enter the number of free frames: ");
			scanf("%d", &n_free_frames);
			printf(" Enter the number of frames required by the process: ");
			scanf("%d", &n_reqd_frames);
			getchar();
			printf(" Enter the reference string: ");
			char space;
			do
			{
				scanf("%d%c", &sequence[index++], &space);
			} while (space == ' ' && space != '\n');
			break;
		case 2:
			printf("\n\t\tFIFO\n");
			FIFO(sequence, index, n_reqd_frames);
			break;
		case 3:
			printf("\n\t\t\tOPTIMAL\n");
			optimal(sequence, index, n_reqd_frames);
			break;
		case 4:
			printf("\n\t\tLRU\n");
			LRU(sequence, index, n_reqd_frames);
			break;
		case 5:
			printf("\n\t\tLFU\n");
			LFU(sequence, index, n_reqd_frames);
			break;
		case 6:
			exit(0);
		default:
			printf(" Invalid Input!\n");
		}
		printf("\n");
	}
	return 0;
}
