#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct tableRow
{
    char name[20];
    int addr;
};
struct ListNode
{
    struct tableRow row;
    struct ListNode *next;
};
struct tree_element
{
    char name[20];
    int ftype, nc, level;
    struct tree_element *link[3];
};
typedef struct tree_element node;
void create(node **root, int lev, char *dname)
{
    int i, gap;
    if (*root == NULL)
    {
        (*root) = (node *)malloc(sizeof(node));
        printf("Enter name of dir/file(under %s) :", dname);
        scanf("%s", (*root)->name);
        printf("enter 1 for Dir/2 for file :");
        scanf("%d", &(*root)->ftype);
        (*root)->level = lev;
        for (i = 0; i < 3; i++)
            (*root)->link[i] = NULL;
        if ((*root)->ftype == 1)
        {
            printf("No of sub directories/files(for %s):", (*root)->name);
            scanf("%d", &(*root)->nc);
            for (i = 0; i < (*root)->nc; i++)
                create(&((*root)->link[i]), lev + 1, (*root)->name);
        }
        else
            (*root)->nc = 0;
    }
}
void draw(node *tree, int space)
{
    if (tree == NULL)
        return;
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("%s\n", tree->name);
    space += 5;
    draw(tree->link[1], space);
    draw(tree->link[2], space);
    draw(tree->link[0], space);
}
void append(struct ListNode **head_ref, struct tableRow row)
{
    struct ListNode *new_node = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *last = *head_ref;
    new_node->row = row;
    new_node->next = NULL;
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}

void main()
{
    srand(0);
    printf("\t\t\tFile Organization Techniques");
    struct ListNode *head = NULL;
    int size = 0;
    node *root;
    root = NULL;
    printf("\n1.Single Level Directory\n2.Tree structure directory\n");
    printf("\nEnter Choice:");
    int ch;
    scanf("%d", &ch);
    while (1)
    {
        if (ch == 1)
        {
            printf("\n1.Create a file\n2.List the files\n3.Exit\n");
            printf("\nEnter Choice:");
            int ch1;
            scanf("%d", &ch1);
            if (ch1 == 1)
            {
                struct tableRow row;
                printf("Enter file name:");
                scanf("%s", row.name);
            rando:
                row.addr = rand() % 1000;
                struct ListNode *temp = head;
                for (int i = 0; i < size; i++)
                {
                    if (strcmp(row.name, temp->row.name) == 0)
                    {
                        printf("\n\tName collision");
                        goto end;
                    }
                    if (row.addr == temp->row.addr)
                    {
                        goto rando;
                    }
                    temp = temp->next;
                }
                append(&head, row);
                size += 1;
            end:
                printf("");
            }
            else if (ch1 == 2)
            {
                printf("Contents of root directory:");
                struct ListNode *temp = head;
                for (int i = 0; i < size; i++)
                {
                    printf("\n%s %d", temp->row.name, temp->row.addr);
                    temp = temp->next;
                }
            }
            else if (ch1 == 3)
            {
                exit(0);
            }
            else
            {
                printf("Invalid Choice");
            }
        }
        else if (ch == 2)
        {
            printf("\n1.Create a file\n2.List the files\n3.Exit\n");
            printf("\nEnter Choice:");
            int ch1;
            scanf("%d", &ch1);
            if (ch1 == 1)
            {
                create(&root, 0, "root");
            }
            else if (ch1 == 2)
            {
                draw(root, 0);
            }
            else if (ch1 == 3)
            {
                exit(0);
            }
            else
            {
                printf("Invalid Choice");
            }
        }
        else if (ch == 3)
        {
            exit(0);
        }
        else
        {
            printf("Invalid Choice");
        }
    }
}
