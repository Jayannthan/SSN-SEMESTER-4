#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef struct schedule *SCH;
typedef struct schedule
{
    char id[3];
    int waiting;
    int arrival;
    int turn_around;
    int burst;
    int completion;
    int priority;
} sch;

void gantt_chart(SCH P[], int n)
{
    int i, j;

    printf(" ");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < P[i]->burst; j++)
            printf("--");

        printf("- ");
    }
    printf("\n| ");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < P[i]->burst - 1; j++)
            printf(" ");
        printf("P%s", P[i]->id);
        for (j = 0; j < P[i]->burst - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < P[i]->burst; j++)
            printf("--");
        printf("- ");
    }
    printf("\n");

    printf("0");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < P[i]->burst; j++)
            printf("  ");
        printf(" ");
        if (P[i]->completion > 9)
            printf("\b");
        printf("%d", P[i]->completion);
    }
    printf("\n");
}

void priority_scheduling(SCH P[], int n)
{
    int rem_time[n];
    for (int i = 0; i < n; i++)
    {
        rem_time[i] = P[i]->burst;
    }
    SCH arr[MAX];
    double avg_wait = 0, trn_around = 0;
    int ptr = 0, completed = 0, cur_time = 0;
    while (completed < n)
    {
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (P[i]->arrival <= cur_time && rem_time[i] > 0 && (index == -1 || P[i]->priority < P[index]->priority))
            {
                index = i;
            }
        }
        cur_time++;
        if (ptr != 0 && strcmp(arr[ptr - 1]->id, P[index]->id) == 0)
            ptr--;
        else
        {
            arr[ptr] = (SCH)malloc(sizeof(sch));
            strcpy(arr[ptr]->id, P[index]->id);
            arr[ptr]->burst = 0;
        }
        arr[ptr]->burst++;
        arr[ptr]->completion = cur_time;
        ptr++;
        rem_time[index]--;
        if (rem_time[index] == 0)
        {
            completed++;
            P[index]->completion = cur_time;
            P[index]->waiting = P[index]->completion - P[index]->arrival - P[index]->burst;
            P[index]->turn_around = P[index]->completion - P[index]->arrival;
            avg_wait += P[index]->waiting;
            trn_around += P[index]->turn_around;
        }
    }

    printf("PID   Arrival_Time   Burst_Time   Waiting_Time   Completion_Time    Turnaround_Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s         %d              %d            %d              %d                  %d\n", P[i]->id, P[i]->arrival, P[i]->burst, P[i]->waiting, P[i]->completion, P[i]->turn_around);
    }
    printf("\n");
    printf("\t\tAverage Waiting time :  %.2f", avg_wait / n);
    printf("\t Turn_around time : %.2f\n", trn_around / n);
    gantt_chart(arr, ptr);
}

void round_robin(SCH P[], int n, int quantum)
{
    int rem_time[n];
    for (int i = 0; i < n; i++)
    {
        rem_time[i] = P[i]->burst;
    }
    SCH arr[MAX];
    double avg_wait = 0, trn_around = 0;
    int ptr = 0, completed = 0, cur_time = 0;
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (rem_time[i] > 0)
            {
                arr[ptr] = (SCH)malloc(sizeof(sch));
                strcpy(arr[ptr]->id, P[i]->id);
                if (rem_time[i] > quantum)
                {
                    arr[ptr]->burst = quantum;
                    rem_time[i] = rem_time[i] - quantum;
                    cur_time = cur_time + quantum;
                }
                else
                {
                    arr[ptr]->burst = rem_time[i];
                    cur_time += rem_time[i];
                    rem_time[i] = 0;
                    P[i]->completion = cur_time;
                    P[i]->waiting = P[i]->completion - P[i]->arrival - P[i]->burst;
                    P[i]->turn_around = P[i]->completion - P[i]->arrival;
                    completed++;
                    avg_wait += P[i]->waiting;
                    trn_around += P[i]->turn_around;
                }
                arr[ptr]->completion = cur_time;
                ptr++;
            }
        }
    }
    printf("Process   Burst_Time   Waiting_Time   Completion_Time    Turnaround_Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s	  %d            %d              %d                  %d\n", P[i]->id, P[i]->burst, P[i]->waiting, P[i]->completion, P[i]->turn_around);
    }
    printf("\n");
    printf("Average Waiting time :  %.2f\n", avg_wait / n);
    printf("Average Turn_around time : %.2f\n", trn_around / n);
    gantt_chart(arr, ptr);
}

int main()
{
    int n;
    char ch;
    do
    {
        printf("What to perform :\n1.Priority\n2.Round Robin\n");
        int choice;
        scanf("%d", &choice);
        printf("Enter the number of Processes: ");
        scanf("%d", &n);
        if (choice == 1)
        {

            SCH P[n];
            for (int i = 0; i < n; i++)
            {
                printf("Process number %d : \n", i + 1);
                P[i] = malloc(sizeof(sch));
                printf("Process ID: ");
                scanf("%s", P[i]->id);
                printf("Arrival Time :");
                scanf("%d", &P[i]->arrival);
                printf("Burst Time :");
                scanf("%d", &P[i]->burst);
                printf("Priority :");
                scanf("%d", &P[i]->priority);
            }
            priority_scheduling(P, n);
        }

        else if (choice == 2)
        {

            SCH P[n];
            for (int i = 0; i < n; i++)
            {
                printf("Process number %d : \n", i + 1);
                P[i] = malloc(sizeof(sch));
                printf("Enter the process id : ");
                scanf("%s", P[i]->id);
                printf("Enter the Burst time : ");
                scanf("%d", &P[i]->burst);
            }
            printf("Enter the quantum : ");
            int quantum;
            scanf("%d", &quantum);
            round_robin(P, n, quantum);
        }
        printf("Do you want to exit from the program(Y/N) : ");
        scanf("%s", &ch);
    } while (ch == 'N');
}
