#include<stdio.h>


int stone[50001] = { 0 };

int f_judge(int a, int L, int M, int N);

int main(void)
{
	int L, M, N;
	scanf("%d%d%d", &L, &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d", &stone[i]);
	int left = 1, right = L;
	int ans = 0;
	stone[N + 1] = L;//最后一块石头
	while (left < right)
	{
		int mid = (left + right) / 2;
		if (f_judge(mid,L,M,N))
		{
			ans = mid;
			left = mid + 1;
		}
		else
			right = mid - 1;
	}
	printf("%d", ans);

}

int f_judge(int a, int L, int M, int N)
{
	int token = 0, ret = 0, step_now = 0;
	for (int i = 1; i <= N + 1; i++)
	{
		if ((stone[i] - stone[step_now]) < a)
			token++;
		else
			step_now = i;
	}
	if (token <= M)return 1;
	else
		return 0;
}