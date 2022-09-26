#include <stdio.h>
#define MAX 100
typedef struct bankersdata
{
	int no_resources, no_process;
	int alloc[MAX][MAX];
	int avlbl[MAX];
	int req[MAX][MAX];
	int f[MAX];
	int array[MAX];
} bankersdata;

bankersdata bk;

void getdata()
{
	printf("Enter no. of process:");
	scanf(" %d", &bk.no_process);
	printf("\nEnter no. of resources:");
	scanf(" %d", &bk.no_resources);
	printf("Enter no . of allocated resources to process:\n");
	for (int i = 0; i < bk.no_process; i++)
	{
		printf("\tP%d:", i + 1);
		for (int j = 0; j < bk.no_resources; j++)
		{
			scanf(" %d", &bk.alloc[i][j]);
		}
	}
	printf("Enter no . of request vector of resources to process:\n");
	for (int i = 0; i < bk.no_process; i++)
	{
		printf("\tP%d:", i + 1);
		for (int j = 0; j < bk.no_resources; j++)
		{
			scanf(" %d", &bk.req[i][j]);
		}
	}
	printf("Enter no . of available resources after allocation:");
	for (int j = 0; j < bk.no_resources; j++)
	{
		scanf(" %d", &bk.avlbl[j]);
	}
	for (int j = 0; j < bk.no_process; j++)
	{
		bk.f[j] = 0;
	}
}

void bankers()
{
	int flag = 1;
	int ind;
	int index = -1;
	while (flag)
	{
		flag = 0;

		for (int i = 0; i < bk.no_process; i++)
		{
			if (bk.f[i] != 1)
			{
				ind = 1;
				for (int j = 0; j < bk.no_resources; j++)
				{
					if (bk.avlbl[j] < bk.req[i][j])
					{
						ind = 0;
					}
				}
				if (ind == 1)
				{
					printf("%d\t", i);
					flag = 1;
					bk.f[i] = 1;
					bk.array[++index] = i;
					for (int j = 0; j < bk.no_resources; j++)
					{
						bk.avlbl[j] += bk.alloc[i][j];
					}
				}
			}
		}
	}
	int done = 0;
	if (index == bk.no_process - 1)
	{
		done = 1;
	}
	if (done == 0)
	{
		printf("\nDeadlock Present...");
	}
	else
	{
		printf("\n No Deadlock Present...");
		for (int i = 0; i <= index; i++)
		{
			printf(" %d -->", bk.array[i] + 1);
		}
	}
}

int main(int argc, char const *argv[])
{
	getdata();
	bankers();
	return 0;
}
