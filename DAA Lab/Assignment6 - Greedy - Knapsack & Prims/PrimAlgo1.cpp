#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
typedef struct Graph *graph;

typedef struct Graph
{
    int nv;
    int **am;
    // Array to store constructed MST
    int *parent;
    // Key values used to pick minimum weight edge in cut
    int *key;
    // To represent set of vertices included in MST
    bool *MST_Set;
} Graph;

graph creategraph(int v)
{
    graph g = (graph)malloc(sizeof(Graph));

    g->nv = v;

    g->am = (int **)malloc(v * sizeof(int *));
    g->parent = (int *)malloc(v * sizeof(int *));
    g->key = (int *)malloc(v * sizeof(int *));
    g->MST_Set = (bool *)malloc(v * sizeof(bool *));
    for (int i = 0; i < v; i++)
    {
        g->am[i] = (int *)malloc(v * sizeof(int));
    }
    // initialising graph
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            g->am[i][j] = 0;
        }
    }

    // Initialize all keys as INFINITE
    for (int i = 0; i < v; i++)
    {
        g->key[i] = INT_MAX;
        g->MST_Set[i] = false;
    }
    g->key[0] = 0;
    g->parent[0] = -1;

    return g;
}

graph fillmatrix(graph g, int i, int j, int w)
{
    if (i < g->nv && j < g->nv)
    {
        g->am[i][j] = w;
        g->am[j][i] = w;
    }
    return g;
}

graph getgraph(graph g)
{
    char v1, v2;
    int width;
    printf("\nEdge:\n\tvertice 1:");
    scanf(" %c", &v1);
    printf("\tvertice 2:");
    scanf(" %c", &v2);
    printf("\tweight:");
    scanf("%d", &width);

    while (v1 != '0' && v2 != '0')
    {
        int vv1 = v1 - 'A';
        int vv2 = v2 - 'A';
        g = fillmatrix(g, vv1, vv2, width);
        printf("\nEdge:\n\tvertice 1:");
        scanf(" %c", &v1);
        printf("\tvertice 2:");
        scanf(" %c", &v2);
        printf("\tWidth:");
        scanf("%d", &width);
    }
    return g;
}

void printadjmat(graph g)
{
    printf("\n=====Adjacancy Matrix=====\n");
    printf("\t");
    for (int i = 0; i < g->nv; i++)
    {
        printf("%c\t", 'A' + i);
    }
    printf("\n");

    for (int i = 0; i < g->nv; i++)
    {
        printf("%c\t", 'A' + i);
        for (int j = 0; j < g->nv; j++)
        {
            printf("%d\t", g->am[i][j]);
        }
        printf("\n");
    }
}

// function to pick minimum key from vertex
int minkey(graph g)
{
    int min_val = INT_MAX;
    int min_index;
    for (int i = 0; i < g->nv; i++)
    {
        if (g->MST_Set[i] == false and g->key[i] < min_val)
        {
            min_val = g->key[i];
            min_index = i;
        }
    }
    return min_index;
}

void printMST(graph g)
{
    cout << "\n\n Edge\tWeight\n";
    for (int i = 1; i < g->nv; i++)
    {
        cout << (char)(g->parent[i] + 'A') << " - " << (char)(i + 'A') << "\t" << g->am[i][g->parent[i]] << endl;
    }
}
void primsMST(graph g)
{
    for (int i = 0; i < g->nv - 1; i++)
    {
        // picking minimum key from vertex and not included in MST
        int min_key = minkey(g);

        // set the min_key as added to MST
        g->MST_Set[min_key] = true;

        // Updating the key value and parent index of the adjacent vertices of the selected vertex
        for (int j = 0; j < g->nv; j++)
        {
            if ((g->am[min_key][j]) and (g->MST_Set[j] == false) and (g->am[min_key][j] < g->key[j]))
            {
                g->parent[j] = min_key;
                g->key[j] = g->am[min_key][j];
            }
        }
    }
    printMST(g);
}

int main(int argc, char const *argv[])
{
    int n;
    printf("\nEnter no. of vertices:");
    scanf("%d", &n);
    graph g;
    g = (graph)malloc(sizeof(Graph));
    g = NULL;
    g = creategraph(n);
    printf("\nEnter Edges(Enter '0 0 0' to exit):\n");
    g = getgraph(g);
    printadjmat(g);
    primsMST(g);
}