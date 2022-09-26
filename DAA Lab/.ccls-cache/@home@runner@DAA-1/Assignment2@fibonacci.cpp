#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int fibonaccirec(int n)
{
    if ((n == 1) || (n == 0))
    {
        return (n);
    }
    else
    {
        return (fibonaccirec(n - 1) + fibonaccirec(n - 2));
    }
}
void fibreccaller(int n)
{
    int i = 0;
    while (i < n)
    {
        cout << " " << fibonaccirec(i);
        i++;
    }
}
void fibiter(int n)
{
    int x = 0, y = 1, z = 0;
    for (int i = 0; i < n; i++)
    {
        cout << x << " ";
        z = x + y;
        x = y;
        y = z;
    }
}
double PHI = 1.6180339;
int f[6] = {0, 1, 1, 2, 3, 5};
int fibgolden(int n)
{
    if (n < 6)
        return f[n];
    int t = 5, fn = 5;
    while (t < n)
    {
        fn = round(fn * PHI);
        t++;
    }
    return fn;
}
void fibgolcaller(int n)
{
    int i = 0;
    while (i < n)
    {
        cout << " " << fibgolden(i);
        i++;
    }
}

int main()
{
    int n;
    cout << "Enter no. of numbbers in fib. series:";
    cin >> n;
    cout << "\nRecursive:";
    fibreccaller(n);
    cout << "\nIterative:";
    fibiter(n);
    cout << "\nGolden Ratio:";
    fibgolcaller(n);
}