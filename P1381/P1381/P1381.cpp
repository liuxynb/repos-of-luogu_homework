#include<stdio.h>
//#include<string.h>

#define ll long long
//#define MAXN 1010
const int mod = 1e6;
char str[110];
int key1[100010], key2[100010];
int on_need[5000005], visit[5000005], on_line[5000005];
int ans = (1<<29);
int Hash(char* str);
int main(void)
{
	int n, m, cnt = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", str);
		key1[i] = Hash(str);
		on_need[key1[i]] = 1;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%s",str);
		key2[i] = Hash(str);
		if (on_need[key2[i]] && !visit[key2[i]])
		{
			cnt++;
			visit[key2[i]] = 1;
		}
	}
	if (!cnt)
	{
		printf("0\n0");
		return 0;
	}
	else
		printf("%d\n", cnt);

	int left = 1, right = 1;
	while (1)//尺取法
	{
		if (cnt)
		{
			if (right > m)
				break;
			if (on_need[key2[right]])
			{
				if (!on_line[key2[right]])
					cnt--;
				on_line[key2[right]]++;
			}
			right++;
		}
		else 
		{
			while (!on_need[key2[left]])
				left++;
			if (left > right)
				break;
			ans = ans > (right - left) ? (right - left) : ans;
			if (on_line[key2[left]] == 1)
				cnt++;
			if (on_line[key2[left]] >= 1)
			{
				on_line[key2[left]]--;
				left++;
			}
		}
	}
	printf("%d", ans);
	return 0;

}
int Hash(char* str)
{
	int hash_seed = 13131;
	ll hashkey = 0;
	while (*str)
	{
		hashkey = hashkey * hash_seed + (*str);
		hashkey %= mod;
		str++;
	}
	//hashkey %= mod;
	return hashkey;
}