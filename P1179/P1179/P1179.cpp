#include<stdio.h>
int main(void)
{
	int a, b, ans = 0;
	scanf("%d%d", &a, &b);
	for (int i = a; i <= b; i++)
	{
		int x = i;
		while (x)
		{
			if (x % 10 == 2)ans++;
			x /= 10;
		}
	}
	printf("%d", ans);
}