#include <stdio.h>
#include <string.h>
#define MAX 100
typedef struct process
{
	char pid[3];
	int start;
	int end;
	int size;
} process;
typedef struct partition
{
	int num;
	process pro_arr[MAX];
	int start;
	int end;
	int size;
	int free;
} partition;

partition blocks[MAX];
int no_blocks;

void firstfit()
{
	char temppid[3];
	int tempsize;
	printf("\nEnter incoming processs ID:");
	scanf(" %s", temppid);
	printf("Enter size of incoming processs:");
	scanf(" %d", &tempsize);
	int alloc = 0;
	for (int i = 0; i < no_blocks; i++)
	{
		if (tempsize <= blocks[i].free)
		{
			strcpy(blocks[i].pro_arr[blocks[i].num].pid, temppid);
			blocks[i].pro_arr[blocks[i].num].size = tempsize;
			blocks[i].pro_arr[blocks[i].num].start = blocks[i].start + blocks[i].size - blocks[i].free;
			blocks[i].pro_arr[blocks[i].num].end = blocks[i].pro_arr[blocks[i].num].start + tempsize;
			blocks[i].num++;
			blocks[i].free -= tempsize;
			alloc = 1;
			printf("\n!!!Allocated!!!\n");

			break;
		}
	}
	if (alloc == 0)
	{
		printf("\n!!!NO SPACE TO ALLOCATE!!!");
	}
}
void dealloc()
{
	char temppid[3];
	int tempsize;
	printf("\nEnter processs ID to deallocate:");
	scanf(" %s", temppid);
	int found = 0;
	for (int i = 0; i < no_blocks; i++)
	{
		for (int j = 0; j < blocks[i].num; j++)
		{
			if (strcmp(temppid, blocks[i].pro_arr[j].pid) == 0)
			{
				printf("Process found!!!");
				for (int k = j + 1; k < blocks[i].num; k++)
				{
					blocks[i].pro_arr[k].start -= blocks[i].pro_arr[j].size;
					blocks[i].pro_arr[k].end -= blocks[i].pro_arr[j].size;
				}
				blocks[i].free += blocks[i].pro_arr[j].size;
				memmove(blocks[i].pro_arr + j * sizeof(process), blocks[i].pro_arr + (j + 1) * sizeof(process), sizeof(process));
				blocks[i].num--;
				found = 1;
				printf("Process Deallocated!!!");
				break;
			}
		}
	}
	if (found == 0)
	{
		printf("Process not found");
	}
}
void display_alloc()
{
	printf(" ");
	for (int i = 0; i < no_blocks; i++)
	{
		for (int j = 0; j < blocks[i].num; j++)
		{
			printf("------- ");
		}
		if (blocks[i].free != 0)
		{
			printf("------- ");
		}
	}
	printf("\n");
	for (int i = 0; i < no_blocks; i++)
	{
		for (int j = 0; j < blocks[i].num; j++)
		{
			printf("   %s   |", blocks[i].pro_arr[j].pid);
		}
		if (blocks[i].free != 0)
		{
			printf("   H   |");
		}
	}
	printf("\n");
	for (int i = 0; i < no_blocks; i++)
	{
		for (int j = 0; j < blocks[i].num; j++)
		{
			printf("------- ");
		}
		if (blocks[i].free != 0)
		{
			printf("------- ");
		}
	}
	printf("\n");

	for (int i = 0; i < no_blocks; i++)
	{
		for (int j = 0; j < blocks[i].num; j++)
		{
			printf("%d      ", blocks[i].pro_arr[j].start);
		}
		if (blocks[i].free != 0)
		{
			printf("%d      ", blocks[i].start + blocks[i].size - blocks[i].free);
		}
		if (i == no_blocks - 1)
		{
			printf("%d", blocks[i].end);
		}
	}
	printf("\n");
}
void display_free()
{
	printf(" ");
	for (int i = 0; i < no_blocks; i++)
	{
		printf("------- ");
	}
	printf("\n");
	for (int i = 0; i < no_blocks; i++)
	{
		if (blocks[i].free != 0)
		{
			printf("   %d   |", blocks[i].free);
		}
		else
		{
			printf("   0   |");
		}
	}
	printf("\n");
	for (int i = 0; i < no_blocks; i++)
	{
		printf("------- ");
	}
	printf("\n");
	printf("%d      ", blocks[0].start);
	for (int i = 0; i < no_blocks; i++)
	{
		printf("%d      ", blocks[i].end);
	}
	printf("\n");
}
void print()
{
	printf("\nPhysical Memory\n");
	display_alloc();
	printf("\nFREE POOL\n");
	display_free();
}
void coalese()
{
	for (int i = 1; i < no_blocks; i++)
	{
		printf("\nin");
		if (blocks[i].free == blocks[i].size && blocks[i - 1].free != blocks[i - 1].size)
		{
			printf("\ninif\n");

			blocks[i - 1].end = blocks[i - 1].end - blocks[i - 1].free;
			blocks[i - 1].size = blocks[i - 1].end - blocks[i - 1].start;
			blocks[i - 1].free = 0;
			blocks[i].start = blocks[i - 1].end;
			blocks[i].size = blocks[i].end - blocks[i].start;
			blocks[i].free = blocks[i].size;
			print();
		}
		else if (blocks[i].free == blocks[i].size && blocks[i - 1].free == blocks[i - 1].size)
		{
			printf("\ninifel\n");

			blocks[i - 1].end = blocks[i].end;
			blocks[i - 1].size = blocks[i - 1].end - blocks[i - 1].start;
			blocks[i - 1].free = blocks[i - 1].size;
			printf("\ninifel2\n");
			for (int j = i + 1; j < no_blocks; j++)
			{
				blocks[j - 1] = blocks[j];
			}

			// memmove(blocks + (i * sizeof(blocks)), blocks + ((i + 1) * sizeof(blocks)), sizeof(blocks));
			no_blocks--;
			i--;
			print();
		}
	}
	print();
}

int main(int argc, char const *argv[])
{
	printf("\nEnter no. of blocks:");
	scanf(" %d", &no_blocks);
	for (int i = 0; i < no_blocks; i++)
	{
		printf("Block %d:", i + 1);
		blocks[i].num = 0;
		printf("\n\tEnter start:");
		scanf(" %d", &blocks[i].start);
		printf("\tEnter end:");
		scanf(" %d", &blocks[i].end);
		blocks[i].size = blocks[i].end - blocks[i].start;
		blocks[i].free = blocks[i].size;
	}
	int choice = 0;
	printf("\nMENU\n\t1.Entry\n\t2.Deallocate\n\t3.Coalese\n\t4.Print\n\t5.Exit\nEnter your choice:");
	scanf(" %d", &choice);

	while (choice != 5)
	{
		switch (choice)
		{
		case 1:
			firstfit();
			break;
		case 2:
			dealloc();
			break;
		case 3:
			coalese();
			break;
		case 4:
			print();
			break;

		default:
			break;
		}
		printf("\nMENU\n\t1.Entry\n\t2.Deallocate\n\t3.Coalese\n\t4.Print\n\t5.Exit\nEnter your choice:");
		scanf(" %d", &choice);
	}

	return 0;
}
