//#include<stdio.h>
//#include<stdlib.h>
//
//
//
//int main(void)
//{
//	struct grades
//	{
//		int chinese;
//		int math;
//		int eng;
//		int sum;
//		int num;
//	};
//
//	
//	
//	
//	int memb;
//	scanf("%d", &memb);
//	grades *A = (grades*)malloc(sizeof(grades) * memb);
//	for (int i = 0; i < memb; i++)
//	{
//		scanf("%d%d%d", &A[i].chinese, &A[i].math, &A[i].eng);
//		A[i].sum = A[i].chinese + A[i].math + A[i].eng;
//		A[i].num = i + 1;
//	}
//	for (int i = 0; i < memb; i++)
//	{
//		for (int j = i; j < memb; j++)
//		{
//			if (A[i].sum < A[j].sum)
//			{
//				grades swap = A[i];
//				A[i] = A[j];
//				A[j] = swap;
//				
//			}
//		}
//	}
//	for (int i = 1; i < memb; i++)
//	{
//		if (A[i].sum == A[i-1].sum&&A[i].chinese>A[i-1].chinese)
//		{			
//			grades swap = A[i];
//			A[i] = A[i-1];
//			A[i-1] = swap;
//		}
//	}
//	for (int i = 1; i < memb; i++)
//	{
//		if (A[i].sum == A[i - 1].sum && A[i].chinese == A[i - 1].chinese && A[i].num < A[i-1].num)
//		{
//			grades swap = A[i];
//			A[i] = A[i - 1];
//			A[i - 1] = swap;
//		}
//	}
//
//	for (int i = 0; i < 5; i++)
//	{
//		printf("%d %d", A[i].num, A[i].sum);
//		if (i != 4)putchar('\n');
//	}
//	return 0;
//}
//

#include<stdio.h>
#include<stdlib.h>
void swap(int* a, int* b)
{
	int swap = *a;
	*a = *b;
	*b = swap;
}
int main(void)
{
	




	int memb;
	scanf("%d", &memb);
	int chinese[1000];
	int math;
	int eng;
	int sum[1000];
	int num[1000];
	for (int i = 0; i < memb; i++)
	{
		scanf("%d%d%d", &chinese[i], &math, &eng);
		sum[i] = chinese[i] + math + eng;
		num[i] = i + 1;
	}
	for (int i = 0; i < memb; i++)
	{
		for (int j = i; j < memb; j++)
		{
			if (sum[i] <sum[j])
			{
				swap(&sum[i], &sum[j]);
				swap(&num[i], &num[j]);
				swap(&chinese[i], &chinese[j]);
			}
		}
	}
	for (int i = 1; i < memb; i++)
	{
		if (sum[i] == sum[i - 1] && chinese[i] > chinese[i-1])
		{
			swap(&sum[i], &sum[i-1]);
			swap(&num[i], &num[i - 1]);
			swap(&chinese[i], &chinese[i - 1]);
		}
	}
	for (int i = 1; i < memb; i++)
	{
		if (sum[i] == sum[i - 1] && chinese[i] == chinese[i - 1] && num[i] < num[i-1])
		{
			swap(&sum[i], &sum[i - 1]);
			swap(&num[i], &num[i - 1]);
			swap(&chinese[i], &chinese[i - 1]);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		printf("%d %d", num[i], sum[i]);
		if (i != 4)putchar('\n');
	}
	return 0;
}