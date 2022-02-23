#include<stdio.h>
int num[100001];
void quickSort(int left, int right);
int main(void)
{
	int n ;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);
	quickSort(0, n - 1);
	for (int i = 0; i < n; i++)
	{
		printf("%d", num[i]);
		if (i < n - 1)putchar(' ');
	}
	return 0;
}

void quickSort(int left, int right)
{
	int mid = num[(left + right) / 2];
	int i = left, j = right;
	while (i<=j)
	{
		while (num[i] < mid)
			i++;
		while (num[j] > mid)
			j--;
		if (i <= j)
		{
			int swap = num[i];
			num[i] = num[j];
			num[j] = swap;
			i++, j--;
		}
	}
	if (i < right)quickSort(i, right);
	if (j > left)quickSort(left, j);
}
