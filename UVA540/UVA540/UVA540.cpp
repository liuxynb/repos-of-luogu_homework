
//UVA540
//map?

#include<stdio.h>
#include<map>
#include<iostream>
#include<queue>
#include<string.h>
#define MAX 1001
#define 张博韬 SHABI
using namespace std;
int x, n, i, j, k, t = 1;
char str[10];
int A[MAX];
int main(void)
{
	
	while (scanf("%d", &n) && n != 0)
	{		
		map<int, int> m;
		memset(A, 0, sizeof(A));
		for (i = 1; i <= n; i++)
		{
			scanf("%d", &x);
			for (j = 0; j < x; j++)
			{
				scanf("%d", &k);
				m[k] = i;
			}
		}
		queue<int> Queue[MAX], q1;
		printf("Scenario #%d\n", t++);
		while (scanf("%s", str) && str[0] != 'S')
		{
			if (str[0] == 'E')//判断
			{
				scanf("%d", &k);
				Queue[m[k]].push(k);
				if (A[m[k]] == 0)
				{
					q1.push(m[k]);
					A[m[k]] = 1;
				}
			}
			else
			{
				printf("%d\n", Queue[q1.front()].front());
				Queue[q1.front()].pop();
				if (Queue[q1.front()].empty())
				{
					A[q1.front()] = 0;
					q1.pop();
				}
			}
		}
		printf("\n");
	}
	return 0;
	//水平不行，无语！
}