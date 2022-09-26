// Assignment 1: Develop a C program to implement Banker’s algorithm for deadlock avoidance with multiple instances of resource types

#include <stdio.h>
//#include <conio.h>
#include <string.h>
#define max 100
/*
3
3
2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
*/
typedef struct bankersdata
{
    int no_of_process;
    int no_of_resources;
    char process_name[max][5];
    char resources_name[max][5];
    int available_instance[max];   // available_instance[no_of_resources]
    int max_req[max][max];         // max_req[no_of_process][no_of_resources];
    int allocation[max][max];      // allocation[no_of_process][no_of_resources];
    int f[max], safesequence[max]; // f[no_of_process],safesequence[no_of_process]
    int need[max][max];
} bankersdata;

void printdata(bankersdata *bk)
{
    printf("Pid\tAlloc\tMax  \tNeed \tAvail\t\n--\t");
    for (int i = 0; i < bk->no_of_resources; i++)
    {
        printf("%s ", bk->resources_name[i]);
    }
    printf("\t");
    for (int i = 0; i < bk->no_of_resources; i++)
    {
        printf("%s ", bk->resources_name[i]);
    }
    printf("\t");
    for (int i = 0; i < bk->no_of_resources; i++)
    {
        printf("%s ", bk->resources_name[i]);
    }
    printf("\t");
    for (int i = 0; i < bk->no_of_resources; i++)
    {
        printf("%s ", bk->resources_name[i]);
    }
    printf("\t");
    printf("\n----------------------------------\n");
    for (int i = 0; i < bk->no_of_process; i++)
    {
        printf("%s ", bk->process_name[i]);
        for (int j = 0; j < bk->no_of_resources; j++)
        {
            printf(" %d", bk->allocation[i][j]);
        }
        printf("\t");
        for (int j = 0; j < bk->no_of_resources; j++)
        {
            printf(" %d", bk->max_req[i][j]);
        }
        printf("\t");
        for (int j = 0; j < bk->no_of_resources; j++)
        {
            printf(" %d", bk->need[i][j]);
        }
        printf("\t");
        if (i == 0)
        {
            for (int j = 0; j < bk->no_of_resources; j++)
            {
                printf(" %d", bk->available_instance[j]);
            }
        }
        printf("\t\n");
    }
}
void bankersalgo(bankersdata *bk)
{
    int ind = 0;
    int y = 0;
    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < bk->no_of_process; i++)
        {
            if (bk->f[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < bk->no_of_resources; j++)
                {
                    if (bk->need[i][j] > bk->available_instance[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    bk->safesequence[ind] = i;
                    ind++;
                    for (int j = 0; j < bk->no_of_resources; j++)
                    {
                        bk->available_instance[j] += bk->allocation[i][j];
                    }
                    bk->f[i] = 1;
                }
            }
        }
    }
    int flag = 1;
    for (int i = 0; i < bk->no_of_process; i++)
    {
        if (bk->f[i] == 0)
        {
            flag = 0;
            printf("\n\n!!!!NOT A SAFE SYSTEM!!!!\nDue to the following processes:");
        	break;
        }
    }
    if (flag == 1)
    {
        printf("SAFE SEQUENCE\n");
        for (int i = 0; i < bk->no_of_process - 1; i++)
        {
            printf(" %s ->", bk->process_name[bk->safesequence[i]]);
        }
        printf(" %s", bk->process_name[bk->safesequence[bk->no_of_process - 1]]);
    }
    else
    {
    	for (int i = 0; i < bk->no_of_process; i++)
    	{
        	if (bk->f[i] == 0)
        	{
            	printf(" %s ", bk->process_name[i]);
        	}
    	}
    }
}

