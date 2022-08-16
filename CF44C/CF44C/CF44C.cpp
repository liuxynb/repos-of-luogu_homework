#include<stdio.h>

int main(void)
{
	int n, m; //n天假期，安排m个人来浇花
	scanf("%d%d", &n, &m);
	int line[101]={0};
	for (int i = 0; i < m; i++)
	{
		int left,right;
		scanf("%d%d", &left, &right);
		line[left] += 1;
		line[right + 1] -= 1;
	}
	for (int i = 2; i <= n; i++)
		line[i] += line[i - 1];
	for(int i=1; i<=n; i++)
		if (line[i] != 1)
		{
			printf("%d %d", i, line[i]);
			return 0;
		}
	printf("OK");
	return 0;
	
}