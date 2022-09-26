#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

long karatsuba(long x, long y)
{
	if (x < 10 and y < 10)
	{
		return x * y;
	}
	int size = max(to_string(x).length(), to_string(y).length());
	int n = ceil(size / 2);
	long p = pow(10, n);
	long a, b, c, d, e, ac, bd;
	a = floor(x / p);
	c = floor(y / p);
	b = x % p;
	d = y % p;
	ac = karatsuba(a, c);
	bd = karatsuba(b, d);
	e = karatsuba(a + b, c + d) - ac - bd;

	return (ac * pow(10, 2 * n) + bd + e * pow(10, n));
}

int main(int argc, char const *argv[])
{
	int a = 123;
	int b = 12345;
	cout << karatsuba(a, b);
	return 0;
}
