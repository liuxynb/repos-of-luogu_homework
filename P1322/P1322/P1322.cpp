#include<stdio.h>
#include<math.h>
#include<string.h>

char str[255], sub[255];


int func(char* str)
{
	int ans=0;//输出
	int len = strlen(str);
	int x, multi;
	for (int i = 0; i < len; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')continue;
		if (str[i] == 'R')
		{
			sscanf(&str[i + 7], "%d", &multi);
			int left, right, t = 0;
			for (int j = i + 7; j < len; j++)
				if (str[j] == '[')
				{
					left = j;
					break;
				}
			for (int j = left + 1; j < len; j++)
			{
				if (t == 0 && str[j] == ']')
				{
					right = j;
					break;
				}
				switch (str[j])
				{
					case '[':t++; break;
					case ']':t--; break;
				}
			}
			for (int j = left + 1; j < right; j++)
				sub[j - left - 1] = str[j];
			sub[right - left - 1] = '\0';//字符串结尾.
			ans += multi * func(sub);
			i = right;
		}
		else if (str[i] == 'F')
		{
			sscanf(&str[i + 3], "%d", &x);
			ans = ans + x;
		}
		else if (str[i] == 'B')
		{
			sscanf(&str[i + 3], "%d", &x);
			ans = ans - x;
		}
	}
	return ans;
}
int main(void)
{
	gets_s(str);
	//func(str);
	printf("%d", abs(func(str)));
}