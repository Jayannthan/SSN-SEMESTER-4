#include <stdio.h>
#include <string.h>


void print(memory *mem)
{
	for (int i = 0; i < mem->no_of_block; i++)
	{
		for (int j = 0; j <= mem->blocks[i].no_of_current_process; j++)
			printf("-------------");
		if (mem->blocks[i].free_space != 0)
			printf("------------");
	}
	printf("\n");
	printf("|");
	for (int i = 0; i < mem->no_of_block; i++)
	{
		for (int j = 0; j <= mem->blocks[i].no_of_current_process; j++)
			printf("     %s     |", mem->blocks[i].process[j].process_name);
		if (mem->blocks[i].free_space != 0)
			printf("     H     |");
	}
	printf("\n");
	for (int i = 0; i < mem->no_of_block; i++)
	{
		for (int j = 0; j <= mem->blocks[i].no_of_current_process; j++)
			printf("-------------");
		if (mem->blocks[i].free_space != 0)
			printf("------------");
	}

	printf("\n");
	for (int i = 0; i < mem->no_of_block; i++)
	{
		printf("%d\t\t\t", mem->blocks[i].starting_addr);
		if (mem->blocks[i].free_space != 0)
			printf("%d\t\t\t", mem->blocks[i].starting_addr + mem->blocks[i].max_space - mem->blocks[i].free_space);
		if (i == mem->no_of_block - 1)
		{
			printf("%d", blocks[i].ending_addr);
		}
	}
	printf("\n");
}
