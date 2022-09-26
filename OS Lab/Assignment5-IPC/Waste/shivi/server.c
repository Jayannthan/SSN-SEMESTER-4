// Server.c
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
struct mesgq
{
	long type;
	char text[200];
} mq;
// int blue()
// {
// 	printf("\033[0;34m");
// 	return 1;
// }
// int green()
// {
// 	printf("\033[0;32m");
// 	return 1;
// }
// int reset()
// {
// 	printf("\033[0m");
// 	return 1;
// }
void main()
{
	int len, msqid1;
	key_t key1 = 1000;

	if ((msqid1 = msgget(key1, 0644 | IPC_CREAT)) == -1)
	{
		perror("msgget error client 1");
		exit(1);
	}

	printf("Server ready :\n");
	printf("PRESS CTRL+D to quit:\n\n");
	mq.type = 1;
	printf("You: ");
	while (fgets(mq.text, sizeof(mq.text), stdin) != NULL)
	{
		len = strlen(mq.text);
		if (mq.text[len - 1] == '\n')
			mq.text[len - 1] = '\0';
		msgsnd(msqid1, &mq, len + 1, 0);
			if (msgrcv(msqid1, &mq, sizeof(mq.text), 1, 0));
			printf("Client: ");
			printf("%s\n\n", mq.text);
			printf("You: ");			
	}
	msgctl(msqid1, IPC_RMID, NULL);

}

