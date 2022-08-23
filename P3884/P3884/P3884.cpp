//#include<stdio.h>
//#define MAXN 1001
//int d1, d2;
//int dep = 1, wid = 1;
//int depth[MAXN], width[MAXN], f[MAXN];
//void DFS(int x, int y);
//int main(void)
//{
//	int n, x, y;
//	scanf("%d", &n);
//	depth[1] = 1;
//	for (int i = 1; i < n; i++)
//	{
//		scanf("%d%d", &x, &y);
//		f[y] = x, depth[y] = depth[x] + 1;
//		dep = dep > depth[y] ? dep : depth[y];
//		width[depth[y]]++;//当前深度下的节点数
//		wid = wid > width[depth[y]] ? wid : width[depth[y]];
//	}
//	scanf("%d%d", &x, &y);
//	printf("%d\n%d\n", dep, wid);
//	DFS(x, y);
//}
//
//void DFS(int x, int y)
//{
//	if (x == y) 
//	{
//		printf("%d", d1 * 2 + d2);
//		return;
//	}
//	if (depth[x] == depth[y])
//	{
//		
//		d1++;
//		d2++;
//		DFS(f[x], f[y]);
//	}
//	if (depth[x] < depth[y])
//	{
//		d2++;
//		DFS(x, f[y]);
//	}
//	else if(depth[x] > depth[y])
//	{
//		d1++;
//		DFS(f[x], y);
//	}
//}
#include<stdio.h>
#define MAXN 1001
void add_vex(int x,int y);
void DFS(int x, int p, int stp);
void LCA(int x, int y);
int f[MAXN], depth[MAXN], width[MAXN];
int head[MAXN], next[MAXN], to[MAXN], tmp;
int n;//树的结点个数 n。
int d1, d2;
int main(void)
{
	scanf("%d", &n);
	int x, y;
	for (int i = 1; i < n; i++)
	{		
		scanf("%d%d", &x, &y);
		add_vex(x, y);
	}
	DFS(1, 0, 1);
	for (int i = 1; i <= n; i++)
		width[depth[i]]++;
	int dep = 1, wid = 1;
	for (int i = 1; i <= n; i++)
	{
		dep = dep > depth[i] ? dep : depth[i];
		wid = wid > width[i] ? wid : width[i];
	}
	//int x, y;
	scanf("%d%d", &x, &y);
	LCA(x, y);
	printf("%d\n%d\n%d", dep, wid, (d1 << 1) + d2);
	return 0;		
}
void add_vex(int x, int y)
{
	to[++tmp] = y;
	next[tmp] = head[x];
	head[x] = tmp;
}
void DFS(int x, int p, int stp)//深搜
{
	f[x] = p;
	depth[x] = stp;
	for (int i = head[x]; i; i = next[i])
	{
		int m = to[i];
		DFS(m, x, 1 + stp);
	}
}
//void LCA(int x, int y)
//{
//	if (depth[x] > depth[y])
//	{
//		while (depth[x] > depth[y])
//		{
//			x = f[x];
//			d1++;
//		}
//		while(x != y)
//		{
//			x = f[x], y = f[y];
//			d1++, d2++;
//		}
//	}
//	else
//	{
//		int swap;
//		swap = x;
//		x = y;
//		y = swap;
//		while (depth[x] > depth[y])
//		{
//			x = f[x];
//			d2++;
//		}
//		while (x != y)
//		{
//			x = f[x], y = f[y];
//			d1++, d2++;
//		}
//
//	}
//}
void LCA(int x, int y)
{
	while (depth[x] > depth[y])
	{
		x = f[x];
		d1++;
	}
	while (depth[x] < depth[y])
	{
		y = f[y];
		d2++;
	}
	while (x != y)
	{
		x = f[x], y = f[y];
		d1++, d2++;
	}

}