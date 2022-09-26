#include <bits/stdc++.h>
#include <iostream>

using namespace std;

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
                }
            a[smallpos]=a[i];
            a[i]=small;
        }
    cout<<"After Sort:";
    for(int i=0;i<n;i++)
        {
            cout<<a[i]<<" ";
        }
    cout<<endl;
    return 0;
}