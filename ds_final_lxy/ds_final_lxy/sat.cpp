#include"def.h"
#include"func.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#define boolCnt Vnum
extern int Vnum;//全局变量V_count:布尔变元个数
extern int* value;//全局变量 value数组,用于记录所以变元的真值 1-真 0-假
extern char filename[200];
extern int transfer[3000];//构造位置数转换为变元自然排列数
extern int transfer_to_loc[1700];//自然排列数转换为位置构造数
/*
 函数名称:status Read_file(char * filename,AdjList * & SATList)
 函数功能:读取名字为filename的文件,根据文件内容创建邻接表
 */
status ReadFile(char* filename, clause*& SATList) {
    if (SATList != NULL) {  //邻接表已创建
        printf("邻接表已存在!\n");
        return INFEASIBLE;
    }
    else {
        FILE* fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("文件打开失败!\n");
            return INFEASIBLE;
        }
        else {
            //Part 1 读入注释
            char ch1, ch2;
            ch1 = getc(fp);
            while (ch1 == 'c') {
                ch2 = getc(fp);
                while (ch2 != '\n') ch2 = getc(fp);//直到读到换行符为止
                ch1 = getc(fp);
            }//结束后ch1读到了p
            getc(fp); getc(fp); getc(fp); getc(fp);//读取cnf
            int C_count = 0; Vnum = 0;//V-变元个数.C-从句个数
            fscanf(fp, "%d%d", &Vnum, &C_count);//读入变元和从句个数
            value = (int*)malloc(sizeof(int) * (Vnum + 1));
            for (int i = 1; i <= Vnum; i++) value[i] = 1;
            //Part 2 根据内容建立邻接表
            SATList = (clause*)malloc(sizeof(clause));
            SATList->head = (cNode*)malloc(sizeof(cNode));
            SATList->next = NULL;
            SATList->head->next = NULL;//邻接表表头初始化

            int number;//读入的数据
            clause* L_tail = SATList;//邻接表的尾结点
            cNode* N_tail = (cNode*)malloc(sizeof(cNode));//单链表的尾结点
            for (int i = 0; i < C_count; i++) {
                clause* newlist = (clause*)malloc(sizeof(clause));//新链表
                newlist->next = NULL;
                newlist->head = (cNode*)malloc(sizeof(cNode));
                newlist->head->next = NULL;
                newlist->num = 0;//新链表初始化
                N_tail = newlist->head;//单个链表的尾结点
                fscanf(fp, "%d", &number);//读入
                while (number) {
                    cNode* newnode = (cNode*)malloc(sizeof(cNode));
                    newnode->data = number;
                    newnode->next = NULL;
                    newlist->num++;
                    N_tail->next = newnode;
                    N_tail = newnode;  //尾插法构建链表
                    fscanf(fp, "%d", &number);
                }
                L_tail->next = newlist;
                L_tail = newlist;//尾插法构建邻接表
            }
            fclose(fp);
            return OK;
        }
    }
}

/*
 函数名称:Out_Content_of_File(AdjList * root)
 函数功能:读取文件创建邻接表后根据邻接表输出文件内容
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
 函数名称:isUnitClaus(SATNode * head)
 函数功能:判断是否为单子句，如果是的返回true，不是返回 false
 */
inline bool isUnitClause(cNode* head) {//判断是否为单子句,采用文字子句消隐法，如果
    if (head->next != NULL && head->next->next == NULL) {
        return true;
    }
    else {
        return false;
    }
}

/*
 函数名称:DestroyAdjList(AdjList * & root)
 函数功能:销毁邻接表
 */
