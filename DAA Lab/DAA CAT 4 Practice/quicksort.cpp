#include <iostream>

using namespace std;
void swap(int a[], int p1, int p2)
{

    int temp = a[p1];
    a[p1] = a[p2];
    a[p2] = temp;
}

int partition(int a[], int l, int h)
{

    int pivot = a[l];
    int i = l, j = h + 1;
    while (i < j)
    {
        do
        {
            i++;
        } while (a[i] <= pivot);
        do
        {
            j--;
        } while (a[j] > pivot);
        if (i < j)
        {
            swap(a, i, j);
        }
    }
    swap(a, l, j);
    return j;
}

void quicksort(int a[], int l, int h)
{
    if (l < h)
    {

        int j = partition(a, l, h);
        quicksort(a, l, j);
        quicksort(a, j + 1, h);
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
int main(int argc, char const *argv[])
{
    int n;
    cout << "Enter size of array:";
    cin >> n;
    int a[n];
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    quicksort(a, 0, n - 1);
    printarray(a, n);
    return 0;
}
