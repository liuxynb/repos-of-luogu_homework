//
//  main.cpp
//  Problem_of_SAT_on_dpll
//
//  Created by 张锦深 on 2022/8/11.
//文字子句消隐法

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define status int
#define OK 1
#define INFEASIBLE -1
//本项目数据结构采用邻接表,dpll算法采用文字子句消隐法
typedef struct LNode {
    int data;
    struct LNode* next;
}SATNode;//
typedef struct Linklists {
    int num;//该子句所含变元个数
    struct Linklists* next;
    LNode* head;
}AdjList;//邻接表表头结点定义

int V_count = 0;//全局变量V_count:布尔变元个数
int* value = NULL;//全局变量 value数组,用于记录所以变元的真值 1-真 0-假
char filename[200];
int transfer[3000];//构造位置数转换为变元自然排列数
int transfer_to_loc[1700];//自然排列数转换为位置构造数

//Part1-CNF
status Read_file(char* filename, AdjList*& SATList);//文件读取/
status Out_Content_of_File(AdjList* root);//全部子句输出/
status DestroyAdjList(AdjList*& root);//销毁邻接表/
bool isUnitClause(SATNode* head);//判断是否为单子句/
bool evaluateClause(SATNode* head);//判断是否子句真假性/
status RemoveClause(AdjList*& root, AdjList* relist);//删除子句/
status AddClause(AdjList*& root, AdjList*& newlist);//添加子句/
void Back_up(AdjList*& root_1, AdjList* origin_root);//备份,用于复制回溯/
bool emptyClause(AdjList* root);//判断是否含有空子句/
bool DPLL(AdjList*& SATList, int choice);//DPLL算法
void DestroyClause(AdjList*& alist);//删除一个子句
status Preserve_the_Result(char filename[], int ret, double time);//保存结果/
void AddNode(SATNode*& head, SATNode*& newnode);//添加结点
int getbool_2sides_optimized(AdjList* root);//优化/
int getbool_2sides(AdjList* root);//同时权衡子句长度和出现频率/
int getMaxbool(AdjList* SATList);//出现频率最大/
int getMaxbool_optimized(AdjList* SATList);//优化/

//Part2-Sudoku
int  Sudoku_Solver(int sudoku[]);//数独解决/
void get_transfer(int transfer[], int transfer_to_loc[]);//得到转换数组,用于自然排列数和位置构造数的转换/
void Create_sudoku(int* sudoku, int idx);//创建双数独格局/
bool isTrue(int sudoku[], int n, int i, int j, int k);//判断填入的数是否符合/
void show_the_sudoku(int sudoku[]);//数独格局呈现
void Diger(int sudoku[], int holes);//挖洞/
void Playsukodu(int* fullboard, int* board, int holes);//交互玩游戏

