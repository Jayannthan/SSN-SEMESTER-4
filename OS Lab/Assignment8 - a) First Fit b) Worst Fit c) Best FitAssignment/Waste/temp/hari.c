#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 15
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// A function to implement bubble sort
void bubbleSort_wf(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] < arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}
void bubbleSort_bf(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}
typedef struct process
{
	char pid[50];
	int start;
	int end;
	int size;
	int alloc;
}
process;

typedef struct partition
{
	int np;
	process P[MAX];
	int maxsize;
	int low;
	int high;
	int free;
}
partition;

int main(int argc, char *argv[])
{
	printf("Memory Allocation Techniques\n\t1.First Fit\n\t2.Worst Fit\n\t3.Best Fit\n\n");
	int choice, n, p, temp, chmat, reqsize;
	printf("Enter choice: ");
	scanf("%d", &chmat);
	char rerun = 'y';
	//Reading data
	char name[50];
	printf("Enter number of partitions: ");
	scanf("%d", &n);
	partition blocks[n];
	partition copy[n];
	for (int i = 0; i < n; i++)
	{
		printf("Block %d\n", i);
		printf("Enter starting address: ");
		scanf("%d", &temp);
		blocks[i].low = temp;
		printf("Enter ending address: ");
		scanf("%d", &temp);
		blocks[i].high = temp;
		blocks[i].maxsize = blocks[i].high - blocks[i].low;
		blocks[i].free = blocks[i].high - blocks[i].low;
		blocks[i].np = -1;
	}

	if (chmat == 1)
	{
		//Menu
		do { 	printf("Menu\n\n1. Entry/Allocate\n\n2.Exit/Deallocate\n\n3.Display\n\n4.Compacting\n\n5.Exit\n\nEnter your choice:\t");
			scanf("%d", &choice);
			if (choice == 1)
			{
				int flag = 0;
				printf("Enter PID: ");
				scanf("%s", name);
				printf("Enter size of process: ");
				scanf("%d", &reqsize);
				for (int i = 0; i < n; i++)
				{
					if (blocks[i].free != 0 && blocks[i].free >= reqsize)
					{
						blocks[i].np += 1;
						strcpy(blocks[i].P[blocks[i].np].pid, name);
						blocks[i].P[blocks[i].np].start = blocks[i].low + blocks[i].maxsize - blocks[i].free;
						blocks[i].P[blocks[i].np].size = reqsize;
						blocks[i].P[blocks[i].np].end = blocks[i].P[blocks[i].np].start + blocks[i].P[blocks[i].np].size;
						blocks[i].free -= reqsize;
						flag = 1;
						break;
					}
				}
				if (flag == 1)
					printf("Memory has been allocated successfully\n");
				else
					printf("Memory unable to be allocated to the process\n");
			}
			else if (choice == 2)
			{
				int flag = 0;
				printf("Enter PID: ");
				scanf("%s", name);
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
					{
						if (!strcmp(name, blocks[i].P[j].pid))
						{
						 				//printf("in loop");
							blocks[i].free += blocks[i].P[j].size;
							blocks[i].P[j].start = -1;
							blocks[i].P[j].size = -1;
							blocks[i].P[j].end = -1;
							blocks[i].np -= 1;
							flag = 1;
						}
					}
				}
				if (flag == 1)
					printf("Memory has been deallocated successfully\n");
				else
					printf("Memory unable to be deallocated from the process\n");
			}
			else if (choice == 3)
			{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
						printf("-------------");
					if (blocks[i].free != 0)
						printf("------------");	//after allocation
				}
				printf("\n");
				printf("|");
				for (int i = 0; i < n; i++)
				{
				 		//printf("%d %d",i,blocks[i].np);
					for (int j = 0; j <= blocks[i].np; j++)
						//printf("%s pid",blocks[i].P[i].pid);
						printf("     %s     |", blocks[i].P[j].pid);
					if (blocks[i].free != 0)
						printf("     H     |");
				}
				printf("\n");
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
						printf("-------------");
					if (blocks[i].free != 0)
						printf("------------");
				}

				printf("\n");
				for (int i = 0; i < n; i++)
				{ 		/*if (i == n-1)
					{
						for (int j = 0 ;j <= blocks[i].np; j++)
					  {
					  	printf("%d\t\t\t", blocks[i].P[blocks[i].np].start);
					    if (j == blocks[i].np && blocks[i].free != 0)
					      printf("%d\t\t\t", blocks[i].P[blocks[i].np].start);
					  }
					  if (blocks[i].free != 0)
					    printf("%d\t\t\t%d", blocks[i].low+blocks[i].maxsize-blocks[i].free, blocks[i].high);
					}*/
					//else
					//{ 		for (int j = 0; j <= blocks[i].np; j++)
						printf("%d\t\t\t", blocks[i].P[j].start);
					if (blocks[i].free != 0)
						printf("%d\t\t\t", blocks[i].low + blocks[i].maxsize - blocks[i].free);
					//}
					if (i == n - 1)
					{
						printf("%d", blocks[i].high);
					}
				}
				printf("\n");
			}
			else if (choice == 4)
			{
				int mv;
				int k = 0;

				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
					{

						if (blocks[i].np > -1)
						{
							mv += blocks[i].free;
							if (k == 0)
							{
								copy[0].low = blocks[0].low;
							}
							else
							{
								copy[k].low = copy[k - 1].high;
							}
							copy[k].high = copy[k].low + blocks[i].P[j].size;
							//printf("%d",copy[k].high);
							copy[k].free = 0;
							copy[k].maxsize = blocks[i].P[j].size;
							copy[k].np = 0;
							copy[k].P[0].alloc = blocks[i].P[j].size;
							strcpy(copy[k].P[0].pid, blocks[i].P[j].pid);
							copy[k].P[0].end = copy[k].high;
							copy[k].P[0].start = copy[k].low;
							copy[k].P[0].size = copy[k].maxsize;
							k++;
						}
						else if (blocks[i].np == -1)
						{
							mv += blocks[i].free;
						}

						//blocks[i+1].P[0].
					}
				}
				copy[k].low = copy[k - 1].high;
				copy[k].high = copy[k].low + mv + 1;
				//printf("%d",copy[k].high);
				copy[k].free = mv;
				copy[k].maxsize = mv;
				copy[k].np = -1;

				for (int i = 0; i < k + 1; i++)
				{
					for (int j = 0; j <= copy[i].np; j++)
						printf("-------------");
					if (copy[i].free != 0)
						printf("------------");	//after allocation
				}
				printf("\n");
				printf("|");
				for (int i = 0; i < k + 1; i++)
				{
				 		//printf("%d %d",i,blocks[i].np);
					for (int j = 0; j <= copy[i].np; j++)
						//printf("%s pid",blocks[i].P[i].pid);
						printf("     %s     |", copy[i].P[j].pid);
					if (copy[i].free != 0)
						printf("     H     |");
				}
				printf("\n");
				for (int i = 0; i < k + 1; i++)
				{
					for (int j = 0; j <= copy[i].np; j++)
						printf("-------------");
					if (copy[i].free != 0)
						printf("------------");
				}

				printf("\n");
				for (int i = 0; i < k + 1; i++)
				{

					for (int j = 0; j <= copy[i].np; j++)
						printf("%d\t\t\t", copy[i].P[j].start);
					if (copy[i].free != 0)
						printf("%d\t\t\t", copy[i].low + copy[i].maxsize - copy[i].free);
					//}
					if (i == k)
					{
						printf("%d", copy[i].high);
					}
				}
				printf("\n");
			}
			else if (choice == 5)
			{
				printf("Program terminating.\n");
				exit(0);
			}
			else
			{
				printf("Wrong Option\n");
			}
			printf("Do you want to continue?[y/n]\t");
			scanf(" %c", &rerun);
		} while (rerun == 'Y' || rerun == 'y');
	}
	else if (chmat == 2)
	{
		//Menu
		do { 	printf("Menu\n\n1. Entry/Allocate\n\n2.Exit/Deallocate\n\n3.Display\n\n4.Compacting\n\n5.Exit\n\nEnter your choice:\t");
			scanf("%d", &choice);
			if (choice == 1)
			{
				int flag = 0;
				int k = 0;
				int copy_block[n];
				printf("Enter PID: ");
				scanf("%s", name);
				printf("Enter size of process: ");
				scanf("%d", &reqsize);
				for (int i = 0; i < n; i++)
				{
					if (blocks[i].free >= reqsize)
					{
						copy_block[k++] = blocks[i].free;
					}
				}
				//for(int i=0;i < n;i++){ 	//  printf("%d",copy_block[i]);
				//}
				bubbleSort_wf(copy_block, n);
				//for(int i=0;i < n;i++){ 	//  printf("%d",copy_block[i]);
				//}
				//for(int i=0;i < n;i++){ 	//  printf("%d",blocks[i].free);
				//}
				for (int i = 0; i < n; i++)
				{
					if (blocks[i].free == copy_block[0] && reqsize <= blocks[i].free)
					{
						blocks[i].np += 1;
						strcpy(blocks[i].P[blocks[i].np].pid, name);
						printf("%s", blocks[i].P[blocks[i].np].pid);
						blocks[i].P[blocks[i].np].start = blocks[i].low + blocks[i].maxsize - blocks[i].free;
						blocks[i].P[blocks[i].np].size = reqsize;
						blocks[i].P[blocks[i].np].end = blocks[i].P[blocks[i].np].start + blocks[i].P[blocks[i].np].size;
						blocks[i].free -= reqsize;
						flag = 1;
						break;
					}
				}
				if (flag == 1)
					printf("Memory has been allocated successfully\n");
				else
					printf("Memory unable to be allocated to the process\n");
			}
			else if (choice == 2)
			{
				int flag = 0;
				printf("Enter PID: ");
				scanf("%s", name);
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
					{
						if (!strcmp(name, blocks[i].P[j].pid))
						{
						 				//printf("in loop");
							blocks[i].free += blocks[i].P[j].size;
							blocks[i].P[j].start = -1;
							blocks[i].P[j].size = -1;
							blocks[i].P[j].end = -1;
							blocks[i].np -= 1;
							flag = 1;
						}
					}
				}
				if (flag == 1)
					printf("Memory has been deallocated successfully\n");
				else
					printf("Memory unable to be deallocated from the process\n");
			}
			else if (choice == 3)
			{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
						printf("-------------");
					if (blocks[i].free != 0)
						printf("------------");	//after allocation
				}
				printf("\n");
				printf("|");
				for (int i = 0; i < n; i++)
				{
				 		//printf("%d %d",i,blocks[i].np);
					for (int j = 0; j <= blocks[i].np; j++)
						//printf("%s pid",blocks[i].P[i].pid);
						printf("     %s     |", blocks[i].P[j].pid);
					if (blocks[i].free != 0)
						printf("     H     |");
				}
				printf("\n");
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
						printf("-------------");
					if (blocks[i].free != 0)
						printf("------------");
				}

				printf("\n");
				for (int i = 0; i < n; i++)
				{ 		/*if (i == n-1)
					{
						for (int j = 0 ;j <= blocks[i].np; j++)
					  {
					  	printf("%d\t\t\t", blocks[i].P[blocks[i].np].start);
					    if (j == blocks[i].np && blocks[i].free != 0)
					      printf("%d\t\t\t", blocks[i].P[blocks[i].np].start);
					  }
					  if (blocks[i].free != 0)
					    printf("%d\t\t\t%d", blocks[i].low+blocks[i].maxsize-blocks[i].free, blocks[i].high);
					}*/
					//else
					//{ 		for (int j = 0; j <= blocks[i].np; j++)
						printf("%d\t\t\t", blocks[i].P[j].start);
					if (blocks[i].free != 0)
						printf("%d\t\t\t", blocks[i].low + blocks[i].maxsize - blocks[i].free);
					//}
					if (i == n - 1)
					{
						printf("%d", blocks[i].high);
					}
				}
				printf("\n");
			}
			else if (choice == 4)
			{
				int mv;
				int k = 0;

				int tmp = blocks[n - 1].high;

				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
					{

						if (blocks[i].np > -1)
						{
							mv += blocks[i].free;
							if (k == 0)
							{
								copy[0].low = blocks[0].low;
							}
							else
							{
								copy[k].low = copy[k - 1].high;
							}
							copy[k].high = copy[k].low + blocks[i].P[j].size;
							//printf("%d",copy[k].high);
							copy[k].free = 0;
							copy[k].maxsize = blocks[i].P[j].size;
							copy[k].np = 0;
							copy[k].P[0].alloc = blocks[i].P[j].size;
							strcpy(copy[k].P[0].pid, blocks[i].P[j].pid);
							copy[k].P[0].end = copy[k].high;
							copy[k].P[0].start = copy[k].low;
							copy[k].P[0].size = copy[k].maxsize;
							k++;
						}
						else if (blocks[i].np == -1)
						{
							mv += blocks[i].free;
						}

						//blocks[i+1].P[0].
					}
				}
				copy[k].low = copy[k - 1].high;
				copy[k].high = tmp;
				//printf("%d",copy[k].high);
				copy[k].free = mv;
				copy[k].maxsize = mv;
				copy[k].np = -1;

				for (int i = 0; i < k + 1; i++)
				{
					for (int j = 0; j <= copy[i].np; j++)
						printf("-------------");
					if (copy[i].free != 0)
						printf("------------");	//after allocation
				}
				printf("\n");
				printf("|");
				for (int i = 0; i < k + 1; i++)
				{
				 		//printf("%d %d",i,blocks[i].np);
					for (int j = 0; j <= copy[i].np; j++)
						//printf("%s pid",blocks[i].P[i].pid);
						printf("     %s     |", copy[i].P[j].pid);
					if (copy[i].free != 0)
						printf("     H     |");
				}
				printf("\n");
				for (int i = 0; i < k + 1; i++)
				{
					for (int j = 0; j <= copy[i].np; j++)
						printf("-------------");
					if (copy[i].free != 0)
						printf("------------");
				}

				printf("\n");
				for (int i = 0; i < k + 1; i++)
				{

					for (int j = 0; j <= copy[i].np; j++)
						printf("%d\t\t\t", copy[i].P[j].start);
					if (copy[i].free != 0)
						printf("%d\t\t\t", copy[i].low + copy[i].maxsize - copy[i].free);
					//}
					if (i == k)
					{
						printf("%d", copy[i].high);
					}
				}
				printf("\n");
			}
			else if (choice == 5)
			{
				printf("Program terminating.\n");
				exit(0);
			}
			else
			{
				printf("Wrong Option\n");
			}
			printf("Do you want to continue?[y/n]\t");
			scanf(" %c", &rerun);
		} while (rerun == 'Y' || rerun == 'y');
	}
	else if (chmat == 3)
	{
		//Menu
		do { 	printf("Menu\n\n1. Entry/Allocate\n\n2.Exit/Deallocate\n\n3.Display\n\n4.Compacting\n\n5.Exit\n\nEnter your choice:\t");
			scanf("%d", &choice);
			if (choice == 1)
			{
				int flag = 0;
				int k = 0;
				int copy_block[n];
				printf("Enter PID: ");
				scanf("%s", name);
				printf("Enter size of process: ");
				scanf("%d", &reqsize);
				for (int i = 0; i < n; i++)
				{
					if (blocks[i].free >= reqsize)
					{
						copy_block[k++] = blocks[i].free;
					}
				}
				//for(int i=0;i < n;i++){ 	// printf("%d",copy_block[i]);
				//}
				//printf("\n");
				bubbleSort_bf(copy_block, n);
				/*for(int i=0;i < n;i++){
        printf("%d",copy_block[i]);
      }
      printf("\n");
      for(int i=0;i < n;i++){
        printf("%d",blocks[i].free);
      }
      printf("\n");
*/
				for (int i = 0; i < n; i++)
				{
					if (blocks[i].free == copy_block[0] && reqsize <= blocks[i].free)
					{
						blocks[i].np += 1;
						strcpy(blocks[i].P[blocks[i].np].pid, name);
						printf("%s", blocks[i].P[blocks[i].np].pid);
						blocks[i].P[blocks[i].np].start = blocks[i].low + blocks[i].maxsize - blocks[i].free;
						blocks[i].P[blocks[i].np].size = reqsize;
						blocks[i].P[blocks[i].np].end = blocks[i].P[blocks[i].np].start + blocks[i].P[blocks[i].np].size;
						blocks[i].free -= reqsize;
						flag = 1;
						break;
					}
				}
				if (flag == 1)
					printf("Memory has been allocated successfully\n");
				else
					printf("Memory unable to be allocated to the process\n");
			}
			else if (choice == 2)
			{
				int flag = 0;
				printf("Enter PID: ");
				scanf("%s", name);
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
					{
						if (!strcmp(name, blocks[i].P[j].pid))
						{
						 				//printf("in loop");
							blocks[i].free += blocks[i].P[j].size;
							blocks[i].P[j].start = -1;
							blocks[i].P[j].size = -1;
							blocks[i].P[j].end = -1;
							blocks[i].np -= 1;
							flag = 1;
						}
					}
				}
				if (flag == 1)
					printf("Memory has been deallocated successfully\n");
				else
					printf("Memory unable to be deallocated from the process\n");
			}
			else if (choice == 3)
			{
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
						printf("-------------");
					if (blocks[i].free != 0)
						printf("------------");	//after allocation
				}
				printf("\n");
				printf("|");
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
						printf("     %s     |", blocks[i].P[j].pid);
					if (blocks[i].free != 0)
						printf("     H     |");
				}
				printf("\n");
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
						printf("-------------");
					if (blocks[i].free != 0)
						printf("------------");
				}

				printf("\n");
				for (int i = 0; i < n; i++)
				{ 		/*if (i == n-1)
					{
						for (int j = 0 ;j <= blocks[i].np; j++)
					  {
					  	printf("%d\t\t\t", blocks[i].P[blocks[i].np].start);
					    if (j == blocks[i].np && blocks[i].free != 0)
					      printf("%d\t\t\t", blocks[i].P[blocks[i].np].start);
					  }
					  if (blocks[i].free != 0)
					    printf("%d\t\t\t%d", blocks[i].low+blocks[i].maxsize-blocks[i].free, blocks[i].high);
					}*/
					//else
					//{ 		for (int j = 0; j <= blocks[i].np; j++)
						printf("%d\t\t\t", blocks[i].P[j].start);
					if (blocks[i].free != 0)
						printf("%d\t\t\t", blocks[i].low + blocks[i].maxsize - blocks[i].free);
					//}
					if (i == n - 1)
					{
						printf("%d", blocks[i].high);
					}
				}
				printf("\n");
			}
			else if (choice == 4)
			{
				int mv;
				int k = 0;

				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j <= blocks[i].np; j++)
					{

						if (blocks[i].np > -1)
						{
							mv += blocks[i].free;
							if (k == 0)
							{
								copy[0].low = blocks[0].low;
							}
							else
							{
								copy[k].low = copy[k - 1].high;
							}
							copy[k].high = copy[k].low + blocks[i].P[j].size;
							//printf("%d",copy[k].high);
							copy[k].free = 0;
							copy[k].maxsize = blocks[i].P[j].size;
							copy[k].np = 0;
							copy[k].P[0].alloc = blocks[i].P[j].size;
							strcpy(copy[k].P[0].pid, blocks[i].P[j].pid);
							copy[k].P[0].end = copy[k].high;
							copy[k].P[0].start = copy[k].low;
							copy[k].P[0].size = copy[k].maxsize;
							k++;
						}
						else if (blocks[i].np == -1)
						{
							mv += blocks[i].free;
						}

						//blocks[i+1].P[0].
					}
				}
				copy[k].low = copy[k - 1].high;
				copy[k].high = copy[k].low + mv;
				//printf("%d",copy[k].high);
				copy[k].free = mv;
				copy[k].maxsize = mv;
				copy[k].np = -1;

				for (int i = 0; i < k + 1; i++)
				{
					for (int j = 0; j <= copy[i].np; j++)
						printf("-------------");
					if (copy[i].free != 0)
						printf("------------");	//after allocation
				}
				printf("\n");
				printf("|");
				for (int i = 0; i < k + 1; i++)
				{
				 		//printf("%d %d",i,blocks[i].np);
					for (int j = 0; j <= copy[i].np; j++)
						//printf("%s pid",blocks[i].P[i].pid);
						printf("     %s     |", copy[i].P[j].pid);
					if (copy[i].free != 0)
						printf("     H     |");
				}
				printf("\n");
				for (int i = 0; i < k + 1; i++)
				{
					for (int j = 0; j <= copy[i].np; j++)
						printf("-------------");
					if (copy[i].free != 0)
						printf("------------");
				}

				printf("\n");
				for (int i = 0; i < k + 1; i++)
				{

					for (int j = 0; j <= copy[i].np; j++)
						printf("%d\t\t\t", copy[i].P[j].start);
					if (copy[i].free != 0)
						printf("%d\t\t\t", copy[i].low + copy[i].maxsize - copy[i].free);
					//}
					if (i == k)
					{
						printf("%d", copy[i].high);
					}
				}
				printf("\n");
			}
			else if (choice == 5)
			{
				printf("Program terminating.\n");
				exit(0);
			}
			else
			{
				printf("Wrong Option\n");
			}
			printf("Do you want to continue?[y/n]\t");
			scanf(" %c", &rerun);
		} while (rerun == 'Y' || rerun == 'y');
	}
	else
		printf("Wrong Option chosen. Program terminated\n");
	return 0;
}
