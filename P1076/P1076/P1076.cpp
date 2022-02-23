#include<stdio.h>
struct room
{
	int stair;
	int num;
};


int main(void)
{
	int N, M;//N表示除了顶层外藏宝楼共N层楼，M表示除顶层外每层楼有M个房间。
	struct room house[100][10];
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			scanf("%d%d", &house[i][j].stair, &house[i][j].num);
		}
	}
	int sum = 0, start, end;
	scanf("%d", &start);
	for (int i = 0; i < N; i++)
	{
		sum = (sum + house[i][start].num) % 20123;
		int have_stair = 0;
		for (int j = 0; j < M; j++)
		{
			if (house[i][j].stair)have_stair++;
		}
		int temp = house[i][start].num % have_stair;
		if (temp == 0) 
			temp = have_stair;
		int cnt = 0;//用于计数。
		end = start;
		for (;;)
		{
			if (house[i][end].stair)
				cnt++;
			if (cnt == temp)
				break;
			end++;
			if (end >= M)end = 0;
		}
		start = end;
	}
	printf("%d", sum);

}