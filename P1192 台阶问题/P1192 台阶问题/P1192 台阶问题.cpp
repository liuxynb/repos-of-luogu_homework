#include<stdio.h>
int main(void)
{
	int n, k;
	scanf("%d%d", &n, &k);
	long long ways[1005] = { 0 };
	ways[0] = ways[1] = 1;
	if (k == 1) ways[2] = 1;
	else ways[2] = 2;
	
	for (int i = 3; i <= n; i++)
		for (int j = 1; j <= k; j++)
		{
			ways[i] += ways[i - j];
			ways[i] %= 100003;
			if ((i - j) == 0)break;
		}
	printf("%lld", ways[n]);
	return 0;

}