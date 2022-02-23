#include<stdio.h>
struct stu
{
	int write;
	int ID;
};

int main(void)
{
	struct stu grades[5000];
	int get_num, put_num;
	scanf("%d%d", &get_num, &put_num);
	put_num = (int)put_num * 1.5;
	for (int i = 0; i < get_num; i++)
	{
		scanf("%d%d", &grades[i].ID, &grades[i].write);
	}
	for (int i = 0; i < get_num; i++)
	{
		for (int j = i; j < get_num; j++)
		{
			if (grades[i].write < grades[j].write)
			{
				struct stu swap;
				swap = grades[i];
				grades[i] = grades[j];
				grades[j] = swap;
			}
		}
	}
	for (int i = 0; i < get_num; i++)
	{
		for (int j = i; j < get_num; j++)
		{
			if (grades[i].ID > grades[j].ID && grades[i].write == grades[j].write)
			{
				struct stu swap;
				swap = grades[i];
				grades[i] = grades[j];
				grades[j] = swap;
			}
		}
	}
	int min_grade = grades[put_num - 1].write;
	int num2;
	for (num2 = get_num - 1; num2 >= 0; num2--)
	{
		if (grades[num2].write == min_grade)
		{
			break;
		}
	}
		
	printf("%d %d\n", min_grade, num2+1);
	for (int i = 0; i <= num2; i++)
	{
		printf("%d %d", grades[i].ID, grades[i].write);
		if (i != num2)putchar('\n');
	}
	
	
}