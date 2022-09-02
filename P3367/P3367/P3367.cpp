#include<stdio.h>
#define MAXN 10086

int fa[MAXN];
int n, m;//n个元素，m个操作
void merge(int x, int y);
int to_find_fa(int x);
int main(void)
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		fa[i] = i;//自己的祖先一开始是自己。
	while (m--)
	{
		int z, x, y;
		scanf("%d%d%d", &z, &x, &y);
		switch (z)
		{
		case 1:
			merge(x, y);
			break;
		case 2:
			if (to_find_fa(x) == to_find_fa(y))
				printf("Y\n");
			else
				printf("N\n");
			break;
		}
	}
	return 0;
}
void merge(int x, int y)
{
	int fx = to_find_fa(x);
	int fy = to_find_fa(y);
	if (fx != fy)
		fa[fx] = fy;
}
int to_find_fa(int x)
{
	if (x != fa[x])
		return fa[x] = to_find_fa(fa[x]);
	return fa[x];
}