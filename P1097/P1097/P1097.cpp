#include<stdio.h>
#include<string.h>
int main(void)
{
	char M[1001], k[101], C[1001];
	scanf("%s%s", k, M);
	int k_len = strlen(k), M_len = strlen(M);
	for (int i = 0; i < k_len; i++)
	{
		if (k[i] >= 'A' && k[i] <= 'Z')k[i] += 32;
	}
	for (int i = 0, j = 0; i < M_len; i++)
	{
		if (((M[i] - k[j] + 'a') <= 'z'&& (M[i] - k[j] + 'a') >= 'a')&& ((M[i]) <= 'z' && (M[i]) >= 'a'))
			C[i] = M[i] - k[j++] + 'a';
		else if (((M[i] - k[j] + 'a') <= 'Z' && (M[i] - k[j] + 'a') >= 'A')&& ((M[i]) <= 'Z' && (M[i]) >= 'A'))
			C[i] = M[i] - k[j++] + 'a';
		else
			C[i] = M[i] - k[j++] + 'a' + 26;
		if (k[j] == '\0')j = 0;
	}
	C[M_len] = '\0';
	printf("%s", C);
	return 0;


}