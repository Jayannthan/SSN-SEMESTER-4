#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include<math.h>

#define FIFO_FILE "/tmp/filesharingspace"

void delay()
{
	for (int c = 1; c <= 32767; c++) 
       		for (int d = 1; d <= 32767; d++) 
       			{}
}
int main()
{
	int fd;
   	char readbuf[1024];
   	char end[10];
	int to_end;
	int read_bytes;
   	char str[30];

   	mkfifo(FIFO_FILE, S_IFIFO|0640);
   	strcpy(end, "end");
  	fd = open(FIFO_FILE, O_RDWR);
  	
   	while(1)
   	{
        	read_bytes = read(fd, readbuf, sizeof(readbuf));
      		readbuf[read_bytes] = '\0';
      		printf("\nFile request received: %s\nContents of file sent...\n",readbuf);
      		to_end = strcmp(readbuf, end);
      		if (to_end == 0)
      		{
         		close(fd);	
         		break;
      		}
      		int file=open(readbuf,O_RDONLY);

	        if(file==-1)
	        {
	      		strcpy(str,"File Not Found!!!!\n");
	      		sprintf(readbuf,"File Not Found!!!");
	      	}
	      	else
	      	{
	      		strcpy(str,"Sent!\n");
	      		char contents[1024];
	      		read(file,contents,1024);
	      		close(file);
	      		strcpy(readbuf,contents);
	      	}	

	      	delay();
	      	printf("%s",str);
	      	write(fd, readbuf, strlen(readbuf));
	}
  	return 0;
}

