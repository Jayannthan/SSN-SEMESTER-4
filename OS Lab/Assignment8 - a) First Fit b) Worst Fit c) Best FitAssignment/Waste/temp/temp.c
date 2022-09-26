#include <stdio.h>
#include <string.h>
int main()
{
	int a[]={1,2,3,4,5,6,7,8,9,10};
	for(int i=0;i<10;i++) printf(" %d ",a[i]);
	memmove(a+5,a+6,sizeof(a)/sizeof(int));
	printf("\n");
	for(int i=0;i<sizeof(a)/sizeof(int)-1;i++) printf(" %d ",a[i]);
	return 0;
}
