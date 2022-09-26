// header files#include #include #include 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <climits>
using namespace std;

typedef struct Graph * graph;

typedef struct Graph
{
	int nv;
	int **am;	// Array to store constructed Min Span Tree(adjacency matrix)
	int *parent;	// Key values used for min cut principle
	int *key;	// Vertices included in Min Span Tree
	bool *T_Set;
}
Graph;

// ----funtion to create a graph -----
graph creategraph(int v)
{
	graph g = (graph) malloc(sizeof(Graph));
	g->nv = v;
	g->am = (int **) malloc(v* sizeof(int*));
	// adjacency matrix initialisation
	g->parent = (int*) malloc(v* sizeof(int*));
	g->key = (int*) malloc(v* sizeof(int*));
	g->T_Set = (bool*) malloc(v* sizeof(bool*));
	for (int i = 0; i < v; i++)
	{
		// memory allocation
		g->am[i] = (int*) malloc(v* sizeof(int));
	}
	for (int i = 0; i < v; i++)
	{
		// adjacency matrix to 0
		for (int j = 0; j < v; j++)
		{
			g->am[i][j] = 0;
		}
	}
	for (int i = 0; i < v; i++)
	{
		// Initialize all keys as INFINITE
		g->key[i] = INT_MAX;
		g->T_Set[i] = false;
	}
	g->key[0] = 0;
	g->parent[0] = -1;
	return g;
}

// ----funtion to add edge values in the graph -----
graph fillmatrix(graph g, int i, int j, int w)
{
	if (i < g->nv && j < g->nv)
	{
		g->am[i][j] = w;
		// g->am[j][i] = w;
	}
	return g;
}

// ----function to get a graph edges -----
graph getgraph(graph g)
{
	char v1, v2;
	int width;
	printf("\nEdge ::\nVertice 1 :: ");
	cin >> v1;
	printf(" Vertice 2 :: ");
	cin >> v2;
	printf(" Weight of edge :: ");
	cin >> width;
	while (v1 != '0' && v2 != '0')
	{
		int vv1 = v1 - 'A';
		int vv2 = v2 - 'A';
		g = fillmatrix(g, vv1, vv2, width);
		printf("\nEdge ::\nVertice 1 :: ");
		cin >> v1;
		printf(" Vertice 2 :: ");
		cin >> v2;
		printf(" Weight of edge :: ");
		cin >> width;
	}
	return g;
}

int minkey(graph g)
{
	int min_val = INT_MAX;
	int min_index;
	for (int i = 0; i < g->nv; i++)
	{
		if (g->T_Set[i] == false and g->key[i] < min_val)
		{
			min_val = g->key[i];
			min_index = i;
		}
	}
	return min_index;
}

void printadj(int parent[], int des, int src)
{
	int j=des;
    do
    {
        j=parent[j];
        cout<<(char)(j+'A')<<" -> ";
    }while(parent[j]!=-1);
	cout << (char)(src + 65)<<endl;
}

void DijkstraAlgo(graph g, int src)
{
	// adjacency matrix
	int parent[g->nv];
	parent[src] = -1;
	for (int k = 0; k < g->nv; k++)
	{
		g->key[k] = INT_MAX;
		g->T_Set[k] = false;
	}
	g->key[src] = 0;	// Source vertex distance is set 0
	for (int k = 0; k < g->nv; k++)
	{
		int m = minkey(g);
		g->T_Set[m] = true;
		for (int k = 0; k < g->nv; k++)
		{
			// updating the distance of neighbouring vertex
			if (!g->T_Set[k] && g->am[m][k] && g->key[m] != INT_MAX && g->key[m] + g->am[m][k] < g->key[k])
				g->key[k] = g->key[m] + g->am[m][k];
			parent[k] = m;
		}
	}
	cout << "\n------------------------------------------\n Vertex\t\tDistance from source vertex \n------------------------------------------" << endl;
	for (int k = 0; k < g->nv; k++)
	{
		char str = 65 + k;
		cout << str << "\t\t\t" << g->key[k] << "\t";
		printadj(parent, k, src);
	}
}

int main()
{
	graph g;
	int n, src;
	char ch;
	printf("\nEnter no. of vertices:");
	cin >> n;
	g = (graph) malloc(sizeof(Graph));
	g = NULL;
	g = creategraph(n);
	printf("\nEnter the Edges (Enter '0 0 0' to exit) ::\n");
	g = getgraph(g);
	printf("Enter the source vertex :: ");
	cin >> ch;
	src = ch - 65;
	DijkstraAlgo(g, src);
	return 0;
}