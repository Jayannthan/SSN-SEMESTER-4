#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FIFO_FILE "/tmp/filesharingspace"

int main()
{
	int fd;
	int end_process;
	int stringlen;
	int read_bytes;
	char readbuf[1024];
	char end_str[5];
	printf("FIFO_CLIENT: Request files from Server ( to end enter \"end\")\n");
	fd = open(FIFO_FILE, O_CREAT | O_RDWR);
	strcpy(end_str, "end");

	while (1)
	{
		printf("Enter filename: ");
		fgets(readbuf, sizeof(readbuf), stdin);
		stringlen = strlen(readbuf);
		readbuf[stringlen - 1] = '\0';

		if (strcmp(readbuf, end_str) != 0)
		{
			write(fd, readbuf, strlen(readbuf));
			printf("\nFile: %s\n", readbuf);
			printf("File Request Sent...\n");

			read_bytes = read(fd, readbuf, sizeof(readbuf));
			readbuf[read_bytes] = '\0';
			printf("Contents of File: \n%s\n\n", readbuf);
		}
		else
		{
			write(fd, readbuf, strlen(readbuf));
			close(fd);
			break;
		}
	}
	return 0;
}