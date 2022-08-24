//#include<stdio.h>
//#define MAXN 10001
//int m, n;//棋盘的大小，棋盘上有颜色的格子的数量。
//int map[MAXN][MAXN];//储存颜色。
//int cost[MAXN][MAXN];
//int walk[MAXN][MAXN];
//const int dx[4] = { -1,0,0,1 };
//const int dy[4] = { 0,-1,1,0 };
//int flag;//判断是否有解。
//void DFS(int x, int y, int stp/*花费*/, int used);
//int main(void)
//{
//	scanf("%d%d", &m, &n);
//	for (int i = 1; i <= n; i++)
//		for (int j = 1; j <= n; j++)
//			cost[i][j] = 0x3f;//初始化最大值。
//    for (int i = 1; i <= n; i++)
//    {
//        int x, y, c;
//        scanf("%d%d%d", &x, &y, &c);
//        map[x][y] = 1 + c;//方便//map[][]=2 代表黄色，map[][]=1代表红色
//    }
//    walk[1][1] = 1;
//    DFS(1, 1, 0, 0);
//    if (flag == 1)
//    {
//        printf("%d\n", cost[m][m]);
//    }
//    else
//    {
//        printf("-1\n");
//    }
//
//    return 0;
//}
//void DFS(int x, int y, int stp/*花费*/, int used)//used判断是否使用过魔法。
//{
//    if ((!(x >= 1 && x <= m && y >= 1 && y <= m)) || (stp >= cost[x][y]))return;
//    cost[x][y] = stp;   
//    if (x == m && y == m)
//    {
//        flag = 1;
//        return;
//    }
//    for (int i = 0; i < 4; i++)
//    {
//        int mx = x + dx[i];
//        int my = y + dy[i];
//        if ((mx >= 1 && mx <= m && my >= 1 && my <= m)&&(walk[mx][my]==0))//合法
//        {
//            if (map[mx][my] != 0)
//            {
//                if (map[mx][my] == map[x][y])
//                {
//                    walk[mx][my] = 1;
//                    DFS(mx, my, stp, 0);
//                    walk[mx][my] = 0;
//                }
//                else
//                {
//                    walk[mx][my] = 1;
//                    DFS(mx, my, stp + 1, 0);
//                    walk[mx][my] = 0;
//                }
//            }
//            else if(map[mx][my] == 0 && used==0)
//            {
//                map[mx][my] = map[x][y]; //暂时变色 
//                walk[mx][my] = 1;
//                DFS(mx, my, stp + 2, 1);
//                map[mx][my] = 0;  
//                walk[mx][my] = 0;
//            }
//        }
//    }
//
//}
#include<stdio.h>
#define INF 0x3f3f3f3f
#define MAXN 10001
int map[MAXN][MAXN];
int walked[MAXN][MAXN];
int f[MAXN][MAXN];
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int m, n;
int ans = INF;
int min(int a, int b)
{
	if (a > b)return b;
	else return a;
}
void DFS(int x, int y, int color, int sum)
{
	if (x<1 || x>m || y<1 || y>m || walked[x][y] || sum >= f[x][y])return;
	if (x == m && y == m)
	{
		ans = min(ans, sum); return;
	}
	f[x][y] = sum;
	if (map[x][y] == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			if (map[x + dx[i]][y + dy[i]] != 0 && !walked[x + dx[i]][y + dy[i]])
			{
				if (map[x + dx[i]][y + dy[i]] == color)
				{
					walked[x][y] = 1;
					DFS(x + dx[i], y + dy[i], color, sum);
					walked[x][y] = 0;
				}
				else
				{
					walked[x][y] = 1;
					DFS(x + dx[i], y + dy[i], map[x + dx[i]][y + dy[i]], sum + 1);
					walked[x][y] = 0;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (map[x + dx[i]][y + dy[i]] == 0 && !walked[x + dx[i]][y + dy[i]])
			{
				walked[x][y] = 1;
				DFS(x + dx[i], y + dy[i], map[x][y], sum + 2);
				walked[x][y] = 0;
			}
			else if (!walked[x + dx[i]][y + dy[i]])
			{
				if (map[x + dx[i]][y + dy[i]] != color)
				{
					walked[x][y] = 1;
					DFS(x + dx[i], y + dy[i], map[x + dx[i]][y + dy[i]], sum + 1);
					walked[x][y] = 0;
				}
				else
				{
					walked[x][y] = 1;
					DFS(x + dx[i], y + dy[i], map[x + dx[i]][y + dy[i]], sum);
					walked[x][y] = 0;
				}
			}
		}
	}
}
int main(void)
{
	
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			f[i][j] = INF;
	for (int i = 1; i <= n; i++)
	{
		int x, y, color;
		scanf("%d%d%d", &x, &y, &color);
		map[x][y] = color + 1;
	}
	DFS(1, 1, map[1][1], 0);
	if (ans == INF)
		printf("-1");
	else 
		printf("%d", ans);
	return 0;
}
