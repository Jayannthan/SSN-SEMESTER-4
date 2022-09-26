#include <stdio.h>
#define MAX 100
typedef struct process
{
	char pid[3];
	int at;
	int bt;
	int temp_bt;
	int wt;
	int tat;
	int ct;
} process;

process pr[MAX], temp_process[MAX];
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
		pr[i].temp_bt = pr[i].bt;
	}
	pr[no_Process].at = 9999;
	int count = 0;
	for (int t = 0; count != no_Process; t++)
	{
		int minbt = pr[no_Process];
		int minindex = no_Process;
		for (int i = 0; i < no_Process; i++)
		{
			if (minbt > pr[i].bt && pr[i].at <= t && pr[i].bt > 0)
			{
				minindex = i;
				minbt = pr[i].bt;
			}
			pr[minindex].bt--;
			if (pr[minindex].bt == 0)
			{
				count++;
				pr[minindex].ct = t;
				pr[minindex].tat = t - pr[minindex].at;
				pr[minindex].wt = t - pr[minindex].at - pr[minbt].temp_bt;
			}
		}
	}

	printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n");
	for (int i = 0; i < no_Process; i++)
	{
		printf("%s \t%d \t%d \t%d \t%d \t%d \n", pr[i].pid, pr[i].at, pr[i].bt, pr[i].ct, pr[i].tat, pr[i].wt);
	}
	printdata();

	return 0;
}
