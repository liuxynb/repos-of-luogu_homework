#include<stdio.h>
#include<string.h>
int p1, p2, p3;
int open(char a, char b)
{
	int ans = 1;
	if (p1 == 2)
	{
		if (a >= 'a' && a <= 'z')a -= 32;
		if (b >= 'a' && b <= 'z')b -= 32;
	}

	if (p3 == 1)
	{
		for (char i = a + 1; i < b; i++)
		{
			for (int j = 0; j < p2; j++)
			{
				printf("%c", (p1 == 3) ? '*' : i);
				ans = 0;
			}
		}

	}
	else
	{
		for (char i = b - 1; i > a; i--)
		{
			for (int j = 0; j < p2; j++)
			{
				printf("%c", (p1 == 3) ? '*' : i);
				ans = 0;
			}
		}
	}
	if ((a-b)==(-1))ans = 0;
	return ans;
}
int main(void)
{

	char str[120];
	scanf("%d %d %d %s", &p1, &p2, &p3, str);
	//printf("%d%d%d\n%s\n", p1, p2, p3, str);
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] != '-')putchar(str[i]);
		else
		{
			if (str[i + 1] == '\0')putchar(str[i]);
			else if (str[i + 1] == '-')putchar(str[i]);
			else if (i == 0 || str[i - 1] == '-')putchar(str[i]);
			else if (str[i - 1] > str[i + 1])putchar(str[i]);
			else if (str[i - 1]<='9'&& str[i + 1]>='a')putchar(str[i]);
			else
			{
				if (open(str[i - 1], str[i + 1]))putchar(str[i]);
			}
		}
	}
	return 0;

}