// Implement Merge Sort and call insertion sort for n=12, instead of recursive calls.

#include <iostream>
using namespace std;

void display(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void display_specific(int *array, int b, int l)
{
    for (int i = b; i < l; i++)
        cout << array[i] << " ";
    cout << endl;
}

void merge(int *array, int l, int m, int r)
{
    for (int i = l; i <= r; i++)
    {
        int big = array[i];
        int j = i - 1;

        while (big < array[j] && j >= l)
        {

            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = big;
    }
    cout << endl;
    cout << "Left:";
    display_specific(array, l, m + 1);
    cout << "Right:";
    display_specific(array, m + 1, r + 1);
    cout << "Merged:";
    display_specific(array, l, r + 1);
}
void mergeSort(int *array, int l, int r)
{
    int m;
    if (l < r)
    {
        int m = l + (r - l) / 2;

        cout << "\nDividing array:";
        display_specific(array, l, r + 1);
        cout << "into ";
        display_specific(array, l, m + 1);
        cout << "and ";
        display_specific(array, m + 1, r + 1);

        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}
int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    int arr[n];
    cout << "Enter elements:" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << "Array before Sorting: ";
    display(arr, n);
    mergeSort(arr, 0, n - 1);
    cout << endl;
    cout << "Array after Sorting: ";
    display(arr, n);
}