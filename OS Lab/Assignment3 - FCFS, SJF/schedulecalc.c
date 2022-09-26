/*Algorithm: 1. Read the following a. Number of processes b. Process IDs c. Arrival time for each process d. Burst Time for each process 2. Design a menu with FCFSand SJFoptions 3. Upon selection of menu option apply the corresponding algorithm. 4. Compute the Turnaround Time, Average waiting Time for each of the algorithm. 5. Tabularize the results. 6. Display the Gantt Chart.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

int main()
{
    char ch = 'y';
    while (ch == 'y' || ch == 'Y')
    {
        int choice;
        printf("\nMenu\n\t1.FCFS\n\t2.SJF\nEnter Choice:");
        scanf(" %d", &choice);
        switch (choice)
        {
        case 1:
        {
            printf("\nFCFS\n");
            int no_of_process;
            printf("\nNumber of Processes :");
            scanf(" %d", &no_of_process);
            int arrival[no_of_process], burst[no_of_process], turnaround[no_of_process], waiting[no_of_process], totalwaitingtime = 0, totalturnaround = 0;
            char pid[no_of_process][3];
            for (int i = 0; i < no_of_process; i++)
            {
                printf("\n\nProcess %d\n", i + 1);
                printf("Process ID: ");
                scanf(" %s", pid[i]);
                printf("Arrival Time :");
                scanf(" %d", &arrival[i]);
                printf("Burst Time :");
                scanf(" %d", &burst[i]);
                if (i == 0)
                {
                    waiting[i] = 0;
                }
                else
                {
                    waiting[i] = burst[i - 1] + waiting[i - 1];
                }
                turnaround[i] = burst[i] + waiting[i];
                totalwaitingtime += waiting[i];
                totalturnaround += turnaround[i];
            }
            printf("\nP_ID  Arrival_Time  Burst_Time  Turnaround_Time  Waiting Time");
            for (int i = 0; i < no_of_process; i++)
            {
                printf("\n %3s %7d %11d %11d %15d", pid[i], arrival[i], burst[i], turnaround[i], waiting[i]);
            }

            float avgwaiting = (float)(totalwaitingtime / no_of_process);
            float avgturnaround = (float)(totalturnaround / no_of_process);
            printf("\n\t\tAVERAGE  AverageWaitingTime=%.2f\tAverageTurnaroundTime=%.2f\n", avgwaiting, avgturnaround);
            break;
        }

        case 2:
        {
            printf("\nFCFS\n");
            int no_of_process;
            printf("\nNumber of Processes :");
            scanf(" %d", &no_of_process);
            int arrival[no_of_process], burst[no_of_process], turnaround[no_of_process], waiting[no_of_process], totalwaitingtime = 0, totalturnaround = 0;
            char pid[no_of_process][5];
            for (int i = 0; i < no_of_process; i++)
            {
                printf("\n\nProcess %d\n", i + 1);
                printf("Process ID: ");
                scanf(" %s", pid[i]);
                printf("Arrival Time :");
                scanf(" %d", &arrival[i]);
                printf("Burst Time :");
                scanf(" %d", &burst[i]);
            }
            int pos;
            int tempburst;
            char temppid[3];
            for (int i = 0; i < no_of_process; i++)
            {
                pos = i;
                for (int j = i + 1; j < no_of_process; j++)
                {
                    if (burst[j] < burst[pos] && arrival[j] <= arrival[pos])
                        pos = j;
                }

                tempburst = burst[i];
                burst[i] = burst[pos];
                burst[pos] = tempburst;
                strcpy(temppid, pid[i]);
                strcpy(pid[i], pid[pos]);
                strcpy(pid[pos], temppid);
            }
            waiting[0] = 0;
            for (int i = 1; i < no_of_process; i++)
            {
                waiting[i] = 0;
                for (int j = 0; j < i; j++)
                {
                    waiting[i] += burst[j];
                }
                totalwaitingtime += waiting[i];
                turnaround[i] = burst[i] + waiting[i];
                totalturnaround += turnaround[i];
            }
            printf("\nP_ID  Arrival_Time  Burst_Time  Turnaround_Time  Waiting Time");
            for (int i = 0; i < no_of_process; i++)
            {
                printf("\n %3s %7d %11d %11d %15d", pid[i], arrival[i], burst[i], turnaround[i], waiting[i]);
            }

            float avgwaiting = (float)(totalwaitingtime / no_of_process);
            float avgturnaround = (float)(totalturnaround / no_of_process);
            printf("\n\t\tAVERAGE  AverageWaitingTime=%.2f\tAverageTurnaroundTime=%.2f\n", avgwaiting, avgturnaround);
        }
        break;
        case 3:
            printf("Exiting...");
            return 0;
        }
        printf("\nWant to Continue ( Y/N):");
        scanf(" %c", &ch);
    }
    return 0;
}