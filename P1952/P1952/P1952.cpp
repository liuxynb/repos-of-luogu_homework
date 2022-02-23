#include<stdio.h>
#include<string.h>
int main(void)
{
	int N, num1[200]={0}, num2[200]={0}, sum[201] = {0};
	scanf("%d", &N);
	char c;
	char str1[201], str2[201], ans[202];
	scanf("%s%s", str1, str2);
	int len1 = strlen(str1), len2 = strlen(str2);
	for (int i = 0; i < len1 ; i++)
	{
		if (str1[len1 - i - 1] >= '0' && str1[len1 - i - 1] <= '9')
		{
			num1[i] = str1[len1 - i - 1] - '0';
		}
		else
		{
			num1[i] = str1[len1 - i - 1] - 'a' + 10;
		}
	}
	for (int i = 0; i < len2; i++)
	{
		if (str2[len2 - i - 1] >= '0' && str2[len2 - i - 1] <= '9')
		{
			num2[i] = str2[len2 - i - 1] - '0';
		}
		else
		{
			num2[i] = str2[len2 - i - 1] - 'a' + 10;
		}
	}
	int max_len = (len1 < len2) ? len2 : len1;
	for (int i = 0; i < max_len; i++)
	{
		sum[i] += (num1[i] + num2[i]);
		if (sum[i]>=N)
		{
			sum[i] -= N;
			sum[i + 1]++;
		}
		if (sum[max_len])max_len++;
	}
	for (int i = 0; i < max_len; i++)
	{
		if (sum[i] < 10)
		{
			ans[max_len - 1 - i] = sum[i] + '0';
		}
		else 
		{
			ans[max_len - 1 - i] = sum[i] + 'a' - 10;
		}
	}
	ans[max_len] = '\0';
	printf("%s", ans);

}