#include<stdio.h>
double a, b, c, d;
double f(double x);
int main(void)
{

	double left, right, mid;
	int temp = 0;
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	for (int i = -100; i <= 100; i++)
	{
		left = i, right = i + 1;
		if (f(left) == 0)
		{
			printf("%.2f", left); 
			temp++;
			if (temp <= 2) putchar(' ');
			else break;
			continue;
		}
		if (f(left) * f(right) < 0)
		{
			for (int j = 0; j < 30; j++)
			{
				mid = (left + right) / 2;
				if (f(left) * f(mid) < 0)
					right = mid;
				else
					left = mid;
			}
			printf("%.2f", left);
			temp++;
			if (temp <= 2) putchar(' ');
			else break;
		}

	}
	return 0;
}


double f(double x)
{
	return a * x * x * x + b * x * x + c * x + d;
}
	