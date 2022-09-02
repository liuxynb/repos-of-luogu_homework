//dijkstra
#include<stdio.h>
#define MAXN 510086
#define INF 2147483647
#define ll long long
struct EDGE
{
	int to;
	int next;
	int len;
}edge[MAXN];
int head_vex[MAXN];
int p;//指针.
ll ans[MAXN];
int visit[MAXN];
int m, n, s;//分别表示点的个数、有向边的个数、出发点的编号。
void input_edge();
int main(void)
{
	scanf("%d%d%d", &m, &n, &s);
	for (int i = 1; i <= n; i++)
		ans[i] = INF;
	ans[s] = 0;
	input_edge();
	int cur = s;
	while (!visit[cur])
	{
		ll MIN = INF;
		visit[cur] = 1;
		for (int i = head_vex[cur]; i != 0; i = edge[i].next)
			if (!visit[edge[i].to] && ans[edge[i].to] > ans[cur] + edge[i].len)
				ans[edge[i].to] = ans[cur] + edge[i].len;
		for(int i=1;i<=m;i++)
			if (ans[i] < MIN && !visit[i])
			{
				MIN = ans[i];
				cur = i;
			}
	}
	for (int i = 1; i <= m; i++)
		printf("%d ", ans[i]);
	return 0;
}
void input_edge()
{
	int u, v, w;//表示一条 u→v 的，长度为 w 的边。
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		edge[++p].to = v;
		edge[p].len = w;
		edge[p].next = head_vex[u];
		head_vex[u] = p;
	}
}