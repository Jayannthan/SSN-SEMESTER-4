#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

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

void insertionSortrecursive(int a[], int n)
{
    if (n == 1)
    {
        return;
    }

    insertionSortrecursive(a, n - 1);
    int last = a[n - 1];
    int j = n - 2;
    while (j > 0 and a[j] > last)
    {
        a[j + 1] = a[j];
        j--;
    }
    a[j + 1] = last;
}

int main()
{
    // std::ofstream myfile("insertion.csv", std::ios::app);
    // myfile << "n"
    //        << ","
    //        << "(n * (n - 1)) / 2"
    //        << ","
    //        << "n * n"
    //        << ","
    //        << "comparison"
    //        << ","
    //        << "swaps" << endl;

    for (int i = 1; i <= 1000; i++)
    {
        int n = i;
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
    }
    return 0;
}