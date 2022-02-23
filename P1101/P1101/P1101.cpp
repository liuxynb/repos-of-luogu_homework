#include<stdio.h>

char str[] = { "yizhong" };
int step[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
char matrix[101][101];
int ans[101][101] = { 0 };//判断数组初始化。

void dfs(int dx, int dy, int i, int j, int cnt,int len);

int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", matrix[i]);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 'y')
			{
				for (int k = 0; k < 8; k++)
				{
					if (matrix[i + step[k][0]][j + step[k][1]]=='i')
					{
						dfs(step[k][0], step[k][1], i, j, 0, n);
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (ans[i][j])
				printf("%c", matrix[i][j]);
			else
				putchar('*');
		}
		if (i != n - 1)putchar('\n');
	}
}

void dfs(int dx, int dy, int m, int n, int cnt,int len)
{
	if(cnt==7)
	{
		for (int i = 1; i <= 7; i++)
		{
			ans[m - dx * i][n - dy * i] = 1;
		}
	}
	if (m >= 0 && m < len && n >= 0 && n < len)
	{
		if (matrix[m][n] == str[cnt])
		{
			dfs(dx, dy, m + dx, n + dy, cnt + 1, len);
		}
	}
}