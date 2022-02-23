#include<stdio.h>
#define MAX 10001
int main(void)
{
	int a[MAX], b[MAX], c[MAX], d[MAX], n;
	int x, y;//表示所求的地面的点的坐标
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
	}
	scanf("%d%d", &x, &y);
	int ans = -1;
	for (int i = n - 1; i >= 0; i--)
	{
		if (x >= a[i] && y >= b[i] && x <= a[i] + c[i] && y <= b[i] + d[i])
		{
			ans = i + 1;
			break;
		}
	}
	printf("%d", ans);
	return 0;


}