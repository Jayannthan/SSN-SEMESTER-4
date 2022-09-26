#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
#include<ctype.h>

int strcmpi(char const *a, char const *b) //case insensitive comparision
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}

void display(char A[][20],int n) //display array
{
	for(int i=0; i<n; i++)
		printf("%s \n", A[i]);
}

void sort(char A[][20],int n) //sort the array
{
	char temp[30];
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n-1-i; j++)
		{
			if(strcmpi(A[j],A[j+1]) > 0)
			{
				strcpy(temp,A[j]);
       			strcpy(A[j],A[j+1]);
       			strcpy(A[j+1],temp);
      			}
    		}
  	}
  	display(A,n);
}

int cp(int argc,char *arg[],int i)
{
	//checking no of args
	if(argc!=3)
	{
		printf("Invalid no of args!\n");
		return -1;	
	}
	
	//checking src file	
	int fds=open(arg[1],O_RDONLY);
	if(fds==-1)
	{
		printf("Source File doesnt exist!\n");
		close(fds);
		return -1;	
	}
	int fdd;
	//checking dest file
	if(i) // cp -i 
	{
		fdd=open(arg[2],O_WRONLY);
		if(fdd!=-1) //if the file exists 
		{
			char ch;
			printf("Overwrite %s file?(y/n) ",arg[2]);
			scanf(" %c",&ch);
			if(!(ch=='y'||ch=='Y')) //other than y/Y
			{
				close(fdd);
				return -1;
			}
		}
		close(fdd);
	}
	fdd=creat(arg[2],0600); //even if the file exists or doesnt	
	//reading src and writing into dest
	char buf[500];	
	int nr,nw=0;
	while((nr=read(fds,buf,500))!=0)
        	nw+=write(fdd,buf,nr);
        	
        if(nw!=-1)
		printf("COPIED!\n");
	else
		printf("Error while copying\n");
		
	close(fds);
	close(fdd);
	return 0;
}

int grep(int argc,char *arg[],char c)
{
	//checking no of args
	if(argc!=3)
	{
		printf("Invalid no of args!\n");
		return -1;	
	}
	
	//checking src file
	int fd=open(arg[2],O_RDONLY);
	if(fd==-1)
	{
		printf("Source File doesnt exist!\n");
		close(fd);
		return -1;	
	}
	
	char line[100],buf[1024];	
	int l=0,i=0,nr,count=0;
	nr=read(fd,buf,1024);
	close(fd);
	
	while(l<nr)
	{	
		for(i=0;buf[l]!='\n'&&l<nr;i++,l++)
		{
			line[i]=buf[l]; //extracting lines
		}
		line[i]='\0';
		l++;
		if(c=='v' && (!strstr(line,arg[1]))) // -v
			printf("%s\n",line);
		else if(c!='v' && strstr(line,arg[1]))
		{
			if(c==' ')
				printf("%s\n",line);
			else if(c=='c')
				count++;
			else // -n
				printf("%d:%s\n",++count,line);
		}
	}
	if(c=='c')
		printf("%d\n",count);		
	return 0;
}

void ls(const char *dir,char c)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	if(!dh)
	{
		//printf("Dir Error!\n");
		closedir(dh);
		return;
	}
	char dirs[100][20];
	int n=0;
	while(d=readdir(dh))
	{
		if(c==' ')
		{
			if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
                		continue;
                }
		strcpy(dirs[n++],d->d_name);//printf("%s\t\n",d->d_name);
			
	}
	closedir(dh);
	sort(dirs,n);
}

void ls2(const char *dir,int k)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	if(!dh)
	{
		closedir(dh);
		return;
	}
	char dirs[100][20];
	int n=0;
	while(d=readdir(dh))
	{	
		if (d->d_type == DT_DIR) 
		{
			if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
				continue;
			!k?printf("\n."):printf("\n./%s",dir);
			printf("/%s:\n",d->d_name);
			ls(d->d_name,' ');
			ls2(d->d_name,k+1);
			//printf("\n");
		}	
	}
	closedir(dh);
}

int main(int argc,char *arg[])
{
	int ch;
	do
	{
		printf("\n---------------------\nMenu:\n1.cp\n2.cp -i\n3.grep\n4.grep -c\n5.grep -v\n6.grep -n\n7.ls\n8.ls -a\n9.ls- l\n10.ls -R\n11.Exit\nChoice: ");
		scanf("%d",&ch);
		printf("\n");
		switch(ch)
		{
			case 1:cp(argc,arg,0);
				break;
			case 2:cp(argc,arg,1);
				break;
			case 3:grep(argc,arg,' ');
				break;
			case 4:grep(argc,arg,'c');
				break;
			case 5:grep(argc,arg,'v');
				break;
			case 6:grep(argc,arg,'n');
				break;
			case 7:ls(".",' ');
				break;
			case 8:ls(".",'a');
				break;
			case 9:ls(".",'l');  //didnt do yet
				break;
			case 10:printf(".:\n");
				ls(".",' ');
				ls2(".",0);
				break;
			case 11:printf("\nExiting...\n");
				break;
			default:printf("\nInvalid choice!\n");					
		}
	}while(ch!=11);
	return 0;
}
