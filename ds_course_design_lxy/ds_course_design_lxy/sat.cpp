#include"def.h"
#include"func.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
extern char FileName[200];
extern struct SAT P;
extern Sud S;
extern clause* p1;
//初始化问题
void initP(struct SAT* P)
{
	P->root = NULL;
	P->vnum = P->stnum = 0;
	for (int i = 0; i < MAX_VARNUM + 1; i++)
		P->count[i] = P->ans[i] = 0;
}
//DPLL算法
void DPLL(struct SAT* P)
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
//读取一个cnf文件的注释
void ReadFile_check(struct SAT* P, FILE* fp)
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
//读取一个cnf文件的各个子句
void ReadFile(struct SAT* P, FILE* fp)
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
	clause* p1 = (clause*)malloc(sizeof(clause)); //p1是一个指向子句的指针
	P->root = p1;
	for (int i = 1; i <= P->stnum; i++)
	{
		if (i != 1)//第一个子句时，不用为p1申请储存空间
		{
			p1->next = (clause*)malloc(sizeof(clause));
			p1 = p1->next;
		}
		int u = 0;//用于记录各个变量
		p1->mark = 0; p1->num = 0; p1->head = NULL;
		fscanf(fp, "%d", &u);
		cNode* p = NULL;//p是一个指向文字的指针
		if (u) { //读取第一个数据
			P->count[abs(u)]++;
			p = (cNode*)malloc(sizeof(cNode));
			p1->head = p;
			p1->num++;
			p->data = u;
			p->mark = 0;
			fscanf(fp, "%d", &u);
		}
		while (u)//u不是终止符0时，循环读取后面的数据
		{
			P->count[abs(u)]++;
			p->next = (cNode*)malloc(sizeof(cNode));
			p = p->next;
			p1->num++;
			p->data = u;
			p->mark = 0;
			fscanf(fp, "%d", &u);
		}
		if (p) p->next = NULL;
	}
	p1->next = NULL;
	return;
}
//打印cnf文件中的各个子句
void PrintFile(struct SAT* P)
{
	if (!P->stnum) { printf("尚未读取文件！\n"); return; }
	printf("文件中的子句如下：\n");
	printf("___________________________\n");
	clause* p1 = P->root;
	while (p1)
	{
		cNode* p = NULL;
		printf("%d: ", p1->num);
		for (p = p1->head; p; p = p->next)
			printf("%5d", p->data);
		printf("\n");
		p1 = p1->next;
	}
	printf("___________________________\n");
	return;
}
//在子句集中找到一个单子句，返回该单子句中所包含的文字的值
int FindUnitClause(struct SAT* P)
{
	clause* p1 = NULL;
	cNode* p = NULL;
	int unit = 0;
	for (p1 = P->root; p1; p1 = p1->next)
	{
		if (p1->mark) continue;
		if (p1->num > 1) continue;
		p = p1->head;
		while (p && p->mark) p = p->next;
		if (p) {
			unit = p->data; break;
		}
	}
	return unit;
}
//从子句集中删除包含x的子句，并从各个子句删除文字-x，保存删除时的深度depth
status DeleteUnitClause(struct SAT* P, int x, int depth)
{
	clause* p1 = NULL;
	cNode* p = NULL;
	for (p1 = P->root; p1; p1 = p1->next)
	{
		if (p1->mark) continue;                    //如果句子已经被删除，则指针指向下一个句子
		for (p = p1->head; p; p = p->next)           //遍历子句中每个文字
		{
			if (p->mark) continue;                 //如果文字已经被删除，则指针指向下一个文字
			if (p->data == x)                     //如果文字与已经赋值的文字相同，则删除这个子句
			{
				p1->mark = depth;                  //将子句标记为回溯深度，删除句子
				P->stnum--;                        //减少子句集中句子的数目
				for (p = p1->head; p; p = p->next)   //从头开始遍历子句，减少未被标记的文字出现的次数
				{
					if (p->mark) continue;         //如果文字在之前已经被删除，则指针指向下一个文字
					else {
						P->count[abs(p->data)]--;//p->mark = depth;//此处是增加的句子
					}//减少子句中现有文字在子句集中出现的数目
				}
				break;                             //删除子句后退出文字遍历的循环
			}
			else if (p->data + x == 0)            //如果文字与已经赋值的文字相反，则从子句中删除该文字
			{
				p->mark = depth;                   //从子句中删除该文字，用depth表示其回溯深度
				p1->num--;                         //更新子句中文字的数目
				P->count[abs(p->data)]--;         //减少文字在子句集中出现的次数
				if (p1->num == 0) return ERROR;    //如果出现空子句，即发生冲突，返回ERROR
			}
		}
	}
	return OK;//不出现冲突，返回OK
}
//恢复被删除的变元和相关子句
void recover(struct SAT* P, int depth)
{
	clause* p1 = NULL;
	cNode* p = NULL;
	for (p1 = P->root; p1; p1 = p1->next)
	{
		if (p1->mark == depth)//若子句在depth层被删除
		{
			p1->mark = 0;//恢复其有效性
			P->stnum++;
			for (p = p1->head; p; p = p->next)
			{
				if (p->mark == depth)//若文字在depth层被删除
				{
					p->mark = 0;//恢复其有效性
					p1->num++;//增加子句中文字的数目
					P->count[abs(p->data)]++;//更新文字出现的次数
					continue;
				}
				else if (p->mark == 0) P->count[abs(p->data)]++;//更新未被删除的文字出现的次数
			}
			continue;
		}
		for (p = p1->head; p; p = p->next)//若子句在depth层未被删除，检查该子句是否有在depth层被删除的变量
		{
			if (p->mark != depth) continue;
			p->mark = 0;                     //恢复文字的有效性
			p1->num++;                       //增加子句中文字的数目
			P->count[abs(p->data)]++;       //更新文字出现的次数
		}
	}
}
//释放子句s的空间(仅释放s的空间，不考虑指向子句s的前一子句和s指向的后一子句)
void FreeClause(clause* s)
{
	cNode* p1;
	for (p1 = s->head; p1;)
	{
		cNode* p2 = p1;
		p1 = p1->next;
		free(p2);
	}
	free(s);
}
//在P的根节点后运用首插法插入一个单子句，单子句中唯一文字的值为x
void AddUnitClause(struct SAT* P, int x)
{
	clause* p1 = (clause*)malloc(sizeof(clause));
	cNode* p = (cNode*)malloc(sizeof(cNode));
	clause* p2 = P->root;
	//P->root=p1,p1->nextst=p2
	p1->mark = 0;
	p1->next = p2;
	p1->num = 1;
	p1->head = p;
	p->mark = 0;
	p->data = x;
	p->next = NULL;
	P->stnum++;
	P->root = p1;
	P->count[abs(x)]++;
}
//删除AddUnitClause函数插入的第一个子句，并释放其储存空间
void DeleteFirstClause(struct SAT* P)
{
	clause* p1 = P->root;
	P->count[abs(p1->head->data)]--;
	P->root = p1->next;
	P->stnum--;
	FreeClause(p1);
}
//改进算法权值计算公式
double J(int n)
{
	return pow(2.0, (double)(-n));
}
//改进算法备用（如果没有全为正的变元的子句时）
int getNextBool_2SidedJW_optimized(clause* cnf)
{
	int boolCnt = P.vnum;
	double* weight = (double*)malloc(sizeof(double) * (boolCnt * 2 + 1));
	for (int i = 0; i <= boolCnt * 2; i++)
		weight[i] = 0.0;
	for (clause* pc = cnf; pc; pc = pc->next)
		for (cNode* pn = pc->head; pn; pn = pn->next)
		{
			if (pn->data > 0)
				weight[pn->data] += J(pc->num);
			else
				weight[boolCnt - pn->data] += J(pc->num);
		}
	double maxWeight = 0.0;
	int maxBool;
	for (int i = 1; i <= boolCnt; i++)
		if (weight[i] + weight[i + boolCnt] > maxWeight)
		{
			maxWeight = weight[i] + weight[i + boolCnt], maxBool = i;
		}
	if (weight[maxBool] < weight[maxBool + boolCnt])
		maxBool = -maxBool;
	free(weight);
	return maxBool;
}
//改进算法
int getNextBool_Positive_2SidedJW(clause* cnf)
{	
	int boolCnt = 100000000;
	int* mark = (int*)malloc(sizeof(int) * (boolCnt + 1));
	double* weight = (double*)malloc(sizeof(double) * (boolCnt * 2 + 1));
	for (int i = 0; i <= boolCnt; i++)
		mark[i] = 0;
	for (int i = 0; i <= boolCnt * 2; i++)
		weight[i] = 0.0;
	for (clause* pc = cnf; pc; pc = pc->next)
		for (cNode* pn = pc->head; pn; pn = pn->next)
		{
			if (pn->data < 0)
				break;
			else if (pn->next == NULL)
			{
				for (cNode* tmp = pc->head; tmp; tmp = tmp->next)
					mark[tmp->data] = 1;
				break;
			}
		}
	for (clause* pc = cnf; pc; pc = pc->next)
		for (cNode* pn = pc->head; pn; pn = pn->next)
		{
			if (mark[abs(pn->data)])
			{
				if (pn->data > 0)
					weight[pn->data] += J(pc->num);
				else
					weight[boolCnt - pn->data] += J(pc->num);
			}
		}
	free(mark);
	double maxWeight = 0.0;
	int maxBool = 0;
	for (int i = 1; i <= boolCnt; i++)
		if (weight[i] + weight[i + boolCnt] > maxWeight)
		{
			maxWeight = weight[i] + weight[i + boolCnt], maxBool = i;
		}
	if (weight[maxBool] < weight[maxBool + boolCnt])
		maxBool = -maxBool;
	free(weight);
	if (maxBool == 0)
		maxBool = getNextBool_2SidedJW_optimized(cnf);
	return maxBool;
}
//改进前算法（找到一个出现次数最多的变量，返回变量的值，返回值总是正值）
int SelectMax(struct SAT* P)
{
	int max = 0;
	int ans = 0;
	for (int i = 1; i <= P->vnum; i++)
		if (P->count[i] > max) { max = P->count[i]; ans = i; }
	return ans;
}
//打印各个变量出现的次数
void PrintCount(struct SAT* P)
{
	for (int i = 1; i <= P->vnum; i++)
		printf("变量%d出现的次数为: %d\n", i, P->count[i]);
}
//对SAT问题求解，P为所求解的问题，depth为已经进行的深度，x为线索变量
status solve(struct SAT* P, int depth, int x)
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
	//int maxv = getNextBool_Positive_2SidedJW(P->root);
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
//给后缀为.cnf的文件形成其对应的答案文件，result为运行结果，time为运行时间，name为cnf文件名
void FormAnsFile(struct SAT* P, int result, int time, char name[200])
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
//打印SAT文件的答案
void PrintAns(struct SAT P)
{
	for (int i = 1; i <= P.vnum; i++)
	{
		printf("%5d ", (P.ans[i] * 2 - 1) * i);
		if (!(i % 10))printf("\n");
	}
}
//检查答案是否正确
status CheckAns(struct SAT P)
{
	clause* p1 = NULL;
	cNode* p = NULL;
	int flag = 1;
	for (p1 = P.root; p1; p1 = p1->next)
	{
		int count = 0;
		for (p = p1->head; p; p = p->next)
		{
			if (p->data > 0 && P.ans[p->data]) count++;
			else if (p->data < 0 && !P.ans[-p->data])count++;
			if (count) break;
		}
		if (count == 0) flag = 0;
	}
	if (flag == 1) return OK;
	else return ERROR;
}
//差劲的算法
int SelectFirst(struct SAT* P)
{
	clause* p1 = P->root;
	cNode* p = NULL;
	for (p1 = P->root; p1; p1 = p1->next)
		for (p = p1->head; p; p = p->next)
			if (p->mark == 0) return p->data;
}
//差劲的算法
status solve1(struct SAT* P, int depth, int x)
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
