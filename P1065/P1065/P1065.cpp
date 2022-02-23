#include<stdio.h>
struct MyStruct1
{
	int num;
	int spent;
};
int main(void)
{
	int m, n;//m(<20)表示机器数(工序数)，n(<20)表示工件数.
	scanf("%d%d", &m, &n);
	int order[500];
	int cost[21][8001] = { 0 };
	struct MyStruct1 information[21][21];
	for (int i = 1; i <= n * m; i++)
	{
		scanf("%d", &order[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &information[i][j].num);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &information[i][j].spent);
		}
	}//input.
	int step[21] = { 0 };
	int last[21] = { 0 };
	int last_time = 0;
	for (int i = 1; i <= n * m; i++)
	{
		int now_item = order[i];
		step[now_item]++;
		int now_num = information[now_item][step[now_item]].num;
		int now_spent = information[now_item][step[now_item]].spent;
		int temp = 0;
		for (int j = last[now_item] + 1;; j++)
		{
			if (cost[now_num][j] == 0)temp++;
			else temp = 0;
			if (temp == now_spent)
			{
				for (int k = j - now_spent + 1; k <= j; k++)
				{
					cost[now_num][k]++;
				}
				last[now_item] = j;
				if (j > last_time)last_time = j;
				break;
			}
		}
	}
	printf("%d", last_time);
	return 0;
	
} 