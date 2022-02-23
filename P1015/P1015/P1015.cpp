#include<stdio.h>
#include<math.h>
#include<string.h>

int main(void)
{
	int N, ans = 0, temp_num[401]={0};
	char M[110];
	scanf("%d%s", &N, M);
	int len = strlen(M);
	for (int i = 0; i < len; i++)
	{
		if (M[i] >= '0' && M[i] <= '9')
		{
			temp_num[i] = M[i] - '0';
		}
		else
		{
			temp_num[i] = M[i] - 'A' + 10;
		}
	}
	for (; ans < 30; ans++)
	{
		for (int i = 0; i < len; i++)
		{
			if (i <= (len-1) / 2)
				temp_num[i] += temp_num[len - i - 1];
			else
				temp_num[i] = temp_num[len - i - 1];
		}
		for (int i = 0; i < len; i++)
		{
			if (temp_num[i] >= N)
			{
				temp_num[i] -= N;
				temp_num[i+1]++;
			}
		}
		if (temp_num[len] != 0)len++;
		if (judge(temp_num,len))
			break;
	}
	if (ans >= 30)puts("Impossible!");
	else 
	{
		printf("STEP=%d", ans+1);
	}
	return 0;




	
	
}