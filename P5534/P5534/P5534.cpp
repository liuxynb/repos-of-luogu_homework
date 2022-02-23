#include<stdio.h>

int main(void)
{
	int a1, a2, n;
	scanf("%d%d%d", &a1, &a2, &n);
	long long d = a2 - a1;
	long long sum = (a1 + a1 + (n - 1) * d) * n / 2;
	printf("%lld", sum);
}