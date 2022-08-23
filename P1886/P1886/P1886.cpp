//P1886 滑动窗口 /【模板】单调队列
#include<stdio.h>
#define MAX 1000001
int q1[MAX], q2[MAX];
int num[MAX];
int n, k;
void MaxQueue(void);
void MinQueue(void);

int main(void)
{
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	MinQueue();
	putchar('\n');
	MaxQueue();
	return 0;
}
void MaxQueue(void)//单调最大值
{
	int head = 1, tail = 0;
	for (int i = 1; i <= n; i++)
	{
		while (head <= tail && q2[head] + k <= i)head++;
		while (head <= tail && num[i] > num[q2[tail]])tail--;
		q2[++tail] = i;
		if (i >= k)printf("%d ", num[q2[head]]);
	}
}
void MinQueue(void)
{
	int head = 1, tail = 0;
	for (int i = 1; i <= n; i++)
	{
		while (head <= tail && q1[head] + k <= i)head++;
		while (head <= tail && num[i]<=num[q1[tail]])tail--;
		q1[++tail] = i;
		if (i >= k)printf("%d ", num[q1[head]]);
	}
}