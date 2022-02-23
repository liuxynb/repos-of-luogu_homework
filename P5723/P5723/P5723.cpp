#include<stdio.h>
#include<math.h>
int isPrime(int num)
{
	int ret = 1;
	for (int i = 2; i <= sqrt(num); i++) 
	{
		if (num % i == 0)
		{
			ret = 0;
			break;
		}
	}
	return ret;
}



int main(void)
{
	int L, sum = 0, ans[100000], j = 0;
	scanf("%d", &L);
	for (int i = 2; sum <= L; i++)
	{
		if (isPrime(i))
		{
			sum += i;
			if (sum > L) break;
			ans[j++] = i;
		}
	}
	for (int i = 0; i < j; i++)
	{
		printf("%d\n", ans[i]);

	}
	printf("%d\n", j);
}