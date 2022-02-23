#include<stdio.h>
#include<string.h>
int main(void)
{
	char str1[502], str2[502];
	int num1[501] = { 0 }, num2[501] = { 0 }, sum[502] = { 0 };
	scanf("%s%s", str1, str2);
	int len1 = strlen(str1), len2 = strlen(str2);
	for (int i = 0; i < len1; i++)
		num1[len1 - i - 1] = str1[i] - '0';
	for (int i = 0; i < len2; i++)
		num2[len2 - i - 1] = str2[i] - '0';
	int max = (len1 > len2) ? len1 : len2;
	for (int i = 0; i < max; i++)
	{
		sum[i] += num1[i] + num2[i];
		if (sum[i] / 10)
		{
			sum[i] %= 10;
			sum[i + 1]++;
		}
	}
	if (sum[max])max++;
	for (int i = max - 1; i >= 0; i--)
	{
		printf("%d", sum[i]);
	}
	return 0;

}