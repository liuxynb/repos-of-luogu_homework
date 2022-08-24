#include<stdio.h>
#include<string.h>
char str1[10001], str2[10001];
void DFS(int pre_le, int pre_r, int ino_le, int ino_r);
int main(void)
{
	scanf("%s%s", str1, str2);
	int len = strlen(str1);
	DFS(0, len - 1, 0, len - 1);
	return 0;
}
void DFS(int pre_le, int pre_r, int ino_le, int ino_r)
{
	if (pre_le > pre_le || ino_le > ino_r)return;
	for (int i = pre_le; i <= pre_r; i++)
	{
		if (str1[i] == str2[ino_le])
		{
			DFS(pre_le, i - 1, ino_le + 1, ino_le + i - pre_le);
			DFS(i + 1, ino_r, ino_le + i - pre_le + 1, ino_r);
			printf("%c", str1[i]);
		}
		
	}
	
}