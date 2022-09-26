#include <bits/stdc++.h>
using namespace std;

int BinCoeff(int n, int k)
{
    if(n<k)
    {
        return 0;
    }
    vector<vector<int>> C(n+1, vector<int>(n+1));
    for (int i = 0; i <= n; i++)
    { 
        for (int j = 0; j <= min(i,k); j++)
        {
            if (j == 0 or j == i)
            {
                C[i][j] = 1;
            }
            else
            {
                C[i][j] = C[i-1][j]+C[i-1][j-1];
            }
        }
    }
    return C[n][k];
}


int main()
{
    int n;
    cout << "\nEnter no. of terms in expression:";
    cin >> n;
    int k;

    cout << "Enter term to find coefficient:";
    cin >> k;

    cout << "\n" <<n<<"C"<<k<<" = "<< BinCoeff(n,k)<<endl;
    return 0;
}
