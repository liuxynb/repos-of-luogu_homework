//#include<stdio.h>
//long long fib[100000000] = { 0 };
//int main(void)
//{
//	long long M, n;
//	scanf("%lld", &M);
//	
//	fib[0] = 0, fib[1] = 1;
//	for (long long i = 2; i < 10000000; i++)
//	{
//		fib[i] = fib[i - 1] + fib[i - 2];
//		if (fib[i] % M == 1 && fib[i - 1] % M == 0) 
//		{
//			n = i - 1;
//			break;
//		}
//	}
//	if (M == 1)printf("1");
//	else printf("%lld", n);
//	
//
//}
#include<stdio.h>
long long fib[100000000] = { 0 }, m;
long long func(long long i);

int main(void)
{
	scanf("%lld", &m);
	long long i;
	for (i = 1;; i++)
		if (func(i) == 0 && func(i + 1) == 1)
			break;
	printf("%lld", i);
	return 0;
}
long long func(long long i)
{
	if (i == 1 || i == 2)return fib[i] = (1 % m);
	else if (fib[i] != 0)return fib[i];
	else return fib[i] = (func(i - 1) + func(i - 2)) % m;
}
