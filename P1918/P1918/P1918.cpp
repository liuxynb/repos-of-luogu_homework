#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
struct data
{
	ll sign;
	ll num;
}ball[100001];
int n, q;
ll m, ans;
bool cmp(struct data x, struct data y)
{
	return x.num < y.num;
}
int f(ll k, ll left, ll right)
{
	if (left > right)return 0;
	ll mid = (left + right) / 2;
	if (ball[mid].num == k)
	{
		ans = ball[mid].sign;
		return 1;
	}
	if (k < ball[mid].num)return f(k, left, mid - 1);
	else return f(k, mid + 1, right);
	
}
int main(void)
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &ball[i].num);
		ball[i].sign = i;
	}
	sort(ball + 1, ball + n + 1, cmp);
	scanf("%d",&q);
	for (int i = 1; i <= q; i++)
	{
		scanf("%lld", &m);
		if (f(m, 1, n))
			printf("%lld\n", ans);
		else
			printf("0\n");
	}
	return 0;
	
}