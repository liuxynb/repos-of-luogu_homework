#include<stdio.h>
#define MAXN 100086
#define MAXN2 1100
struct EDGE
{
	int v, wide;
	int next;
}edge[MAXN];
int head[MAXN];
int n, p;//n个点，p条边
int tmp;
int c[MAXN2], u[MAXN2];
int In[MAXN2], Out[MAXN2];
int visit[MAXN2];
void input(void)
{
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &c[i], &u[i]);
		if (c[i] > 0)u[i] = -1;//输入神经元
	}
	for (int i = 1; i <= p; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		edge[++tmp].v = b;
		edge[tmp].wide = c;
		edge[tmp].next = head[a];
		head[a] = tmp;
		In[b]++;
		Out[a]++;
	}
}
void topsort(void)
{
	for (int times = 1; times <= n; times++)
		for (int i = 1; i <= n; i++)
		{
			if (In[i] == 0 && visit[i] == 0)
			{
				visit[i] = 1;
				if (u[i] != -1)c[i] -= u[i];
				for (int j = head[i]; j > 0; j = edge[j].next)
				{
					if (c[i] > 0)
						c[edge[j].v] += c[i] * edge[j].wide;
					In[edge[j].v]--;
				}
				break;
			}
			
		}
}
void output(void)
{
	int flag = 0;
	for (int i = 1; i <= n; i++)
		if (Out[i] == 0 && c[i] > 0)//只要输出层神经元状态，
		{
			flag++;
			break;
		}
	if (flag)
	{
		for (int i = 1; i <= n; i++)
			if (Out[i] == 0 && c[i] > 0)//只要输出层神经元状态，
				printf("%d %d\n", i, c[i]);
	}
	else
		printf("NULL");
}
int main(void)
{
	input();
	topsort();
	output();
	return 0;
}
