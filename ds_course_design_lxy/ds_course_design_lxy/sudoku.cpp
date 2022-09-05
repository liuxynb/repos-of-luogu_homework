#include"def.h"
#include"func.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
extern char FileName[200];
extern struct problem P;
extern Sud S;
extern statement* p1;
void SudSolve() {
	initS(&S);
	printf("请输入测试文件名:");
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
	printf("DPLL过程用时%2d ms\n", t2 - t1);
	SudAns(P, &S);
	PrintSud(S);
}
int VarTrans(int i, int j, int n) {
	return (i - 1) * 81 + (j - 1) * 9 + n;
}
void initS(Sud* S)
{
	for (int i = 0; i <= 9; i++)
		for (int j = 0; j <= 9; j++)
			S->original[i][j] = S->pattern[i][j] = 0;
	S->num = 0;
}
void ReadSudFile(Sud* S, char FileName[200])
{
	char ch;
	FILE* fp = NULL;
	fp = fopen(FileName, "r");
	if (!fp) {
		printf("打开失败，请检查文件并重新输入。\n"); return;
	}
	else printf("文件打开成功！\n");
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
void PrintSud(Sud S)
{
	printf("原数独中共有%d个提示数字，初始形式如下：\n", S.num);
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
			printf("%3d", S.original[i][j]);
		printf("\n");
	}
	printf("数独答案如下：\n");
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
			printf("%3d", S.pattern[i][j]);
		printf("\n");
	}
	return;
}
void transform(Sud S, char FileName[200])
{
	int len = strlen(FileName);
	FileName[len] = '.'; FileName[len + 1] = 'c'; FileName[len + 2] = 'n'; FileName[len + 3] = 'f';
	FILE* fp = NULL;
	fp = fopen(FileName, "w");
	int d[9][2] = { {0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2} };
	fprintf(fp, "p cnf %d %d\n", 729, 11988 + S.num * 9);
	int x, y, n;
	int i, j, count;
	{//将特有规则录入cnf文件
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
	{//将基础规则录入cnf文件
		for (i = 1; i <= 9; i++)//对于9行，每一行有(9*C92+9)个子句
		{
			for (n = 1; n <= 9; n++)//111或121或131……n为填入的数字，9次循环，每循环一次填入一个句子
			{
				for (j = 1; j <= 9; j++)//j为列号，
					fprintf(fp, "%d ", VarTrans(i, j, n));
				fprintf(fp, "0\n");
			}
			for (n = 1; n <= 9; n++)//n为填入的数字，9次循环
				for (count = 1; count <= 9; count++)//这里循环输入非111或非121，等，共C92个句子
					for (j = count + 1; j <= 9; j++)
						fprintf(fp, "%d %d 0\n", -VarTrans(i, count, n), -VarTrans(i, j, n));
		}
		for (j = 1; j <= 9; j++)//对于9列，每一列有(9*C92+9)个子句
		{
			for (n = 1; n <= 9; n++)//111或211或311……n为填入的数字，9次循环，每循环一次填入一个句子
			{
				for (i = 1; i <= 9; i++)//i为行号
					fprintf(fp, "%d ", VarTrans(i, j, n));
				fprintf(fp, "0\n");
			}
			for (n = 1; n <= 9; n++)//n为填入的数字，9次循环
				for (count = 1; count <= 9; count++)//这里循环输入非111或非211，等，共C92个句子
					for (i = count + 1; i <= 9; i++)
						fprintf(fp, "%d %d 0\n", -VarTrans(count, j, n), -VarTrans(i, j, n));
		}
		for (count = 0; count < 9; count++)//对于9个九宫格，每个格子有(9*C92+9)个子句
		{
			x = 1 + d[count][0] * 3;
			y = 1 + d[count][1] * 3;//每个宫格左上角格子的位置
			for (n = 1; n <= 9; n++)//n为填入的数字
			{
				for (int m = 0; m < 9; m++)
					fprintf(fp, "%d ", VarTrans(x + d[m][0], y + d[m][1], n));
				fprintf(fp, "0\n");
			}
			for (n = 1; n <= 9; n++)//n为填入的数字，9次循环
				for (int m1 = 0; m1 < 9; m1++)//控制格子中的9个位置，共C92个句子
					for (int m2 = m1 + 1; m2 < 9; m2++)
						fprintf(fp, "%d %d 0\n", -VarTrans(x + d[m1][0], y + d[m1][1], n), -VarTrans(x + d[m2][0], y + d[m2][1], n));
		}
		for (i = 1; i <= 9; i++) {
			for (j = 1; j <= 9; j++)//对于81个格子，每个格子有(C92+1)个句子
			{
				for (n = 1; n <= 9; n++)//n为填入的数字
					fprintf(fp, "%d ", VarTrans(i, j, n));
				fprintf(fp, "0\n");
				for (n = 1; n <= 9; n++)
					for (count = n + 1; count <= 9; count++)
						fprintf(fp, "%d %d 0\n", -VarTrans(i, j, n), -VarTrans(i, j, count));
			}
		}
	}
	//将规则录入cnf文件
	fclose(fp);
}
void SudAns(struct problem* P, Sud* S)
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
		printf("请选择难度：\n");
		printf("   1.简单     2.中等     3.困难 \n");
		scanf("%d", &diff);
		printf("正在生成数独，请稍等……");
		DSud* K = Sudcreate();//随机形成一个数独
		Sud* k = K->k1;
		Sud* k2 = K->k2;
		for (int i = 1; i <= 9; i++)
			for (int j = 1; j <= 9; j++)
				k->original[i][j] = k->pattern[i][j];
		for (int i = 1; i <= 9; i++)
			for (int j = 1; j <= 9; j++)
				k2->original[i][j] = k2->pattern[i][j];
		DigHole(k);//给数独挖洞
		DigHole(k2);//给数独挖洞
		for (int i = 7; i <= 9; i++)//恢复公共部分
			for (int j = 7; j <= 9; j++)
			{
				k->original[i][j] = k->pattern[i][j]; k->num++;
				k2->original[i-6][j-6] = k2->pattern[i-6][j-6]; k2->num++;
			}

		DigHole2(k, k2);//一起判断公共部分
		for (int i = 1; i <= (3 - diff) * 10; i++) //根据难度给出提示
		{
			hint(k, k2);
			
		}
		op = 1;
		while (op)
		{
			system("cls");
			printf("------------sudoku------------\n\n");
			for (int i = 1; i <= 6; i++) {
				for (int j = 1; j <= 9; j++) {
					printf("%3d", k->original[i][j]);
				}
				printf("\n");
			}
			for (int i = 7; i <= 9; i++) {
				//printf("                           ");
				for (int j = 1; j <= 9; j++) {
					printf("%3d", k->original[i][j]);
				}
				for (int j = 4; j <= 9; j++)
				{
					printf("%3d", k2->original[i][j]);
				}
				printf("\n");
			}
			for (int i = 4; i <= 9; i++) {
				printf("                  ");
				for (int j = 1; j <= 9; j++) {
					printf("%3d", k2->original[i][j]);
				}
				printf("\n");
			}
		
			
			printf("------------------------------\n");
			printf("\n1.填写        2.更多提示\n0.显示答案/退出\n");
			scanf("%d", &op);
			if (op == 2) hint(k, k2);
			if (op == 1)
			{
				printf("\n输入填写的坐标与待填值:");
				scanf("%d%d%d", &x, &y, &v);
				if (!k->original[x][y] && v == k->pattern[x][y])
				{
					printf("\n填写正确!\n");
					k->original[x][y] = k->pattern[x][y];
					getchar(); getchar();
				}
				else {
					printf("\n答案错误\n");
					getchar(); getchar();
				}
			}
		}
		for (int i = 1; i <= 6; i++) {
			for (int j = 1; j <= 9; j++) {
				printf("%3d", k->pattern[i][j]);
			}
			printf("\n");
		}
		for (int i = 7; i <= 9; i++) {
			//printf("                           ");
			for (int j = 1; j <= 9; j++) {
				printf("%3d", k->pattern[i][j]);
			}
			for (int j = 4; j <= 9; j++)
			{
				printf("%3d", k2->pattern[i][j]);
			}
			printf("\n");
		}
		for (int i = 4; i <= 9; i++) {
			printf("                  ");
			for (int j = 1; j <= 9; j++) {
				printf("%3d", k2->pattern[i][j]);
			}
			printf("\n");
		}
		printf("1.再来一局       0.退出\n");
		free(k);
		scanf("%d", &choice);
	}
}
void FormSudFile(FILE* fp, Sud* k) //将数独写入一个文件中
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(fp, "%d ", k->original[i][j]);
		}
		fprintf(fp, "\n");
	}
}
void InputSud2(Sud* k, Sud* k2, problem* P)
{
	int i, j, n;
	for (i = 7; i <= 9; i++)
		for (j = 7; j <= 9; j++)
			for (n = 1; n <= 9; n++)
				if (P->ans[VarTrans(i, j, n)] == 1)
				{
					k2->original[i - 6][j - 6] = n;
					k2->num++;
				}
}
DSud* Sudcreate() 
{
	int x, y, v;
	srand(time(NULL));
	x = rand() % 9 + 1;//随机确定数独一个位置的数值
	y = rand() % 9 + 1;
	v = rand() % 9 + 1;
	Sud* k = (Sud*)malloc(sizeof(Sud));
	Sud* k2 = (Sud*)malloc(sizeof(Sud));
	initS(k);
	initS(k2);
	k->num = 1;
	k->original[x][y] = v;
	FILE* fp = fopen("sud.txt", "w");
	FormSudFile(fp, k);//形成一个数独文件
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
	solve(P, 1, 0);//求解只含有一个数字的数独
	t2 = clock();
	SudAns(P, k);
	k->num = 81;


	//生成二号数独
	InputSud2(k, k2, P);
	FILE* fp2 = fopen("sud2.txt", "w");
	FormSudFile(fp2, k2);//形成一个数独文件
	fclose(fp2);
	char temp2[200] = "sud2.txt";
	transform(*k2, temp2);
	problem* P2 = (problem*)malloc(sizeof(problem));
	initP(P2);
	fp2 = fopen(temp2, "r");
	ReadFile(P2, fp2);
	fclose(fp2);
	solve(P2, 1, 0);//求解只含有一个数字的数独
	SudAns(P2, k2);
	k2->num = 81;
	DSud *K = (DSud*)malloc(sizeof(DSud));
	K->k1 = k;
	K->k2 = k2;
	return K;
}

