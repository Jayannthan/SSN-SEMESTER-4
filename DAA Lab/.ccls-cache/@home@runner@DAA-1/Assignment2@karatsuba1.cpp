#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;

long karatsuba(long x,long y)
{
    if(x<10 and y<10)
    {
        return x*y;
    }

    long size = max(to_string(x).length(),to_string(y).length());
    int n = (int)ceil(size / 2.0);
    long p = (long)pow(10, n);
    long a = (long)floor(x / (double)p);
    long b = x % p;
    long c = (long)floor(y / (double)p);
    long d = y % p;
    long ac = karatsuba(a, c);
    long bd = karatsuba(b, d);
    long e = karatsuba(a + b, c + d) - ac - bd;
    return (long)(pow(10 * 1L, 2 * n) * ac + pow(10 * 1L, n) * e + bd);
}

int main()
{
    int a,b;
    cout<<"Enter a:";
    cin>>a;
    cout<<"Enter b:";
    cin>>b;
    cout<<a<<" * "<<b<<" = "<<karatsuba(a,b)<<endl;
    return 0;
}