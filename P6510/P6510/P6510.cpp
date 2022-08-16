#include<stdio.h>
#include<math.h>

#define MAX 1000001
int n;//n表示奶牛的头数
int s1[MAX], s2[MAX], height[MAX];
int t1, t2;

int to_find()
{
	int left = 1, right = t2;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (s2[mid] > s1[t1]) right = mid - 1;
		else left = mid + 1;
	}
	return left;
}
int main(void)
{
	scanf("%d", &n);
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &height[i]);
		while (height[s1[t1]] < height[i] && t1)t1--;//最大
		while (height[s2[t2]] > height[i] && t2)t2--;//最小
		int le = to_find();
		if (le != t2 + 1) ans = ((ans > (i - s2[le] + 1)) ? ans : (i - s2[le] + 1));
		s1[++t1] = i; s2[++t2] = i;
	}
	printf("%d", ans);
	return 0;

}
