#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct File
{
	char fname[25];
	int sad;
	int flag;
	char parent[25];
	char label[2];
};
struct SLD
{
	int no_files;
	struct File *F[30];
};
struct RootDirectory
{
	struct File *D[30];
	int n_file;
};
void SingleLevel(struct SLD *S)
{
	int opt = 0, cnt = 0;
	char fname[25];
	static int ind = 0;
	while (opt != 3)
	{
		printf("\n\n1.Create a file\n2.List the files\n3.Exit\n\nEnter your option: ");
		scanf("%d", &opt);
		if (opt == 1)
		{
			printf("\nEnter the name of the file: ");
			scanf("%s", fname);
			for (int i = 0; i < S->no_files; i++)
				if (strcmp(fname, S->F[i]->fname) == 0)
				{
					printf("\nError: File already exists with the same name!\n");
					cnt = 1;
				}
			if (cnt != 1)
			{
				strcpy(S->F[S->no_files]->fname, fname);
				S->F[S->no_files]->sad = rand();
				S->F[S->no_files]->flag = 1;
				printf("\nFile created! ");
				S->no_files++;
			}
		}
		else if (opt == 2)
		{
			printf("\nContents of root directory:");
			printf("\n\nFileName\t\t\t\tLocation\n");
			for (int i = 0; i < S->no_files; i++)
				if (S->F[i]->flag == 1)
					printf("\n %s\t\t\t\t\t%d", S->F[i]->fname, S->F[i]->sad);
		}
		else if (opt == 3)
			exit(0);
		else
			printf("\nEnter a valid option!\n");
	}
}
void STree(struct RootDirectory *R)
{
	int opt;
	char dName[25], dn[25];
	printf("\n\nTREE STRUCTURES DIRECTORY ");
	strcpy(R->D[R->n_file]->fname, "Home");
	R->D[R->n_file]->flag = 0;
	R->D[R->n_file]->sad = rand();
	strcpy(R->D[R->n_file]->parent, "Root");
	R->n_file++;
	strcpy(R->D[R->n_file]->fname, "User");
	R->D[R->n_file]->flag = 0;
	R->D[R->n_file]->sad = rand();
	strcpy(R->D[R->n_file]->parent, "Root");
	R->n_file++;
	strcpy(R->D[R->n_file]->fname, "Programs");
	R->D[R->n_file]->flag = 0;
	R->D[R->n_file]->sad = rand();
	strcpy(R->D[R->n_file]->parent, "Root");
	R->n_file++;
	while (opt != 4)
	{
		printf("\n\n1.Create Directory\n2.Create File\n3.List files\n4.Exit\n\nEnter your option: ");
		scanf("%d", &opt);
		if (opt == 1)
		{
			printf("\nROOT->\n\t\t~Home\n\t\t~User\n\t\t~Programs");
			printf("\n\nChoose a Directory: ");
			scanf("%s", dName);
			for (int i = 0; i < R->n_file; i++)
				if (strcmp(R->D[i]->fname, dName) == 0)
				{
					if (R->D[i]->flag >= 5)
					{
						printf("\n\nError: Cannot create,Directory Full");
						break;
					}
					else
					{
						printf("\n\nEnter Name: ");
						scanf("%s", R->D[R->n_file]->fname);
						strcpy(R->D[R->n_file]->label, "d");
						R->D[R->n_file]->flag = 1;
						strcpy(R->D[R->n_file]->parent, dName);
						R->D[R->n_file]->sad = rand();
						R->n_file++;
						break;
					}
				}
		}
		else if (opt == 2)
		{
			printf("\nROOT->\n\t\t~Home\n\t\t~User\n\t\t~Programs");
			printf("\n\nChoose a Directory: ");
			scanf("%s", dName);
			strcpy(dn, dName);
			printf("\n\t%s->", dName);
			for (int i = 0; i < R->n_file; i++)
				if (strcmp(R->D[i]->parent, dName) == 0)
					printf("\n\t\t\t~%s", R->D[i]->fname);
			printf("\n\nChoose a Directory or None : ");
			scanf("%s", dName);
			if (strcmp(dName, "None") == 0)
			{
				printf("\n\nEnter Name: ");
				scanf("%s", R->D[R->n_file]->fname);
				strcpy(R->D[R->n_file]->label, "f");
				R->D[R->n_file]->flag = 1;
				strcpy(R->D[R->n_file]->parent, dn);
				R->D[R->n_file]->sad = rand();
				R->n_file++;
			}
			else
			{
				printf("\n\nEnter Name: ");
				scanf("%s", R->D[R->n_file]->fname);
				strcpy(R->D[R->n_file]->label, "f");
				R->D[R->n_file]->flag = 1;
				strcpy(R->D[R->n_file]->parent, dName);
				R->D[R->n_file]->sad = rand();
				R->n_file++;
			}
		}
		else if (opt == 3)
		{
			printf("\n\n~HOME->");
			for (int i = 0; i < R->n_file; i++)
				if (strcmp(R->D[i]->parent, "Home") == 0)
				{
					printf("\n\t\t-%s:/%s", R->D[i]->label, R->D[i]->fname);
					for (int j = 0; j < R->n_file; j++)
						if (strcmp(R->D[j]->parent, R->D[i]->fname) == 0)
							printf("\n\t\t\t\t\t-%s:/%s", R->D[j]->label, R->D[j]->fname);
				}
			printf("\n\n~USER->");
			for (int i = 0; i < R->n_file; i++)
				if (strcmp(R->D[i]->parent, "User") == 0)
				{
					printf("\n\t\t-%s:/%s", R->D[i]->label, R->D[i]->fname);
					for (int j = 0; j < R->n_file; j++)
						if (strcmp(R->D[j]->parent, R->D[i]->fname) == 0)
							printf("\n\t\t\t\t\t-%s:/%s", R->D[j]->label, R->D[j]->fname);
				}
			printf("\n\n~PROGRAMS->");
			for (int i = 0; i < R->n_file; i++)
				if (strcmp(R->D[i]->parent, "Programs") == 0)
				{
					printf("\n\t\t-%s:/%s", R->D[i]->label, R->D[i]->fname);
					for (int j = 0; j < R->n_file; j++)
						if (strcmp(R->D[j]->parent, R->D[i]->fname) == 0)
							printf("\n\t\t\t\t\t-%s:/%s", R->D[j]->label, R->D[j]->fname);
				}
		}
	}
}
int main()
{
	int n, choice;
	printf("\n\t\t\tFILE ORGANIZATION TECHNIQUES");
	struct SLD *S = (struct SLD *)malloc(sizeof(struct SLD));
	struct RootDirectory *R = (struct RootDirectory *)malloc(sizeof(struct RootDirectory));
	for (int i = 0; i < 30; i++)
	{
		S->F[i] = (struct File *)malloc(sizeof(struct File));
		R->D[i] = (struct File *)malloc(sizeof(struct File));
	}
	printf("\n\n1.Single Level Directory\n2.Tree structures directory\n\nEnter your option: ");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		SingleLevel(S);
		break;
	case 2:
		STree(R);
		break;
	}
	return 0;
}
