/*Algorithm: 1. Read the following a. Number of processes b. Process IDs c. Arrival time for each process d. Burst Time for each process 2. Design a menu with FCFSand SJFoptions 3. Upon selection of menu option apply the corresponding algorithm. 4. Compute the Turnaround Time, Average waiting Time for each of the algorithm. 5. Tabularize the results. 6. Display the Gantt Chart.*/

#include<stdio.h>
#include<stdlib.h>
#define MAX_TIME 100
typedef struct process{
	char process_id[5];
	int burst_time, arrival_time, active, remaining_time;
}process;

int comparator(const void *p, const void *q) 
{
    int b1 = ((struct process *)p)->burst_time;
    int b2 = ((struct process *)q)->burst_time; 
    int a1 = ((struct process *)p)->arrival_time;
    int a2 = ((struct process *)q)->arrival_time; 
    if (b1 < b2) return -1;
	return 1;
}

int comparator1(const void *p, const void *q) 
{
    int a1 = ((struct process *)p)->arrival_time;
    int a2 = ((struct process *)q)->arrival_time; 
    if (a1 < a2) return -1;
	return 1;
}
int main() {
	int ch;
	char cont;
	do {
		printf("\t\tCPU SCHEDULING ALGORITHMS\n1. FCFS\n2. SJF\n3. EXIT\nEnter your option: ");
		scanf("%d", &ch);
		int number_of_processes;
		process p[100];
		int turnaround_time, waiting_time;
		int curr_time = 0;
		double avg_wt, avg_tt;
		int sum_wt = 0, sum_tt = 0;
		switch(ch) {
			case 1: printf("FCFS CPU SCHEDULER\n");
					printf("Number of Processes: ");
					scanf("%d", &number_of_processes);
					for (int i = 1; i <= number_of_processes; i ++) {
						printf("Process ID: ");						
						scanf("%s", p[i].process_id);				
						printf("arrival Time: ");						
						scanf("%d", &p[i].arrival_time);				
						printf("Burst Time: ");						
						scanf("%d", &p[i].burst_time);				
					}				
					for (int i = 0; i < 84; i ++) printf("-");
					printf("\n");
					qsort((void*)(p + 1), number_of_processes, sizeof(p[1]), comparator1);					
					printf("Process ID\tArrival Time\tBurst Time\tTurnaround Time \tWaiting Time\n");
					for (int i = 0; i < 84; i ++) printf("-");
					printf("\n");
					for (int i = 1; i <= number_of_processes; i ++) {
						waiting_time = curr_time - p[i].arrival_time;
						if (waiting_time < 0) waiting_time = 0;						
						turnaround_time = waiting_time + p[i].burst_time;
						if (curr_time < p[i].arrival_time) curr_time = p[i].arrival_time + p[i].burst_time;
						else curr_time = curr_time + p[i].burst_time;	
						printf("%s\t\t%d\t\t%d\t\t%d\t\t\t%d\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, turnaround_time, waiting_time);			
						sum_wt += waiting_time;
						sum_tt += turnaround_time;	
					}
					for (int i = 0; i < 84; i ++) printf("-");
					printf("\n");
					avg_wt = 1.0l * sum_wt / number_of_processes;
					avg_tt = 1.0l * sum_tt / number_of_processes;
					printf("\t\t\t\tAverage:\t%lf\t\t%lf\n", avg_tt, avg_wt);
					printf("\t\t\t\t");
					for (int i = 0; i < 52; i ++) printf("-");
					printf("\n");					
					break;
			case 2: printf("SJF CPU SCHEDULER\n");
					int ch1;
					printf("MENU\n1.Pre-emptive\n2.Non Pre-emptive\nEnter choice: ");
					scanf("%d",& ch1); 
					if (ch1 == 1) {
						printf("Number of Processes: ");
						scanf("%d", &number_of_processes);
						for (int i = 1; i <= number_of_processes; i ++) {
							printf("Process ID: ");						
							scanf("%s", p[i].process_id);					
							printf("Burst Time: ");						
							scanf("%d", &p[i].burst_time);
							p[i].arrival_time = 0;				
						}				
						qsort((void*)(p + 1), number_of_processes, sizeof(p[1]), comparator);					
						for (int i = 0; i < 84; i ++) printf("-");
						printf("\n");
						printf("Process ID\tArrival Time\tBurst Time\tTurnaround Time \tWaiting Time\n");
						for (int i = 0; i < 84; i ++) printf("-");
						printf("\n");
						for (int i = 1; i <= number_of_processes; i ++) {
							waiting_time = curr_time - p[i].arrival_time;
							if (waiting_time < 0) waiting_time = 0;						
							turnaround_time = waiting_time + p[i].burst_time;
							if (curr_time < p[i].arrival_time) curr_time = p[i].arrival_time + p[i].burst_time;
							else curr_time = curr_time + p[i].burst_time;	
							printf("%s\t\t%d\t\t%d\t\t%d\t\t\t%d\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, turnaround_time, waiting_time);					
							sum_wt += waiting_time;
							sum_tt += turnaround_time;	
						}
						for (int i = 0; i < 84; i ++) printf("-");
						printf("\n");
						avg_wt = 1.0l * sum_wt / number_of_processes;
						avg_tt = 1.0l * sum_tt / number_of_processes;
						printf("\t\t\t\tAverage:\t%lf\t\t%lf\n", avg_tt, avg_wt);
						printf("\t\t\t\t");
						for (int i = 0; i < 52; i ++) printf("-");
						printf("\n");
					}
					else if (ch1 == 2){
						printf("Number of Processes: ");
						scanf("%d", &number_of_processes);
						for (int i = 1; i <= number_of_processes; i ++) {
							printf("Process ID: ");						
							scanf("%s", p[i].process_id);				
							printf("arrival Time: ");						
							scanf("%d", &p[i].arrival_time);				
							printf("Burst Time: ");						
							scanf("%d", &p[i].burst_time);				
							p[i].active = 1;
							p[i].remaining_time = p[i].burst_time;
						}				
						for (int i = 0; i < 84; i ++) printf("-");
						printf("\n");
						printf("Process ID\tArrival Time\tBurst Time\tTurnaround Time \tWaiting Time\n");
						for (int i = 0; i < 84; i ++) printf("-");
						printf("\n");
						for (int t = 0; t <= MAX_TIME; t ++) { 
							int best_remaining_time_pos = -1;
							for (int i = 1; i <= number_of_processes; i ++) {
								if (p[i].active && p[i].arrival_time <= t && (best_remaining_time_pos == -1 || p[i].remaining_time < p[best_remaining_time_pos].remaining_time )) {
									best_remaining_time_pos = i;			
								}
							}
							if (p[best_remaining_time_pos].active && p[best_remaining_time_pos].arrival_time <= t) {
								p[best_remaining_time_pos].remaining_time -= 1;
								if (!p[best_remaining_time_pos].remaining_time) {
									p[best_remaining_time_pos].active = 0;
									turnaround_time = t + 1 - p[best_remaining_time_pos].arrival_time;
									waiting_time = turnaround_time - p[best_remaining_time_pos].burst_time;
									printf("%s\t\t%d\t\t%d\t\t%d\t\t\t%d\n", p[best_remaining_time_pos].process_id, p[best_remaining_time_pos].arrival_time, p[best_remaining_time_pos].burst_time, turnaround_time, waiting_time);				
									sum_wt += waiting_time;
									sum_tt += turnaround_time;
								}
							}
						}
						for (int i = 0; i < 84; i ++) printf("-");
						printf("\n");
						avg_wt = 1.0l * sum_wt / number_of_processes;
						avg_tt = 1.0l * sum_tt / number_of_processes;
						printf("\t\t\t\tAverage:\t%lf\t\t%lf\n", avg_tt, avg_wt);
						printf("\t\t\t\t");
						for (int i = 0; i < 52; i ++) printf("-");
						printf("\n");
										
					}
					else {
						printf("Wrong choice\n");
					}
					break;				
			case 3: exit(0);
			default: printf("Invalid choice\n");
		}	
		printf("Want to Continue (Y/N): ");
		scanf(" %c", &cont);
		printf("\n");
	}while(cont == 'y' || cont == 'Y');
}