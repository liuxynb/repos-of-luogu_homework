//卡特兰数
#include<stdio.h>
int main(void)
{
	int a, b[20] = { 0 };
	scanf("%d", &a);
	b[0] = b[1] = 1;
	for (int i = 2; i <= a; i++)//ans = f[0]*f[n-1] + f[1]*f[n-2] + ... + f[n-1]*f[0];
		for (int j = 0; j < i; j++)
			b[i] += b[i - j - 1] * b[j];
	printf("%d", b[a]);
	return 0;


}