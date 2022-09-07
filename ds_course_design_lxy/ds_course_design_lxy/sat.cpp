#include"def.h"
#include"func.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
extern char FileName[200];
extern struct SAT P;
extern Sud S;
extern clause* p1;
//��ʼ������
void initP(struct SAT* P)
{
	P->root = NULL;
	P->vnum = P->stnum = 0;
	for (int i = 0; i < MAX_VARNUM + 1; i++)
		P->count[i] = P->ans[i] = 0;
}
//DPLL�㷨
void DPLL(struct SAT* P)
{
	if (P->stnum == 0) { printf("��δ��ȡ�ļ���"); return; }
	time_t t1, t2;
	t1 = clock();
	int result = solve(P, 1, 0);
	t2 = clock();
	recover(P, 1);
	if (result == OK) printf("�����㣡\n");
	else printf("�������㣡\n");
	time_t t3, t4;
	t3 = clock();
	result = solve1(P, 1, 0);
	t4 = clock();
	if (t2 - t1 > t4 - t3) {
		printf("DPLL�����Ż�ǰ��ʱ%2d ms\n", t2 - t1);
		printf("DPLL�����Ż�����ʱ%2d ms\n", t4 - t3);
	}
	else {
		printf("DPLL�����Ż�ǰ��ʱ%2d ms\n", t4 - t3);
		printf("DPLL�����Ż�����ʱ%2d ms\n", t2 - t1);
	}
	FormAnsFile(P, result, t2 - t1, FileName);
}
//��ȡһ��cnf�ļ���ע��
void ReadFile_check(struct SAT* P, FILE* fp)
{
	if (!fp) {
		printf("��ʧ�ܣ������ļ����������롣\n"); return;
	}
	else printf("�ļ��򿪳ɹ���\n");
	char ch, a[5000];
	ch = fgetc(fp);
	printf("����ע���������£�\n");
	while (ch == 'c') {
		fgets(a, 5000, fp);
		printf("c %s", a);
		ch = fgetc(fp);
	}
}
//��ȡһ��cnf�ļ��ĸ����Ӿ�
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
	clause* p1 = (clause*)malloc(sizeof(clause)); //p1��һ��ָ���Ӿ��ָ��
	P->root = p1;
	for (int i = 1; i <= P->stnum; i++)
	{
		if (i != 1)//��һ���Ӿ�ʱ������Ϊp1���봢��ռ�
		{
			p1->next = (clause*)malloc(sizeof(clause));
			p1 = p1->next;
		}
		int u = 0;//���ڼ�¼��������
		p1->mark = 0; p1->num = 0; p1->head = NULL;
		fscanf(fp, "%d", &u);
		cNode* p = NULL;//p��һ��ָ�����ֵ�ָ��
		if (u) { //��ȡ��һ������
			P->count[abs(u)]++;
			p = (cNode*)malloc(sizeof(cNode));
			p1->head = p;
			p1->num++;
			p->data = u;
			p->mark = 0;
			fscanf(fp, "%d", &u);
		}
		while (u)//u������ֹ��0ʱ��ѭ����ȡ���������
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
//��ӡcnf�ļ��еĸ����Ӿ�
void PrintFile(struct SAT* P)
{
	if (!P->stnum) { printf("��δ��ȡ�ļ���\n"); return; }
	printf("�ļ��е��Ӿ����£�\n");
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
//���Ӿ伯���ҵ�һ�����Ӿ䣬���ظõ��Ӿ��������������ֵ�ֵ
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
//���Ӿ伯��ɾ������x���Ӿ䣬���Ӹ����Ӿ�ɾ������-x������ɾ��ʱ�����depth
status DeleteUnitClause(struct SAT* P, int x, int depth)
{
	clause* p1 = NULL;
	cNode* p = NULL;
	for (p1 = P->root; p1; p1 = p1->next)
	{
		if (p1->mark) continue;                    //��������Ѿ���ɾ������ָ��ָ����һ������
		for (p = p1->head; p; p = p->next)           //�����Ӿ���ÿ������
		{
			if (p->mark) continue;                 //��������Ѿ���ɾ������ָ��ָ����һ������
			if (p->data == x)                     //����������Ѿ���ֵ��������ͬ����ɾ������Ӿ�
			{
				p1->mark = depth;                  //���Ӿ���Ϊ������ȣ�ɾ������
				P->stnum--;                        //�����Ӿ伯�о��ӵ���Ŀ
				for (p = p1->head; p; p = p->next)   //��ͷ��ʼ�����Ӿ䣬����δ����ǵ����ֳ��ֵĴ���
				{
					if (p->mark) continue;         //���������֮ǰ�Ѿ���ɾ������ָ��ָ����һ������
					else {
						P->count[abs(p->data)]--;//p->mark = depth;//�˴������ӵľ���
					}//�����Ӿ��������������Ӿ伯�г��ֵ���Ŀ
				}
				break;                             //ɾ���Ӿ���˳����ֱ�����ѭ��
			}
			else if (p->data + x == 0)            //����������Ѿ���ֵ�������෴������Ӿ���ɾ��������
			{
				p->mark = depth;                   //���Ӿ���ɾ�������֣���depth��ʾ��������
				p1->num--;                         //�����Ӿ������ֵ���Ŀ
				P->count[abs(p->data)]--;         //�����������Ӿ伯�г��ֵĴ���
				if (p1->num == 0) return ERROR;    //������ֿ��Ӿ䣬��������ͻ������ERROR
			}
		}
	}
	return OK;//�����ֳ�ͻ������OK
}
//�ָ���ɾ���ı�Ԫ������Ӿ�
void recover(struct SAT* P, int depth)
{
	clause* p1 = NULL;
	cNode* p = NULL;
	for (p1 = P->root; p1; p1 = p1->next)
	{
		if (p1->mark == depth)//���Ӿ���depth�㱻ɾ��
		{
			p1->mark = 0;//�ָ�����Ч��
			P->stnum++;
			for (p = p1->head; p; p = p->next)
			{
				if (p->mark == depth)//��������depth�㱻ɾ��
				{
					p->mark = 0;//�ָ�����Ч��
					p1->num++;//�����Ӿ������ֵ���Ŀ
					P->count[abs(p->data)]++;//�������ֳ��ֵĴ���
					continue;
				}
				else if (p->mark == 0) P->count[abs(p->data)]++;//����δ��ɾ�������ֳ��ֵĴ���
			}
			continue;
		}
		for (p = p1->head; p; p = p->next)//���Ӿ���depth��δ��ɾ���������Ӿ��Ƿ�����depth�㱻ɾ���ı���
		{
			if (p->mark != depth) continue;
			p->mark = 0;                     //�ָ����ֵ���Ч��
			p1->num++;                       //�����Ӿ������ֵ���Ŀ
			P->count[abs(p->data)]++;       //�������ֳ��ֵĴ���
		}
	}
}
//�ͷ��Ӿ�s�Ŀռ�(���ͷ�s�Ŀռ䣬������ָ���Ӿ�s��ǰһ�Ӿ��sָ��ĺ�һ�Ӿ�)
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
//��P�ĸ��ڵ�������ײ巨����һ�����Ӿ䣬���Ӿ���Ψһ���ֵ�ֵΪx
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
//ɾ��AddUnitClause��������ĵ�һ���Ӿ䣬���ͷ��䴢��ռ�
void DeleteFirstClause(struct SAT* P)
{
	clause* p1 = P->root;
	P->count[abs(p1->head->data)]--;
	P->root = p1->next;
	P->stnum--;
	FreeClause(p1);
}
//�Ľ��㷨Ȩֵ���㹫ʽ
double J(int n)
{
	return pow(2.0, (double)(-n));
}
//�Ľ��㷨���ã����û��ȫΪ���ı�Ԫ���Ӿ�ʱ��
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
//�Ľ��㷨
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
//�Ľ�ǰ�㷨���ҵ�һ�����ִ������ı��������ر�����ֵ������ֵ������ֵ��
int SelectMax(struct SAT* P)
{
	int max = 0;
	int ans = 0;
	for (int i = 1; i <= P->vnum; i++)
		if (P->count[i] > max) { max = P->count[i]; ans = i; }
	return ans;
}
//��ӡ�����������ֵĴ���
void PrintCount(struct SAT* P)
{
	for (int i = 1; i <= P->vnum; i++)
		printf("����%d���ֵĴ���Ϊ: %d\n", i, P->count[i]);
}
//��SAT������⣬PΪ���������⣬depthΪ�Ѿ����е���ȣ�xΪ��������
status solve(struct SAT* P, int depth, int x)
{
	int single = 0;
	if (!x) single = FindUnitClause(P);//���û�и�������ֵ������Ѱһ�����Ӿ�
	else single = x;//�������������ֵ�����Ӿ�ı�����Ϊ����ֵ
	while (single)//����Ӿ伯�����ҵ����Ӿ�
	{
		if (single > 0) P->ans[single] = true;//�����Ӿ丳ֵ���絥�Ӿ�Ϊ������ȡֵ1���絥�Ӿ���зǣ���ȡֵ0
		else P->ans[-single] = false;
		int flag = DeleteUnitClause(P, single, depth);//���ݵ��Ӿ䴫������ɾ���������Ӿ�
		if (flag == ERROR) return ERROR;//�緵��ֵΪERROR���������޽⣬�����������������
		single = FindUnitClause(P);//Ѱ����һ�����Ӿ�
	}
	int maxv = SelectMax(P);//�ҵ�һ�����ִ������ı�Ԫ
	//int maxv = getNextBool_Positive_2SidedJW(P->root);
	if (!maxv) return OK;//����Ҳ��������ı�Ԫ����������ϣ�����OK
	AddUnitClause(P, maxv);//ѡȡ�ı���ȡ1�������Ӿ伯
	if (solve(P, depth + 1, maxv)) {//�ոռ���ĵ��Ӿ��Ϊ�棬��Ϊ����ֵ
		recover(P, depth + 1);//��solveΪ�棬��ָ�����һ��
		DeleteFirstClause(P);//ɾ������ĵ��Ӿ�
		return OK;//���ɹ�
	}
	recover(P, depth + 1);//��solve��Ϊ�棬��ָ�����һ��
	DeleteFirstClause(P);//ɾ������ĵ��Ӿ�
	AddUnitClause(P, 0 - maxv);//�����䷴��
	if (solve(P, depth + 1, 0 - maxv)) {//�ոռ���ĵ��Ӿ��Ϊ�棬��Ϊ����ֵ
		recover(P, depth + 1);//��solveΪ�棬��ָ�����һ��
		DeleteFirstClause(P);//ɾ������ĵ��Ӿ�
		return OK;//���ɹ�
	}
	recover(P, depth + 1);//��solve��Ϊ�棬��ָ�����һ��
	DeleteFirstClause(P);//ɾ������ĵ��Ӿ�
	return ERROR;//�纯���������ˣ������޽⣬����ERROR
}
//����׺Ϊ.cnf���ļ��γ����Ӧ�Ĵ��ļ���resultΪ���н����timeΪ����ʱ�䣬nameΪcnf�ļ���
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
//��ӡSAT�ļ��Ĵ�
void PrintAns(struct SAT P)
{
	for (int i = 1; i <= P.vnum; i++)
	{
		printf("%5d ", (P.ans[i] * 2 - 1) * i);
		if (!(i % 10))printf("\n");
	}
}
//�����Ƿ���ȷ
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
//����㷨
int SelectFirst(struct SAT* P)
{
	clause* p1 = P->root;
	cNode* p = NULL;
	for (p1 = P->root; p1; p1 = p1->next)
		for (p = p1->head; p; p = p->next)
			if (p->mark == 0) return p->data;
}
//����㷨
status solve1(struct SAT* P, int depth, int x)
{
	int single = 0;
	if (!x) single = FindUnitClause(P);//���û�и�������ֵ������Ѱһ�����Ӿ�
	else single = x;//�������������ֵ�����Ӿ�ı�����Ϊ����ֵ
	while (single)//����Ӿ伯�����ҵ����Ӿ�
	{
		if (single > 0) P->ans[single] = true;//�����Ӿ丳ֵ���絥�Ӿ�Ϊ������ȡֵ1���絥�Ӿ���зǣ���ȡֵ0
		else P->ans[-single] = false;
		int flag = DeleteUnitClause(P, single, depth);//���ݵ��Ӿ䴫������ɾ���������Ӿ�
		if (flag == ERROR) return ERROR;//�緵��ֵΪERROR���������޽⣬�����������������
		single = FindUnitClause(P);//Ѱ����һ�����Ӿ�
	}
	int maxv = SelectFirst(P);//�ҵ�һ�����ִ������ı�Ԫ
	if (!maxv) return OK;//����Ҳ��������ı�Ԫ����������ϣ�����OK
	AddUnitClause(P, maxv);//ѡȡ�ı���ȡ1�������Ӿ伯
	if (solve(P, depth + 1, maxv)) {//�ոռ���ĵ��Ӿ��Ϊ�棬��Ϊ����ֵ
		recover(P, depth + 1);//��solveΪ�棬��ָ�����һ��
		DeleteFirstClause(P);//ɾ������ĵ��Ӿ�
		return OK;//���ɹ�
	}
	recover(P, depth + 1);//��solve��Ϊ�棬��ָ�����һ��
	DeleteFirstClause(P);//ɾ������ĵ��Ӿ�
	AddUnitClause(P, 0 - maxv);//�����䷴��
	if (solve(P, depth + 1, 0 - maxv)) {//�ոռ���ĵ��Ӿ��Ϊ�棬��Ϊ����ֵ
		recover(P, depth + 1);//��solveΪ�棬��ָ�����һ��
		DeleteFirstClause(P);//ɾ������ĵ��Ӿ�
		return OK;//���ɹ�
	}
	recover(P, depth + 1);//��solve��Ϊ�棬��ָ�����һ��
	DeleteFirstClause(P);//ɾ������ĵ��Ӿ�
	return ERROR;//�纯���������ˣ������޽⣬����ERROR
}
