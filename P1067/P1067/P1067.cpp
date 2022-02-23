#include<stdio.h>

int main(void)
{
	int n;
	int sub[101];
	scanf("%d", &n);
	for (int i = 0; i <= n; i++)
		scanf("%d", &sub[i]);
	for(int i=0;i<=n;i++)
	{
		if (sub[i] != 0)
		{
			if (i > 0 && sub[i] > 0)putchar('+');
			if (sub[i] == -1 && i != n)putchar('-');
			else if (sub[i] == 1 && i != n);
			else printf("%d", sub[i]);
			if (i == n - 1)printf("x");
			else if (i != n)printf("x^%d", n - i);
		}

	}
	return 0;
}