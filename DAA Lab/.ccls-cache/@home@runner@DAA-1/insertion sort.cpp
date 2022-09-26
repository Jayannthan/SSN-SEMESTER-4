#include <bits/stdc++.h>
#include <iostream>

using namespace std;

void swap(int a[],int init, int fin)
{
    for(int i=fin;i>init;i--)
        {
            int a[i]=a[i-1];
        }
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
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    for(int i=i;i<n-1;i++)
    {
        int key=a[i];
            
    }
    cout<<"After Sort:";
    for(int i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    return 0;
}