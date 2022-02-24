#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;

struct inf
{
	int grade;
	long long power;
	int sign;
}mem[200010],win[100005],lose[100005];
//void merge(int n);
bool comp(struct inf a, struct inf b);
int main(void)
{
	int n, r, q;
	scanf("%d%d%d", &n, &r, &q);
	for (int i = 1; i <= 2 * n; i++)
	{
		scanf("%d", &mem[i].grade);
		mem[i].sign = i;
	}	
	for (int i = 1; i <= 2 * n; i++)
		scanf("%lld", &mem[i].power);
	sort(mem+1, mem+2*n+1, comp);

	for (int i = 0; i < r; i++)
	{
		int w = 0, l = 0;
		for (int j = 1; j <= 2 * n; j += 2)
		{
			if (mem[j].power > mem[j + 1].power)
			{
				mem[j].grade++;
				win[++w] = mem[j];
				lose[++l] = mem[j + 1];
			}
			else 
			{
				mem[j + 1].grade++;
				win[++w] = mem[j + 1];
				lose[++l] = mem[j];
			}
		}
		merge(lose + 1, lose + n + 1, win + 1, win + n + 1, mem + 1,comp);
	}

	printf("%d", mem[q].sign);
	return 0;
}
//void merge(int n)
//{
//	int i = 1, j = 1, cnt = 0;
//	while (cnt < 2*n)
//	{
//		if (comp(win[i], lose[j]))
//			mem[++cnt] = win[i++];
//		else mem[++cnt] = lose[j++];
//	}
//}
bool comp(struct inf a, struct inf b)
{
	if (a.grade == b.grade)
		return a.sign < b.sign;
	else
		return a.grade > b.grade;
	
}
