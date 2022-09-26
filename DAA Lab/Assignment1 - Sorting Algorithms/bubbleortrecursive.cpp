#include <iostream>
#include <fstream>

using namespace std;
void bubblesortrecursive(int a[], int n)
{
	if (n == 1)
	{
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (a[i] > a[i + 1])
		{
			swap(a[i], a[i + 1]);
		}
	}
	bubblesortrecursive(a, n - 1);
}

int main()
{
	// int n = 100;
	for (int i = 1; i <= 5; i++)
	{
		int a[i];
		for (int j = 0; j < i; j++)
		{
			a[j] = rand() % 10000;
		}
		bubblesortrecursive(a, i);
		for (int j = 0; j < i; j++)
		{
			cout << a[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
