#include<stdio.h>

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int map[32][32], n;
void bfs(int p, int q);
int main(void)
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &map[i][j]);
	for (int i = 0; i < n; i++) 
	{
		int flag = 0;
		for (int j = 0; j < n; j++)
		{
			if (map[i][j])
			{
				bfs(i + 1, j + 1);
				flag = 1;
				break;
			}
		}
		if (flag)break;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%d ", map[i][j]);
		putchar('\n');
	}
}
void bfs(int p, int q)
{
	int queue[1000][2];
	int front, tail;
	map[p][q] = 2;
	front = 0, tail = 1;
	queue[1][1] = p, queue[1][2] = q;
	do{
		front++;
		for (int i = 0; i < 4; i++)
		{
			int x = queue[front][1] + dx[i], y = queue[front][2] + dy[i];
			if (map[x][y] == 0)//可以入队
			{
				queue[++tail][1] = x, queue[tail][2] = y;
				map[x][y] = 2;
			}
		}
		
	}while (front < tail);

}