#include"def.h"
#include"func.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#define boolCnt Vnum
extern int Vnum;//ȫ�ֱ���V_count:������Ԫ����
extern int* value;//ȫ�ֱ��� value����,���ڼ�¼���Ա�Ԫ����ֵ 1-�� 0-��
extern char filename[200];
extern int transfer[3000];//����λ����ת��Ϊ��Ԫ��Ȼ������
extern int transfer_to_loc[1700];//��Ȼ������ת��Ϊλ�ù�����
/*
 ��������:status Read_file(char * filename,AdjList * & SATList)
 ��������:��ȡ����Ϊfilename���ļ�,�����ļ����ݴ����ڽӱ�
 */
status ReadFile(char* filename, clause*& SATList) {
    if (SATList != NULL) {  //�ڽӱ��Ѵ���
        printf("�ڽӱ��Ѵ���!\n");
        return INFEASIBLE;
    }
    else {
        FILE* fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("�ļ���ʧ��!\n");
            return INFEASIBLE;
        }
        else {
            //Part 1 ����ע��
            char ch1, ch2;
            ch1 = getc(fp);
            while (ch1 == 'c') {
                ch2 = getc(fp);
                while (ch2 != '\n') ch2 = getc(fp);//ֱ���������з�Ϊֹ
                ch1 = getc(fp);
            }//������ch1������p
            getc(fp); getc(fp); getc(fp); getc(fp);//��ȡcnf
            int C_count = 0; Vnum = 0;//V-��Ԫ����.C-�Ӿ����
            fscanf(fp, "%d%d", &Vnum, &C_count);//�����Ԫ�ʹӾ����
            value = (int*)malloc(sizeof(int) * (Vnum + 1));
            for (int i = 1; i <= Vnum; i++) value[i] = 1;
            //Part 2 �������ݽ����ڽӱ�
            SATList = (clause*)malloc(sizeof(clause));
            SATList->head = (cNode*)malloc(sizeof(cNode));
            SATList->next = NULL;
            SATList->head->next = NULL;//�ڽӱ��ͷ��ʼ��

            int number;//���������
            clause* L_tail = SATList;//�ڽӱ��β���
            cNode* N_tail = (cNode*)malloc(sizeof(cNode));//�������β���
            for (int i = 0; i < C_count; i++) {
                clause* newlist = (clause*)malloc(sizeof(clause));//������
                newlist->next = NULL;
                newlist->head = (cNode*)malloc(sizeof(cNode));
                newlist->head->next = NULL;
                newlist->num = 0;//�������ʼ��
                N_tail = newlist->head;//���������β���
                fscanf(fp, "%d", &number);//����
                while (number) {
                    cNode* newnode = (cNode*)malloc(sizeof(cNode));
                    newnode->data = number;
                    newnode->next = NULL;
                    newlist->num++;
                    N_tail->next = newnode;
                    N_tail = newnode;  //β�巨��������
                    fscanf(fp, "%d", &number);
                }
                L_tail->next = newlist;
                L_tail = newlist;//β�巨�����ڽӱ�
            }
            fclose(fp);
            return OK;
        }
    }
}

/*
 ��������:Out_Content_of_File(AdjList * root)
 ��������:��ȡ�ļ������ڽӱ������ڽӱ�����ļ�����
 */
status OutputFileContent(clause* root) {
    if (root == NULL) {
        return INFEASIBLE;
    }
    else {
        clause* hp = NULL;
        cNode* tp = NULL;
        for (hp = root->next; hp != NULL; hp = hp->next) {
            for (tp = hp->head->next; tp; tp = tp->next) {
                printf("%d ", tp->data);
            }
            printf("\n");
        }
        free(hp); free(tp);
        return OK;
    }
}

/*
 ��������:isUnitClaus(SATNode * head)
 ��������:�ж��Ƿ�Ϊ���Ӿ䣬����ǵķ���true�����Ƿ��� false
 */
inline bool isUnitClause(cNode* head) {//�ж��Ƿ�Ϊ���Ӿ�,���������Ӿ������������
    if (head->next != NULL && head->next->next == NULL) {
        return true;
    }
    else {
        return false;
    }
}

/*
 ��������:DestroyAdjList(AdjList * & root)
 ��������:�����ڽӱ�
 */
