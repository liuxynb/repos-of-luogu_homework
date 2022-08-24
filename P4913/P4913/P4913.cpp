#include<stdio.h>
#define MAXN 10001
void DFS(int fa, int depth);
struct Node
{
	int left;
	int right;
}tree[MAXN];
int ans;
int n;//第一行一个整数 n，表示结点数。

int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &tree[i].left, &tree[i].right);
	DFS(1, 1);
	printf("%d", ans);
	return 0;

}
void DFS(int fa, int depth)
{
	if (fa == 0)return;
	ans = ans > depth ? ans : depth;
	DFS(tree[fa].left, depth + 1);
	DFS(tree[fa].right, depth + 1);

}