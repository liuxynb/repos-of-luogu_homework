#include<stdio.h>

#define ll long long
#define MAX 100005

ll N;//表示电路板中节点的个数。
ll S;//为该电路板的激发器的编号。
struct Edge
{
	ll v;
	ll next;
	ll dis;
} e[MAX];
ll ans[MAX], maxn[MAX];
ll Head[MAX];//存放出节点
ll m;

void DFS(ll u, ll f);
void add(ll u, ll v, ll dis);

int main(void)
{
	scanf("%lld%lld", &N, &S);
	for (ll i = 1; i < N; i++)
	{
		ll u, v, dis;
		scanf("%lld%lld%lld", &u, &v, &dis);
		add(u, v, dis);
		add(v, u, dis);
	}
	DFS(S, 0);
	printf("%lld", ans[S]);
}

void add(ll u, ll v, ll dis)
{
	e[++m].v = v;
	e[m].dis = dis;
	e[m].next = Head[u];
	Head[u] = m;
}
void DFS(ll u, ll f)
{
	ans[u] = 0, maxn[u] = 0;
	ll sum, cnt;
	sum = cnt = 0;
	for (ll i = Head[u]; i != 0; i = e[i].next)
	{
		if (e[i].v == f)continue;
		DFS(e[i].v, u); cnt++;
		ans[u] += ans[e[i].v];
		maxn[u] = ((maxn[e[i].v] + e[i].dis) > maxn[u]) ? (maxn[e[i].v] + e[i].dis) : maxn[u];
		sum += maxn[e[i].v] + e[i].dis;
	}
	ans[u] += maxn[u] * cnt - sum;

}

