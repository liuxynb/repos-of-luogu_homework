#include<stdio.h>
struct infor
{
	char name[11];
	int head;
}people[1000001];
int main(void)
{
	int n, m;//表示玩具小人的个数和指令的条数。
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d%s", &people[i].head, people[i].name);
	int locat_now = 1;
	for (int i = 0; i < m; i++)
	{
		int a, s;
		scanf("%d%d", &a, &s);
		if (a == 0 && people[locat_now].head == 0)locat_now = (locat_now + n - s) % n;//<-
		else if (a == 0 && people[locat_now].head == 1)locat_now = (locat_now + s) % n;//->
		else if (a == 1 && people[locat_now].head == 0)locat_now = (locat_now + s) % n;//->
		else locat_now = (locat_now + n - s) % n;//<-

	}
	printf("%s", people[locat_now].name);
	return 0;
}