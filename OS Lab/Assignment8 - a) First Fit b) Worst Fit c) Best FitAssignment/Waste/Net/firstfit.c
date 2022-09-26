
// 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45
#include <stdio.h>

void main()
{
	int bsize[10], psize[10], bno, pno, flags[10], allocation[10], i, j;

	for (i = 0; i < 10; i++)
	{
		flags[i] = 0;
		allocation[i] = -1;
	}
	printf("Enter no. of blocks: ");
	scanf("%d", &bno);
	printf("\nEnter size of each block: ");
	for (i = 0; i < bno; i++)
	{
		scanf("%d", &bsize[i]);
	}

	printf("\nEnter no. of processes: ");
	scanf("%d", &pno);
	printf("\nEnter size of each process: ");
	for (i = 0; i < pno; i++)
	{
		scanf("%d", &psize[i]);
	}
	for (i = 0; i < pno; i++) // allocation as per first fit
	{
		for (j = 0; j < bno; j++)
		{
			if (flags[j] == 0 && bsize[j] >= psize[i])
			{
				allocation[j] = i;
				flags[j] = 1;
				break;
			}
		}
	}
	// display allocation details
	printf("\nBlock no.\tsize\t\tprocess no.\t\tsize");
	for (i = 0; i < bno; i++)
	{
		printf("\n%d\t\t%d\t\t", i + 1, bsize[i]);
		if (flags[i] == 1)
		{
			printf("%d\t\t\t%d", allocation[i] + 1, psize[allocation[i]]);
		}
		else
		{
			printf("Not allocated");
		}
	}
}