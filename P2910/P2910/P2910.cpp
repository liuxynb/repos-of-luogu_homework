#include<stdio.h>
#define MAXN 10001
int dis[MAXN][MAXN];
int path[MAXN];
int n, m;
void Floyd(void);
int main(void)
{	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d", &path[i]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &dis[i][j]);
	Floyd();
	int minn = dis[1][path[1]];
	for (int i = 2; i <= m; i++)
		minn += dis[path[i - 1]][path[i]];
	minn += dis[path[m]][n];
	printf("%d", minn);
	return 0;
}
void Floyd(void)
{
	for (int tmp = 1; tmp <= n; tmp++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				dis[i][j] = dis[i][j] > (dis[i][tmp] + dis[tmp][j]) ? (dis[i][tmp] + dis[tmp][j]) : dis[i][j];
}