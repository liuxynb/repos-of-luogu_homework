#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int N;
	int num[100];
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &num[i]);
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = i; j < N; j++)
		{
			if (num[i] > num[j])
			{
				int swap = num[i];
				num[i] = num[j];
				num[j] = swap;
			}
		}
	}
	int temp = 0, ans[100];
	for (int i = 0; i < N; i++)
	{
		if (i > 0)
		{
			if (num[i] != num[i - 1])
				ans[temp++] = num[i];
		}
		else
			ans[temp++] = num[i];
	}
	printf("%d\n", temp);
	for (int i = 0; i < temp; i++)
	{
		printf("%d", ans[i]);
		if (i != temp - 1)
			putchar(' ');
	}
}