#include <bits/stdc++.h>
#include <iostream>

using namespace std;

void swap(int arr[],int init, int fin)
{
    for(int i=fin;i>=init;i--)
    {
        arr[i]=arr[i-1];
    }
}
void printarray(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    cout<<endl;
    
    cout<<"Before Sort:";
    printarray(a,n);
    for(int i=i;i<n-1;i++)
    {
        int small=a[i];
        int smallpos=i;
        for(int j = i+1; j<n;j++)
        {
            if(a[j]<small)
            {
                small=a[j];
                smallpos=j;
            }
            
        }
        if(i!=smallpos)
        {
            swap(a,i,smallpos);
            a[i]=small;
        }
        printarray(a,n);
    }
    cout<<"After Sort:";
    printarray(a,n);
    return 0;
}