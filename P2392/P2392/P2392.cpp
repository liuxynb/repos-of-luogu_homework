#include<stdio.h>
int main(void)
{
	int num_question[4], ans = 0;
	for (int i = 0; i < 4; i++) 
	{
		scanf("%d", &num_question[i]);
	}
	for (int i = 0; i < 4; i++) 
	{
		int sum = 0, dp[10000] = { 0 }, cost[20] = { 0 };
		for (int j = 0; j < num_question[i]; j++) 
		{
			scanf("%d", &cost[j]);
			sum += cost[j];
		}
		for (int j = 0; j < num_question[i]; j++)
		{
			for (int k = sum / 2; k >= cost[j]; k--)
			{
				dp[k] = (dp[k] >(dp[k - cost[j]] + cost[j])) ? dp[k] : (dp[k - cost[j]] + cost[j]);
			}
		}
		ans += sum - dp[sum / 2];
	}
	printf("%d", ans);
	return 0;
		

}