#include<stdio.h>
#define MAXN 10086
#define ll long long
ll heap[MAXN];
int len;
void push_heap(ll x);
ll pop_heap(void);
int main(void)
{
	int n;
	ll sum = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		ll a;
		scanf("%lld", &a);
		push_heap(a);//压数入堆。
	}
	while (len != 1)
	{
		ll x = pop_heap(), y = pop_heap();
		push_heap(x + y);
		sum += x + y;
	}
	printf("%lld", sum);
	return 0;
}
void push_heap(ll x)
{
	heap[++len] = x;
	int i = len;
	while( i != 1&& heap[i] < heap[i / 2])
	{		
		ll swap = heap[i];
		heap[i] = heap[i / 2];
		heap[i / 2] = swap;
		i /= 2;
	}
}
ll pop_heap(void)
{
	ll ret = heap[1];
	heap[1] = heap[len];
	len--;//长度减一。
	int fa = 1;
	int s;
	while (fa * 2 <= len)
	{
		if (fa * 2 + 1 > len || heap[fa * 2] < heap[fa * 2 + 1])
			s = fa * 2;
		else
			s = fa * 2 + 1;
		if (heap[fa] > heap[s])
		{
			ll swap = heap[fa];
			heap[fa] = heap[s];
			heap[s] = swap;
			fa =s;
		}
		else
			break;
	}
	return ret;
}
