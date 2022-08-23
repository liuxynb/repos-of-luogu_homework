#include<stdio.h>
#include<string.h>
char str[1024];
void FBI(int left, int right);
int main(void)
{
	int k;
	scanf("%d", &k);
	scanf("%s", str);
	FBI(0, (1 << k) - 1);
	return 0;
}
void FBI(int left,int right)
{
	int mid1 = (left + right) / 2;
	int mid2 = (left + right + 1) / 2;
	if (right > left)
	{
		FBI(left, mid1);
		FBI(mid2, right);
	}
	int flag_B = 1, flag_I = 1;
	for (int i = 0; i <= right - left; i++)
	{
		if (str[left + i] == '1')
			flag_B = 0;
		else
			flag_I = 0;
	}
	if (flag_B)putchar('B');
	else if (flag_I)putchar('I');
	else putchar('F');
}