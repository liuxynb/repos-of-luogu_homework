#include<stdio.h>
int main(void)
{
	int Spend[12];
	for (int i = 0; i < 12; i++) {
		scanf("%d", &Spend[i]);
	}
	int Remainder = 0;
	int last_money = 0;
	int ret = 0;
	int i = 0;
	for (; i < 12; i++)
	{
		Remainder += 300;
		Remainder -= Spend[i];
		if (Remainder >= 100) {
			last_money += Remainder / 100 * 100;
			Remainder -= Remainder / 100 * 100;
		}
		else if (Remainder < 0) {
			ret = 1;
			break;
		}
	}
	if (ret) printf("%d", -(i+1));
	else printf("%.0f", Remainder + 1.2 * last_money);
	return 0;

}