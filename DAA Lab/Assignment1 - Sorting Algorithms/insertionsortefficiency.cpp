#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

bool checker(int a[], int n)
{
    for (int i = 1; i < n - 1; i++)
    {
        if (a[i] < a[i - 1])
        {
            return false;
        }
    }
    return true;
}

void swap(int arr[], int init, int fin)
{
    for (int i = fin; i >= init; i--)
    {
        arr[i] = arr[i - 1];
    }
}
void printarray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

void insertionSort(int a[], int n)
{
    int swaps = 0, comparison = 0;
    for (int i = 1; i < n; i++)
    {
        if (!checker(a, n))
        {
            int big = a[i];
            int j = i - 1;
            comparison++;
            while (big < a[j] && j >= 0)
            {
                swaps++;
                a[j + 1] = a[j];
                --j;
                comparison++;
            }
            a[j + 1] = big;
        }
        else
        {
            break;
        }
    }
    cout << swaps << " " << comparison << endl;
    std::ofstream myfile("insertiontemp.csv", std::ios::app);
    myfile << n << "," << (n * (n - 1)) / 2 << "," << n * n << "," << comparison << "," << swaps << endl;
    // swapcomparison[0] = swaps;
    // swapcomparison[1] = comparison;
}

int main()
{
    std::ofstream myfile("insertion.csv", std::ios::app);
    myfile << "n"
           << ","
           << "(n * (n - 1)) / 2"
           << ","
           << "n * n"
           << ","
           << "comparison"
           << ","
           << "swaps" << endl;

    for (int i = 1; i <= 1000; i++)
    {
        int n = i;
        // int swapcomparison[2] = {0, 0};
        int a[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = rand() % 10000;
        }
        cout << endl;
        cout << "Before Sort:";
        printarray(a, n);
        insertionSort(a, n);
        cout << "After Sort:";
        printarray(a, n);
        // fout << swapcomparison[0] << ", "
        //      << swapcomparison[1]
        //      << "\n";
    }
    return 0;
}