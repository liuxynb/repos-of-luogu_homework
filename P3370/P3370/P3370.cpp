#include<stdio.h>
//#include <corecrt_search.h>
char str[1010];
unsigned int output[10010];
unsigned int Hash(char* str)
{
	unsigned int hash_seed = 13131;
	unsigned int hashkey = 0;
	while (*str)
	{
		hashkey = hashkey * hash_seed + (*str);
		str++;
	}
	return (hashkey & 0x7fffffff);
}
int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s",str);
		output[i] = Hash(str);
	}
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
			if (output[i] > output[j])
			{
				int swap = output[j];
				output[j] = output[i];
				output[i] = swap;
			}
	int ans = 0;
	for (int i = 1; i < n; i++)
	{
		if (output[i] != output[i + 1])
			ans++;
	}
	printf("%d", ans+1);
	return 0;
}
