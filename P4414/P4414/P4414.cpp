#include<stdio.h>

int main(void)
{
	int num[3];
	char rule[4];
	for (int i = 0; i < 3; i++)
		scanf("%d", &num[i]);
	scanf("%s", rule);
	for(int i=0;i<3;i++)
		for(int j=i;j<3;j++)
			if (num[i] > num[j])
			{
				int swap;
				swap = num[i];
				num[i] = num[j];
				num[j] = swap;
			}
	for (int i = 0; i < 3; i++)
	{
		switch (rule[i])
		{
		case 'A':printf("%d", num[0]); break;
		case 'B':printf("%d", num[1]); break;
		case 'C':printf("%d", num[2]); 
		}
		if (i < 2)putchar(' ');
	}
	return 0;
}
	