#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int findStep(int n)
{
    if (n == 0)
        return 1;
    else if (n < 0)
        return 0;

    else
        return findStep(n - 3) + findStep(n - 2) + findStep(n - 1);
}

int main()
{
    int n;
    cout << "Enter no. of steps:";
    cin >> n;
    cout << "\nNo of ways:" << findStep(n);
}