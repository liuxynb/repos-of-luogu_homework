#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ll long long
char str[100], str2[100];
void reverse(ll s)
{
	ll n = 0;
	while (s)
	{
		n = n * 10 + s % 10;
		s /= 10;
	}
	printf("%lld", n);
}
int main(void)
{
	char str[100];
	ll num;//存储数
	gets_s(str);
	int k = 0;
	int i = 0;
	for (; i < strlen(str); i++)
	{
		if (str[i] > 57 || str[i] < 48)break;
		else k++;
	}
	if (k == strlen(str))
	{
		i = strlen(str)-1;
		while (str[i] == '0')--i;
		if (i == -1)
		{
			printf("0");
			return 0;
		}
		for (; i >= 0; i--)
			printf("%c", str[i]);
	}
	else if (k == (strlen(str) - 1))
	{
		sscanf(str, "%lld", &num);
		reverse(num);
		putchar('%');
	}
	else
	{
		sscanf(str, "%lld", &num);
		reverse(num);
		printf("%c", str[i]);
		i++;
		for (int j = 0; i < strlen(str); i++, j++)
			str2[j] = str[i];
		sscanf(str2, "%lld", &num);
		reverse(num);		
	}
	return 0;
}
