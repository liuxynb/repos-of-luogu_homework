#include<stdio.h>
int main(void)
{
	int N, Na, Nb;
	scanf("%d%d%d", &N, &Na, &Nb);//N,NA,NB, 分别表示共进行N次猜拳、小A出拳的周期长度，小B出拳的周期长度。
	int round1[200], round2[200];
	for (int i = 0; i < Na; i++)
	{
		scanf("%d", &round1[i]);
	}
	for (int i = 0; i < Nb; i++)
	{
		scanf("%d", &round2[i]);
	}
	int ag = 0, bg = 0;//a,b的得分。
	int ta = 0, tb = 0;//用于计数。
	for (int i = 0; i < N; i++)
	{
		if (ta == Na)ta = 0;
		if (tb == Nb)tb = 0;

		if ((round1[ta] == 0 && round2[tb] == 2) ||
			(round1[ta] == 0 && round2[tb] == 3) ||
			(round1[ta] == 1 && round2[tb] == 0) ||
			(round1[ta] == 1 && round2[tb] == 3) ||
			(round1[ta] == 2 && round2[tb] == 1) ||
			(round1[ta] == 2 && round2[tb] == 4) ||
			(round1[ta] == 3 && round2[tb] == 2) ||
			(round1[ta] == 3 && round2[tb] == 4) ||
			(round1[ta] == 4 && round2[tb] == 0) ||
			(round1[ta] == 4 && round2[tb] == 1)) ag++;

		else if ((round1[ta] == 0 && round2[tb] == 1) ||
			(round1[ta] == 0 && round2[tb] == 4) ||
			(round1[ta] == 1 && round2[tb] == 2) ||
			(round1[ta] == 1 && round2[tb] == 4) ||
			(round1[ta] == 2 && round2[tb] == 0) ||
			(round1[ta] == 2 && round2[tb] == 3) ||
			(round1[ta] == 3 && round2[tb] == 0) ||
			(round1[ta] == 3 && round2[tb] == 1) ||
			(round1[ta] == 4 && round2[tb] == 2) ||
			(round1[ta] == 4 && round2[tb] == 3)) bg++;
		ta++;
		tb++;
	}
	printf("%d %d", ag, bg);
}