#include<stdio.h>

long long ans = 0;
int num[100001], sort_num[100001];
void msort(int left, int right);

int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	msort(1, n);
	printf("%lld\n", ans);
	/*for (int i = 1; i <= n; i++)
		printf("%d ", sort_num[i]);*/

}
void msort(int left, int right)
{
	int mid = (left + right) / 2;
	if (left == right)
		return;
	else
	{
		msort(left, mid);
		msort(1 + mid, right);
	}
	int i = left, j = mid + 1;
	int temp = left;
	while (i <= mid && j <= right)
	{
		if (num[i] > num[j])
		{
			ans += mid + 1 - i;//算逆序数。
			sort_num[temp++] = num[j++];
		}
		else
			sort_num[temp++] = num[i++];
	}
	while (i <= mid)
		sort_num[temp++] = num[i++];
	while (j <= right)
		sort_num[temp++] = num[j++];
	for (int i = left; i <= right; i++)
		num[i] = sort_num[i];
	return;
}