inline status DestroyAdjList(clause*& root) {
    if (root == NULL) {
        return INFEASIBLE;
    }
    else {
        clause* hp = root->next;//表头指针
        cNode* np = NULL;//结点指针
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
 函数名称:AddClause(AdjList * & root,AdjList * newlist)
 函数功能:将newlist插入在root邻接表表头(首插法)
 */

status AddClause(clause*& root, clause*& newlist) {
    if (root == NULL) return INFEASIBLE;
    else {
        newlist->next = root->next;
        root->next = newlist;//插入在邻接表表头
        return OK;
    }
}

/*
 函数名字:RemoveClause(AdjList * & root,AdjList * relist)
 函数功能:从邻接表root中删除单链表relist
 */

inline status RemoveClause(clause*& root, clause* relist) {//消隐子句
    if (root == NULL) return INFEASIBLE;
    else {
        clause* q = root, * p = root->next;
        while (p) {
            if (p == relist)break;
            q = p;
            p = p->next;
        }//找到relist
        q->next = p->next;
        cNode* tq = NULL, * tp = p->head;
        while (tp) {
            tq = tp;
            tp = tp->next;
            free(tq);
        }//释放relist链表空间
        free(p);//释放表头空间
        return OK;
    }
}

/*
 *函数名称:inline void RemoveNode(AdjList * & linklist,SATNode * Node)
 *函数功能:在邻接表linklist中删除Node 结点
 */
inline void RemoveNode(clause*& linklist, cNode* Node) {
    cNode* q = linklist->head, * p = linklist->head->next;
    for (; p != Node && p; q = p, p = p->next);
    q->next = p->next;
    free(p);
}
/*
 函数名称:evaluateClause(SATNode * head)
 函数功能:判断head链表的真假
 */
bool evaluateClause(cNode* head) {    //判断真假性
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
 函数名称:void Back_up(AdjList * & root_1,AdjList * root_2)
 函数功能:将邻接表root_2的内容复制备份到邻接表root_1
 */
inline void Back_up(clause*& root_1, clause* origin_root) {
    root_1->next = NULL;
    root_1->head = NULL;
    clause* lp = origin_root->next;
    clause* L_tail = root_1;//新邻接表的尾结点
    while (lp) {
        clause* newlist = (clause*)malloc(sizeof(clause));//新链表
        newlist->next = NULL;
        newlist->head = (cNode*)malloc(sizeof(cNode));
        newlist->num = lp->num;//新链表的初始化
        cNode* np = lp->head->next;
        cNode* N_tail = newlist->head;//新链表的尾结点
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
 *函数名称:bool emptyClause(AdjList * root)
 *函数功能:判断邻接表中是否有空子句(无法满足的句子)
 */
inline bool emptyClause(clause* root) {
    clause* lp = root->next;

    for (; lp; lp = lp->next) {
        if (lp->head->next == NULL) return true;
    }
    return false;
}
/*
 *函数名称：void DestroyClause(AdjList * & alist)
 *函数功能：销毁子句并释放子句alist的空间
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
    for (int i = 1; i <= 2 * Vnum; i++) cnt[i] = 0;//计数器初始化
    clause* lp = SATList->next;
    for (; lp; lp = lp->next) {
        cNode* np = lp->head->next;
        for (; np; np = np->next) {
            if (np->data > 0) cnt[np->data]++;
            else cnt[Vnum - np->data]++;
        }
    }//出现频率统计
    int max = 0;
    int Maxword = 0;
    for (int i = 1; i <= Vnum; i++) {
        if (cnt[i] > max) {
            max = cnt[i];
            Maxword = i;
        }
    }//找到出现频率最大的正变元
    if (Maxword == 0) {
        for (int i = Vnum + 1; i <= Vnum * 2; i++) {
            if (cnt[i] > max) {
                max = cnt[i];
                Maxword = i - Vnum;
            }
        }
    }//如果全为负,找到出现频率最大的负变元
    free(cnt);//释放空间
    return Maxword;
}

int getMaxbool(clause* SATList) {
    int* cnt = (int*)malloc(sizeof(int) * (Vnum + 1));
    for (int i = 1; i <= Vnum; i++) cnt[i] = 0;//计数器初始化
    clause* lp = SATList->next;
    for (; lp; lp = lp->next) {
        cNode* np = lp->head->next;
        for (; np; np = np->next) {
            cnt[abs(np->data)]++;
        }
    }//出现频率统计
    int max = 0;
    int Maxword = 0;
    for (int i = 1; i <= Vnum; i++) {
        if (cnt[i] > max) {
            max = cnt[i];
            Maxword = i;
        }
    }
    free(cnt);//释放空间
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
 *函数名称：inline int DPLL(AdjList * & SATList)
 *函数功能：利用DPLL算法求解SATList
 */
bool DPLL(clause*& SATList, int choice) {//DPLL求解过程
    while (1) {
        clause* lp = SATList->next;
        int num = 0;
        while (lp && isUnitClause(lp->head) == false) lp = lp->next;
        if (lp == NULL) break;
        else {
            num = lp->head->next->data;
            if (num > 0) value[num] = 1;
            else value[-num] = 0;
        }//找到单子句并为其赋值
        clause* lq = SATList->next;
        clause* pre = SATList;//前驱结点
        while (lq) {
            clause* c_lq = lq->next;
            cNode* tq = lq->head->next;
            while (tq)
            {
                if (tq->data == num) {//真子句,子句消隐

                    //RemoveClause(SATList,lq);
                    pre->next = lq->next;
                    DestroyClause(lq);//删除子句
                    break;;
                }
                else if (tq->data == -num) {//假文字，文字消隐
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
        }//利用单子句规则遍历化简
        free(lq);
        if (SATList->next == NULL) {        //空集
            //printf("空集!\n");
            return 1;
        }
        else if (emptyClause(SATList)) {     //含有空子句(不可满足句子)
           //printf("含有空子句!\n");
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
    if (DPLL(c_SATList, choice) == 1) return 1;//第一分支
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
 *函数名称：status Preserve_the_Result(char filename[],int ret,double time)
 *函数功能：将求解结果以及求解时间保存在filename的res后缀文件中
 */
status PreserveResult(char filename[], int ret, double time) {
    for (int i = 0; filename[i] != '\0'; i++) {
        if (filename[i] == '.' && filename[i + 4] == '\0') {
            filename[i + 1] = 'r';
            filename[i + 2] = 'e';
            filename[i + 3] = 's';
            break;
        }
    }//修改后缀
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("打开失败!\n");
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