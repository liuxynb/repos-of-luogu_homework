#include<stdio.h>
int main(void)
{
	int n, x;
	int times = 0;
	scanf("%d%d", & n, &x);
	for (int i = 1; i <= n; i++)
	{
		char num[] = "kkkkkkkk";
		sprintf(num, "%d", i);
		for (int j = 0; num[j] != 'k'; j++)
		{
			if (num[j] == ('0' + x)) times++;
		}

	}
	printf("%d", times);
}