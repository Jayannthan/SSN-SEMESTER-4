#include <iostream>
#include <fstream>

using namespace std;
void bubblesort(int a[], int n)
{
	// int a[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 10000;
	}
	cout << '\n';
	int comparison = 0, swaps = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			comparison++;
			if (a[j] > a[j + 1])
			{
				swaps++;
				swap(a[j], a[j + 1]);
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << '\n';
	std::ofstream myfile("bubblesort.csv", std::ios::app);
	myfile << n << "," << (n * (n - 1)) / 2 << "," << n * n << "," << comparison << "," << swaps << "\n";
	cout << n << " " << swaps << '\n';
	myfile.close();
}

int main()
{
	// int n = 100;
	for (int i = 1; i <= 1000; i++)
	{
		int a[i];
		bubblesort(a, i);
	}
	return 0;
}
