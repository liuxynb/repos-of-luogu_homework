#include<stdio.h>
int value[1001], ans[1001];
int main(void)
{
	ans[0] = 1;
	int N, M;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &value[i]);
	for (int i = 1; i <= N; i++)
		for (int j = M; j >= value[i]; j--)
			ans[j] += ans[j - value[i]];
	printf("%d", ans[M]);
	return 0;
}