void DigHole(Sud* k) {
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
void DigHole2(Sud* k,Sud *k2) 
{
	for (int i = 1; i <= 3; i++) 
	{
		int flag1 = 0, flag2 = 0;
		if (i % 2) 
		{
			for (int j = 1; j <= 3; j++) 
			{
				flag1 = Candig2(k, i + 6, j + 6);
				flag2 = Candig2(k2, i, j);
				if (flag1 && flag2)
				{
					k->original[i+6][j+6] = 0;//可以挖洞
					k->num--;
					k2->original[i][j] = 0;
					k2->num--;
				}
			}
		}
		else 
		{
			for (int j = 3; j >= 1; j--) 
			{
				flag1 = Candig2(k, i + 6, j + 6);
				flag2 = Candig2(k2, i, j);
				if (flag1 && flag2)
				{
					k->original[i+6][j+6] = 0;//可以挖洞
					k->num--;
					k2->original[i][j] = 0;
					k2->num--;
				}
			}
		}
	}
}
status Candig(Sud* k, int x, int y) //函数的修改都在original的基础上
{
	char temp[200] = "temp";
	FILE* fp1;
	int flag;
	if (k->original[x][y] == 0) return ERROR;
	for (int i = 1; i <= 9; i++) //试填除原来数字之外的8个数字，若都不能满足说明可以挖洞
	{
		if (i == k->pattern[x][y]) continue;//和原数字相同，则比较下一个数字
		k->original[x][y] = i;//给空格处填入一个数字，检查其是否有解
		transform(*k, temp);//将挖洞位置填入其它值，生成新的cnf文件
		problem* P = (problem*)malloc(sizeof(problem));
		initP(P);
		fp1 = fopen(temp, "r");
		ReadFile(P, fp1);
		fclose(fp1);
		flag = solve(P, 1, 0);
		if (flag == OK) {//若能满足，说明不能挖洞，给数独恢复其值
			k->original[x][y] = k->pattern[x][y];
			return ERROR;
		}
	}
	k->original[x][y] = 0;//可以挖洞
	k->num--;
	return OK;
}
status Candig2(Sud* k, int x, int y) //函数的修改都在original的基础上
{
	char temp[200] = "temp";
	FILE* fp1;
	int flag;
	if (k->original[x][y] == 0) return ERROR;
	for (int i = 1; i <= 9; i++) //试填除原来数字之外的8个数字，若都不能满足说明可以挖洞
	{
		if (i == k->pattern[x][y]) continue;//和原数字相同，则比较下一个数字
		k->original[x][y] = i;//给空格处填入一个数字，检查其是否有解
		transform(*k, temp);//将挖洞位置填入其它值，生成新的cnf文件
		problem* P = (problem*)malloc(sizeof(problem));
		initP(P);
		fp1 = fopen(temp, "r");
		ReadFile(P, fp1);
		fclose(fp1);
		flag = solve(P, 1, 0);
		if (flag == OK) {//若能满足，说明不能挖洞，给数独恢复其值
			k->original[x][y] = k->pattern[x][y];
			return ERROR;
		}
	}
	return OK;
}
void hint(Sud* k,Sud* k2) 
{
	int x, y, flag;
	flag = 1;
	srand(time(NULL));
	while (flag) {
		x = rand() % 9 + 1;
		y = rand() % 9 + 1;
		if (!k->original[x][y]|| !k2->original[x][y]) 
		{
			k->original[x][y] = k->pattern[x][y];
			k2->original[x][y] = k2->pattern[x][y];
			flag = 0;
		}
	}

}

