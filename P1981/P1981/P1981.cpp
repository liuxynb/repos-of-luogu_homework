#include<stdio.h>
int main(void)
{
	int num1, num2, sum=0;
	char c;
	scanf("%d", &num1);
	while (scanf("%c", &c) && c!='\n')
	{
		scanf("%d", &num2);
		if (c == '*')num1 = num1 * num2 % 10000;
		else 
		{
			sum = (sum + num1) % 10000; 
			num1 = num2; 
		}
		
	}
	printf("%d\n", (sum + num1) % 10000); 
	return 0;
}