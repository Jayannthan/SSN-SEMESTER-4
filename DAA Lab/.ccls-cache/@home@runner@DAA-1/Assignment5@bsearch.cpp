#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

int bsearch(int a[],int beg,int last,int size,int key,int check[])
{
    if(beg>last)
    {
        return -1;
    }
    else
    {
        int mid=(beg+last)/2;
        if(a[mid]==key)
        {
            return mid+1;
        }
        else if(a[mid]<key)
        {
            check[0]++;
            return bsearch(a,mid+1,last,size,key,check);
        }
        else
        {
            check[0]++;
            return bsearch(a,beg,mid-1,size,key,check);
        }
    }
}

int main()
{
    for(int i=1;i<=5000;i++)
    {
        int n=i;
        int check[1]={0};
        int a[n];
        for(int i=0;i<n;i++)
        {
            a[i]=rand()%10000;
        }
        int key=rand()%10000;;
        cout<<endl;
        int pos=bsearch(a,0,n-1,n,key,check);
        if(pos==-1)
        {
            cout<<"\nNot Found"<<endl;
        }
        else
        {
            cout<<"\n"<<key<<" found at position: "<<pos<<endl;
        }
        std::ofstream myfile("op.csv",std::ios::app);
        myfile<<n<<","<<check[0]<<endl;
    }
    // int n;
    // cout<<"Enter no. of Elements in array:";
    // cin>>n;
    // int a[n];
    // cout<<"Enter Elements of array:";
    // for(int i=0;i<n;i++)
    // {
    //     cin>>a[i];
    // }
    // int key;
    // cout<<"Enter key to search:";
    // cin>>key;

    // int pos=bsearch(a,0,n-1,n,key);
    // if(pos==-1)
    // {
    //     cout<<"\nNot Found"<<endl;
    // }
    // else
    // {
    //     cout<<"\n"<<key<<" found at position: "<<pos<<endl;
    // }
    
    return 0;
}