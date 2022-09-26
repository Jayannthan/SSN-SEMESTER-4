#include <stdlib.h>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    int n;
    cout << "Enter n:";
    cin >> n;
    bool is_prime[n + 1];
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = false;
    is_prime[1] = false;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i] && i * i <= n)
        {
            for (int j = i * i; j <= n; j += i)
            {
                is_prime[j] = false;
            }
        }
    }

    cout << "\n Prime numbers less than or equal to " << n << endl;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i])
        {
            cout << i << " ";
        }
    }

    return 0;
}