inline status DestroyAdjList(clause*& root) {
    if (root == NULL) {
        return INFEASIBLE;
    }
    else {
        clause* hp = root->next;//��ͷָ��
        cNode* np = NULL;//���ָ��
        while (hp) {
            np = hp->head;
            while (np) {
                cNode* tp = np;
                np = np->next;
                free(tp);
            }
            clause* tp = hp;
            hp = hp->next;
            free(tp);
        }
        root = NULL;
        return OK;
    }
}

/*
 ��������:AddClause(AdjList * & root,AdjList * newlist)
 ��������:��newlist������root�ڽӱ��ͷ(�ײ巨)
 */

status AddClause(clause*& root, clause*& newlist) {
    if (root == NULL) return INFEASIBLE;
    else {
        newlist->next = root->next;
        root->next = newlist;//�������ڽӱ��ͷ
        return OK;
    }
}

/*
 ��������:RemoveClause(AdjList * & root,AdjList * relist)
 ��������:���ڽӱ�root��ɾ��������relist
 */

inline status RemoveClause(clause*& root, clause* relist) {//�����Ӿ�
    if (root == NULL) return INFEASIBLE;
    else {
        clause* q = root, * p = root->next;
        while (p) {
            if (p == relist)break;
            q = p;
            p = p->next;
        }//�ҵ�relist
        q->next = p->next;
        cNode* tq = NULL, * tp = p->head;
        while (tp) {
            tq = tp;
            tp = tp->next;
            free(tq);
        }//�ͷ�relist����ռ�
        free(p);//�ͷű�ͷ�ռ�
        return OK;
    }
}

/*
 *��������:inline void RemoveNode(AdjList * & linklist,SATNode * Node)
 *��������:���ڽӱ�linklist��ɾ��Node ���
 */
inline void RemoveNode(clause*& linklist, cNode* Node) {
    cNode* q = linklist->head, * p = linklist->head->next;
    for (; p != Node && p; q = p, p = p->next);
    q->next = p->next;
    free(p);
}
/*
 ��������:evaluateClause(SATNode * head)
 ��������:�ж�head��������
 */
bool evaluateClause(cNode* head) {    //�ж������
    cNode* p = head->next;
    while (p) {
        //debug:printf("%d\n",value[p->data]);
        if (p->data > 0 && value[p->data] == 1) return true;
        else if (p->data < 0 && value[-p->data] == 1) return true;
        else p = p->next;
    }
    return false;
}

/*
 ��������:void Back_up(AdjList * & root_1,AdjList * root_2)
 ��������:���ڽӱ�root_2�����ݸ��Ʊ��ݵ��ڽӱ�root_1
 */
inline void Back_up(clause*& root_1, clause* origin_root) {
    root_1->next = NULL;
    root_1->head = NULL;
    clause* lp = origin_root->next;
    clause* L_tail = root_1;//���ڽӱ��β���
    while (lp) {
        clause* newlist = (clause*)malloc(sizeof(clause));//������
        newlist->next = NULL;
        newlist->head = (cNode*)malloc(sizeof(cNode));
        newlist->num = lp->num;//������ĳ�ʼ��
        cNode* np = lp->head->next;
        cNode* N_tail = newlist->head;//�������β���
        while (np) {
            cNode* newnode = (cNode*)malloc(sizeof(cNode));
            newnode->next = NULL;
            newnode->data = np->data;
            N_tail->next = newnode;
            N_tail = newnode;
            np = np->next;
        }
        L_tail->next = newlist;
        L_tail = newlist;
        lp = lp->next;
    }
}
/*
 *��������:bool emptyClause(AdjList * root)
 *��������:�ж��ڽӱ����Ƿ��п��Ӿ�(�޷�����ľ���)
 */
inline bool emptyClause(clause* root) {
    clause* lp = root->next;

    for (; lp; lp = lp->next) {
        if (lp->head->next == NULL) return true;
    }
    return false;
}
/*
 *�������ƣ�void DestroyClause(AdjList * & alist)
 *�������ܣ������Ӿ䲢�ͷ��Ӿ�alist�Ŀռ�
 */
void DestroyClause(clause*& alist) {
    cNode* p = alist->head, * q = p;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    alist->head = NULL;
    free(alist);
    alist = NULL;
}