int main() {
    AdjList* SATList = NULL;
    int op = 1, op1 = 1, op2 = 1;
    while (op) {
        system("cls"); printf("\n\n");
        printf("-------------------------------------------------\n");
        printf("        系统功能菜单\n");
        printf("    1.SAT       2.双数独游戏\n");
        printf("    0.Exit\n");
        printf("-------------------------------------------------\n");
        printf("请选择你的操作[0-2]:");
        scanf("%d", &op);
        switch (op) {
        case 1: {//CNF系统
            op1 = 1;
            while (op1) {
                system("cls");    printf("\n\n");
                printf("        SAT功能菜单 \n");
                printf("-------------------------------------------------\n");
                printf("1.读取cnf文件            2.遍历输出每个子句\n");
                printf("3.DPLL求解SAT问题并保存    0.退出\n");
                // printf("0.退出\n");
                printf("-------------------------------------------------\n");
                printf("    请选择你的操作[0~4]:");
                scanf("%d", &op1);
                switch (op1) {
                case 1: {//Read the CNF_file
                    SATList = NULL;
                    printf("请输入需要读取的文件名!\n");
                    scanf("%s", filename);
                    if (Read_file(filename, SATList) == OK) {
                        printf("读取成功!\n");

                    }
                    else {
                        printf("读取失败!\n");
                    }
                    getchar();
                    getchar();
                    break;
                }
                case 2: {//Output the content of the file
                    if (Out_Content_of_File(SATList) == OK) {
                        printf("输出成功!\n");
                    }
                    else {
                        printf("文件未读取!\n");
                    }
                    getchar();
                    getchar();
                    break;
                }
                case 3: {//Solve the CNF problem with DPLL and preserve the result
                    double begin = clock();
                    int choice;
                    printf("请选择变量决策策略!\n");
                    printf("1.VSIDS         2.VSIDS_optimized\n");
                    printf("3.2Sides_Stragety  4.3_optimized\n");
                    scanf("%d", &choice);
                    int ret = DPLL(SATList, choice);
                    double end = clock();
                    if (ret == 1) {
                        printf("有解!各变元的真值如下\n");
                        for (int i = 1; i <= V_count; i++) {
                            if (value[i] == 1) {
                                printf("%d ", i);
                            }
                            else {
                                printf("-%d ", i);
                            }
                        }
                    }
                    else {
                        printf("无解!\n");
                    }
                    double time = (end - begin) * 1000 / CLOCKS_PER_SEC;
                    printf("\n运行时间为 %lfms\n", time);
                    if (Preserve_the_Result(filename, ret, time) == OK) {
                        printf("保存成功!\n");
                    }
                    else {
                        printf("保存失败!\n");
                    }

                    getchar();
                    getchar();
                    break;
                }
                default:
                    getchar();
                    break;
                }
            }
            getchar();
            getchar();
            break;
        }
        case 2: {//数独系统
            V_count = 729 * 2;
            get_transfer(transfer, transfer_to_loc);
            op2 = 1;
            while (op2) {
                system("cls"); printf("\n\n");
                printf("-------------------------------------------------\n");
                printf("        Suduko功能菜单\n");
                printf("    1.双数独创建并求解     2.双数独游戏\n");
                printf("    0.Exit\n");
                printf("-------------------------------------------------\n");
                printf("    请选择你的操作[0~4]:");
                scanf("%d", &op2);
                switch (op2) {
                case 1: {//Double_sudoku game
                    int sudoku[163] = { 0 };
                    //get_transfer();
                    printf("请输入选择的难度系数[0-5]（0-定制)：\n");
                    int idx;//难度系数
                    scanf("%d", &idx);
                    //V_count=729*2;
                    if (idx) {
                        Create_sudoku(sudoku, idx);
                        printf("\n生成数独题目如下!\n");
                        show_the_sudoku(sudoku);
                    }//挖洞算法创建数独
                    else if (idx == 0) {
                        int n, x, y, num;
                        printf("请输入你想添加的数!(格式 n(1-左上，2-右下） i（行） j（列） k（填入的数）结束输入以0结束\n");
                        scanf("%d%d%d%d", &n, &x, &y, &num);
                        while (n) {
                            if (sudoku[(n - 1) * 81 + (x - 1) * 9 + y] == 0 && isTrue(sudoku, n, x, y, num)) {//未填入且符合填入规则
                                if (n == 1 && x >= 7 && y >= 7) {//第一模块的右下角
                                    sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = num;
                                    sudoku[81 + (x - 7) * 9 + y - 6] = num;
                                }
                                else if (n == 2 && x <= 3 && y <= 3) {//第二模块的右下角
                                    sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = num;
                                    sudoku[(x + 5) * 9 + y + 6] = num;
                                }
                                else {//非交叉部分
                                    sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = num;
                                }
                            }
                            else {
                                printf("输入不合格!\n");
                            }
                            scanf("%d%d%d%d", &n, &x, &y, &num);
                        }
                        printf("定制数独如下!\n");
                        show_the_sudoku(sudoku);
                    }
                    //show_the_sudoku(sudoku);
                    int ret = Sudoku_Solver(sudoku);
                    if (ret) {
                        printf("\n数独解如下!\n");
                        show_the_sudoku(sudoku);
                    }
                    else {
                        printf("数独无解!\n");
                    }
                    getchar();
                    getchar();
                    break;
                }
                case 2: {//PlaytheSudoku
                    printf("请输入选择的难度系数[1-5]：\n");
                    int idx;//难度系数
                    scanf("%d", &idx);
                    int board[163] = { 0 }, fullboard[163] = { 0 };//board为题目 ，fullboard为结果
                    Create_sudoku(fullboard, idx);
                    for (int i = 1; i <= 162; i++) {
                        board[i] = fullboard[i];
                    }//复制得到数独题目board
                    //show_the_sudoku(board);
                    Sudoku_Solver(fullboard);
                    //show_the_sudoku(fullboard);
                    Playsukodu(fullboard, board, idx * 20);
                    break;
                }
                default:
                    break;
                }

            }
            getchar();
            getchar();
            break;
        }
        default:
            getchar();
            getchar();
            break;
        }
    }
    return 0;
}

/*
 函数名称:status Read_file(char * filename,AdjList * & SATList)
 函数功能:读取名字为filename的文件,根据文件内容创建邻接表
 */
