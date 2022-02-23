#include<stdio.h>
#include<string.h>
int main(void)
{
	int n, p;
	char str1[10001], str2[10001], str3[10001];
	scanf("%d%s%d", &n, str2, &p);
	strcpy(str1, str2);
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{			
			if (str1[i] > str1[j])
			{
				int swap = str1[i];
				str1[i] = str1[j];
				str1[j] = swap;
			}
		}
	}
	int k;
	for (int i = n-1; i >= 0 ; i--)
	{	
		if (i == n - 1)
		{
			for (int j = 0; j < n; j++)
			{
				if (str1[j] == str2[p - 1])
				{
					k = j;
					break;
				}
			}
		}
		else 
		{
			for (int j = n - 1; j >= 0; j--)
			{
				if (str1[j] == str2[k])
				{
					k = j;
					str1[j] = '1';
					break;
				}
			}

		}
		str3[i] = str2[k];
	}
	str3[n] = '\0';
	printf("%s", str3);
	return 0;	
}