#include<stdio.h>
int stack[100], top;
void push(int num);
void pop(char a);
int main(void)
{
	char a = getchar();
	int num = 0;
	while (a != '@')
	{		
		if (a >= '0' && a <= '9')
		{
			num *= 10;
			num += a - '0';
		}
		else if (a == '.')
		{
			push(num);
			num = 0;
		}
		else
			pop(a);
		a = getchar();
	}
	printf("%d", stack[top]);
	return 0;
}
void push(int num)
{
	stack[++top] = num;
}
void pop(char a)
{
	int num = 0;//存放运算结果。
	if (top <= 0)
	{
		printf("Underflow!");
		return;
	}
	switch (a)
	{
	case '+':num = stack[top - 1] + stack[top]; break;
	case '-':num = stack[top - 1] - stack[top]; break;
	case '*':num = stack[top - 1] * stack[top]; break;
	case '/':num = stack[top - 1] / stack[top]; break;
	}
	top -= 2; push(num);
}
