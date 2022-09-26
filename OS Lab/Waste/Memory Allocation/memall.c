#include <stdio.h>
#include <string.h>
#define max 100
typedef struct process_store
{
    char process_name[5];
    int allocated_into,process_size;
} process_store;

typedef struct blocks_store
{
	int starting_addr,ending_addr;
    int free_space,max_space;
    int no_of_current_process;
    process_store process[max];
    char status;
} blocks_store;

typedef struct memory
{
    int no_of_block;
    blocks_store blocks[max];
} memory;

memory create_memory()
{
	memory mem;
	printf("\nEnter no. of blocks:");
	scanf(" %d",&mem.no_of_block);
	for(int i=0;i<mem.no_of_block;i++)
	{
		printf("\nEnter starting address of block %d:",i+1);
		scanf(" %d",&mem.blocks[i].starting_addr);
		printf("\nEnter ending address of block %d:",i+1);
		scanf(" %d",&mem.blocks[i].ending_addr);
		mem.blocks[i].max_space=mem.blocks[i].ending_addr-mem.blocks[i].starting_addr;
		mem.blocks[i].free_space=mem.blocks[i].max_space;
		mem.blocks[i].status='H';
		mem.blocks[i].no_of_current_process=0;
	}
	return mem;
}
void deallocate(memory *mem)
{
	printf("\nDEALLOCATION\n:");
	char name[5];
	printf("\nEnter name of process to deallocate:");
	scanf(" %s",name);
	for(int i=0;i<mem->no_of_block;i++)
	{
		if(mem->blocks[i].status == 'H')
		{
			continue;
		}
		else
		{
			for(int j=0;j<mem->blocks[i].no_of_current_process;j++)
			{
				if(strcmp(mem->blocks[i].process[j].process_name,name)==0)
				{
					mem->blocks[i].free_space+=mem->blocks[i].process[j].process_size;
					memmove(mem->blocks+i,mem->blocks+i+1,sizeof(mem->blocks));
					mem->blocks[i].no_of_current_process--;
					if(mem->blocks[i].no_of_current_process==0)
					{
						mem->blocks[i].status='H';
					}
					printf("\nProcess removed from block %d\n",i+1);
					return;
				}
			}
		}
	}
}
void firstfit_allocation(memory *mem)
{
	printf("\nFIRST FIT ALLOCATION:\n");
	int size;
	char name[5];
	printf("\nEnter name of incoming process:");
	scanf(" %s",name);
	printf("\nEnter size of incoming process:");
	scanf(" %d",&size);
	for(int i=0;i<mem->no_of_block;i++)
	{
		if(size<=mem->blocks[i].free_space)
		{
			int pos=mem->blocks[i].no_of_current_process;
			strcpy(mem->blocks[i].process[pos].process_name,name);
			mem->blocks[i].free_space-=size;
			mem->blocks[i].process[pos].process_size=size;
			mem->blocks[i].process[pos].allocated_into=i;
			mem->blocks[i].no_of_current_process++;
			mem->blocks[i].status='N';
			printf("\nAllocated\n");
			return;
		}
	}
	printf("\nNO SPACE FOUND IN ANY OF THE BLOCKS TO ALLOCATE THE PROCESS\n");
}

void bestfit_allocation(memory *mem)
{
	printf("\nBEST FIT ALLOCATION:\n");
	int size;
	char name[5];
	int min=9999;
	int insert=-1;
	printf("\nEnter name of incoming process:");
	scanf(" %s",name);
	printf("\nEnter size of incoming process:");
	scanf(" %d",&size);
	for(int i=0;i<mem->no_of_block;i++)
	{
		if(size<=mem->blocks[i].free_space)
		{
			if(mem->blocks[i].free_space-size < min)
			{
				min=mem->blocks[i].free_space-size;
				insert=i;
			}
		}
	}
	if(insert==-1)
	{
		printf("\nNO SPACE FOUND IN ANY OF THE BLOCKS TO ALLOCATE THE PROCESS\n");
	}
	else
	{
		int pos=mem->blocks[insert].no_of_current_process;
		strcpy(mem->blocks[insert].process[pos].process_name,name);
		mem->blocks[insert].free_space-=size;
		mem->blocks[insert].process[pos].process_size=size;
		mem->blocks[insert].process[pos].allocated_into=insert;
		mem->blocks[insert].no_of_current_process++;
		mem->blocks[insert].status='N';
		printf("\nAllocated\n");
	}
}