int getMaxbool_optimized(clause* SATList) {
    int* cnt = (int*)malloc(sizeof(int) * (2 * Vnum + 1));
    for (int i = 1; i <= 2 * Vnum; i++) cnt[i] = 0;//��������ʼ��
    clause* lp = SATList->next;
    for (; lp; lp = lp->next) {
        cNode* np = lp->head->next;
        for (; np; np = np->next) {
            if (np->data > 0) cnt[np->data]++;
            else cnt[Vnum - np->data]++;
        }
    }//����Ƶ��ͳ��
    int max = 0;
    int Maxword = 0;
    for (int i = 1; i <= Vnum; i++) {
        if (cnt[i] > max) {
            max = cnt[i];
            Maxword = i;
        }
    }//�ҵ�����Ƶ����������Ԫ
    if (Maxword == 0) {
        for (int i = Vnum + 1; i <= Vnum * 2; i++) {
            if (cnt[i] > max) {
                max = cnt[i];
                Maxword = i - Vnum;
            }
        }
    }//���ȫΪ��,�ҵ�����Ƶ�����ĸ���Ԫ
    free(cnt);//�ͷſռ�
    return Maxword;
}

int getMaxbool(clause* SATList) {
    int* cnt = (int*)malloc(sizeof(int) * (Vnum + 1));
    for (int i = 1; i <= Vnum; i++) cnt[i] = 0;//��������ʼ��
    clause* lp = SATList->next;
    for (; lp; lp = lp->next) {
        cNode* np = lp->head->next;
        for (; np; np = np->next) {
            cnt[abs(np->data)]++;
        }
    }//����Ƶ��ͳ��
    int max = 0;
    int Maxword = 0;
    for (int i = 1; i <= Vnum; i++) {
        if (cnt[i] > max) {
            max = cnt[i];
            Maxword = i;
        }
    }
    free(cnt);//�ͷſռ�
    return Maxword;
}

int getbool_2sides(clause* root) {
    double* weight = (double*)malloc(sizeof(double) * (Vnum + 1));
    for (int i = 1; i <= Vnum; i++) {
        weight[i] = 0.0;
    }
    clause* lp = root->next;
    for (; lp; lp = lp->next) {
        cNode* tp = lp->head->next;
        for (; tp; tp = tp->next) {
            weight[abs(tp->data)] += pow(2, -lp->num);
        }
    }
    int Maxword = 0;
    double Maxweight = 0.0;
    for (int i = 1; i <= Vnum; i++) {
        if (weight[i] >= Maxweight) {
            Maxweight = weight[i];
            Maxword = i;
        }
    }
    free(weight);
    return Maxword;
}
int getbool_2sides_optimized(clause* root) {
    double* weight = (double*)malloc(sizeof(double) * (2 * Vnum + 1));
    for (int i = 1; i <= 2 * Vnum; i++) {
        weight[i] = 0.0;
    }
    clause* lp = root->next;
    for (; lp; lp = lp->next) {
        cNode* tp = lp->head->next;
        for (; tp; tp = tp->next) {
            if (tp->data > 0) {
                weight[tp->data] += pow(2, -lp->num);
            }
            else {
                weight[Vnum - tp->data] += pow(2, -lp->num);
            }
        }
    }
    int Maxword = 0;
    double Maxweight = 0.0;
    for (int i = 1; i <= Vnum; i++) {
        if (weight[i] + weight[i + Vnum] > Maxweight) {
            Maxweight = weight[i] + weight[i + Vnum];
            Maxword = i;
        }
    }
    if (weight[Maxword] < weight[Maxword + Vnum]) {
        Maxword = -Maxword;
    }
    free(weight);
    return Maxword;
}
double J(int n)
{
    return pow(2.0, (double)(-n));
}
int getNextBool_Positive_2SidedJW(clause* root)
{
    
    int* mark = (int*)malloc(sizeof(int) * (boolCnt + 1));
    double* weight = (double*)malloc(sizeof(double) * (boolCnt * 2 + 1));
    for (int i = 0; i <= boolCnt; i++)
        mark[i] = 0;
    for (int i = 0; i <= boolCnt * 2; i++)
        weight[i] = 0.0;
    for (clause* pc = root; pc; pc = pc->next)
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
    for (clause* pc = root; pc; pc = pc->next)
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
        maxBool = getbool_2sides_optimized(root);
    return maxBool;
}
/*
 *�������ƣ�inline int DPLL(AdjList * & SATList)
 *�������ܣ�����DPLL�㷨���SATList
 */
