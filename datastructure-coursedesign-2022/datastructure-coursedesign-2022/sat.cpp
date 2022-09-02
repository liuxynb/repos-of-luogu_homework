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
void _ReadFile(struct problem* P, FILE* fp)
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
	statement* p1 = (statement*)malloc(sizeof(statement)); //p1��һ��ָ���Ӿ��ָ��
	P->root = p1;
	for (int i = 1; i <= P->stnum; i++)
	{
		if (i != 1)//��һ���Ӿ�ʱ������Ϊp1���봢��ռ�
		{
			p1->nextst = (statement*)malloc(sizeof(statement));
			p1 = p1->nextst;
		}
		int u = 0;//���ڼ�¼��������
		p1->mark = 0; p1->num = 0; p1->next = NULL;
		fscanf(fp, "%d", &u);
		node* p = NULL;//p��һ��ָ�����ֵ�ָ��
		if (u) { //��ȡ��һ������
			P->count[abs(u)]++;
			p = (node*)malloc(sizeof(node));
			p1->next = p;
			p1->num++;
			p->value = u;
			p->mark = 0;
			fscanf(fp, "%d", &u);
		}
		while (u)//u������ֹ��0ʱ��ѭ����ȡ���������
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
	if (!P->stnum) { printf("��δ��ȡ�ļ���\n"); return; }
	printf("�ļ��е��Ӿ����£�\n");
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
		if (p1->mark) continue;                    //��������Ѿ���ɾ������ָ��ָ����һ������
		for (p = p1->next; p; p = p->next)           //�����Ӿ���ÿ������
		{
			if (p->mark) continue;                 //��������Ѿ���ɾ������ָ��ָ����һ������
			if (p->value == x)                     //����������Ѿ���ֵ��������ͬ����ɾ������Ӿ�
			{
				p1->mark = depth;                  //���Ӿ���Ϊ������ȣ�ɾ������
				P->stnum--;                        //�����Ӿ伯�о��ӵ���Ŀ
				for (p = p1->next; p; p = p->next)   //��ͷ��ʼ�����Ӿ䣬����δ����ǵ����ֳ��ֵĴ���
				{
					if (p->mark) continue;         //���������֮ǰ�Ѿ���ɾ������ָ��ָ����һ������
					else {
						P->count[abs(p->value)]--;//p->mark = depth;//�˴������ӵľ���
					}//�����Ӿ��������������Ӿ伯�г��ֵ���Ŀ
				}
				break;                             //ɾ���Ӿ���˳����ֱ�����ѭ��
			}
			else if (p->value + x == 0)            //����������Ѿ���ֵ�������෴������Ӿ���ɾ��������
			{
				p->mark = depth;                   //���Ӿ���ɾ�������֣���depth��ʾ��������
				p1->num--;                         //�����Ӿ������ֵ���Ŀ
				P->count[abs(p->value)]--;         //�����������Ӿ伯�г��ֵĴ���
				if (p1->num == 0) return ERROR;    //������ֿ��Ӿ䣬��������ͻ������ERROR
			}
		}
	}
	return OK;//�����ֳ�ͻ������OK
}
void recover(struct problem* P, int depth)
{
	statement* p1 = NULL;
	node* p = NULL;
	for (p1 = P->root; p1; p1 = p1->nextst)
	{
		if (p1->mark == depth)//���Ӿ���depth�㱻ɾ��
		{
			p1->mark = 0;//�ָ�����Ч��
			P->stnum++;
			for (p = p1->next; p; p = p->next)
			{
				if (p->mark == depth)//��������depth�㱻ɾ��
				{
					p->mark = 0;//�ָ�����Ч��
					p1->num++;//�����Ӿ������ֵ���Ŀ
					P->count[abs(p->value)]++;//�������ֳ��ֵĴ���
					continue;
				}
				else if (p->mark == 0) P->count[abs(p->value)]++;//����δ��ɾ�������ֳ��ֵĴ���
			}
			continue;
		}
		for (p = p1->next; p; p = p->next)//���Ӿ���depth��δ��ɾ���������Ӿ��Ƿ�����depth�㱻ɾ���ı���
		{
			if (p->mark != depth) continue;
			p->mark = 0;                     //�ָ����ֵ���Ч��
			p1->num++;                       //�����Ӿ������ֵ���Ŀ
			P->count[abs(p->value)]++;       //�������ֳ��ֵĴ���
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
		printf("����%d���ֵĴ���Ϊ: %d\n", i, P->count[i]);
}
status solve(struct problem* P, int depth, int x)
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
