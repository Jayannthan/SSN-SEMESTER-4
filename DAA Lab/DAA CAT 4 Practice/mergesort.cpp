#include <iostream>

using namespace std;
void merge(int a[], int l, int mid, int h)
{
    int leftsize = mid - l + 1, rightsize = h - mid;
    int lefta[leftsize], righta[rightsize];
    for (int i = 0; i < leftsize; i++)
    {
        lefta[i] = a[l + i];
    }
    for (int i = 0; i < rightsize; i++)
    {
        righta[i] = a[mid + i + 1];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < leftsize and j < rightsize)
    {
        if (lefta[i] <= righta[j])
        {
            a[k] = lefta[i];
            i++;
        }
        else
        {
            a[k] = righta[j];
            j++;
        }
        k++;    
    }
    while (i < leftsize)
    {
        a[k] = lefta[i];
        i++;
        k++;
    }
    while (j < rightsize)
    {
        a[k] = righta[j];
        j++;
        k++;
    }
}
void mergesort(int a[], int l, int h)
{
    if (l < h)
    {
        int mid = (l + h) / 2;
        mergesort(a, l, mid);
        mergesort(a, mid + 1, h);
        merge(a, l, mid, h);
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
    mergesort(a, 0, n - 1);
    printarray(a, n);
    return 0;
}