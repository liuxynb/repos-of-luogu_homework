#include<stdio.h>
#include <vcruntime_string.h>

#define MAXN 1010
int tuopo[MAXN][MAXN];
int station_to_stop[MAXN]; 
int lev[MAXN];//级别。
int del[MAXN];//标记删除的点。
int input_st[MAXN];
int stack[MAXN];
int high_st;
int top;
int n, m;
void topsort(void);
int main(void)
{	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		memset(station_to_stop, 0, sizeof(station_to_stop));
		int a; scanf("%d", &a);
		for (int j = 1; j <= a; j++)
		{
			scanf("%d", &input_st[j]);
			station_to_stop[input_st[j]] = 1;//本站有火车停靠。
		}
		for(int j=input_st[1]; j<=input_st[a]; j++)
			if(!station_to_stop[j])//没有火车停靠
				for(int k=1; k<=a; k++)
					if (!tuopo[j][input_st[k]])
					{
						tuopo[j][input_st[k]]=1;
						lev[input_st[k]]++;//升级
					}
	}
	topsort();	
	printf("%d", high_st-1);
	return 0;
}
void topsort(void)
{
	do
	{
		top = 0;
		for (int i = 1; i <= n; i++)
			if (!del[i] && !lev[i])
			{
				del[i]=1;
				stack[++top] = i;
			}
		for (int i = 1; i <= top; i++)
			for (int j = 1; j <= n; j++)
				if (tuopo[stack[i]][j])
				{
					tuopo[stack[i]][j] = 0;
					lev[j]--;
				}
		high_st++;
	} while (top);
}
//#include<iostream>
//#include<cstdio>
//#include<cstring>
//using namespace std;
//int n, m, ans, stop[1005], s, tp[1005][1005], cd[1005], tt[1005], top;
//bool book[1005], de[1005];
//int main() {
//	scanf("%d %d", &n, &m);
//	for (int i = 1; i <= m; i++)
//	{
//		memset(book, 0, sizeof(book));
//		scanf("%d", &s);
//		for (int j = 1; j <= s; j++)
//		{
//			scanf("%d", &stop[j]);
//			book[stop[j]] = 1;//路径中有的站点
//		}
//		for (int j = stop[1]; j <= stop[s]; j++)
//		{
//			if (!book[j])
//			{
//				for (int k = 1; k <= s; k++)
//				{
//					if (!tp[j][stop[k]])
//					{
//						tp[j][stop[k]] = 1;//LV of j<LV of stop[k]
//						cd[stop[k]]++;//LV<stop[k]的多了一个
//					}
//				}
//			}
//		}
//	}
//	do
//	{
//		top = 0;
//		for (int i = 1; i <= n; i++)
//		{
//			if (cd[i] == 0 && !de[i])//cd[i]=0:等级不高于任何其他站台
//			{
//				tt[++top] = i;//第top个此次等级最低的站台
//				de[i] = 1;//已经确定等级，即已出队
//			}
//		}
//		for (int i = 1; i <= top; i++)
//		{
//			for (int j = 1; j <= n; j++)
//			{
//				if (tp[tt[i]][j])
//				{
//					tp[tt[i]][j] = 0;//tt[i]出队后 LV of j与LV of tt[i]无法比较
//					cd[j]--;//LV<stop[k]的少了一个
//				}
//			}
//		}
//		ans++;
//	} while (top);
//	printf("%d", ans - 1);//最后一次top=0，即没有出队的站台，所以最后一次无用，ans-1
//	return 0;
//}


//10 8
//3 1 2 3
//3 1 5 3
//3 7 8 9
//4 1 3 5 6
//3 3 5 6
//3 1 5 9
//5 4 5 6 7 9
//3 1 5 10