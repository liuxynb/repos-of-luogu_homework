#include"define.h"
#include"function.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
extern char FileName[200];
extern struct problem P;
extern sud S;
extern statement* p1;
void SudSolve() {
	initS(&S);
	printf("����������ļ���:");
	scanf("%s", FileName);
	ReadSudFile(&S, FileName);
	transform(S, FileName);
	problem* P = (problem*)malloc(sizeof(problem));
	initP(P);
	FILE* fp = fopen(FileName, "r");
	ReadFile(P, fp);
	time_t t1, t2;
	t1 = clock();
	solve(P, 1, 0);
	t2 = clock();
	printf("DPLL������ʱ%2d ms\n", t2 - t1);
	SudAns(P, &S);
	PrintSud(S);
}
int VarTrans(int i, int j, int n) {
	return (i - 1) * 81 + (j - 1) * 9 + n;
}
void initS(sud* S)
{
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 9; j++)
			S->original[i][j] = S->pattern[i][j] = 0;
	S->num = 0;
}
void ReadSudFile(sud* S, char FileName[200])
{
	char ch;
	FILE* fp = NULL;
	fp = fopen(FileName, "r");
	if (!fp) {
		printf("��ʧ�ܣ������ļ����������롣\n"); return;
	}
	else printf("�ļ��򿪳ɹ���\n");
	int i = 1, j = 1;
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch >= '0' && ch <= '9') {
			S->original[i][j] = ch - '0', j++; if (ch - '0') S->num++;
		}
		else if (ch == '.') j++;
		if (j >= 10) j = 1, i++;
		if (i >= 10) break;
	}
	fclose(fp);
	return;
}
void PrintSud(sud S)
{
	printf("ԭ�����й���%d����ʾ���֣���ʼ��ʽ���£�\n", S.num);
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
			printf("%3d", S.original[i][j]);
		printf("\n");
	}
	printf("���������£�\n");
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
			printf("%3d", S.pattern[i][j]);
		printf("\n");
	}
	return;
}
void transform(sud S, char FileName[200])
{
	int len = strlen(FileName);
	FileName[len] = '.'; FileName[len + 1] = 'c'; FileName[len + 2] = 'n'; FileName[len + 3] = 'f';
	FILE* fp = NULL;
	fp = fopen(FileName, "w");
	int d[9][2] = { {0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2} };
	fprintf(fp, "p cnf %d %d\n", 729, 11988 + S.num * 9);
	int x, y, n;
	int i, j, count;
	{//�����й���¼��cnf�ļ�
		for (i = 1; i <= 9; i++) {
			for (j = 1; j <= 9; j++)
			{
				if (S.original[i][j]) {
					fprintf(fp, "%d 0\n", VarTrans(i, j, S.original[i][j]));
					for (int x = 1; x <= 9; x++)
					{
						if (x == S.original[i][j]) continue;
						fprintf(fp, "%d 0\n", -VarTrans(i, j, x));
					}
				}
			}
		}
	}
	{//����������¼��cnf�ļ�
		for (i = 1; i <= 9; i++)//����9�У�ÿһ����(9*C92+9)���Ӿ�
		{
			for (n = 1; n <= 9; n++)//111��121��131����nΪ��������֣�9��ѭ����ÿѭ��һ������һ������
			{
				for (j = 1; j <= 9; j++)//jΪ�кţ�
					fprintf(fp, "%d ", VarTrans(i, j, n));
				fprintf(fp, "0\n");
			}
			for (n = 1; n <= 9; n++)//nΪ��������֣�9��ѭ��
				for (count = 1; count <= 9; count++)//����ѭ�������111���121���ȣ���C92������
					for (j = count + 1; j <= 9; j++)
						fprintf(fp, "%d %d 0\n", -VarTrans(i, count, n), -VarTrans(i, j, n));
		}
		for (j = 1; j <= 9; j++)//����9�У�ÿһ����(9*C92+9)���Ӿ�
		{
			for (n = 1; n <= 9; n++)//111��211��311����nΪ��������֣�9��ѭ����ÿѭ��һ������һ������
			{
				for (i = 1; i <= 9; i++)//iΪ�к�
					fprintf(fp, "%d ", VarTrans(i, j, n));
				fprintf(fp, "0\n");
			}
			for (n = 1; n <= 9; n++)//nΪ��������֣�9��ѭ��
				for (count = 1; count <= 9; count++)//����ѭ�������111���211���ȣ���C92������
					for (i = count + 1; i <= 9; i++)
						fprintf(fp, "%d %d 0\n", -VarTrans(count, j, n), -VarTrans(i, j, n));
		}
		for (count = 0; count < 9; count++)//����9���Ź���ÿ��������(9*C92+9)���Ӿ�
		{
			x = 1 + d[count][0] * 3;
			y = 1 + d[count][1] * 3;//ÿ���������ϽǸ��ӵ�λ��
			for (n = 1; n <= 9; n++)//nΪ���������
			{
				for (int m = 0; m < 9; m++)
					fprintf(fp, "%d ", VarTrans(x + d[m][0], y + d[m][1], n));
				fprintf(fp, "0\n");
			}
			for (n = 1; n <= 9; n++)//nΪ��������֣�9��ѭ��
				for (int m1 = 0; m1 < 9; m1++)//���Ƹ����е�9��λ�ã���C92������
					for (int m2 = m1 + 1; m2 < 9; m2++)
						fprintf(fp, "%d %d 0\n", -VarTrans(x + d[m1][0], y + d[m1][1], n), -VarTrans(x + d[m2][0], y + d[m2][1], n));
		}
		for (i = 1; i <= 9; i++) {
			for (j = 1; j <= 9; j++)//����81�����ӣ�ÿ��������(C92+1)������
			{
				for (n = 1; n <= 9; n++)//nΪ���������
					fprintf(fp, "%d ", VarTrans(i, j, n));
				fprintf(fp, "0\n");
				for (n = 1; n <= 9; n++)
					for (count = n + 1; count <= 9; count++)
						fprintf(fp, "%d %d 0\n", -VarTrans(i, j, n), -VarTrans(i, j, count));
			}
		}
	}
	//������¼��cnf�ļ�
	fclose(fp);
}
void SudAns(struct problem* P, sud* S)
{
	int i, j, n;
	for (i = 1; i <= 9; i++)
		for (j = 1; j <= 9; j++)
			for (n = 1; n <= 9; n++)
				if (P->ans[VarTrans(i, j, n)] == 1)
					S->pattern[i][j] = n;
}
void SudPlay()
{
	int choice = 1, diff, op;
	int x, y, v;
	while (choice) {
		system("cls");
		printf("��ѡ���Ѷȣ�\n");
		printf("   1.��     2.�е�     3.���� \n");
		scanf("%d", &diff);
		printf("�����������������Եȡ���");
		sud* k = Sudcreate();//����γ�һ������
		for (int i = 1; i <= 9; i++)
			for (int j = 1; j <= 9; j++)
				k->original[i][j] = k->pattern[i][j];
		DigHole(k);//�������ڶ�
		for (int i = 1; i <= (3 - diff) * 10; i++) //�����Ѷȸ�����ʾ
			hint(k);
		op = 1;
		while (op)
		{
			system("cls");
			printf("------------sudoku------------\n\n");
			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9; j++) {
					printf("%3d", k->original[i][j]);
				}
				printf("\n");
			}
			printf("------------------------------\n");
			printf("\n1.��д        2.������ʾ\n0.��ʾ��/�˳�\n");
			scanf("%d", &op);
			if (op == 2) hint(k);
			if (op == 1)
			{
				printf("\n������д�����������ֵ:");
				scanf("%d%d%d", &x, &y, &v);
				if (!k->original[x][y] && v == k->pattern[x][y])
				{
					printf("\n��д��ȷ!\n");
					k->original[x][y] = k->pattern[x][y];
					getchar(); getchar();
				}
				else {
					printf("\n�𰸴���\n");
					getchar(); getchar();
				}
			}
		}
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				printf("%3d", k->pattern[i][j]);
			}
			printf("\n");
		}
		printf("1.����һ��       0.�˳�\n");
		free(k);
		scanf("%d", &choice);
	}
}
void FormSudFile(FILE* fp, sud* k) //������д��һ���ļ���
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(fp, "%d ", k->original[i][j]);
		}
		fprintf(fp, "\n");
	}
}
sud* Sudcreate() {
	int x, y, v;
	srand(time(NULL));
	x = rand() % 9 + 1;//���ȷ������һ��λ�õ���ֵ
	y = rand() % 9 + 1;
	v = rand() % 9 + 1;
	sud* k = (sud*)malloc(sizeof(sud));
	initS(k);
	k->num = 1;
	k->original[x][y] = v;
	FILE* fp = fopen("sud.txt", "w");
	FormSudFile(fp, k);//�γ�һ�������ļ�
	fclose(fp);

	char temp[200] = "sud.txt";
	transform(*k, temp);
	problem* P = (problem*)malloc(sizeof(problem));
	initP(P);
	fp = fopen(temp, "r");
	ReadFile(P, fp);
	fclose(fp);
	time_t t1, t2;
	t1 = clock();
	solve(P, 1, 0);//���ֻ����һ�����ֵ�����
	t2 = clock();
	SudAns(P, k);
	k->num = 81;
	return k;
}
void DigHole(sud* k) {
	for (int i = 1; i <= 9; i++) {
		if (i % 2) {
			for (int j = 1; j <= 9; j++) {
				Candig(k, i, j);
			}
		}
		else {
			for (int j = 9; j >= 1; j--) {
				Candig(k, i, j);
			}
		}
	}
}
status Candig(sud* k, int x, int y) //�������޸Ķ���original�Ļ�����
{
	char temp[200] = "temp";
	FILE* fp1;
	int flag;
	if (k->original[x][y] == 0) return ERROR;
	for (int i = 1; i <= 9; i++) //�����ԭ������֮���8�����֣�������������˵�������ڶ�
	{
		if (i == k->pattern[x][y]) continue;//��ԭ������ͬ����Ƚ���һ������
		k->original[x][y] = i;//���ո�����һ�����֣�������Ƿ��н�
		transform(*k, temp);//���ڶ�λ����������ֵ�������µ�cnf�ļ�
		problem* P = (problem*)malloc(sizeof(problem));
		initP(P);
		fp1 = fopen(temp, "r");
		ReadFile(P, fp1);
		fclose(fp1);
		flag = solve(P, 1, 0);
		if (flag == OK) {//�������㣬˵�������ڶ����������ָ���ֵ
			k->original[x][y] = k->pattern[x][y];
			return ERROR;
		}
	}
	k->original[x][y] = 0;//�����ڶ�
	k->num--;
	return OK;
}
void hint(sud* k) {
	int x, y, flag;
	flag = 1;
	srand(time(NULL));
	while (flag) {
		x = rand() % 9 + 1;
		y = rand() % 9 + 1;
		if (!k->original[x][y]) {
			k->original[x][y] = k->pattern[x][y];
			flag = 0;
		}
	}
}