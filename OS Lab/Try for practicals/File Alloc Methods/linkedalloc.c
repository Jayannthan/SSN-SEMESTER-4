#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 100
typedef struct dir
{
    char fname[20];
    int start;
    int length;
    int end;
    int linked[MAX];
    struct dir *next;
} dir;
typedef struct node
{
    char fname[20];
    int blockid;
    int status;
    int fileblocktable[100];
    struct node *next;
    struct node *link;
} node;
typedef struct fileDetails
{
    char fname[20];
    int fsize;
    int fileblocks;
} fileDetails;
fileDetails files[MAX];
node blocks[MAX];
int no_blocks, no_files, memsize, block_size, no_free_blocks;

void linked_alloc()
{
    dir directory[no_files];
    int found, count_rand, temp, ind = 0;
    for (int i = 0; i < no_files; i++)
    {
        int tempind = 0;
        if (files[i].fileblocks <= no_free_blocks)
        {
            for (int j = 0; j < files[i].fileblocks; j++)
            {
                found = 0;
                while (found == 0)
                {
                    temp = rand() % no_blocks;
                    if (blocks[temp].status == 0)
                    {
                        found = 1;
                    }
                }
                blocks[temp].status = 1;
                strcpy(blocks[temp].fname, files[i].fname);
                if (j == 0)
                {
                    strcpy(directory[ind].fname, files[i].fname);
                    directory[ind].start = temp;
                    directory[ind].linked[tempind++] = temp;
                }
                if (j == files[i].fileblocks - 1)
                {
                    directory[ind].end = temp;
                    directory[ind].linked[tempind++] = temp;
                }
                else if (j != 0)
                {
                    directory[ind].linked[tempind++] = temp;
                }
            }
            ind++;
        }
        else
        {
            printf("\nSpace not enough for %d file\n", i + 1);
        }
    }
    printf("\nDirectory\nFile\tStart\tEnd\tPath\n");
    for (int i = 0; i <= ind; i++)
    {
        printf("%s\t%d\t%d\t", directory[i].fname, directory[i].start, directory[i].end);
        for (int j = 0;; j++)
        {
            if (directory[i].linked[j] == directory[i].end)
            {
                break;
            }
            printf("%d-->", directory[i].linked[j]);
        }
        printf("\n");
    }
}
int main(int argc, char const *argv[])
{
    srand(time(0));
    printf("Enter memory size:");
    scanf(" %d", &memsize);
    printf("Enter block size:");
    scanf(" %d", &block_size);
    no_blocks = floor(memsize / block_size);
    printf("\nNo of blocks: %d\n", no_blocks);
    no_free_blocks = no_blocks;
    for (int i = 0; i < no_blocks; i++)
    {
        strcpy(blocks[i].fname, "free");
        blocks[i].status = 0;
        blocks[i].blockid = i + 1;
    }
    printf("Enter no of files:");
    scanf(" %d", &no_files);
    printf("\nEnter file details:");

    for (int i = 0; i < no_files; i++)
    {
        printf("file %d:\n", i + 1);
        printf("\tFilename:");
        scanf(" %s", files[i].fname);
        printf("\tSize:");
        scanf(" %d", &files[i].fsize);
        files[i].fileblocks = ceil(files[i].fsize / block_size);
    }
    linked_alloc();

    return 0;
}
