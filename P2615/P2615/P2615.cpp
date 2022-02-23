#include<stdio.h>
#define N 40
int main(void)
{
	int n;
	scanf("%d", &n);
	int matrix[N][N]={0}, column = n / 2, row = 0;
	matrix[row][column] = 1;
	for (int i = 2; i <= n * n; i++)
	{
		if (row == 0 && column != n - 1) 
		{
			row = n - 1;
			column++;
			matrix[row][column] = i;
		}
		else if (row != 0 && column == n - 1)
		{
			row--;
			column = 0;
			matrix[row][column] = i;
		}
		else if (row == 0 && column == n - 1)
		{
			row++;
			matrix[row][column] = i;
		}
		else
		{
			if (matrix[row-1][column+1] == 0)
			{
				row--;
				column++;
				matrix[row][column] = i;
			}
			else
			{
				row++;
				matrix[row][column] = i;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d", matrix[i][j]);
			putchar(' ');
		}
		putchar('\n');
	}
}