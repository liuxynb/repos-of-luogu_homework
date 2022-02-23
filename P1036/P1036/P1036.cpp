#include<stdio.h>
#include<math.h>

int ans = 0, num[20] = { 0 };
int n, k;
void dfs(int start, int cnt, int sum);
int isPrime(int a);
int main(void)
{	
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &num[i]);
	}
	dfs(0, 0, 0);
	printf("%d", ans);
}

int isPrime(int a)
{
	int ret = 1;
	for (int i = 2; i <= sqrt(a); i++)
	{
		if (a % i == 0)
		{
			ret = 0;
			break;
		}		
	}
	return ret;
}

void dfs(int start, int cnt, int sum)//start为起始数。
{
	if (cnt == k)
	{
		if (isPrime(sum)==1)ans++;
	}
	for (int i = start; i < n; i++)
	{
		dfs(i + 1, cnt + 1, sum + num[i]);
	}
}