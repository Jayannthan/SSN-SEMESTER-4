#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
// #include <bits/stdc++>
#include <climits>
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
    // To represent set of vertices included in graph
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

    return g;
}

graph fillmatrix(graph g, int i, int j)
{
    if (i < g->nv && j < g->nv)
    {
        g->am[i][j] = 1;
        // g->am[j][i] = w;
    }
    return g;
}

graph getgraph(graph g)
{
    char v1, v2;
    int width;
    printf("\nEdge:\n\tvertice 1:");
    cin>>v1;
    printf("\tvertice 2:");
    cin>>v2;
    // printf("\tweight:");
    // scanf("%d", &width);

    while (v1 != '0' && v2 != '0')
    {
        int vv1 = v1 - 'A';
        int vv2 = v2 - 'A'; 
        g = fillmatrix(g, vv1, vv2);
        printf("\nEdge:\n\tvertice 1:");
        cin>>v1;
        printf("\tvertice 2:");
        cin>>v2;
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

// void putdata(int *r[],int nv)
// {
    
// }

void warshall(graph g)
{
    int r[g->nv][g->nv][g->nv];
    for (int k= 0; k < g->nv; ++k)
    {
        for (int i = 0; i < g->nv; ++i)
        {
            for (int j = 0; j < g->nv; ++j)
            {
                if (k==0)
                {
                    r[k][i][j]=g->am[i][j];
                }
                else
                {
                    if (r[k-1][i][j]==1 or (r[k-1][i][k]==1 and r[k-1][i][k]==1))
                    {
                        r[k][i][j]=1;
                    }
                    else
                    {
                        r[k][i][j]=0;
                    }
                }
            }
        }
    }
    for (int i = 0; i < g->nv; ++i)
    {
        cout<<"Path from "<< (char)(i+65) <<"you can go to:";
        for (int j = 0; j < g->nv; ++j)
        {
            if (r[g->nv-1][i][j]==1)
            {
                cout<<(char)(j+65);
            }
        }
        cout<<endl;
    }
}

int main(int argc, char const *argv[])
{
    int n;
    printf("\nEnter no. of vertices:");
    cin>>n;
    graph g;
    g = (graph)malloc(sizeof(Graph));
    g = NULL;
    g = creategraph(n);
    printf("\nEnter Edges(Enter '0 0 0' to exit):\n");
    g = getgraph(g);
    printadjmat(g);
    warshall(g);
}
