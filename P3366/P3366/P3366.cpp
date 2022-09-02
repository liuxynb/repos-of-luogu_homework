#include<stdio.h>
#include <algorithm>

#define MAXN 4000010

struct EDGE
{
	int u, v;
	int w;
}edge[MAXN];
int f[MAXN];
int cmp(EDGE a, EDGE b)
{
	return a.w < b.w;
}
int to_find(int x)
{
	while (x != f[x]) 
	{
		x = f[x];
		f[x] = f[f[x]];
	}
	return x;
}

int main(void)
{
	int n, m;//表示该图共有 N 个结点和 M 条无向边。
	int sum=0;
	int cnt=0;//后续循环次数（最多n-1条边）
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		f[i] = i;//初始化。
	for (int i = 0; i < m; i++)
		scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
	std::sort(edge, edge + m, cmp);
	for (int i = 0; i < m; i++)
	{
		int du = to_find(edge[i].u), dv = to_find(edge[i].v);
		if (du == dv)continue;//已经连通
		sum += edge[i].w;
		f[dv] = du;
		++cnt;
		if (cnt == n - 1)break;
	}
	if (cnt == n - 1)
		printf("%d", sum);
	else
		printf("orz");
	return 0;
}