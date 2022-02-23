#include<stdio.h>

long long sign[25][25][25];
long long w(long long a, long long b, long long c);

int main(void)
{
	while (1) 
	{
		long long a, b, c;
		//sign[25][25][25] = { 0 };
		scanf("%lld%lld%lld", &a, &b, &c);
		if (a == -1 && b == -1 && c == -1)break;
		printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, w(a, b, c));
		//printf("%lld\n", w(a, b, c));
	}
	return 0;

}

long long w(long long a, long long b, long long c)
{
	
	if (a <= 0 || b <= 0 || c <= 0)
		return 1;
	if (a > 20 || b > 20 || c > 20)
	{
		a = b = c = 20;
	}
	if (sign[a][b][c])
		return sign[a][b][c];
	else if (a < b && b < c)
		sign[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
	else 
		sign[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
	return sign[a][b][c];
}
