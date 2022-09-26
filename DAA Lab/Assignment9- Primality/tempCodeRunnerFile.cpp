#include <stdlib.h>
#include <iostream>
using namespace std;
long long binpow(long long a, long long b, long long m)
{
    a %= m;
    long long rem = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            rem = rem * a % m;
        }
        a = a * a % m;
        b = b / 2;
    }
    return rem;
}

int main(int argc, char const *argv[])
{
    long long a, b, m;
    cout << "Enter a:";
    cin >> a;
    cout << "Enter b:";
    cin >> b;
    cout << "Enter m:";
    cin >> m;
    cout << a << "^" << b << " mod " << m << " = " << binpow(a, b, m);
    return 0;
}
