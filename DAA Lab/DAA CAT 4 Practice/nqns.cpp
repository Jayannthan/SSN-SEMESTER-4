
#include <iostream>
#include <vector>
using namespace std;

bool safe(int r, int c, vector<vector<int>> &graph)
{
    int tr = r, tc = c;
    while (tr >= 0 && tc >= 0)
    {
        if (graph[tr][tc] == 1)
        {
            return false;
        }
        tr--;
        tc--;
    }
    tr = r;
    tc = c;
    while (tc >= 0)
    {
        if (graph[tr][tc] == 1)
        {
            return false;
        }
        tc--;
    }
    tr = r;
    tc = c;
    while (tr < 8 && tc >= 0)
    {
        if (graph[tr][tc] == 1)
        {
            return false;
        }
        tr++;
        tc--;
    }

    return true;
}

bool place(int col, vector<vector<int>> &graph)
{
    if (col == 8)
    {
        return true;
    }
    for (int i = 0; i < 8; i++)
    {
        if (safe(i, col, graph))
        {
            graph[i][col] = 1;
            if (place(col + 1, graph))
            {
                return true;
            }
            graph[i][col] = 0;
        }
    }
    return false;
}

int main()
{
    vector<vector<int>> graph(8, vector<int>(8, 0));
    if (place(0, graph))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
    }
}