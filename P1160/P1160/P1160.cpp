#include<stdio.h>

struct Node
{
	int front;
	int next;
}list[100001];

//int first;//第一个元素下标

void addList(int num, int a, int left_right)
{
	if (left_right == 1)//插入到右边
	{
		list[num].front = a;
		list[num].next = list[a].next;
		list[list[a].next].front = num;
		list[a].next = num;
	}
	else//插入到左边
	{
		a = list[a].front;
		list[num].front = a;
		list[num].next = list[a].next;
		list[list[a].next].front = num;
		list[a].next = num;
	}
}

void deleteList(int num)
{
	if (list[num].front != -1)
	{
		list[list[num].front].next = list[num].next;
		list[list[num].next].front = list[num].front;
		list[num].front = -1;
	}
}
int main(void)
{
	int num;
	scanf("%d", &num);
	list[0].front = -1, list[0].next = 1;
	list[1].front = 0, list[1].next = -1;
	int a, b, c;
	for (int i = 2; i <= num; i++)
	{
		scanf("%d%d", &a, &b);
		addList(i, a, b);
	}
	int delnum;
	scanf("%d", &delnum);
	for (int i = 0; i < delnum; i++)
	{
		scanf("%d", &c);
		deleteList(c);
	}
	for (int i = list[0].next; i != -1; i = list[i].next)
		printf("%d ", i);
	return 0;
}