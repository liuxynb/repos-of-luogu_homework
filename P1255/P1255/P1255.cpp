#include<stdio.h>

int matrix[5002][5002];//用于高精度计算。
int len = 1 , N;

void fib(int x);

int main(void)
{
	scanf("%d", &N);
	matrix[1][1] = 1;
	matrix[2][1] = 2;
	for (int i = 3; i <= N; i++)
	{
		fib(i);
	}
	for (int i = len; i > 0; i--)
	{
		printf("%d", matrix[N][i]);
	}
	return 0;
}
void fib(int x)
{
	int up_add = 0;
	for (int i = 1; i <= len; i++)
	{
		matrix[x][i] += matrix[x - 1][i] + matrix[x - 2][i];
		up_add = matrix[x][i] / 10;
		matrix[x][i] %= 10;
		matrix[x][i + 1] += up_add;
	}
	if (up_add)len++;

	//while (matrix[x][len] == 0)
	//	if (len > 0)len--;
	

}