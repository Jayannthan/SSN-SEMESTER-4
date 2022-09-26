#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
typedef struct
{  char fname[20];
   int start;
   int length;
   int end;
   struct dir *next;
}dir;
typedef struct
{  char fname[20];
   int blockid;
   int fileblocktable[100];
   struct node *next;
   struct node *link;
}node;
typedef struct
{  char fname[20];
   int fsize;
   int fileblocks;
}fileDetails;
int nof,nob,bsize;
void insert(node *head,node data)
{  node *t;
   node *newnode;
   newnode=(node*)malloc(sizeof(node));
   newnode->blockid=data.blockid;
   strcpy(newnode->fname,data.fname);
   newnode->next=NULL;
   t=head;
   while(t->next!=NULL)
     t=t->next;
   t->next=newnode;
}
void contiguous_allocation(node* mainm,fileDetails filedata[])
{  dir d[nof];
   int i,j;
   int alloc=0;
   int randno;
   int occur[nob+1];
   node *t;
   node *start;
   int found;
   int count_rand;
   for(i=0;i<nof;i++)
   {  found=0;
      count_rand=0;
      for(j=1;j<=nob;j++)
        occur[j]=0;
      while(count_rand!=nob)
      {  randno = (rand() % nob) + 1;
         while(occur[randno]!=0)
           randno = (rand() % nob) + 1;
         count_rand++;
         occur[randno]=1;
         t=mainm;
         for(j=0;j<randno;j++)
           t=t->next;
         start=t;
         found=1;
         for(j=0;j<filedata[i].fileblocks;j++)
         {  if(t==NULL)
              break;
            if(strcmp(t->fname,"Free")==0)
            {  t=t->next;
               continue;
            }
            else
            {  found=0;
               break;
            }
         }
         if(found==1)
         {  d[alloc].start=start->blockid;
            d[alloc].length=filedata[i].fileblocks;
            strcpy(d[alloc].fname,filedata[i].fname);
            for(j=0;j<filedata[i].fileblocks;j++)
            {  strcpy(start->fname,filedata[i].fname);
               start=start->next;
            }
            break;
         }
      }
      if(found==0)
        printf("\nMEMORY UNAVAILABLE\n");
      else
        alloc++;
   }
   printf("\nNo. of files allocated:%d\n",alloc);
   printf("\nDirectory\n\n");
   printf("\tFile Name\tStart\tLength\n\n");
   for(i=0;i<alloc;i++)
     printf("\t%s\t\t%d\t%d\n",d[i].fname,d[i].start,d[i].length);
   printf("\n");
}
void linked_allocation(fileDetails filedata[],node *mainm)
{  node *temp,*start,*new;
   int i,j,k;
   int randno;
   int found;
   dir d[nof];
   int startpos;
   for(i=0;i<nof;i++)
     for(j=0;j<filedata[i].fileblocks;j++)
     {  found=0;
        while(found==0)
        {  randno=(rand()%nob)+1;
           temp=mainm;
           for(k=0;k<randno;k++)
             temp=temp->next;
           if(strcmp(temp->fname,"Free")==0)
           {  strcpy(temp->fname,filedata[i].fname);
              found=1;
              if(j==0)
              {  new=temp;
                 strcpy(d[i].fname,filedata[i].fname);
                 d[i].start=temp->blockid;
              }
              else if(j==filedata[i].fileblocks-1)
              {  new->link=temp;
                 temp->link=NULL;
                 d[i].end=temp->blockid;
              }
              else
              {  new->link=temp;
                 new=new->link;
              }
           }
        }
     }
   printf("\nDirectory\n\n");
   printf("\tFile Name\tStart\tEnd\n\n");
   for(i=0;i<nof;i++)
   printf("\t%s\t\t%d\t%d\n",d[i].fname,d[i].start,d[i].end);
   printf("\nIndividual File listing\n\n");
   printf("File Name\t\tData-Block\n\n");
   for(i=0;i<nof;i++)
   {  printf("%s\t\t\t",d[i].fname);
      startpos=d[i].start;
      temp=mainm;
      for(j=0;j<startpos;j++)
        temp=temp->next;
      printf("Data-block %d\n",temp->blockid);
      temp=temp->link;
      while(temp!=NULL)
      {  printf("\t\t\tData-block %d\n",temp->blockid);
         temp=temp->link;
      }
      printf("\n");
   }
}
void indexed_allocation(fileDetails filedata[],node *mainm)
{  node *temp,*start,*indexblock;
   int i,j,k;
   int indexblockid;
   int randno;
   int found;
   dir d[nof];
   for(i=0;i<nof;i++)
   {  found=0;
      while(found!=1)
      {  randno = (rand() % nob ) + 1;
         temp=mainm;
         for(k=0;k<randno;k++)
           temp=temp->next;
         if(strcmp(temp->fname,"Free")==0)
         {  found=1;
            strcpy(temp->fname,filedata[i].fname);
         }
      }
      indexblock=temp;
      strcpy(d[i].fname,filedata[i].fname);
      d[i].start=indexblock->blockid;
      for(j=0;j<filedata[i].fileblocks;j++)
      {  found=0;
         while(found!=1)
         {  randno = (rand() % nob ) + 1;
            temp=mainm;
            for(k=0;k<randno;k++)
              temp=temp->next;
            if(strcmp(temp->fname,"Free")==0)
            {  found=1;
               strcpy(temp->fname,filedata[i].fname);
               indexblock->fileblocktable[j]=temp->blockid;
            }
         }
      }
   }
   printf("\nDirectory\n\n");
   printf("\tFile Name\tIndexed Block\n\n");
   for(i=0;i<nof;i++)
     printf("\t%s\t\t%d\n",d[i].fname,d[i].start);
   printf("\n\nIndex Table\n");
   printf("\nFile Name\t\tBlock Indexed\n");
   for(i=0;i<nof;i++)
   {  indexblockid=d[i].start;
      temp=mainm;
      for(j=0;j<indexblockid;j++)
        temp=temp->next;
      printf("\n%s",temp->fname);
      for(j=0;j<filedata[i].fileblocks;j++)
        printf("\t\t\tData-block %d\n",temp->fileblocktable[j]);
   }
   printf("\n");
}
void main()
{  int mem_size,choice=1,i;
   node data;
   node *mainm;
   node *temp;
   fileDetails filedata[100];
   mainm=malloc(sizeof(node));
   mainm->next=NULL;
   printf("Main memory size: ");
   scanf("%d",&mem_size);
   printf("Size of each block in the disk: ");
   scanf("%d KB",&bsize);
   nob=(int)mem_size/bsize;
   printf("Total no. of blocks available: %d\n",nob);
   for(i=0;i<nob;i++)
   {  data.blockid=i+1;
      strcpy(data.fname,"Free");
      insert(mainm,data);
   }
   printf("Number of files to be allocated: ");
   scanf("%d",&nof);
   for(i=0;i<nof;i++)
   {  printf("\nName of file %d: ",i+1);
      scanf("%s",filedata[i].fname);
      printf("Size of file %d: ",i+1);
      scanf("%d KB",&filedata[i].fsize);
      filedata[i].fileblocks=ceil((float)filedata[i].fsize/(float)bsize);
   }
   printf("\n\n\t\t\tFILE ALLOCATION TECHNIQUES\n\n");
   printf("1.Contiguous\n2.Linked\n3.Indexed\n4.Exit\n\n");
   printf("Choose the Allocation scheme: ");
   scanf("%d",&choice);
   do
   {  temp=mainm->next;
      while(temp!=NULL)
      {  strcpy(temp->fname,"Free");
         temp=temp->next;
      }
      srand(time(NULL));
      switch(choice)
      {  case 1:
           contiguous_allocation(mainm,filedata);
           break;
         case 2:
           linked_allocation(filedata,mainm);
           break;
         case 3:
           indexed_allocation(filedata,mainm);
           break;
         default:
           exit(0);
      }
      printf("Choose the Allocation scheme: ");
      scanf("%d",&choice);
   }while(choice!=4);
}
