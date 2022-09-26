#include <stdio.h>
#include <pthread.h>
int arr[50], n, i;

void *calc_avg()
{
	float sum = 0;
	float average;
	/*printf("enter size:");
	scanf("%d", &n);
	printf("\nenter array elements:\n");
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}*/
	for (i = 0; i < n; i++)
	{
		sum = sum + arr[i];
	}
	average = sum / n;
	printf("The average value is:%.2f", average);
}
void *calc_min()
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
void *calc_max()
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
int main(int argc,char* argv[])
{
	int m;
	n=argc-1;
	for (i = 0; i < n; i++)
	{
		arr[i]=atoi(argv[i+1]);
	}
	pthread_t t;
	m = pthread_create(&t, NULL, &calc_avg, NULL);
	pthread_join(t, NULL);
	m = pthread_create(&t, NULL, &calc_min, NULL);
	pthread_join(t, NULL);
	m = pthread_create(&t, NULL, &calc_max, NULL);
	pthread_join(t, NULL);
}
