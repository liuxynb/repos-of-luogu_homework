#include<stdio.h>

int step[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
char index[101][101] = { '.' };
int n, m, ans = 0;
void dfs(int x, int y);

int main(void)
{
	scanf("%d%d", &n, &m);//n行m列。
	for (int i = 0; i < n; i++)
		scanf("%s", index[i]);
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if (index[i][j] == 'W')
			{
				dfs(i, j);
				ans++;
			}
	printf("%d", ans);
}

void dfs(int x, int y)
{
	index[x][y] = '.';
	for (int i = 0; i < 8; i++)
		if (index[x + step[i][0]][y + step[i][1]] == 'W')
			dfs(x + step[i][0], y + step[i][1]);
}