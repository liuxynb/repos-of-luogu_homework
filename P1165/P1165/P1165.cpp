#include<stdio.h>
#define INF 20001
int main(void)
{
	int s1[INF] = { 0 }, s2[INF] = { 0 }, top_a, top_b, n;//s2为最大栈
	top_a = top_b = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int x, y;
		scanf("%d", &x);
		if (x == 0)
		{
			scanf("%d", &y);
			s1[++top_a] = y;
			if (y > s2[top_b])s2[top_b + 1] = y;
			else s2[top_b + 1] = s2[top_b];
			top_b++;
		}
		else if (x == 1)
			top_a--, top_b--;
		else
			printf("%d\n", s2[top_b]);
	}
	return 0;
}