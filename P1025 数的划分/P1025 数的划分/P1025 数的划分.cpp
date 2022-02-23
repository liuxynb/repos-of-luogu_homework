#include<stdio.h>

int ans = 0, n, k;
void dfs(int x, int un_use, int temp);

int main(void)
{
	scanf("%d%d", &n, &k);
	dfs(1, n, 0);
	printf("%d", ans);
	return 0;
}
void dfs(int x, int un_use, int temp)
{
	if (temp == k)
	{		
		ans++;
		//printf("%d\n", x);
		return;
	}
	for (int i = x; i <= un_use / (k - temp); i++)
	{
		dfs(i, un_use - i, temp + 1);
		if ((k - temp) == 1)break;
	}
}