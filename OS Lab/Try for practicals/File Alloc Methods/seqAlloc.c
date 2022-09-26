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

void contig_alloc()
{
    dir directory[no_files];
    int found, count_rand, temp, ind = 0;
    for (int i = 0; i < no_files; i++)
    {

        if (files[i].fileblocks <= no_free_blocks)
        {
            found = 0;
            while (found != 1 && count_rand <= no_free_blocks)
            {
                count_rand++;
                temp = rand() % no_blocks;
                int j;
                for (j = temp; j < temp + files[i].fileblocks; j++)
                {
                    if (blocks[j].status != 0)
                    {
                        break;
                    }
                }
                if (j == (temp + files[i].fileblocks))
                {
                    found = 1;
                }
            }
            if (found == 1)
            {
                printf("\nDONE\n");
                strcpy(directory[ind].fname, files[i].fname);
                directory[ind].start = temp;
                directory[ind].length = files[i].fileblocks;
                for (int j = temp; j < temp + files[i].fileblocks; j++)
                {
                    strcpy(blocks[j].fname, files[i].fname);
                    blocks[j].status = 1;
                }
                ind++;
            }
            else
            {
                printf("\nSpace not enough for %d file\n", i + 1);
            }
        }
        else
        {
            printf("\nSpace not enough for %d file\n", i + 1);
        }
    }
    printf("\nDirectory\nFile\tStart\tLength\n");
    for (int i = 0; i <= ind; i++)
    {
        printf("%s\t%d\t%d\n", directory[i].fname, directory[i].start, directory[i].length);
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
    contig_alloc();

    return 0;
}
