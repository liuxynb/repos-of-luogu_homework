#include <iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 100861
vector<int>map[MAXN];//vector是邻接表。
int visit[MAXN];
//void add_vex(int from, int to);
void DFS(int x);
void BFS(int x);
int main(void)
{
	int n, m;//n篇文章，m条参考文献引用方式。
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		int f, t;
		scanf("%d%d", &f, &t);
		map[f].push_back(t);
	}
	for (int i = 1; i <= n; i++)//每个表头后面链接的结点从小到大排序 
		sort(map[i].begin(), map[i].end());
	DFS(1);
	putchar('\n');
	memset(visit, 0, sizeof(visit));
	BFS(1);
	return 0;
}
void DFS(int x)
{
	if (visit[x])return;
	printf("%d ", x);
	visit[x] = 1;
	for (int i = 0; i < map[x].size(); i++)
		DFS(map[x][i]);			
}
void BFS(int x)
{
	//if (visit[x])return;
	queue<int>q;//队列.
	visit[x] = 1;
	q.push(x);
	while (!q.empty())
	{
		int y = q.front();
		q.pop();
		printf("%d ", y);
		for (int i = 0; i < map[y].size(); i++)
		{
			if (visit[map[y][i]] == 0)
			{
				visit[map[y][i]] = 1;
				q.push(map[y][i]);
			}
		}
	}
}
