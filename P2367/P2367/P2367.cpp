#include<stdio.h>

int main(void)
{
	int n, p;
	int input[50005] = { 0 }, diff[50005] = { 0 };
	scanf("%d%d", &n, &p); //第一行有两个整数 n，p，代表学生数与增加分数的次数.
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &input[i]);
		diff[i] = input[i] - input[i - 1];
	}
	while (p--)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		diff[x] += z;
		diff[y+1] -= z;
	}
	int Min = diff[1];
	for (int i = 2; i <= n; i++)
	{
		diff[i] += diff[i - 1];
		if (diff[i] < Min) Min = diff[i];
	}
	printf("%d", Min);
	return 0;
}