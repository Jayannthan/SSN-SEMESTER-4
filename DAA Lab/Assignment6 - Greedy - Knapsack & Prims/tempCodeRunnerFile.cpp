#include <bits/stdc++.h>
using namespace std;

int KNAPSACK(int W, int v[], int w[], int n)
{
    vector<vector<int>> F(n + 1, vector<int>(W + 1));

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            if (i == 0 || j == 0)
            {
                F[i][j] = 0;
            }
            else if (w[i - 1] <= j)
            {
                F[i][j] = max(F[i - 1][j], v[i - 1] + F[i - 1][j - w[i - 1]]);
            }
            else
            {
                F[i][j] = F[i - 1][j];
            }
        }
    }
    return F[n][W];
}

int main()
{
    int n;
    cout << "\nEnter no. of items:";
    cin >> n;

    int v[n], w[n];
    for (int i = 0; i < n; i++)
    {
        cout << "\nItem " << i + 1 << endl;
        cout << "\tWeight:";
        cin >> w[i];
        cout << "\tValue:";
        cin >> v[i];
    }

    int W;
    cout << "Enter MAX Weight:";
    cin >> W;

    cout << "\nMaximum Value you can carry = " << KNAPSACK(W, v, w, n);

    return 0;
}