status Read_file(char* filename, AdjList*& SATList) {
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
            int C_count = 0; V_count = 0;//V-变元个数.C-从句个数
            fscanf(fp, "%d%d", &V_count, &C_count);//读入变元和从句个数
            value = (int*)malloc(sizeof(int) * (V_count + 1));
            for (int i = 1; i <= V_count; i++) value[i] = 1;
            //Part 2 根据内容建立邻接表
            SATList = (AdjList*)malloc(sizeof(AdjList));
            SATList->head = (SATNode*)malloc(sizeof(SATNode));
            SATList->next = NULL;
            SATList->head->next = NULL;//邻接表表头初始化

            int number;//读入的数据
            AdjList* L_tail = SATList;//邻接表的尾结点
            SATNode* N_tail = (SATNode*)malloc(sizeof(SATNode));//单链表的尾结点
            for (int i = 0; i < C_count; i++) {
                AdjList* newlist = (AdjList*)malloc(sizeof(AdjList));//新链表
                newlist->next = NULL;
                newlist->head = (SATNode*)malloc(sizeof(SATNode));
                newlist->head->next = NULL;
                newlist->num = 0;//新链表初始化
                N_tail = newlist->head;//单个链表的尾结点
                fscanf(fp, "%d", &number);//读入
                while (number) {
                    SATNode* newnode = (SATNode*)malloc(sizeof(SATNode));
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
inline status Out_Content_of_File(AdjList* root) {
    if (root == NULL) {
        return INFEASIBLE;
    }
    else {
        AdjList* hp = NULL;
        SATNode* tp = NULL;
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
inline bool isUnitClause(SATNode* head) {//判断是否为单子句,采用文字子句消隐法，如果
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
inline status DestroyAdjList(AdjList*& root) {
    if (root == NULL) {
        return INFEASIBLE;
    }
    else {
        AdjList* hp = root->next;//表头指针
        SATNode* np = NULL;//结点指针
        while (hp) {
            np = hp->head;
            while (np) {
                SATNode* tp = np;
                np = np->next;
                free(tp);
            }
            AdjList* tp = hp;
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

status AddClause(AdjList*& root, AdjList*& newlist) {
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

inline status RemoveClause(AdjList*& root, AdjList* relist) {//消隐子句
    if (root == NULL) return INFEASIBLE;
    else {
        AdjList* q = root, * p = root->next;
        while (p) {
            if (p == relist)break;
            q = p;
            p = p->next;
        }//找到relist
        q->next = p->next;
        SATNode* tq = NULL, * tp = p->head;
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
inline void RemoveNode(AdjList*& linklist, SATNode* Node) {
    SATNode* q = linklist->head, * p = linklist->head->next;
    for (; p != Node && p; q = p, p = p->next);
    q->next = p->next;
    free(p);
}
/*
 函数名称:evaluateClause(SATNode * head)
 函数功能:判断head链表的真假
 */
bool evaluateClause(SATNode* head) {    //判断真假性
    SATNode* p = head->next;
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
inline void Back_up(AdjList*& root_1, AdjList* origin_root) {
    root_1->next = NULL;
    root_1->head = NULL;
    AdjList* lp = origin_root->next;
    AdjList* L_tail = root_1;//新邻接表的尾结点
    while (lp) {
        AdjList* newlist = (AdjList*)malloc(sizeof(AdjList));//新链表
        newlist->next = NULL;
        newlist->head = (SATNode*)malloc(sizeof(SATNode));
        newlist->num = lp->num;//新链表的初始化
        SATNode* np = lp->head->next;
        SATNode* N_tail = newlist->head;//新链表的尾结点
        while (np) {
            SATNode* newnode = (SATNode*)malloc(sizeof(SATNode));
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
inline bool emptyClause(AdjList* root) {
    AdjList* lp = root->next;

    for (; lp; lp = lp->next) {
        if (lp->head->next == NULL) return true;
    }
    return false;
}
/*
 *函数名称：void DestroyClause(AdjList * & alist)
 *函数功能：销毁子句并释放子句alist的空间
 */
void DestroyClause(AdjList*& alist) {
    SATNode* p = alist->head, * q = p;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    alist->head = NULL;
    free(alist);
    alist = NULL;
}

int getMaxbool_optimized(AdjList* SATList) {
    int* cnt = (int*)malloc(sizeof(int) * (2 * V_count + 1));
    for (int i = 1; i <= 2 * V_count; i++) cnt[i] = 0;//计数器初始化
    AdjList* lp = SATList->next;
    for (; lp; lp = lp->next) {
        SATNode* np = lp->head->next;
        for (; np; np = np->next) {
            if (np->data > 0) cnt[np->data]++;
            else cnt[V_count - np->data]++;
        }
    }//出现频率统计
    int max = 0;
    int Maxword = 0;
    for (int i = 1; i <= V_count; i++) {
        if (cnt[i] > max) {
            max = cnt[i];
            Maxword = i;
        }
    }//找到出现频率最大的正变元
    if (Maxword == 0) {
        for (int i = V_count + 1; i <= V_count * 2; i++) {
            if (cnt[i] > max) {
                max = cnt[i];
                Maxword = i - V_count;
            }
        }
    }//如果全为负,找到出现频率最大的负变元
    free(cnt);//释放空间
    return Maxword;
}

int getMaxbool(AdjList* SATList) {
    int* cnt = (int*)malloc(sizeof(int) * (V_count + 1));
    for (int i = 1; i <= V_count; i++) cnt[i] = 0;//计数器初始化
    AdjList* lp = SATList->next;
    for (; lp; lp = lp->next) {
        SATNode* np = lp->head->next;
        for (; np; np = np->next) {
            cnt[abs(np->data)]++;
        }
    }//出现频率统计
    int max = 0;
    int Maxword = 0;
    for (int i = 1; i <= V_count; i++) {
        if (cnt[i] > max) {
            max = cnt[i];
            Maxword = i;
        }
    }
    free(cnt);//释放空间
    return Maxword;
}

int getbool_2sides(AdjList* root) {
    double* weight = (double*)malloc(sizeof(double) * (V_count + 1));
    for (int i = 1; i <= V_count; i++) {
        weight[i] = 0.0;
    }
    AdjList* lp = root->next;
    for (; lp; lp = lp->next) {
        SATNode* tp = lp->head->next;
        for (; tp; tp = tp->next) {
            weight[abs(tp->data)] += pow(2, -lp->num);
        }
    }
    int Maxword = 0;
    double Maxweight = 0.0;
    for (int i = 1; i <= V_count; i++) {
        if (weight[i] >= Maxweight) {
            Maxweight = weight[i];
            Maxword = i;
        }
    }
    free(weight);
    return Maxword;
}
int getbool_2sides_optimized(AdjList* root) {
    double* weight = (double*)malloc(sizeof(double) * (2 * V_count + 1));
    for (int i = 1; i <= 2 * V_count; i++) {
        weight[i] = 0.0;
    }
    AdjList* lp = root->next;
    for (; lp; lp = lp->next) {
        SATNode* tp = lp->head->next;
        for (; tp; tp = tp->next) {
            if (tp->data > 0) {
                weight[tp->data] += pow(2, -lp->num);
            }
            else {
                weight[V_count - tp->data] += pow(2, -lp->num);
            }
        }
    }
    int Maxword = 0;
    double Maxweight = 0.0;
    for (int i = 1; i <= V_count; i++) {
        if (weight[i] + weight[i + V_count] > Maxweight) {
            Maxweight = weight[i] + weight[i + V_count];
            Maxword = i;
        }
    }
    if (weight[Maxword] < weight[Maxword + V_count]) {
        Maxword = -Maxword;
    }
    free(weight);
    return Maxword;
}
/*
 *函数名称：inline int DPLL(AdjList * & SATList)
 *函数功能：利用DPLL算法求解SATList
 */
inline bool DPLL(AdjList*& SATList, int choice) {//DPLL求解过程
    while (1) {
        AdjList* lp = SATList->next;
        int num = 0;
        while (lp && isUnitClause(lp->head) == false) lp = lp->next;
        if (lp == NULL) break;
        else {
            num = lp->head->next->data;
            if (num > 0) value[num] = 1;
            else value[-num] = 0;
        }//找到单子句并为其赋值
        AdjList* lq = SATList->next;
        AdjList* pre = SATList;//前驱结点
        while (lq) {
            AdjList* c_lq = lq->next;
            SATNode* tq = lq->head->next;
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
    }//寻找单子句并化简
    //VSIDS策略
    /*int * cnt=(int *)malloc(sizeof(int)*(2*V_count+1));
    for(int i=1;i<=2*V_count;i++) cnt[i]=0;//计数器初始化
    AdjList * lp=SATList->next;
    for(;lp;lp=lp->next){
        SATNode * np=lp->head->next;
        for(;np;np=np->next){
            if(np->data>0) cnt[np->data]++;
            else cnt[V_count-np->data]++;
        }
    }//出现频率统计
    int max=0;
    int Maxword=0;
    for(int i=1;i<=V_count;i++){
        if(cnt[i]>max){
            max=cnt[i];
            Maxword=i;
        }
    }//找到出现频率最大的正变元
    if(Maxword==0){
        for(int i=V_count+1;i<=V_count*2;i++){
            if(cnt[i]>max){
                max=cnt[i];
                Maxword=V_count-i;
            }
        }
    }//如果全为负,找到出现频率最大的负变元
    free(cnt);//释放空间*/
    //int Maxword=SATList->next->head->next->data;//选择第一句的第一变元
    //为找到的变量开一个单变元子句
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
    }
    AdjList* newlist = (AdjList*)malloc(sizeof(AdjList));
    newlist->next = NULL;
    newlist->head = (SATNode*)malloc(sizeof(SATNode));
    SATNode* newnode = (SATNode*)malloc(sizeof(SATNode));
    newnode->next = NULL;
    newnode->data = Maxword;
    newlist->head->next = newnode;
    AdjList* c_SATList = (AdjList*)malloc(sizeof(AdjList));
    Back_up(c_SATList, SATList);
    AddClause(c_SATList, newlist);
    if (DPLL(c_SATList, choice) == 1) return 1;//第一分支
    DestroyAdjList(c_SATList);

    newlist = (AdjList*)malloc(sizeof(AdjList));
    newlist->next = NULL;
    newlist->head = (SATNode*)malloc(sizeof(SATNode));
    newnode = (SATNode*)malloc(sizeof(SATNode));
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
status Preserve_the_Result(char filename[], int ret, double time) {
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
            for (int i = 1; i <= V_count; i++) {
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
/*
 *函数名称：void get_transfer()
 *函数功能：得到自然排列数与位置构造数之间的转换数组 tranfer 和 transfer_to_loc
 */
void get_transfer(int transfer[], int transfer_to_loc[]) {
    int n, i, j, k, cnt = 1;
    for (n = 1; n <= 2; n++) {//n-1-左上盘，n-2-右下盘
        for (i = 1; i <= 9; i++) {//行
            for (j = 1; j <= 9; j++) {//列
                for (k = 1; k <= 9; k++) {//填的数
                    transfer_to_loc[cnt] = n * 1000 + i * 100 + j * 10 + k;//自然排列数转化为构造数
                    transfer[n * 1000 + i * 100 + j * 10 + k] = cnt;//构造数转化为自然排列数
                    cnt++;

                }
            }
        }
    }
}//得到构造数和自然排列数之间的转换数组
/*
 *函数名称：void AddNode(SATNode * & head,SATNode *& newnode)
 *函数功能：在链表head中添加newnode（首插法）
 */
void AddNode(SATNode*& head, SATNode*& newnode) {
    newnode->next = head->next;
    head->next = newnode;
}
/*
 *函数名称：void Diger(int *sudoku,int holes)
 *函数功能：挖洞算法，在双数组sudoku中挖holes个洞
 */
void Diger(int* sudoku, int holes) {
    int cnt = 0;
    bool mark[163];//标记是否被挖
    for (cnt = 1; cnt <= 162; cnt++) {
        mark[cnt] = false;//表示没有被挖
    }
    cnt = 0;
    srand(time(0));
    while (cnt < holes) {
        int n = rand() % 2 + 1;
        int x = rand() % 9 + 1;
        int y = rand() % 9 + 1;
        if (mark[(n - 1) * 81 + (x - 1) * 9 + y] == false) {
            cnt++;
            if (n == 1 && x >= 7 && y >= 7) {//挖的是第一个模块的右下角
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = 0;
                sudoku[81 + (x - 7) * 9 + y - 6] = 0;
                mark[(n - 1) * 81 + (x - 1) * 9 + y] = true;
                mark[81 + (x - 7) * 9 + y - 6] = true;
            }
            else if (n == 2 && x <= 3 && y <= 3) {//挖的是第二个模块左上角
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = 0;
                sudoku[(x + 5) * 9 + y + 6] = 0;
                mark[(n - 1) * 81 + (x - 1) * 9 + y] = true;
                mark[(x + 5) * 9 + y + 6] = true;
            }
            else {//非交叉部分
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = 0;
                mark[(n - 1) * 81 + (x - 1) * 9 + y] = true;
            }
        }//挖的洞符合规则 1.之前没有被挖过
    }
    return;
}
/*
 *函数名称：Create_sudoku(int  sudoku[],AdjList * & root,int idx)
 *函数功能：利用生成终盘后挖洞算法生成数独原题
 */
void Create_sudoku(int  sudoku[], int idx) {
    V_count = 729 * 2;
    //建立终盘

    //先随机扔几个数
    //srand(time(0));
    srand(time(NULL));
    int n, x, y, num;
    int flag = 1;
    for (int t = 0; t < 16 && flag;) {//
        n = rand() % 2 + 1;
        x = rand() % 9 + 1;//行
        y = rand() % 9 + 1;//列
        num = rand() % 9 + 1;//填的数
        if (sudoku[(n - 1) * 81 + (x - 1) * 9 + y] == 0 && isTrue(sudoku, n, x, y, num)) {//未填入且符合填入规则
            t++;
            if (n == 1 && x >= 7 && y >= 7) {//第一模块的右下角
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = num;
                sudoku[81 + (x - 7) * 9 + y - 6] = num;
            }
            else if (n == 2 && x <= 3 && y <= 3) {//第二模块的右下角
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = num;
                sudoku[(x + 5) * 9 + y + 6] = num;
            }
            else {//非交叉部分
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = num;
            }
            if (t > 10) {
                if (Sudoku_Solver(sudoku)) {//生成终盘
                    flag = 0;
                    //printf("终盘如下!\n");
                    //show_the_sudoku(sudoku);//
                }
            }
        }
    }

    //挖洞 diger
    Diger(sudoku, idx * 20);

}
/*
 *函数名称：bool isTrue(int sudoku[],int n,int i,int j,int k)
 *函数功能：判断填入的数是否符合数独规则
 */
bool isTrue(int sudoku[], int n, int i, int j, int k) {//sudoku为双数组，n为哪个盘，i为行(从1开始），j为列（从1开始），k为数（1-9）
    //需要判断行是否有重复，列是否有重复，九宫格内是否有重复

    for (int m = 1; m <= 9; m++) {
        if (sudoku[(n - 1) * 81 + (i - 1) * 9 + m] == k) return false;//行存在相同的
        if (sudoku[(n - 1) * 81 + (m - 1) * 9 + j] == k) return false;//列存在相同的
    }
    //九宫格
    int line = ((i - 1) / 3) * 3 + 1, col = ((j - 1) / 3) * 3 + 1;//九宫格的起始行列
    for (int a = line; a < line + 3; a++) {
        for (int b = col; b < col + 3; b++) {
            if (sudoku[(n - 1) * 81 + (a - 1) * 9 + b] == k) return false;//九宫格内存在相同的
        }
    }
    return true;
}
/*
 *函数名称:void init_value(int value[])
 *函数功能：初始化value数组，将其均设置为1
 */
void init_value(int value[]) {
    for (int i = 1; i <= V_count; i++) {
        value[i] = 1;//value 初始化
    }
}
/*
 *函数名称：int Sudoku_Solver(int sudoku[])
 *函数功能：将数独规则转化为布尔变元以及CNF语句，利用DPLL求解并将变元转化为数独
 */
int Sudoku_Solver(int sudoku[]) {//利用dpll
    //debug
    //char FileName[100];
    //scanf("%s",FileName);
    //FILE * fp=fopen(FileName, "w");
    //if(fp==NULL){
      //  printf("打开失败!\n");
        //return ;
    //}
    AdjList* root = (AdjList*)malloc(sizeof(AdjList));
    root->head = NULL;
    root->next = NULL;//邻接表根结点初始化

    value = (int*)malloc(sizeof(int) * V_count + 1);
    init_value(value);
    int i, j, k, n;

    //Part0-格子约束
    for (n = 1; n <= 2; n++) {
        for (i = 1; i <= 9; i++) {
            for (j = 1; j <= 9; j++) {
                AdjList* newlist = (AdjList*)malloc(sizeof(AdjList));
                newlist->next = NULL;
                newlist->head = (SATNode*)malloc(sizeof(SATNode));
                newlist->head->next = NULL;
                for (k = 1; k <= 9; k++) {
                    SATNode* newnode = (SATNode*)malloc(sizeof(SATNode));
                    newnode->next = NULL;
                    newnode->data = transfer[n * 1000 + i * 100 + j * 10 + k];
                    AddNode(newlist->head, newnode);
                    for (int m = k + 1; m <= 9; m++) {//不会重复
                        AdjList* newlist1 = (AdjList*)malloc(sizeof(AdjList));
                        newlist1->next = NULL;
                        newlist1->head = (SATNode*)malloc(sizeof(SATNode));
                        newlist1->head->next = NULL;
                        SATNode* newnode1 = (SATNode*)malloc(sizeof(SATNode));
                        newnode1->next = NULL;
                        newnode1->data = -transfer[n * 1000 + i * 100 + j * 10 + k];
                        SATNode* newnode2 = (SATNode*)malloc(sizeof(SATNode));
                        newnode2->next = NULL;
                        newnode2->data = -transfer[n * 1000 + i * 100 + j * 10 + m];
                        AddNode(newlist1->head, newnode1);
                        AddNode(newlist1->head, newnode2);
                        AddClause(root, newlist1);
                    }
                }
                AddClause(root, newlist);//newlist保证每个格子都会出现1-9
            }
        }
    }
    //Part1-行约束，
    //Step1-每一个模块，对于每一个数，每一行都会出现
    for (n = 1; n <= 2; n++) {//模块
        for (k = 1; k <= 9; k++) {//1-9
            for (i = 1; i <= 9; i++) {//行
                AdjList* newlist = (AdjList*)malloc(sizeof(AdjList));
                newlist->head = (SATNode*)malloc(sizeof(SATNode));
                newlist->next = NULL;
                newlist->head->next = NULL;
                for (j = 1; j <= 9; j++) {//列
                    SATNode* newnode = (SATNode*)malloc(sizeof(SATNode));
                    newnode->next = NULL;
                    newnode->data = transfer[n * 1000 + i * 100 + j * 10 + k];
                    newnode->next = newlist->head->next;
                    newlist->head->next = newnode;//首插法,newlist保证每行中都有1-9
                    //debug
                    //fprintf(fp, "%d(%d) ",newnode->data,n*1000+i*100+j*10+k);
                    for (int m = j + 1; m <= 9; m++) {//newlist2 保证一行中任意两个不相同
                        AdjList* newlist2 = (AdjList*)malloc(sizeof(AdjList));
                        newlist2->next = NULL;
                        newlist2->head = (SATNode*)malloc(sizeof(SATNode));
                        newlist2->head->next = NULL;
                        SATNode* newnode1 = (SATNode*)malloc(sizeof(SATNode));
                        newnode1->next = NULL;
                        newnode1->data = -transfer[n * 1000 + i * 100 + j * 10 + k];
                        newnode1->next = newlist2->head->next;
                        newlist2->head->next = newnode1;
                        SATNode* newnode2 = (SATNode*)malloc(sizeof(SATNode));
                        newnode2->next = NULL;
                        newnode2->data = -transfer[n * 1000 + i * 100 + m * 10 + k];
                        newnode2->next = newlist2->head->next;
                        newlist2->head->next = newnode2;
                        AddClause(root, newlist2);
                        //debug
                       // fprintf(fp, "%d(%d) %d(%d)\n",newnode1->data,n*1000+i*100+j*10+k,newnode2->data,n*1000+i*100+m*10+k);
                    }
                }
                //debug
                //fprintf(fp, "\n");
                AddClause(root, newlist);
            }
        }
    }
    //fclose(fp);
    //return ;

    //Part2-列约束
    //Step1-保证每列都会出现1-9
    for (n = 1; n <= 2; n++) {
        for (k = 1; k <= 9; k++) {
            for (j = 1; j <= 9; j++) {
                AdjList* newlist = (AdjList*)malloc(sizeof(AdjList));
                newlist->next = NULL;
                newlist->head = (SATNode*)malloc(sizeof(SATNode));
                newlist->head->next = NULL;//newlist保证每一列都有1-9

                for (i = 1; i <= 9; i++) {
                    SATNode* newnode = (SATNode*)malloc(sizeof(SATNode));
                    newnode->next = NULL;
                    newnode->data = transfer[n * 1000 + i * 100 + j * 10 + k];
                    newnode->next = newlist->head->next;
                    newlist->head->next = newnode;
                    //debug
                    //fprintf(fp, "%d(%d) ",newnode->data,n*1000+i*100+j*10+k);
                    int temp = i;
                    for (int m = i + 1; m <= 9; m++) {
                        AdjList* newlist2 = (AdjList*)malloc(sizeof(AdjList));
                        newlist2->head = (SATNode*)malloc(sizeof(SATNode));
                        newlist2->next = NULL;
                        newlist2->head->next = NULL;
                        SATNode* newnode1 = (SATNode*)malloc(sizeof(SATNode));
                        newnode1->data = -transfer[n * 1000 + temp * 100 + j * 10 + k];
                        newnode1->next = newlist2->head->next;
                        newlist2->head->next = newnode1;
                        SATNode* newnode2 = (SATNode*)malloc(sizeof(SATNode));
                        newnode2->data = -transfer[n * 1000 + m * 100 + j * 10 + k];
                        newnode2->next = newlist2->head->next;
                        newlist2->head->next = newnode2;
                        AddClause(root, newlist2);//newlist2保证每一列1-9不重复
                    }
                }
                //debug
                //fprintf(fp, "\n");
                AddClause(root, newlist);
            }
        }
    }
    //debug
    //fclose(fp);
    //return;
    //Part3-九宫格约束
    for (n = 1; n <= 2; n++) {
        for (int a = 1; a <= 9; a += 3) {
            for (int b = 1; b <= 9; b += 3) {//a,b表示所约束九宫格的左上角坐标
                for (k = 1; k <= 9; k++) {
                    AdjList* newlist1 = (AdjList*)malloc(sizeof(AdjList));
                    newlist1->next = NULL;
                    newlist1->head = (SATNode*)malloc(sizeof(SATNode));
                    newlist1->head->next = NULL;
                    for (i = a; i < a + 3; i++) {
                        for (j = b; j < b + 3; j++) {
                            SATNode* newnode = (SATNode*)malloc(sizeof(SATNode));
                            newnode->next = NULL;
                            newnode->data = transfer[n * 1000 + i * 100 + j * 10 + k];
                            AddNode(newlist1->head, newnode);
                            // fprintf(fp, "%d(%d) ",newnode->data,n*1000+i*100+j*10+k);
                            for (int c = i; c < a + 3; c++) {
                                for (int d = c == i ? j + 1 : b; d < b + 3; d++) {
                                    AdjList* newlist2 = (AdjList*)malloc(sizeof(AdjList));
                                    newlist2->next = NULL;
                                    newlist2->head = (SATNode*)malloc(sizeof(SATNode));
                                    newlist2->head->next = NULL;
                                    SATNode* newnode1 = (SATNode*)malloc(sizeof(SATNode));
                                    newnode1->next = NULL;
                                    newnode1->data = -transfer[n * 1000 + i * 100 + j * 10 + k];
                                    AddNode(newlist2->head, newnode1);
                                    SATNode* newnode2 = (SATNode*)malloc(sizeof(SATNode));
                                    newnode2->next = NULL;
                                    newnode2->data = -transfer[n * 1000 + c * 100 + d * 10 + k];
                                    AddNode(newlist2->head, newnode2);
                                    // fprintf(fp, "%d(%d) %d(%d)\n",newnode1->data,n*1000+i*100+j*10+k,newnode2->data,n*1000+c*100+d*10+k);
                                    AddClause(root, newlist2);//newlist2用于保证九宫格内1-9不重复
                                }
                            }
                        }
                    }
                    // fprintf(fp, "\n");
                    AddClause(root, newlist1);//newlist1用于保证九宫格一定会出现1-9
                }
            }
        }
    }
    //fclose(fp);
    //return ;

    //Part4-双数独交叉部分等价式约束
    for (k = 1; k <= 9; k++) {
        int n_1 = 1, a_1 = 7, b_1 = 7;//左上盘的最后一个九宫格，从7-7开始
        int n_2 = 2, a_2 = 1, b_2 = 1;//右下盘的第一个九宫格，从1-1开始
        int i_1, i_2, j_1, j_2;
        for (i_1 = a_1, i_2 = a_2; i_1 <= 9 && i_2 <= 3; i_1++, i_2++) {
            for (j_1 = b_1, j_2 = b_2; j_1 <= 9 && j_2 <= 3; j_1++, j_2++) {
                AdjList* newlist1 = (AdjList*)malloc(sizeof(AdjList));
                newlist1->next = NULL;
                newlist1->head = (SATNode*)malloc(sizeof(SATNode));
                newlist1->head->next = NULL;
                SATNode* newnode1 = (SATNode*)malloc(sizeof(SATNode));
                newnode1->next = NULL;
                newnode1->data = transfer[n_1 * 1000 + i_1 * 100 + j_1 * 10 + k];
                SATNode* newnode2 = (SATNode*)malloc(sizeof(SATNode));
                newnode2->next = NULL;
                newnode2->data = -transfer[n_2 * 1000 + i_2 * 100 + j_2 * 10 + k];
                AddNode(newlist1->head, newnode1);
                AddNode(newlist1->head, newnode2);
                //fprintf(fp, "%d(%d) %d(%d) \n",newnode1->data,n_1*1000+i_1*100+j_1*10+k,newnode2->data,n_2*1000+i_2*100+j_2*10+k);
                AddClause(root, newlist1);//newlist1是 1正2负

                AdjList* newlist2 = (AdjList*)malloc(sizeof(AdjList));
                newlist2->next = NULL;
                newlist2->head = (SATNode*)malloc(sizeof(SATNode));
                newlist2->head->next = NULL;
                SATNode* newnode3 = (SATNode*)malloc(sizeof(SATNode));
                newnode3->next = NULL;
                newnode3->data = -transfer[n_1 * 1000 + i_1 * 100 + j_1 * 10 + k];
                AddNode(newlist2->head, newnode3);
                SATNode* newnode4 = (SATNode*)malloc(sizeof(SATNode));
                newnode4->next = NULL;
                newnode4->data = transfer[n_2 * 1000 + i_2 * 100 + j_2 * 10 + k];
                AddNode(newlist2->head, newnode4);
                //fprintf(fp, "%d(%d) %d(%d) \n",newnode3->data,n_1*1000+i_1*100+j_1*10+k,newnode4->data,n_2*1000+i_2*100+j_2*10+k);
                AddClause(root, newlist2);//newlist2是1负2正
            }
        }
    }
    //fclose(fp);
    //return ;

    //Part5-已知条件转换为单子句
    for (n = 1; n <= 2; n++) {
        for (i = 1; i <= 9; i++) {
            for (j = 1; j <= 9; j++) {
                if (sudoku[(n - 1) * 81 + (i - 1) * 9 + j]) {
                    AdjList* newlist = (AdjList*)malloc(sizeof(AdjList));
                    newlist->next = NULL;
                    newlist->head = (SATNode*)malloc(sizeof(SATNode));
                    newlist->head->next = NULL;
                    SATNode* newnode = (SATNode*)malloc(sizeof(SATNode));
                    newnode->next = NULL;
                    newnode->data = transfer[n * 1000 + i * 100 + j * 10 + sudoku[(n - 1) * 81 + (i - 1) * 9 + j]];
                    AddNode(newlist->head, newnode);
                    AddClause(root, newlist);
                }
            }
        }
    }
    //Debug
    //Out_Content_of_File(root);

    //求解
    int res = DPLL(root, 2);
    //printf("\n%d\n",res);
    //Debug
    if (res) {
        //Debug
        //for(i=1;i<=V_count;i++){
            //if(value[i]){
              //  printf("%d ",i);
            //}else{
              //  printf("%d ",-i);
            //}
        //}
        for (i = 1; i <= V_count; i++) {
            if (value[i]) {
                int num = transfer_to_loc[i];//转换为构造数
                int n_, i_, j_, k_;
                k_ = num % 10;//个位
                num /= 10;//舍弃个位

                j_ = num % 10;
                num /= 10;

                i_ = num % 10;
                num /= 10;

                n_ = num % 10;
                num /= 10;

                sudoku[(n_ - 1) * 81 + (i_ - 1) * 9 + j_] = k_;
            }
        }

        return 1;
    }
    else {
        //printf("dpll失败!\n");
        return 0;
    }

}
/*
 *函数名称：void show_the_sudoku(int sudoku[])
 *函数功能：展现数独格局
 */
void show_the_sudoku(int sudoku[]) {
    int i, j;
    //输出第一个数独的前六行
    for (i = 0; i < 6; i++) {
        for (j = 1; j <= 9; j++) {
            printf("%d ", sudoku[i * 9 + j]);
        }
        printf("\n");
    }
    //输出中部交叉的三行
    for (i = 6; i < 9; i++) {
        for (j = 1; j <= 9; j++) {
            printf("%d ", sudoku[i * 9 + j]);
        }//第一个数独的的9个
        for (int k = 0; k < 6; k++) {
            printf("%d ", sudoku[i * 9 + j + 21 + k]);
        }
        printf("\n");
    }
    //输出第二个数独的后六行
    for (i = 3; i < 9; i++) {
        printf("            ");
        for (j = 1; j <= 9; j++) {
            printf("%d ", sudoku[81 + i * 9 + j]);
        }
        printf("\n");
    }
    //Debug
   /* printf("\n");
    for(i=1;i<=9;i++){
        for(j=1;j<=9;j++){
            printf("%d ",sudoku[(i-1)*9+j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i=1;i<=9;i++){
        for(j=1;j<=9;j++){
            printf("%d ",sudoku[81+(i-1)*9+j]);
        }
        printf("\n");
    }*/
}

void Playsukodu(int* fullboard, int* board, int holes) {//fullboard是答案，board是挖空后的结果（即生成的题目），holes是数独剩余未填个数
    bool enter[163] = { 0 };//表示是否填入 0-未填入 1-已填入
    int n, i, j, k;
    for (i = 1; i <= 162; i++) {
        if (board[i]) {
            enter[i] = 1;//表示已经填入了数
        }
    }
    while (1) {
        system("clear");
        printf("        Holes Left:%d\n", holes);
        printf("\033[37;32m    1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n");
        //输出第一个数独的前六行
        int line = 1;
        for (i = 0; i < 6; i++) {
            printf("\033[37;32m%d   ", line++);//输出行号
            for (j = 1; j <= 9; j++) {
                if (enter[i * 9 + j] == 1)
                    printf("\033[37;31m%d  ", board[i * 9 + j]);
                else
                    printf("\033[37;34m%d  ", board[i * 9 + j]);
            }
            printf("\n");
        }
        //输出中部交叉的三行
        for (i = 6; i < 9; i++) {
            printf("\033[37;32m%d   ", line++);
            for (j = 1; j <= 9; j++) {
                if (enter[i * 9 + j] == 1)
                    printf("\033[37;31m%d  ", board[i * 9 + j]);
                else
                    printf("\033[37;34m%d  ", board[i * 9 + j]);
            }//第一个数独的的9个
            for (int k = 0; k < 6; k++) {
                if (enter[i * 9 + j + 21 + k] == 1)
                    printf("\033[37;31m%d  ", board[i * 9 + j + 21 + k]);
                else
                    printf("\033[37;34m%d  ", board[i * 9 + j + 21 + k]);
            }
            printf("\n");
        }
        //输出第二个数独的后六行
        for (i = 3; i < 9; i++) {
            printf("\033[37;32m%d  ", line++);
            printf("                  ");
            for (j = 1; j <= 9; j++) {
                if (enter[81 + i * 9 + j] == 1)
                    printf("\033[37;31m%d  ", board[81 + i * 9 + j]);
                else
                    printf("\033[37;34m%d  ", board[81 + i * 9 + j]);
            }
            printf("\n");
        }
        printf("\033[37;37m请输入选择的操作：0-结束游戏，3-检验答案，4-给予提示,5-橡皮擦\n");
        printf("或输入4个数填写数独，(格式 n(1-左上，2-右下） i（行） j（列） k（填入的数））\n");
        scanf("%d", &n);
        if (n == 0) {//结束游戏
            printf("游戏结束!\n");
            break;
        }
        else if (n == 3) {//检验游戏
            int flag = 1;
            for (int m = 1; m <= 162; m++) {
                if (board[m] != fullboard[m]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                printf("恭喜你，通关了！\n");
            }
            else {
                printf("抱歉，答案错误！\n");
            }
        }
        else if (n == 4) {
            printf("请输入想获得提示的位置:(格式 n(1-左上，2-右下） i（行） j（列）)\n");
            scanf("%d%d%d", &n, &i, &j);
            if (n == 1) {
                printf("左上角第%d行第%d列的数为%d\n", i, j, fullboard[(n - 1) * 81 + (i - 1) * 9 + j]);
                getchar();
                getchar();
            }
            else {
                printf("右下角第%d行第%d列的数为%d\n", i, j, fullboard[(n - 1) * 81 + (i - 1) * 9 + j]);
                getchar();
                getchar();
            }
        }
        else if (n == 5) {//擦去
            printf("请输入想擦除数独格的位置:(格式 n(1-左上，2-右下） i（行） j（列）)\n");
            scanf("%d%d%d", &n, &i, &j);
            if (n == 1 && i >= 7 && i >= 7) {//第一模块的右下角
                board[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
                board[81 + (i - 7) * 9 + j - 6] = 0;
                enter[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
                enter[81 + (i - 7) * 9 + j - 6] = 0;
            }
            else if (n == 2 && i <= 3 && j <= 3) {//第二模块的左上角
                board[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
                board[(i + 5) * 9 + j + 6] = 0;
                enter[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
                enter[(i + 5) * 9 + j + 6] = 0;
            }
            else {//非交叉部分
                board[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
                enter[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
            }
            holes++;
            printf("擦除成功!\n");
        }
        else {
            scanf("%d%d%d", &i, &j, &k);
            if (enter[(n - 1) * 81 + (i - 1) * 9 + j] == false) {
                if (n == 1 && i >= 7 && i >= 7) {//第一模块的右下角
                    board[(n - 1) * 81 + (i - 1) * 9 + j] = k;
                    board[81 + (i - 7) * 9 + j - 6] = k;
                    enter[(n - 1) * 81 + (i - 1) * 9 + j] = 1;
                    enter[81 + (i - 7) * 9 + j - 6] = 1;
                }
                else if (n == 2 && i <= 3 && j <= 3) {//第二模块的右下角
                    board[(n - 1) * 81 + (i - 1) * 9 + j] = k;
                    board[(i + 5) * 9 + j + 6] = k;
                    enter[(n - 1) * 81 + (i - 1) * 9 + j] = 1;
                    enter[(i + 5) * 9 + j + 6] = 1;
                }
                else {//非交叉部分
                    board[(n - 1) * 81 + (i - 1) * 9 + j] = k;
                    enter[(n - 1) * 81 + (i - 1) * 9 + j] = true;
                }
                holes--;
                printf("填入成功!\n");
            }
            else {
                printf("这个位置已被填入!\n");
            }
        }
        getchar();
        getchar();
    }
}
