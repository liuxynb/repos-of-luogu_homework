#include<stdio.h>

int step[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
int index[100][100], ans, token[100][100];
int n, m;//表示了数字矩阵为N行M列。

void dfs(int x, int y, int max);
int judge(int x, int y);

int main(void)
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &index[i][j]);
		ans = 0;
		dfs(0, -1, 0);
		printf("%d\n", ans);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				index[i][j] = token[i][j] = 0;
	}
}

void dfs(int x, int y,int sum)
{
	if (x >= n)
	{
		ans = (ans > sum) ? ans : sum;
		return;
	}
	int xp = x, yp = y + 1;
	if (yp >= m)
		xp = x + 1, yp = 0;
	if (judge(x, y))
	{
		token[x][y] = 1;
		dfs(xp, yp, sum + index[x][y]);
		token[x][y] = 0;
	}
	dfs(xp, yp, sum);
		
}
int judge(int x, int y)
{
	for (int i = 0; i < 8; i++)
		if (token[x + step[i][0]][y + step[i][1]] == 1)
			return 0;
	return 1;
}