#include<stdio.h>
#define NUM 30006
int main(void)
{
	int n;//项数
	scanf("%d", &n);
	int top = 0;//栈顶
	int Input[NUM]={0}, Stack[NUM]={0}, Output[NUM]={0};
	for (int i = 1; i <= n; i++)
		scanf("%d", &Input[i]);
	for (int i = n; i >= 1; i--)
	{
		while (Input[i]>=Input[Stack[top]] && top)
		{
			top--;
		}
		Output[i] = Stack[top];
		Stack[++top] = i;
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", Output[i]);
	return 0;

}