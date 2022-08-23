//#include<stdio.h>
//int f(int n);
//int main(void)
//{
//	printf("%d", f(0));
//	return 0;
//}
//int f(int n)
//{
//	char c;
//	while (scanf("%c", &c) != '\n')
//	{
//		//c = getchar();
//		if (c == 10)break;
//		else if (c == 'a')n++;
//		else if (c == '(')n += f(0);
//		else if (c == ')')return n;
//		else if (c == '|')return (n > f(0)) ? n : f(0);
//	}
//	return n;
//}
//#include<cstdio>
//#include<iostream>
//using namespace std;
//int f();
//int main(void)
//{
//	cout << f();
//	return 0;
//}
//int f()
//{
//	char c;
//	int n = 0;
//	while (scanf("%c", &c) != EOF)
//	{
//		//c = getchar();
//		//if (c == 10)break;
//		if (c == 'a')n++;
//		if (c == '|')return ((n > f()) ? n : f());
//		if (c == '(')n += f();
//		if (c == ')')return n;	
//	}
//	return n;
//}
//#include<stdio.h>
//int f(int j);
//int main(void)
//{
//	printf("%d", f(0));
//	return 0;
//}
//
//int f(int n)
//{
//	char c;
//	while ((scanf("%c", &c)) != EOF)
//	{
//		if (c == 'a') n++;
//		if (c == '(') n = n + f(0);
//		if (c == '|') return (n> f(0))?n:f(0);
//		if (c == ')') return n;
//	}
//	return n;
//}
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
int f(int n) {
	char c;
	while ((c = getchar()) != EOF) 
	{
		if (c == 'a')  n++; 
		if (c == '(')  n = n + f(0); 
		if (c == '|')  return max(n, f(0));
		if (c == ')') return n;
	}
	return n;
}
int main() 
{
	printf("%d", f(0));
	return 0;
}