#include <stdio.h>
#include <pthread.h>
int arr[50], n, i;

void *th1()
{
	float sum = 0;
	float average;
	
	for (i = 0; i < n; i++)
	{
		sum = sum + arr[i];
	}
	average = sum / n;
	printf("The average value is:%f", average);
}
void *th2()
{

	int temp = arr[0];
	for (int i = 1; i < n; i++)
	{
		if (temp > arr[i])
		{
			temp = arr[i];
		}
	}
	printf("\nThe Minimum  value is:=%d", temp);
}
void *th3()
{

	int temp = arr[0];
	for (int i = 1; i < n; i++)
	{
		if (temp < arr[i])
		{
			temp = arr[i];
		}
	}
	printf("\nThe Maximum  value is:=%d\n", temp);
}
int main(int argc,int argv[])
{
	n=argc-1;
	for (i = 0; i < n; i++)
	{
		arr[i]=atoi(argv[i+1]);
	}
	pthread_t t1,t2,t3;
	n = pthread_create(&t1, NULL, &th1, NULL);
	pthread_join(t1, NULL);
	n = pthread_create(&t2, NULL, &th2, NULL);
	pthread_join(t2, NULL);
	n = pthread_create(&t3, NULL, &th3, NULL);
	pthread_join(t3, NULL);
}
