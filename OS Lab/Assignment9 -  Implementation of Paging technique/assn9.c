#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAX 50
struct table
{
	int page[MAX];
	int frame[MAX];
	int no_of_pages;
};
int main()
{
	srand(time(0));
	int no_of_frames, option, process_id, frames_req, no_of_free_frames = 0, no_of_process = 0, m = 1;
	double size, memory_size, page_size;
	int frames[MAX], temp_process[MAX];
	struct table processes_table[MAX];

	printf("\nPAGING TECHNIQUE\n");
	printf("\nEnter the physical memory size: ");
	scanf(" %lf", &memory_size);

	printf("Enter the page size: ");
	scanf(" %lf", &page_size);

	no_of_frames = ceil(memory_size / page_size);
	printf("\nPhysical memory is divided into %d frames.", no_of_frames);
	
	for (int i = 1; i <= no_of_frames; i++)
	{
		frames[i] = 0;
	}
	int n = 10;
	for (int i = 1; i <= n; i++)
	{
		frames[rand() % no_of_frames + 1] = -1;
		no_of_free_frames++;
	}

	printf("\n\nAfter Initialisation: \n\nFree Frames: ");
	for (int i = 1; i <= no_of_frames; i++)
	{
		if (frames[i] == -1)
		{
			printf("%d ", i);
		}
	}
	
	int p = 0;
	printf("\n\nMENU:\n\t1. process_id request\n\t2. Deallocation\n\t3. Page Table display for all input process_id\n\t4. Free Frame list display\n\t5. Exit\n");
	do
	{
		printf("\nEnter the option: ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			printf("\nEnter the process_id requirement (ID,size): P");
			scanf(" %d %lf", &process_id, &size);
			frames_req = ceil(size / page_size);
			processes_table[process_id].no_of_pages = frames_req;
			printf("\nProcess is divivded into %d pages.\n\nPage Table for P%d:\n", frames_req, process_id);
			if (frames_req <= no_of_free_frames)
			{
				p = 0;
				no_of_process++;
				temp_process[no_of_process] = process_id;
				for (int i = 1; i <= frames_req;)
				{
					for (int j = m;;)
					{
						if (frames[j] == -1)
						{
							printf("\n\tPage %d : Frame %d \n", i - 1, j);
							no_of_free_frames--;
							frames[j] = process_id;
							processes_table[process_id].page[p] = i - 1;
							processes_table[process_id].frame[p] = j;
							i++;
							p++;
							break;
						}
						j = j % no_of_frames + 1;
						m = j;
					}
				}
			}
			else
			{
				printf("\nThere is no enough free frames to allocate for this process_id!\n");
			}
			break;
		case 2:
			printf("\nEnter the process_id to be deallocated: P");
			scanf(" %d", &process_id);
			for (int i = 1; i <= no_of_frames; i++)
			{
				if (frames[i] == process_id)
				{
					frames[i] = -1;
					no_of_free_frames++;
				}
			}
			for (int i = 1; i <= no_of_process; i++)
			{
				if (temp_process[i] == process_id)
				{
					temp_process[i] = -1;
					break;
				}
			}
			break;
		case 3:
			for (int k = 1; k <= no_of_process; k++)
			{
				if (temp_process[k] != -1)
				{
					printf("\nPage table for P%d:\n", temp_process[k]);

					for (int i = 0; i < processes_table[temp_process[k]].no_of_pages; i++)
					{
						printf("\n\tPage %d : Frame %d \n", processes_table[temp_process[k]].page[i], processes_table[temp_process[k]].frame[i]);
					}
				}
			}
			break;
		case 4:
			printf("\nFree Frames: ");
			for (int j = m; j <= no_of_frames; j++)
			{
				if (frames[j] == -1)
				{
					printf("%d ", j);
				}
				j = j % no_of_frames + 1;
				m = j;
			}
			printf("\n");
			break;
		case 5:
			printf("\nProgram terminated\n");
			break;
		default:
			printf("\nInvalid option\n");
			break;
		}
	} while (option != 5);
}
