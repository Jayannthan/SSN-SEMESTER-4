#include <iostream>
using namespace std;

int knapsackdp(int v[], int wt[], int n, int m)
{
    int k[n + 1][m + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i == 0 or j == 0)
            {
                k[i][j] = 0;
            }
            else if (j - wt[i] >= 0) 
            {
                k[i][j] = max(k[i - 1][j], v[i] + k[i - 1][j - wt[i]]);
            }
            else
            {
                k[i][j] = k[i - 1][j];
            }
        }
    }
    return k[n][m];
}

int main(int argc, char const *argv[])6
{
    int n;
    cout << "\nEnter no. of elements:";
    cin >> n;
    int v[n + 1], wt[n + 1];
    v[0] = 0, wt[0] = 0;
    for (int i = 1; i < n + 1; i++)
    {
        cout << "\nObject " << i << endl;
        cout << "\tProfit:";
        cin >> v[i];
        cout << "\tWeight:";
        cin >> wt[i];
    }
    int m;
    cout << "\n\nEnter Maximum Capacity:";
    cin >> m;
    cout << endl
         << knapsackdp(v, wt, n, m);
    return 0;
}