bankersdata getdata()
{
    bankersdata bk;
    printf("\nEnter no of process:");
    scanf("%d", &bk.no_of_process);
    printf("\nEnter process ids:\n");
    for (int i = 0; i < bk.no_of_process; i++)
    {
        printf("process name of process %d:", i + 1);
        scanf(" %s", &bk.process_name[i]);
    }

    printf("\nEnter no of resources:");
    scanf("%d", &bk.no_of_resources);
    printf("\nEnter resource ids:\n");
    for (int i = 0; i < bk.no_of_resources; i++)
    {
        printf("resource name of resource %d:", i + 1);
        scanf(" %s", &bk.resources_name[i]);
    }

    printf("\nEnter available instances:\n");
    for (int i = 0; i < bk.no_of_resources; i++)
    {
        printf("available instances of resource %s:", bk.resources_name[i]);
        scanf(" %d", &bk.available_instance[i]);
    }

    printf("\nEnter Maximum requirement:\n");
    for (int i = 0; i < bk.no_of_process; i++)
    {
        printf("Maximum requirement for process %s:", bk.process_name[i]);
        for (int j = 0; j < bk.no_of_resources; j++)
        {
            scanf(" %d", &bk.max_req[i][j]);
        }
    }

    printf("\nEnter Allocated instances:\n");
    for (int i = 0; i < bk.no_of_process; i++)
    {
        printf("Allocated instances for process %s:", bk.process_name[i]);
        for (int j = 0; j < bk.no_of_resources; j++)
        {
            scanf(" %d", &bk.allocation[i][j]);
        }
    }

    for (int i = 0; i < bk.no_of_process; i++)
    {
        bk.f[i] = 0;
        for (int j = 0; j < bk.no_of_resources; j++)
        {
            bk.need[i][j] = bk.max_req[i][j] - bk.allocation[i][j];
        }
    }
    return bk;
}

int main(int argc, char const *argv[])
{
    bankersdata bk = getdata();
    int choice = 0;
    printf("\nMenu:\n\t1.Enter new data\n\t2.PrintData\n\t3.Bankers State\n\t4.Resource Request\n\t5.Exit\nEnter Choice:");
    scanf(" %d", &choice);
    while (choice)
    {
        switch (choice)
        {
        case 1:
        {
            bk = getdata();
            break;
        }
        case 2:
        {
            printdata(&bk);
            break;
        }

        case 3:
        {
            bankersalgo(&bk);
            break;
        }

        case 4:
        {
            char temp_process_name[5];
            printf("\nEnter process id for request:");
            scanf(" %s", &temp_process_name);
            int index_of_process = -1;
            for (int i = 0; i < bk.no_of_process; i++)
            {
                if (strcmp(temp_process_name, bk.process_name[i]) == 0)
                {
                    index_of_process = i;
                    break;
                }
            }
            if (index_of_process == -1)
            {
                printf("\nprocess name not correct!!!\n");
                break;
            }
            else
            {
                int allocation_vector[max];
                printf("\nEnter the request vector for %s:", bk.process_name[index_of_process]);
                for (int i = 0; i < bk.no_of_resources; i++)
                {
                    scanf(" %d", &allocation_vector[i]);
                }
                int flag = 1;
                for (int i = 0; i < bk.no_of_resources; i++)
                {
                    if (allocation_vector[i] > bk.available_instance[i] || allocation_vector[i] > bk.need[index_of_process][i])
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf("\n!!!Resource cannot be allocated!!!");
                    break;
                }
                for (int i = 0; i < bk.no_of_resources; i++)
                {
                    bk.available_instance[i] -= allocation_vector[i];
                    bk.need[index_of_process][i] -= allocation_vector[i];
                    bk.allocation[index_of_process][i] += allocation_vector[i];
                }
                printdata(&bk);
                
                bankersalgo(&bk);
            }
            break;
        }

        case 5:
            return 0;

        default:
        {
            printf("\n!!!Enter correct choice!!!\n");
            break;
        }
        }
        printf("\nMenu:\n\t1.Enter new data\n\t2.PrintData\n\t3.Bankers State\n\t4.Resource Request\n\t5.Exit\nEnter Choice:");
        scanf(" %d", &choice);
    }
    return 0;
}
