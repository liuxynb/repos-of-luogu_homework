#include<stdio.h>


int main(void)
{
	int n, m, sign_num[1001], painter[2001] = { 0 };
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &sign_num[i]);
	int left = 1, right = 1, cnt = 0;
	for (; right <= n; right++)
	{
		
		if (painter[sign_num[right]] == 0)
		{
			painter[sign_num[right]]++;
			cnt++;
		}
		else painter[sign_num[right]]++;
		if (cnt == m)break;
	}
	int min_left = left, min_right = right, min = right - left;
	while(left < right)
	{
		painter[sign_num[left]]--;
		if (painter[sign_num[left]]==0)
		{
			while (painter[sign_num[left]] == 0 && ((right + 1) <= n))
			{
				right++;
				painter[sign_num[right]]++;
			}
		}
		if (painter[sign_num[left]] == 0)break;
		left++;
		if ((right - left) < min)
		{
			min_left = left;
			min_right = right;
			min = right - left;
		}
	}
	printf("%d %d", min_left, min_right);
}