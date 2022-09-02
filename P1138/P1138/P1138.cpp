#include<stdio.h>
int bot[30001];
int main(void)
{
	int n, k, cnt = 0;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		bot[x]++;
	}
	for (int i = 1; i <= 30001; i++)
	{
		if (bot[i])cnt++;
		if (cnt == k) 
		{			
			printf("%d", i);
			return 0;
		}
	}
	printf("NO RESULT");
	return 0;
}