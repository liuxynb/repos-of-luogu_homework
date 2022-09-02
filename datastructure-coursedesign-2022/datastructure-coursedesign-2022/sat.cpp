#include"define.h"
#include"function.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
extern char FileName[200];
extern struct problem P;
extern sud S;
extern statement* p1;
void initP(struct problem* P)
{
	P->root = NULL;
	P->vnum = P->stnum = 0;
	for (int i = 0; i < MAX_VARNUM + 1; i++)
		P->count[i] = P->ans[i] = 0;
}
void DPLL(struct problem* P)
{
	if (P->stnum == 0) { printf("尚未读取文件！"); return; }
	time_t t1, t2;
	t1 = clock();
	int result = solve(P, 1, 0);
	t2 = clock();
	recover(P, 1);
	if (result == OK) printf("可满足！\n");
	else printf("不可满足！\n");
	time_t t3, t4;
	t3 = clock();
	result = solve1(P, 1, 0);
	t4 = clock();
	if (t2 - t1 > t4 - t3) {
		printf("DPLL过程优化前用时%2d ms\n", t2 - t1);
		printf("DPLL过程优化后用时%2d ms\n", t4 - t3);
	}
	else {
		printf("DPLL过程优化前用时%2d ms\n", t4 - t3);
		printf("DPLL过程优化后用时%2d ms\n", t2 - t1);
	}
	FormAnsFile(P, result, t2 - t1, FileName);
}
void _ReadFile(struct problem* P, FILE* fp)
{
	if (!fp) {
		printf("打开失败，请检查文件并重新输入。\n"); return;
	}
	else printf("文件打开成功！\n");
	char ch, a[5000];
	ch = fgetc(fp);
	printf("其中注释内容如下：\n");
	while (ch == 'c') {
		fgets(a, 5000, fp);
		printf("c %s", a);
		ch = fgetc(fp);
	}
}
void ReadFile(struct problem* P, FILE* fp)
{
	/*while (fread(&ch, sizeof(char), 1, fp))
	{
		if (ch != 'p') printf("%c", ch);
		else break;
	}*/
	if (!fp) return;
	char a[5000], ch;
	ch = fgetc(fp);
	while (ch == 'c') {
		fgets(a, 5000, fp);
		ch = fgetc(fp);
	}
	fscanf(fp, "%s%d%d", a, &P->vnum, &P->stnum);
	statement* p1 = (statement*)malloc(sizeof(statement)); //p1是一个指向子句的指针
	P->root = p1;
	for (int i = 1; i <= P->stnum; i++)
	{
		if (i != 1)//第一个子句时，不用为p1申请储存空间
		{
			p1->nextst = (statement*)malloc(sizeof(statement));
			p1 = p1->nextst;
		}
		int u = 0;//用于记录各个变量
		p1->mark = 0; p1->num = 0; p1->next = NULL;
		fscanf(fp, "%d", &u);
		node* p = NULL;//p是一个指向文字的指针
		if (u) { //读取第一个数据
			P->count[abs(u)]++;
			p = (node*)malloc(sizeof(node));
			p1->next = p;
			p1->num++;
			p->value = u;
			p->mark = 0;
			fscanf(fp, "%d", &u);
		}
		while (u)//u不是终止符0时，循环读取后面的数据
		{
			P->count[abs(u)]++;
			p->next = (node*)malloc(sizeof(node));
			p = p->next;
			p1->num++;
			p->value = u;
			p->mark = 0;
			fscanf(fp, "%d", &u);
		}
		if (p) p->next = NULL;
	}
	p1->nextst = NULL;
	return;
}
void PrintFile(struct problem* P)
{
	if (!P->stnum) { printf("尚未读取文件！\n"); return; }
	printf("文件中的子句如下：\n");
	printf("___________________________\n");
	statement* p1 = P->root;
	while (p1)
	{
		node* p = NULL;
		printf("%d: ", p1->num);
		for (p = p1->next; p; p = p->next)
			printf("%5d", p->value);
		printf("\n");
		p1 = p1->nextst;
	}
	printf("___________________________\n");
	return;
}
int FindUnitClause(struct problem* P)
{
	statement* p1 = NULL;
	node* p = NULL;
	int unit = 0;
	for (p1 = P->root; p1; p1 = p1->nextst)
	{
		if (p1->mark) continue;
		if (p1->num > 1) continue;
		p = p1->next;
		while (p && p->mark) p = p->next;
		if (p) {
			unit = p->value; break;
		}
	}
	return unit;
}
status DeleteUnitClause(struct problem* P, int x, int depth)
{
	statement* p1 = NULL;
	node* p = NULL;
	for (p1 = P->root; p1; p1 = p1->nextst)
	{
		if (p1->mark) continue;                    //如果句子已经被删除，则指针指向下一个句子
		for (p = p1->next; p; p = p->next)           //遍历子句中每个文字
		{
			if (p->mark) continue;                 //如果文字已经被删除，则指针指向下一个文字
			if (p->value == x)                     //如果文字与已经赋值的文字相同，则删除这个子句
			{
				p1->mark = depth;                  //将子句标记为回溯深度，删除句子
				P->stnum--;                        //减少子句集中句子的数目
				for (p = p1->next; p; p = p->next)   //从头开始遍历子句，减少未被标记的文字出现的次数
				{
					if (p->mark) continue;         //如果文字在之前已经被删除，则指针指向下一个文字
					else {
						P->count[abs(p->value)]--;//p->mark = depth;//此处是增加的句子
					}//减少子句中现有文字在子句集中出现的数目
				}
				break;                             //删除子句后退出文字遍历的循环
			}
			else if (p->value + x == 0)            //如果文字与已经赋值的文字相反，则从子句中删除该文字
			{
				p->mark = depth;                   //从子句中删除该文字，用depth表示其回溯深度
				p1->num--;                         //更新子句中文字的数目
				P->count[abs(p->value)]--;         //减少文字在子句集中出现的次数
				if (p1->num == 0) return ERROR;    //如果出现空子句，即发生冲突，返回ERROR
			}
		}
	}
	return OK;//不出现冲突，返回OK
}
void recover(struct problem* P, int depth)
{
	statement* p1 = NULL;
	node* p = NULL;
	for (p1 = P->root; p1; p1 = p1->nextst)
	{
		if (p1->mark == depth)//若子句在depth层被删除
		{
			p1->mark = 0;//恢复其有效性
			P->stnum++;
			for (p = p1->next; p; p = p->next)
			{
				if (p->mark == depth)//若文字在depth层被删除
				{
					p->mark = 0;//恢复其有效性
					p1->num++;//增加子句中文字的数目
					P->count[abs(p->value)]++;//更新文字出现的次数
					continue;
				}
				else if (p->mark == 0) P->count[abs(p->value)]++;//更新未被删除的文字出现的次数
			}
			continue;
		}
		for (p = p1->next; p; p = p->next)//若子句在depth层未被删除，检查该子句是否有在depth层被删除的变量
		{
			if (p->mark != depth) continue;
			p->mark = 0;                     //恢复文字的有效性
			p1->num++;                       //增加子句中文字的数目
			P->count[abs(p->value)]++;       //更新文字出现的次数
		}
	}
}
void FreeClause(statement* s)
{
	node* p1;
	for (p1 = s->next; p1;)
	{
		node* p2 = p1;
		p1 = p1->next;
		free(p2);
	}
	free(s);
}
void AddUnitClause(struct problem* P, int x)
{
	statement* p1 = (statement*)malloc(sizeof(statement));
	node* p = (node*)malloc(sizeof(node));
	statement* p2 = P->root;
	//P->root=p1,p1->nextst=p2
	p1->mark = 0;
	p1->nextst = p2;
	p1->num = 1;
	p1->next = p;
	p->mark = 0;
	p->value = x;
	p->next = NULL;
	P->stnum++;
	P->root = p1;
	P->count[abs(x)]++;
}
void DeleteFirstClause(struct problem* P)
{
	statement* p1 = P->root;
	P->count[abs(p1->next->value)]--;
	P->root = p1->nextst;
	P->stnum--;
	FreeClause(p1);
}
int SelectMax(struct problem* P)
{
	int max = 0;
	int ans = 0;
	for (int i = 1; i <= P->vnum; i++)
		if (P->count[i] > max) { max = P->count[i]; ans = i; }
	return ans;
}
void PrintCount(struct problem* P)
{
	for (int i = 1; i <= P->vnum; i++)
		printf("变量%d出现的次数为: %d\n", i, P->count[i]);
}
status solve(struct problem* P, int depth, int x)
{
	int single = 0;
	if (!x) single = FindUnitClause(P);//如果没有给出线索值，则找寻一个单子句
	else single = x;//如果给出了线索值，则单子句的变量就为线索值
	while (single)//如果子句集中能找到单子句
	{
		if (single > 0) P->ans[single] = true;//给单子句赋值，如单子句为正，则取值1；如单子句带有非，则取值0
		else P->ans[-single] = false;
		int flag = DeleteUnitClause(P, single, depth);//根据单子句传播策略删除文字与子句
		if (flag == ERROR) return ERROR;//如返回值为ERROR，则问题无解，结束函数并报告错误
		single = FindUnitClause(P);//寻找下一个单子句
	}
	int maxv = SelectMax(P);//找到一个出现次数最多的变元
	if (!maxv) return OK;//如果找不到这样的变元则代表求解完毕，返回OK
	AddUnitClause(P, maxv);//选取的变量取1，加入子句集
	if (solve(P, depth + 1, maxv)) {//刚刚加入的单子句必为真，作为线索值
		recover(P, depth + 1);//若solve为真，则恢复到上一级
		DeleteFirstClause(P);//删除假设的单子句
		return OK;//求解成功
	}
	recover(P, depth + 1);//若solve不为真，则恢复到上一级
	DeleteFirstClause(P);//删除假设的单子句
	AddUnitClause(P, 0 - maxv);//假设其反面
	if (solve(P, depth + 1, 0 - maxv)) {//刚刚加入的单子句必为真，作为线索值
		recover(P, depth + 1);//若solve为真，则恢复到上一级
		DeleteFirstClause(P);//删除假设的单子句
		return OK;//求解成功
	}
	recover(P, depth + 1);//若solve不为真，则恢复到上一级
	DeleteFirstClause(P);//删除假设的单子句
	return ERROR;//如函数运行至此，代表无解，返回ERROR
}
void FormAnsFile(struct problem* P, int result, int time, char name[200])
{
	FILE* fp;
	int len = strlen(name);
	name[len - 3] = 'r';
	name[len - 2] = 'e';
	name[len - 1] = 's';
	fp = fopen(name, "w+");
	fprintf(fp, "s %d", result);
	if (result != 1)
		fprintf(fp, "\nv");
	else
	{
		for (int i = 1; i <= P->vnum; i++)
		{
			if (i == 1) fprintf(fp, "\nv");
			if (i != 1 && (i - 1) % 10 == 0) fprintf(fp, "\n ");
			if (P->ans[i]) fprintf(fp, "%5d", i);
			else fprintf(fp, "%5d", -i);
		}
	}
	fprintf(fp, "\nt %d", time);
	fclose(fp);
}
void PrintAns(struct problem P)
{
	for (int i = 1; i <= P.vnum; i++)
	{
		printf("%5d ", (P.ans[i] * 2 - 1) * i);
		if (!(i % 10))printf("\n");
	}
}
status CheckAns(struct problem P)
{
	statement* p1 = NULL;
	node* p = NULL;
	int flag = 1;
	for (p1 = P.root; p1; p1 = p1->nextst)
	{
		int count = 0;
		for (p = p1->next; p; p = p->next)
		{
			if (p->value > 0 && P.ans[p->value]) count++;
			else if (p->value < 0 && !P.ans[-p->value])count++;
			if (count) break;
		}
		if (count == 0) flag = 0;
	}
	if (flag == 1) return OK;
	else return ERROR;
}
int SelectFirst(struct problem* P)
{
	statement* p1 = P->root;
	node* p = NULL;
	for (p1 = P->root; p1; p1 = p1->nextst)
		for (p = p1->next; p; p = p->next)
			if (p->mark == 0) return p->value;
}
status solve1(struct problem* P, int depth, int x)
{
	int single = 0;
	if (!x) single = FindUnitClause(P);//如果没有给出线索值，则找寻一个单子句
	else single = x;//如果给出了线索值，则单子句的变量就为线索值
	while (single)//如果子句集中能找到单子句
	{
		if (single > 0) P->ans[single] = true;//给单子句赋值，如单子句为正，则取值1；如单子句带有非，则取值0
		else P->ans[-single] = false;
		int flag = DeleteUnitClause(P, single, depth);//根据单子句传播策略删除文字与子句
		if (flag == ERROR) return ERROR;//如返回值为ERROR，则问题无解，结束函数并报告错误
		single = FindUnitClause(P);//寻找下一个单子句
	}
	int maxv = SelectFirst(P);//找到一个出现次数最多的变元
	if (!maxv) return OK;//如果找不到这样的变元则代表求解完毕，返回OK
	AddUnitClause(P, maxv);//选取的变量取1，加入子句集
	if (solve(P, depth + 1, maxv)) {//刚刚加入的单子句必为真，作为线索值
		recover(P, depth + 1);//若solve为真，则恢复到上一级
		DeleteFirstClause(P);//删除假设的单子句
		return OK;//求解成功
	}
	recover(P, depth + 1);//若solve不为真，则恢复到上一级
	DeleteFirstClause(P);//删除假设的单子句
	AddUnitClause(P, 0 - maxv);//假设其反面
	if (solve(P, depth + 1, 0 - maxv)) {//刚刚加入的单子句必为真，作为线索值
		recover(P, depth + 1);//若solve为真，则恢复到上一级
		DeleteFirstClause(P);//删除假设的单子句
		return OK;//求解成功
	}
	recover(P, depth + 1);//若solve不为真，则恢复到上一级
	DeleteFirstClause(P);//删除假设的单子句
	return ERROR;//如函数运行至此，代表无解，返回ERROR
}
