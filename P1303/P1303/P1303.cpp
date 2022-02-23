#include<stdio.h>
#include<string.h>
#define MAXM 2005
int main(void)
{
	char str1[MAXM], str2[MAXM];
	int num1[MAXM] = { 0 }, num2[MAXM] = { 0 }, sum[MAXM*2] = { 0 };
	scanf("%s%s", str1, str2);
	int len1 = strlen(str1), len2 = strlen(str2);
	for (int i = 0; i < len1; i++)
		num1[len1 - i - 1] = str1[i] - '0';
	for (int i = 0; i < len2; i++)
		num2[len2 - i - 1] = str2[i] - '0';
	for(int i=0;i<len1;i++)
		for (int j = 0; j < len2; j++)
		{
			sum[i + j] += num1[i] * num2[j];
			if (sum[i + j] / 10)
			{
				sum[i + j + 1] += sum[i + j] / 10;
				sum[i + j] %= 10;
			}
		}
	int flag = MAXM * 2 - 1;
	while (flag)
	{
		if (sum[flag])break;
		flag--;
	}
	//if (flag == 0)putchar('0');
	for (int i = flag; i >= 0; i--)
		printf("%d", sum[i]);
	return 0;

}