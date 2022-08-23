#include<stdio.h>
#include<string.h>
#define MAX 1000001
void get_the_next();
void KMP();
int len1, len2;
char str1[MAX], str2[MAX];//str2为模式串。
int next[MAX];
int main(void)
{
	scanf("%s%s", str1, str2);
	len1 = strlen(str1), len2 = strlen(str2);
	get_the_next(); KMP();	
	for (int i = 1; i <= len2; i++)
		printf("%d ", next[i]);
	return 0;
}
void get_the_next()
{
	int p = 0, q = -1;
	next[0] = -1;
	while (p < len2)
	{
		if (q == -1 || str2[p] == str2[q])
		{
			q++, p++;
			next[p] = q;
		}
		else
			q = next[q];//回溯.
	}
}
void KMP()
{
	int p = 0, q = 0;
	while (p < len1)
	{
		if (q == -1 || str1[p] == str2[q])
		{
			p++; q++;
			
		}
		else q = next[q];
		if (q == len2) 
		{ 
			printf("%d\n", p - len2 + 1); 
			q = next[q];
		}
	}
}
