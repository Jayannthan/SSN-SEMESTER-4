#include <stdio.h>
#define MAX 100
typedef struct process
{
	char pid[3];
	int at;
	int bt;
	int wt;
	int tat;
	int ct;
} process;

process pr[MAX];
int no_Process;
process temp;

void printdata()
{
	printf("\n");
	for (int i = 0; i < no_Process; i++)
	{
		for (int j = 0; j < pr[i].bt; j++)
		{
			printf("--");
		}
		printf(" ");
	}

	printf("\n|");
	for (int i = 0; i < no_Process; i++)
	{
		for (int j = 0; j < pr[i].bt - 1; j++)
		{
			printf(" ");
		}
		printf("%s", pr[i].pid);
		for (int j = 0; j < pr[i].bt - 1; j++)
		{
			printf(" ");
		}
		printf("|");
	}

	printf("\n");
	for (int i = 0; i < no_Process; i++)
	{
		for (int j = 0; j < pr[i].bt; j++)
		{
			printf("--");
		}
		printf(" ");
	}
	printf("\n0");
	for (int i = 0; i < no_Process; i++)
	{
		for (int j = 0; j < pr[i].bt; j++)
		{
			printf("  ");
		}
		printf("%d", pr[i].ct);
	}
	printf("\n");
}
int main(int argc, char const *argv[])
{
	printf("\nEnter no of process:");
	scanf(" %d", &no_Process);
	printf("\nEnter process info:\n");
	for (int i = 0; i < no_Process; i++)
	{
		printf("Process %d:", i + 1);
		printf("\tPid:");
		scanf(" %s", pr[i].pid);
		printf("\tArrival Time:");
		scanf(" %d", &pr[i].at);
		printf("\tBurst Time:");
		scanf(" %d", &pr[i].bt);
	}

	for (int i = 0; i < no_Process; i++)
	{
		int minat = pr[i].at;
		int minindex = i;
		for (int j = i + 1; j < no_Process; j++)
		{
			if (minat > pr[j].at)
			{
				minat = pr[j].at;
				minindex = j;
			}
		}
		if (i != minindex)
		{
			temp = pr[i];
			pr[i] = pr[minindex];
			pr[minindex] = temp;
		}
	}
	pr[0].ct = pr[0].at + pr[0].bt;
	pr[0].tat = pr[0].ct - pr[0].at;
	pr[0].wt = pr[0].tat - pr[0].bt;
	for (int i = 1; i < no_Process; i++)
	{
		if (pr[i - 1].ct >= pr[i].at)
		{
			pr[i].ct = pr[i - 1].ct + pr[i].bt;
		}
		else
		{
			pr[i].ct = pr[i].at + pr[0].bt;
		}
		pr[i].tat = pr[i].ct - pr[i].at;
		pr[i].wt = pr[i].tat - pr[i].bt;
	}
	printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
	for (int i = 0; i < no_Process; i++)
	{
		printf("%s \t%d \t%d \t%d \t%d \t%d \n", pr[i].pid, pr[i].at, pr[i].bt, pr[i].ct, pr[i].tat, pr[i].wt);
	}

	printdata();

	return 0;
}
