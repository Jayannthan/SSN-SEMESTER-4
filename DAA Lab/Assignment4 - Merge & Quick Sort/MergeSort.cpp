    // Implement Merge Sort and take a snapshot of the function calling stack and recursive depth

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
    int size_left, size_right;

    size_left = m - l + 1;
    size_right = r - m;

    int left_array[size_left], right_array[size_right];

    for (int i = 0; i < size_left; i++)
        left_array[i] = array[l + i];

    for (int j = 0; j < size_right; j++)
        right_array[j] = array[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < size_left && j < size_right)
    {
        if (left_array[i] <= right_array[j])
        {
            array[k] = left_array[i];
            i++;
        }
        else
        {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }
    while (i < size_left)
    {
        array[k] = left_array[i];
        i++;
        k++;
    }
    while (j < size_right)
    {
        array[k] = right_array[j];
        j++;
        k++;
    }
    cout << endl;
    cout << "Left:";
    display(left_array, size_left);
    cout << "Right:";
    display(right_array, size_right);
    cout << "Merged:";
    display_specific(array, l, k);
}
void mergeSort(int *array, int l, int r)
{
    int m;
    if (l < r)
    {
        int m = (l + (r - l)) / 2;

        cout << "\nDividing array:";
        display_specific(array, l, r+1);
        cout << "into ";
        display_specific(array, l, m+1);
        cout << "and ";
        display_specific(array, m + 1, r+1);

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