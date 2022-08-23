#include<stdio.h>
#include<string.h>
#define MAX 1000
char mid[MAX], pos[MAX];
void DFS(int mid_left, int mid_right, int pos_left, int pos_right)
{
	if (mid_left > mid_right)return;
	if (pos_left > pos_right)return;
	printf("%c", pos[pos_right]);
	for (int i = mid_left; i <= mid_right; i++)
	{
		if (mid[i] == pos[pos_right])
		{
			DFS(mid_left, i - 1, pos_left, pos_left + i - mid_left - 1);
			DFS(i+1,mid_right, pos_left + i - mid_left,pos_right-1);
		}
	}
}
int main(void)
{
	scanf("%s%s", mid, pos);
	DFS(0, strlen(mid) - 1, 0, strlen(mid) - 1);
	return 0;
}