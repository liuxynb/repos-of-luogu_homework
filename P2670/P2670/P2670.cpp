#include<stdio.h>

int main(void)
{
	int n, m;
	scanf("%d%d", &n, &m);
	int map[102][102] = { 0 };
	for (int i = 1; i <= n; i++)
	{
		getchar();
		for (int j = 1; j <= m; j++)
		{
			char c;
			scanf("%c", &c);
			if (c == '*')map[i][j] = 1;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (map[i][j])printf("*");
			else {
				printf("%d", map[i - 1][j - 1] + map[i - 1][j] + map[i - 1][j + 1] + map[i][j - 1] + map[i][j + 1] + map[i + 1][j - 1] + map[i + 1][j] + map[i + 1][j + 1]);
			}
			
		}
		putchar('\n');
	}
	return 0;


}