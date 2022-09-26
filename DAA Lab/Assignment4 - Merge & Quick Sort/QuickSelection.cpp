// Implement QuickSelection

#include <iostream>
using namespace std;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void display(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

int partition(int *array, int low, int high)
{
    int pivot = array[high];

    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

int quickSelect(int array[], int low, int high, int k)
{
    if ((low < high) and (k > 0) and (k < high - low + 1))
    {
        int pi = partition(array, low, high);
        if ((pi - low) == (k - 1))
        {
            return array[pi];
        }
        if (pi - low > k - 1)
        {
            return quickSelect(array, low, pi - 1, k);
        }
        return quickSelect(array, pi + 1, high, k - pi + low - 1);
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
    int k;
    int choice;
    cout << "Menu:\n\t1.Kth Smallest Element\n\t2.Kth Largest Element\nEnter Choice:";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Enter k to find kth smallest element in array: ";
        cin >> k;
        cout << "K-th Smallest Element is " << quickSelect(arr, 0, n - 1, k);
        break;

    case 2:
        cout << "Enter k to find kth largest element in array: ";
        cin >> k;
        cout << "K-th Largest Element is " << quickSelect(arr, 0, n - 1, n - k + 1);
        break;

    default:
        return 0;
        break;
    }
}