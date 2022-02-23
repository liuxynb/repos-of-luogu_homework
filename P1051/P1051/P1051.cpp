#include<stdio.h>
struct inf
{
	char name[21];
	int grade1, grade2;//grade1是期末平均成绩，grade2是班级评议成绩
	int art=0;
	char a, b;//a是否是学生干部，b是否是西部省份学生
	int award=0;
}stu[100];

int main(void)
{
	int n, all_we_get = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s%d%d", stu[i].name, &stu[i].grade1, &stu[i].grade2);
		getchar();
		scanf("%c", &stu[i].a);
		getchar();
		scanf("%c%d", &stu[i].b, &stu[i].art);
		if (stu[i].grade1 > 80 && stu[i].art)stu[i].award += 8000;
		if (stu[i].grade1 > 85 && stu[i].grade2 > 80)stu[i].award += 4000;
		if (stu[i].grade1 > 90)stu[i].award += 2000;
		if (stu[i].grade1 > 85 && stu[i].b == 'Y')stu[i].award += 1000;
		if (stu[i].grade2 > 80 && stu[i].a == 'Y')stu[i].award += 850;
		all_we_get += stu[i].award;
	}
	//printf("%s%d%d%c%c%d", stu[0].name, stu[0].grade1, stu[0].grade2, stu[0].a, stu[0].b, stu[0].art);
	//printf("%d", stu[0].award);
	int max = 0;
	for (int i = 1; i < n; i++)
		if (stu[max].award < stu[i].award)max = i;
	printf("%s\n%d\n%d", stu[max].name, stu[max].award, all_we_get);
}
