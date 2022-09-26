#include <bits/stdc++.h>
#include <iostream>

using namespace std;
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
    for(int i=0;i<n-1;i++)
    {
        int small=a[i];
        int smallpos=i;
        
        for(int j=0;j<n;j++)
        {
            if(a[j]<small)
            {
                small=a[j];
                smallpos=j;
            }
            printarray(a,n);
        }
        a[smallpos]=a[i];
        a[i]=small;
    }
    cout<<"After Sort:";
    printarray(a,n);
    return 0;
}