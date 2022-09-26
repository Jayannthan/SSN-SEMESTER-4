#include <bits/stdc++.h>
using namespace std;

bool arraymaker(int n, unordered_set<int> &s)
{
    if (n == 1)
    {
        return true;
    }

    if (s.find(n) != s.end())
    {
        return false;
    }

    s.insert(n);

    if (n % 2)
    {
        return arraymaker(3 * n + 1, s);
    }
    else
    {
        return arraymaker(n / 2, s);
    }
}

bool checker(int n)
{
    unordered_set<int> s;
    return arraymaker(n, s);
}

int main()
{
    int n;
    cout << "Enter no.:";
    cin >> n;
    if (checker)
    {
        cout << "Yes";
    }
    else
    {
        cout << "NO";
    }
    return 0;
}
