#include<stdio.h>
int main(void)
{
	int a, b, get;
	scanf("%d%d", &a, &b);
	get = a * 10 + b;
	printf("%d", get / 19);
}