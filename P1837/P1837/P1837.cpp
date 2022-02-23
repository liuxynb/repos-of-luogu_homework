#include<stdio.h>

int N;
long long M, tree[1000001];

int to_judge(long long cut_len);

int main(void)
{
	scanf("%d%lld", &N, &M);
	long long right = 0;
	for (int i = 1; i <= N; i++)
	{
		scanf("%lld", &tree[i]);
		if (right < tree[i])
			right = tree[i];
	}
	long long left = 1;
	while (left <= right)
	{
		long long mid = (left + right) / 2;
		if (to_judge(mid) == 1)
			left = mid + 1;
		else
			right = mid - 1;
	}
	printf("%lld", left - 1);

}
int to_judge(long long cut_len)
{
	long long sum = 0;
	for (int i = 1; i <= N; i++)
		if (tree[i] > cut_len)sum += (tree[i] - cut_len);
	if (sum >= M)return 1;
	else return 0;
}