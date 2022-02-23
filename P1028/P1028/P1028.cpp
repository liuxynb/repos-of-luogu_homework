#include<stdio.h>

long long matrix[1001] = { 1,1,2 };
void f(int n);

int main(void)
{
	int n;
	scanf("%d", &n);
	f(n);
	printf("%d", matrix[n]);
	return 0;
}

void f(int n)//递推
{
	for (int i = 1; i <= n; i++)
	{
		if (i % 2==0)matrix[i] = matrix[i - 1] + matrix[i >> 1];
		else matrix[i] = matrix[i - 1];
	}
}