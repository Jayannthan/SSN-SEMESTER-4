#include <iostream>

using namespace std;
#define max 100
typedef struct Graph *graph;
typedef struct Graph
{
    int nv;
    int am[max][max];
    int parent[max];
    int key[max];
    bool mstSet[max];
} Graph;

graph creategraph(int v)
{
    graph g = (graph)malloc(sizeof(Graph));
    g->nv = v;
    for (int i = 0; i < v; i++)
    {
        g->key[i] = INT_MAX;
        g->MST_Set[i] = false;
        for (int j = 0; j < v; j++)
        {
            g->am[i][j] = 0;
        }
    }
    g->key[0] = 0;
    g->parent[0] = -1;

    return g;
}

int minkeyindex(graph g)
{
    int minval = INT_MAX, minindex;
    for (int i = 0; i < g->nv; i++)
    {
        if (g->mstSet[i] == false and g->key[i] < minval)
        {
            minval = g->key[i];
            minindex = i;
        }
    }
    return minindex;
}

void primMST(graph g)
{
    for (int i = 0; i < g->nv; i++)
    {
        int minindex = minkeyindex(g);
        g->mstSet[minindex] = true;
        for (int j = 0; j < g->nv; j++)
        {
            if (g->am[minindex][j] and g->am[minindex][j] < g->key[j] and g->mstSet[j] == false)
            {
               g->key[j]=g->am[minindex][j];
               g->parent[j]=minindex;
            }
        }
    }
}