bool DPLL(clause*& SATList, int choice) {//DPLL������
    while (1) {
        clause* lp = SATList->next;
        int num = 0;
        while (lp && isUnitClause(lp->head) == false) lp = lp->next;
        if (lp == NULL) break;
        else {
            num = lp->head->next->data;
            if (num > 0) value[num] = 1;
            else value[-num] = 0;
        }//�ҵ����Ӿ䲢Ϊ�丳ֵ
        clause* lq = SATList->next;
        clause* pre = SATList;//ǰ�����
        while (lq) {
            clause* c_lq = lq->next;
            cNode* tq = lq->head->next;
            while (tq)
            {
                if (tq->data == num) {//���Ӿ�,�Ӿ�����

                    //RemoveClause(SATList,lq);
                    pre->next = lq->next;
                    DestroyClause(lq);//ɾ���Ӿ�
                    break;;
                }
                else if (tq->data == -num) {//�����֣���������
                    RemoveNode(lq, tq);
                    lq->num--;
                    break;
                }
                else {
                    tq = tq->next;
                }
            }
            if (lq != NULL) {
                pre = lq;
            }
            lq = c_lq;
        }//���õ��Ӿ�����������
        free(lq);
        if (SATList->next == NULL) {        //�ռ�
            //printf("�ռ�!\n");
            return 1;
        }
        else if (emptyClause(SATList)) {     //���п��Ӿ�(�����������)
           //printf("���п��Ӿ�!\n");
            return 0;
        }
    }
    int Maxword = 0;
    switch (choice) {
    case 1: {
        Maxword = getMaxbool(SATList);
        break;
    }
    case 2: {
        Maxword = getMaxbool_optimized(SATList);
        break;
    }
    case 3: {
        Maxword = getbool_2sides(SATList);
        break;
    }
    case 4: {
        Maxword = getbool_2sides_optimized(SATList);
        break;
    }
    case 5: {
        Maxword = getNextBool_Positive_2SidedJW(SATList);
        break;
    }
    }
    clause* newlist = (clause*)malloc(sizeof(clause));
    newlist->next = NULL;
    newlist->head = (cNode*)malloc(sizeof(cNode));
    cNode* newnode = (cNode*)malloc(sizeof(cNode));
    newnode->next = NULL;
    newnode->data = Maxword;
    newlist->head->next = newnode;
    clause* c_SATList = (clause*)malloc(sizeof(clause));
    Back_up(c_SATList, SATList);
    AddClause(c_SATList, newlist);
    if (DPLL(c_SATList, choice) == 1) return 1;//��һ��֧
    DestroyAdjList(c_SATList);

    newlist = (clause*)malloc(sizeof(clause));
    newlist->next = NULL;
    newlist->head = (cNode*)malloc(sizeof(cNode));
    newnode = (cNode*)malloc(sizeof(cNode));
    newnode->next = NULL;
    newnode->data = -Maxword;
    newlist->head->next = newnode;
    AddClause(SATList, newlist);
    if (DPLL(SATList, choice) == 1) return 1;
    DestroyAdjList(SATList);
    return 0;
}

/*
 *�������ƣ�status Preserve_the_Result(char filename[],int ret,double time)
 *�������ܣ���������Լ����ʱ�䱣����filename��res��׺�ļ���
 */
status PreserveResult(char filename[], int ret, double time) {
    for (int i = 0; filename[i] != '\0'; i++) {
        if (filename[i] == '.' && filename[i + 4] == '\0') {
            filename[i + 1] = 'r';
            filename[i + 2] = 'e';
            filename[i + 3] = 's';
            break;
        }
    }//�޸ĺ�׺
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("��ʧ��!\n");
        return INFEASIBLE;
    }
    else {
        fprintf(fp, "s %d\nv ", ret);
        if (ret) {
            for (int i = 1; i <= Vnum; i++) {
                if (value[i] > 0) {
                    fprintf(fp, "%d ", i);
                }
                else {
                    fprintf(fp, "%d ", -i);
                }
            }
        }
        fprintf(fp, "\nt %lf", time);
        fclose(fp);
        return OK;
    }
}