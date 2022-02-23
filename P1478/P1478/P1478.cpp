#include<stdio.h>
struct apple
{
	int length;
	int stren;
};
int main(void)
{
	int n, s, a, b, height, match_num = 0;//苹果数n，力气s。椅子的高度a，陶陶手伸直的最大长度b。
	struct apple match_apple[10000];
	scanf("%d%d%d%d", &n, &s, &a, &b);
	height = a + b;
	for (int i = 0; i < n; i++)
	{
		int L, S;
		scanf("%d%d", &L, &S);
		if (L <= height)
		{
			match_apple[match_num].length = L;
			match_apple[match_num++].stren = S;
		}
	}
	for (int i = 0; i < match_num; i++)
	{
		for (int j = i; j < match_num; j++)
		{
			if (match_apple[i].stren > match_apple[j].stren)
			{
				struct apple swap;
				swap = match_apple[i];
				match_apple[i] = match_apple[j];
				match_apple[j] = swap;
			}
		}
	}
	int used = 0, got = 0;
	for (int i = 0; i < match_num; i++)
	{
		used += match_apple[i].stren;
		if (used > s)break;
		got++;		
	}
	printf("%d", got);

}