void worstfit_allocation(memory *mem)
{
	printf("\nWORST FIT ALLOCATION:\n");
	int size;
	char name[5];
	int maxt=-1;
	int insert=-1;
	printf("\nEnter name of incoming process:");
	scanf(" %s",name);
	printf("\nEnter size of incoming process:");
	scanf(" %d",&size);
	for(int i=0;i<mem->no_of_block;i++)
	{
		if(size<=mem->blocks[i].free_space)
		{
			if(mem->blocks[i].free_space-size > maxt)
			{
				maxt=mem->blocks[i].free_space-size;
				insert=i;
			}
		}
	}
	if(insert==-1)
	{
		printf("\nNO SPACE FOUND IN ANY OF THE BLOCKS TO ALLOCATE THE PROCESS\n");
	}
	else
	{
		int pos=mem->blocks[insert].no_of_current_process;
		strcpy(mem->blocks[insert].process[pos].process_name,name);
		mem->blocks[insert].free_space-=size;
		mem->blocks[insert].process[pos].process_size=size;
		mem->blocks[insert].process[pos].allocated_into=insert;
		mem->blocks[insert].no_of_current_process++;
		mem->blocks[insert].status='N';
		printf("\nAllocated\n");
	}
}


void print(memory *mem)
{
	for (int i = 0; i < mem->no_of_block; i++)
	{
		for (int j = 0; j < mem->blocks[i].no_of_current_process; j++)
			printf("-------------");
		if (mem->blocks[i].free_space != 0)
			printf("------------");
	}
	printf("\n");
	printf("|");
	for (int i = 0; i < mem->no_of_block; i++)
	{
		for (int j = 0; j < mem->blocks[i].no_of_current_process; j++)
			printf("     %s     |", mem->blocks[i].process[j].process_name);
		if (mem->blocks[i].free_space != 0)
			printf("      H     |");
	}
	printf("\n");
	for (int i = 0; i < mem->no_of_block; i++)
	{
		for (int j = 0; j < mem->blocks[i].no_of_current_process; j++)
			printf("-------------");
		if (mem->blocks[i].free_space != 0)
			printf("------------");
	}

	printf("\n");
	for (int i = 0; i < mem->no_of_block; i++)
	{
		printf(" %d\t   ", mem->blocks[i].starting_addr);
		/*if (mem->blocks[i].free_space != 0)
			printf("%d\t\t", mem->blocks[i].starting_addr + mem->blocks[i].max_space - mem->blocks[i].free_space);
		if (i == mem->no_of_block - 1)
		{
			printf("%d", mem->blocks[i].ending_addr);
		}*/
	}
	printf("\n");
}
void firstfit(memory *mem)
{
	int choice;
	printf("\nMenu\n\t1. Entry/Allocate\n\t2.Deallocate\n\t3.Display\n\t4.Exit\n\tEnter Choice:");
	scanf(" %d",&choice);
	while(choice)
	{
		switch(choice)
		{
			case 1:firstfit_allocation(mem);break;
			case 2:deallocate(mem);break;
			case 3:print(mem);break;
			case 4:return;
		}
		printf("\nMenu\n\t1. Entry/Allocate\n\t2.Deallocate\n\t3.Display\n\t4.Exit\n\tEnter Choice:");
		scanf(" %d",&choice);
	}
}
void bestfit(memory *mem)
{
	int choice;
	printf("\nMenu\n\t1. Entry/Allocate\n\t2.Deallocate\n\t3.Display\n\t4.Exit\n\tEnter Choice:");
	scanf(" %d",&choice);
	while(choice)
	{
		switch(choice)
		{
			case 1:bestfit_allocation(mem);break;
			case 2:deallocate(mem);break;
			case 3:print(mem);break;
			case 4:return;
		}
		printf("\nMenu\n\t1. Entry/Allocate\n\t2.Deallocate\n\t3.Display\n\t4.Exit\n\tEnter Choice:");
		scanf(" %d",&choice);
	}
}
void worstfit(memory *mem)
{
	int choice;
	printf("\nMenu\n\t1. Entry/Allocate\n\t2.Deallocate\n\t3.Display\n\t4.Exit\n\tEnter Choice:");
	scanf(" %d",&choice);
	while(choice)
	{
		switch(choice)
		{
			case 1:worstfit_allocation(mem);break;
			case 2:deallocate(mem);break;
			case 3:print(mem);break;
			case 4:return;
		}
		printf("\nMenu\n\t1. Entry/Allocate\n\t2.Deallocate\n\t3.Display\n\t4.Exit\n\tEnter Choice:");
		scanf(" %d",&choice);
	}
}
int main()
{
	printf("\nEnter the Memory Representation:\n");
	memory mem=create_memory();
	int choice;
	printf("\nMenu\n\t1.First Fit\n\t2.Best Fit\n\t3.Worst Fit\n\tEnter Choice:");
	scanf(" %d",&choice);
	switch(choice)
	{
		case 1:firstfit(&mem);break;
		case 2:bestfit(&mem);break;
		case 3:worstfit(&mem);break;
	}
	return 0;
}