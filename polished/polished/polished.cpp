#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define OK 1
#define ERROR 0
#define SUDOKU 1
#define SAT 0

typedef struct cNode
{
    int data;
    cNode* next;
} cNode;
typedef struct clause
{
    int num;
    cNode* head;
    clause* next;
} clause;
typedef int stat;

const int inf = 1061109567;
int boolCnt, clauseCnt, sumOfAns, branchRule;
char fileName[2021], sudokuFileName[2021];

int ABS(int a);
//SAT PART
int read();
stat ReadCNF(clause*& cnf, int satORsudoku);
void destroyClause(clause*& cnf);
void removeClause(clause*& cnf, clause*& cl);
void removeNode(clause* cl, cNode*& nd);
stat addClause(clause* cl, clause*& cnf);
bool isUnitClause(clause* cl);
void delelteSingleClause(clause* s, clause*& cnf);
bool emptyClause(clause* cnf);
void getForgery(clause*& forgery, clause* cnf);
// different ways to get next bool lmao
int getMaxBool(clause* cnf);
int getMaxBool_verSudoku(clause* cnf);
int getNextBool_2SidedJW(clause* cnf);
int getNextBool_2SidedJW_optimized(clause* cnf);
int getNextBool_Positive_2SidedJW(clause* cnf);
bool DPLL(clause*& cnf, int* v, int satORsudoku);
stat printCNF(int s, int* v, double t);
//SUDOKU PART
stat completeGameBoard(int a[][9], int row, int col);
void createFullBoard(int a[][9]);
void calSolution(int a[][9], int row, int col, int mark[]);
void dig(int a[][9], int b[][9], int holes);
stat transSudokuToCNF(int a[][9], int holes);
void gameStart(int fullBoard[][9], int board[9][9], int difficulty);
void gaming(int fullBoard[][9], int board[][9], int holes);

int main()
{
    clause* CNF;
    int op = 1, op1 = 1, op2 = 1, * value, flag_cnf, flag_sdk, difficulty, fullBoard[9][9];
    int board[9][9];
    clock_t start, finish;
    double time;
    bool res;
    while (op)
    {
        system("cls");
        printf("\n\n                    Menu for SAT Solver based on DPLL                   \n\n");
        printf("------------------------------------------------------------------------\n\n");
        printf("                                 1.SAT                                  \n\n");
        printf("                                 2.Sudoku                               \n\n");
        printf("                                 0.Exit                                 \n\n");
        printf("------------------------------------------------------------------------\n\n");
        printf("Input operator:[0~2]\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            flag_cnf = 1, op1 = 1;
            while (op1)
            {
                system("cls");
                printf("\n\n                             *SAT Solver*\n");
                printf("-------------------------------------------------------------------------\n");
                printf("                             1.Read File\n\n");
                printf("                             2.Print File\n\n");
                printf("                             3.DPLL\n\n");
                printf("                             4.Save CNF\n\n");
                printf("                             0.Back To MENU\n\n");
                printf("-------------------------------------------------------------------------\n");
                printf("Input operator:[0~4]\n");
                scanf("%d", &op1);
                switch (op1)
                {
                case 1:
                    printf("Input filename:\n");
                    scanf("%s", fileName);
                    if (ReadCNF(CNF, SAT) == OK)
                        flag_cnf = 0, printf("File Reading Complete!\n");
                    else
                        printf("File Reading Error!\n");
                    getchar(), getchar();
                    break;
                case 2:
                    if (flag_cnf)
                        printf("CNF File Not Input Yet!\n ");
                    else
                    {
                        for (clause* lp = CNF; lp; lp = lp->next)
                        {
                            for (cNode* tp = lp->head; tp; tp = tp->next)
                                printf("%d ", tp->data);
                            printf("\n");
                        }
                    }
                    getchar(), getchar();
                    break;
                case 3:
                    if (flag_cnf)
                        printf("CNF File Not Input Yet!\n ");
                    else
                    {
                        //printf("Please select a branching rule:\n");
                        //printf("1. MostPosNum(Recommended for sudoku cnf)\n2. MOMS\n3. 2 sided J-W\n");
                       // printf("4. Optimized Two-Sided sided Jeroslow-Wang Rule(Recommended for RND cnf)\n5. Positive Two-Sided Jeroslow-Wang Rule.\n");
                        //scanf("%d", &branchRule);
                        branchRule = 5;
                        value = (int*)malloc(sizeof(int) * (boolCnt + 1));
                        for (int i = 0; i <= boolCnt; i++)
                            value[i] = 1;
                        start = clock();
                        res = DPLL(CNF, value, SAT);
                        finish = clock();
                        if (!res)
                            printf("No Answer!\n");
                        else
                        {
                            printf("The Answer's as follow:\n");
                            for (int i = 1; i <= boolCnt; i++)
                            {
                                if (value[i])
                                    printf("%d ", i);
                                else
                                    printf("%d ", -i);
                            }
                            printf("\n");
                        }
                        time = (double)(finish - start) / CLOCKS_PER_SEC;
                        printf("优化后处理时间=%lfms\n", time * 1000);
                    }
                    getchar(), getchar();
                    break;
                case 4:
                    if (flag_cnf)
                        printf("CNF File Not Input Yet!\n ");
                    else
                    {
                        if (printCNF(res, value, time))
                            printf("Save files to *.res of the same name\n");
                        else
                            printf("Files saving error!\n");
                    }
                    getchar(), getchar();
                    break;
                case 0:
                    break;
                }
            }
            break;
        case 2:
            flag_sdk = 1, op2 = 1;
            while (op2)
            {
                system("cls");
                printf("\n\n       *Sudoku*\n");
                printf("*******************************************\n");
                printf("1: CreateSudoku     2:ConvertSudokuToCNF\n");
                printf("3: Solve Sudoku     4: PlaySudoku\n");
                printf("0: Back To MENU\n");
                printf("*******************************************\n");
                printf("Input operator:[0~4]\n");
                scanf("%d", &op2);
                switch (op2)
                {
                case 1:
                    for (int i = 0; i < 9; i++)
                        for (int j = 0; j < 9; j++)
                            fullBoard[i][j] = 0;
                    printf("0.Custom 1.Easy 2.Normal 3.Hard 4.Expert 5.INSANE 6.LUNAR 7.THEORETICALLY MOST DIFFICULT\n");
                    printf("Select a difficulty:\n");
                    scanf("%d", &difficulty);
                    if (!difficulty)
                    {
                        printf("Input the custom hole number:[1~64]\n");
                        scanf("%d", &difficulty);
                    }
                    else
                        difficulty *= 10;
                    gameStart(fullBoard, board, difficulty);
                    flag_sdk = 0;
                    getchar(), getchar();
                    break;
                case 2:
                    if (flag_sdk)
                        printf("Sudoku Not Created Yet!\n ");
                    else
                    {
                        printf("Input FileName:\n");
                        scanf("%s", sudokuFileName);
                        transSudokuToCNF(board, difficulty);
                        printf("%s Saved!\n", sudokuFileName);
                    }
                    getchar(), getchar();
                    break;
                case 3:
                    printf("Input filename:\n");
                    scanf("%s", sudokuFileName);
                    int value[1010];
                    for (int i = 0; i <= 1009; i++)
                        value[i] = 1;
                    ReadCNF(CNF, SUDOKU);
                    start = clock();
                    res = DPLL(CNF, value, SUDOKU);
                    finish = clock();
                    printf("The Answer's as follow:\n");
                    /*                           for (int i = 1; i <= boolCnt; i++)
                            {
                            if (value[i])
                                printf("%d ", i);
                            else
                                printf("%d ", -i);
                            } */
                    for (int i = 1; i <= 9; i++)
                    {
                        for (int j = 1; j <= 9; j++)
                            for (int l = 1; l <= 9; l++)
                                if (value[i * 100 + j * 10 + l] == 1)
                                    printf("%d ", l);
                        printf("\n");
                    }
                    printf("\n");
                    time = (double)(finish - start) / CLOCKS_PER_SEC;
                    printf("Execution Time=%lfms\n", time * 1000);
                    getchar(), getchar();
                    break;
                case 4:
                    gaming(fullBoard, board, difficulty);
                    break;
                case 0:
                    break;
                }
            }
            break;
        case 0:
            break;
        }
    }
    return 0;
}

int ABS(int a)
{
    return a > 0 ? a : -a;
}
int read(FILE* fp)
{
    int flag = 0;
    int x = 0, f = 1;
    char c;
    c = getc(fp);
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1, c = getc(fp);
        else
            return inf;
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getc(fp);
        if (c == -1)
            flag = 1;
    }
    if (!flag && c != ' ' && c != '\n')
        return inf;
    return x * f;
}
stat ReadCNF(clause*& cnf, int satORsudoku)
{
    FILE* fp;
    char ch;
    cNode* pn;
    clause* pc;
    char check[5] = { ' ', 'c', 'n', 'f', ' ' };
    if (satORsudoku == SAT)
        fp = fopen(fileName, "r");
    else
        fp = fopen(sudokuFileName, "r");
    if (!fp)
        return ERROR;
    while ((ch = getc(fp)) == 'c')
        while ((ch = getc(fp)) != '\n')
            continue;
    if (ch != 'p')
        return ERROR;
    for (int i = 0; i < 5; i++)
        if ((ch = getc(fp)) != check[i])
            return ERROR;
    if ((boolCnt = read(fp)) == inf || (clauseCnt = read(fp)) == inf)
        return ERROR;
    cnf = (clause*)malloc(sizeof(clause));
    cnf->next = NULL;
    cnf->head = (cNode*)malloc(sizeof(cNode));
    cnf->head->next = NULL;
    cnf->num = 0;
    pc = cnf;
    pn = cnf->head;
    //^ init part ^
    for (int i = 1; i <= clauseCnt; i++)
    {
        int dat;
        if ((dat = read(fp)) == inf)
            return ERROR;
        while (dat)
        {
            pc->num++;
            pn->data = dat;
            pn->next = (cNode*)malloc(sizeof(cNode));
            if ((dat = read(fp)) == inf)
                return ERROR;
            if (!dat)
                pn->next = NULL;
            pn = pn->next;
        }
        pc->next = (clause*)malloc(sizeof(clause));
        pc->next->num = 0;
        pc->next->head = (cNode*)malloc(sizeof(cNode));
        if (i == clauseCnt)
        {
            pc->next = NULL;
            break;
        }
        pc = pc->next;
        pn = pc->head;
    }
    //^ read part ^
    fclose(fp);
    return OK;
}

void destroyClause(clause*& cnf)
{
    clause* ppc, * pc2;
    cNode* pn1, * pn2;
    ppc = cnf;
    while (ppc)
    {
        pn1 = ppc->head;
        while (pn1)
            pn2 = pn1->next, free(pn1), pn1 = pn2;
        pc2 = ppc->next, free(ppc), ppc = pc2;
    }
    cnf = NULL;
}

void removeClause(clause*& cnf, clause*& cl)
{
    if (cl == cnf)
        cnf = cnf->next;
    else
    {
        clause* ppc = cnf;
        while (ppc && ppc->next != cl)
            ppc = ppc->next;
        ppc->next = ppc->next->next;
    }
    cNode* pn1, * pn2;
    for (pn1 = cl->head; pn1;)
        pn2 = pn1->next, free(pn1), pn1 = pn2;
    free(cl);
    cl = NULL;
}

void removeNode(cNode*& head, cNode*& nd)
{
    cNode* ppn = head;
    if (ppn == nd)
        head = head->next;
    else
    {
        while (ppn && ppn->next != nd)
            ppn = ppn->next;
        ppn->next = ppn->next->next;
    }
    free(nd);
    nd = NULL;
}

stat addClause(clause* cl, clause*& cnf)
{
    if (cl)
    {
        cl->next = cnf;
        cnf = cl;
        return OK;
    }
    return ERROR; //cl is empty
}

bool isUnitClause(clause* cl)
{
    if (cl->head != NULL) {
        if (cl->head->next == NULL)
            return true;
    }
    return false;
}

void delelteSingleClause(clause* s, clause*& cnf)
{
    clause* tmp;
    int n = s->head->data;
    for (clause* ppc = cnf; ppc; ppc = tmp)
    {
        tmp = ppc->next;
        for (cNode* ppn = ppc->head; ppn; ppn = ppn->next)
        {
            if (ppn->data == n)
            {
                removeClause(cnf, ppc);
                break;
            }
            if (ppn->data == -n)
            {
                removeNode(ppc->head, ppn);
                ppc->num--;
                break;
            }
        }
    }
}

bool emptyClause(clause* cnf)
{
    for (clause* p = cnf; p; p = p->next)
        if (!p->head)
            return true;
    return false;
}

void getForgery(clause*& forgery, clause* cnf) // A great forgery is just the same.
{
    clause* ppc, * pc;
    cNode* ppn, * pn;
    forgery = (clause*)malloc(sizeof(clause));
    forgery->head = (cNode*)malloc(sizeof(cNode));
    forgery->next = NULL;
    forgery->head->next = NULL;
    forgery->num = 0;
    for (pc = cnf, ppc = forgery; pc != NULL; pc = pc->next, ppc = ppc->next)
    {
        for (pn = pc->head, ppn = ppc->head; pn != NULL; pn = pn->next, ppn = ppn->next)
        {
            ppc->num++;
            ppn->data = pn->data;
            ppn->next = (cNode*)malloc(sizeof(cNode));
            ppn->next->next = NULL;
            if (pn->next == NULL)
                free(ppn->next), ppn->next = NULL;
        }
        ppc->next = (clause*)malloc(sizeof(clause));
        ppc->next->head = (cNode*)malloc(sizeof(cNode));
        ppc->next->next = NULL;
        ppc->next->head->next = NULL;
        ppc->next->num = 0;
        if (pc->next == NULL)
            free(ppc->next->head), free(ppc->next), ppc->next = NULL;
    }
}

int getMaxBool(clause* cnf)
{
    int* cnt = (int*)malloc(sizeof(int) * (boolCnt * 2 + 1));
    for (int i = 0; i <= boolCnt * 2; i++)
        cnt[i] = 0;
    for (clause* pc = cnf; pc; pc = pc->next)
        for (cNode* pn = pc->head; pn; pn = pn->next)
        {
            if (pn->data > 0)
                cnt[pn->data]++;
            else
                cnt[boolCnt - pn->data]++;
        }
    int maxBool, maxTimes = 0;
    for (int i = 1; i <= boolCnt; i++)
        if (cnt[i] > maxTimes)
            maxTimes = cnt[i], maxBool = i;
    if (maxTimes == 0)
    {
        for (int i = boolCnt + 1; i <= boolCnt * 2; i++)
            if (cnt[i] > maxTimes)
                maxTimes = cnt[i], maxBool = i - boolCnt;
    }
    free(cnt);
    return maxBool;
}

int getMaxBool_verSudoku(clause* cnf)
{
    int cnt[2021] = { 0 };
    for (clause* pc = cnf; pc; pc = pc->next)
        for (cNode* pn = pc->head; pn; pn = pn->next)
        {
            if (pn->data > 0)
                cnt[pn->data]++;
            else
                cnt[1000 - pn->data]++;
        }
    int maxBool, maxTimes = 0;
    for (int i = 1; i <= 1000; i++)
        if (cnt[i + 1000] > maxTimes)
            maxTimes = cnt[i], maxBool = -i;
    if (maxTimes == 0)
    {
        for (int i = 1; i <= 1000; i++)
            if (cnt[i] > maxTimes)
                maxTimes = cnt[i], maxBool = i;
    }
    return maxBool;
}

int getNextBool_MOMS(clause* cnf)
{
    int minNode = boolCnt;
    int* cnt = (int*)malloc((boolCnt + 1) * sizeof(int));
    for (int i = 0; i < boolCnt; i++)
        cnt[i] = 0;
    for (clause* pc = cnf; pc; pc = pc->next)
        if (pc->num < minNode)
            minNode = pc->num;
    for (clause* pc = cnf; pc; pc = pc->next)
        if (pc->num == minNode)
            for (cNode* pn = pc->head; pn; pn = pn->next)
                cnt[ABS(pn->data)]++;
    int maxAppear = 0, maxBool;
    for (int i = 1; i <= boolCnt; i++)
        if (cnt[i] > maxAppear)
            maxAppear = cnt[i], maxBool = i;
    free(cnt);
    return maxBool;
}

double J(int n)
{
    return pow(2.0, (double)(-n));
}

int getNextBool_2SidedJW(clause* cnf)
{
    double* weight = (double*)malloc(sizeof(double) * (boolCnt + 1));
    for (int i = 0; i <= boolCnt; i++)
        weight[i] = 0.0;
    for (clause* pc = cnf; pc; pc = pc->next)
        for (cNode* pn = pc->head; pn; pn = pn->next)
            weight[ABS(pn->data)] += J(pc->num);
    double maxWeight = 0;
    int maxBool;
    for (int i = 1; i <= boolCnt; i++)
        if (weight[i] > maxWeight)
            maxWeight = weight[i], maxBool = i;
    free(weight);
    return maxBool;
}

int getNextBool_2SidedJW_optimized(clause* cnf)
{
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

int getNextBool_Positive_2SidedJW(clause* cnf)
{
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
            if (mark[ABS(pn->data)])
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

bool DPLL(clause*& cnf, int* v, int satORsudoku)
{
    int flag = 1;
    clause* pc;
    while (flag)
    {
        flag = 0;
        pc = cnf;
        while (pc && !isUnitClause(pc))
            pc = pc->next;
        if (pc != NULL)
        {
            if (pc->head->data > 0)
                v[pc->head->data] = 1;
            else
                v[-pc->head->data] = 0;
            delelteSingleClause(pc, cnf);
            //for testing
            // int tmp_cnt = 0;
            //  for (clause *tmp = cnf; tmp;tmp = tmp->next) tmp_cnt++;
            // printf("---->%d\n",tmp_cnt);
            //for testing
            if (cnf == NULL)
                return true;
            else if (emptyClause(cnf))
                return false;
            flag = 1;
        }
    }
    //^ delete single clause ^
    int maxBool;
    if (satORsudoku == SUDOKU)
        maxBool = getMaxBool_verSudoku(cnf);
    else
    {
        if (branchRule == 1)
            maxBool = getMaxBool(cnf);
        //MOMS
        else if (branchRule == 2)
            maxBool = getNextBool_MOMS(cnf);
        //2 Sided J-W
        else if (branchRule == 3)
            maxBool = getNextBool_2SidedJW(cnf);
        // 2 sided J-W optimized
        else if (branchRule == 4)
            maxBool = getNextBool_2SidedJW_optimized(cnf);
        // pos 2 sided J-W
        else
            maxBool = getNextBool_Positive_2SidedJW(cnf);
    }
    //printf("**%d**\n",maxBool);
    //^ pick the best bool. ^
    clause* newSingleClause = (clause*)malloc(sizeof(clause)), * forgery;
    newSingleClause->head = (cNode*)malloc(sizeof(cNode));
    newSingleClause->next = NULL;
    newSingleClause->head->data = maxBool;
    newSingleClause->head->next = NULL;
    newSingleClause->num = 1;
    getForgery(forgery, cnf);
    addClause(newSingleClause, forgery);
    if (DPLL(forgery, v, satORsudoku) == true)
        return true; // The first branch in which the new Single Clause is true;
    destroyClause(forgery);
    newSingleClause = (clause*)malloc(sizeof(clause));
    newSingleClause->head = (cNode*)malloc(sizeof(cNode));
    newSingleClause->next = NULL;
    newSingleClause->head->data = -maxBool;
    newSingleClause->head->next = NULL;
    newSingleClause->num = 1;
    addClause(newSingleClause, cnf);
    bool ans = DPLL(cnf, v, satORsudoku); // The second branch in which the new Single Clause is false.
    destroyClause(cnf);
    return ans;
}

stat printCNF(int s, int* v, double t)
{
    FILE* fp;
    for (int i = 0; fileName[i] != '\0'; i++)
        if (fileName[i] == '.' && fileName[i + 4] == '\0')
        {
            fileName[i + 1] = 'r', fileName[i + 2] = 'e', fileName[i + 3] = 's';
            break;
        }
    if (!(fp = fopen(fileName, "w")))
    {
        printf("File Creating ERROR!\n");
        return ERROR;
    }
    fprintf(fp, "s %d\nv ", s);
    if (s)
        for (int i = 1; i <= boolCnt; i++)
        {
            if (v[i])
                fprintf(fp, "%d ", i);
            else
                fprintf(fp, "%d ", -i);
        }
    fprintf(fp, "\nt %lf", t * 1000);
    fclose(fp);
    return OK;
}

stat completeGameBoard(int a[][9], int row, int col)//row=0,col=1
{
    if (row < 9 && col < 9)
    {
        int mark[10] = { 0 };
        for (int i = 0; i < row; i++)
            mark[a[i][col]] = 1;
        for (int i = 0; i < col; i++)
            mark[a[row][i]] = 1;
        for (int i = row / 3 * 3; i <= row; i++)
        {
            if (i == row)
                for (int j = col / 3 * 3; j < col; j++)
                    mark[a[i][j]] = 1;
            else
                for (int j = col / 3 * 3; j < col / 3 * 3 + 3; j++)
                    mark[a[i][j]] = 1;
        }
        // To mark the number which has been used.
        int flag = 1;
        for (int i = 1; i <= 9 && flag; i++)
        {
            if (!mark[i])
            {
                flag = 0;
                a[row][col] = i;
                if (col == 8 && row != 8) //The order is just like reading order:from left to right while from up to down
                {
                    if (completeGameBoard(a, row + 1, 0) == OK)
                        return OK;
                    else
                        flag = 1;
                }
                else if (col != 8)
                {
                    if (completeGameBoard(a, row, col + 1) == OK)
                        return OK;
                    else
                        flag = 1;
                }
            }
        }
        if (flag)
        {
            a[row][col] = 0; // Proper Number Not Found -> delete and travel back.
            return ERROR;
        }
    }
    return OK;
}

void createFullBoard(int a[][9])
{
    srand(time(0));
    for (int i = 0; i < 9; i++) //random first line
    {
        a[0][i] = rand() % 9 + 1;
        int j = 0;
        while (j < i)
        {
            if (a[0][i] == a[0][j])
                a[0][i] = rand() % 9 + 1, j = 0;
            else
                j++;
        }
    }
    completeGameBoard(a, 1, 0);
}

void calSolution(int a[][9], int row, int col, int mark[])
{
    int possible, minRow, minCol, minPos = 10, minMark[10] = { 0 };
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!a[i][j])
            {
                for (int k = 0; k <= 9; k++)
                    mark[k] = 0;
                for (int k = 0; k < 3; k++)
                    for (int l = 0; l < 3; l++)
                        mark[a[i / 3 * 3 + k][j / 3 * 3 + l]]++;
                for (int k = 0; k < 9; k++)
                    mark[a[k][j]]++;
                for (int k = 0; k < 9; k++)
                    mark[a[i][k]]++;
                possible = 0;
                for (int k = 0; k <= 9; k++)
                    if (!mark[k])
                        possible++;
                if (!possible)
                {
                    a[row][col] = 0;
                    return;
                }
                if (possible < minPos)
                {
                    minPos = possible;
                    minRow = i;
                    minCol = j;
                    for (int k = 1; k <= 9; k++)
                        minMark[k] = mark[k];
                }
            }
    if (minPos == 10)
    {
        sumOfAns++;
        a[row][col] = 0;
        return;
    }
    for (int i = 1; i <= 9; i++)
        if (!minMark[i])
        {
            a[minRow][minCol] = i;
            calSolution(a, minRow, minCol, mark);
        }
    a[row][col] = 0;
    return;
}

void dig(int a[][9], int b[][9], int holes)
{
    int mark[81][2], cnt = 0;
    srand(time(0));
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            b[i][j] = a[i][j];
    for (int i = 0; i < holes; i++) //waiting to be optimized...
    {
        int m, n, flag;
        m = rand() % 9;
        n = rand() % 9;
        flag = 0;
        for (int j = 0; j < cnt; j++)
            if (m == mark[j][0] && n == mark[j][1])
                flag = 1;
        //calculate the amount of solutions
        sumOfAns = 0;
        int markNUM[10] = { 0 }, copyOfb[9][9];
        for (int x = 0; x < 9; x++)
            for (int y = 0; y < 9; y++)
                copyOfb[x][y] = b[x][y];
        copyOfb[m][n] = 0;
        calSolution(copyOfb, 0, 0, markNUM);
        //calculated
        if (!flag && sumOfAns == 1) // a new suitable hole
            b[m][n] = 0, mark[cnt][0] = m, mark[cnt][1] = n, cnt++;
        else
            i--;
    }
}

stat transSudokuToCNF(int a[][9], int holes)
{
    FILE* fp;
    if (!(fp = fopen(sudokuFileName, "w")))
    {
        fprintf(fp, "File creating error!\n");
        return ERROR;
    }
    fprintf(fp, "c A sudoku cnf file.  Holes count:%d\n", holes);
    fprintf(fp, "p cnf  729 %d \n", 8910 - holes);
    // single clause
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (a[i][j])
                fprintf(fp, "%d 0\n", (i + 1) * 100 + (j + 1) * 10 + a[i][j]);
    // every block needs a number
    for (int row = 1; row <= 9; row++)
        for (int col = 1; col <= 9; col++)
        {
            for (int num = 1; num <= 9; num++)
                fprintf(fp, "%d ", row * 100 + col * 10 + num);
            fprintf(fp, "0\n");
        }
    // every row has 9 different numbers
    for (int col = 1; col <= 9; col++)
        for (int num = 1; num <= 9; num++)
            for (int row = 1; row <= 8; row++)
                for (int i = row + 1; i <= 9; i++)
                    fprintf(fp, "%d %d 0\n", 0 - (row * 100 + col * 10 + num), 0 - (i * 100 + col * 10 + num));
    // every column has 9 different numbers
    for (int row = 1; row <= 9; row++)
        for (int num = 1; num <= 9; num++)
            for (int col = 1; col <= 8; col++)
                for (int i = col + 1; i <= 9; i++)
                    fprintf(fp, "%d %d 0\n", 0 - (row * 100 + col * 10 + num), 0 - (row * 100 + i * 10 + num));
    // every 3*3 area has 9 different numbers
    for (int num = 1; num <= 9; num++)
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++)
                for (int row = 1; row <= 3; row++)
                    for (int col = 1; col <= 3; col++)
                        for (int k = col + 1; k <= 3; k++)
                            fprintf(fp, "%d %d 0\n", 0 - ((3 * i + row) * 100 + (3 * j + col) * 10 + num), 0 - ((3 * i + row) * 100 + (3 * j + k) * 10 + num));
    for (int num = 1; num <= 9; num++)
        for (int i = 0; i <= 2; i++)
            for (int j = 0; j <= 2; j++)
                for (int row = 1; row <= 3; row++)
                    for (int col = 1; col <= 3; col++)
                        for (int k = row + 1; k <= 3; k++)
                            for (int l = 1; l <= 3; l++)
                                fprintf(fp, "%d %d 0\n", 0 - ((3 * i + row) * 100 + (3 * j + col) * 10 + num), 0 - ((3 * i + k) * 100 + (3 * j + l) * 10 + num));
    fclose(fp);
    return OK;
}

void gameStart(int fullBoard[][9], int board[][9], int difficulty)
{
    createFullBoard(fullBoard);
    dig(fullBoard, board, difficulty);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
}

void gaming(int fullBoard[][9], int board[][9], int holes)
{
    int x, y, z, enterABLE[9][9] = { 0 }, flag;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!board[i][j])
                enterABLE[i][j] = 1;
    //init part
    while (1)
    {
        system("cls");
        printf("     Holes left: %d\n     ", holes);
        printf("  1 2 3 4 5 6 7 8 9\n     ");
        for (int i = 0; i < 9; i++)
        {
            printf("%d ", i + 1);
            for (int j = 0; j < 9; j++)
            {
                if (!enterABLE[i][j])
                    printf("\033[47;32;5m%d ", board[i][j]);
                else
                    printf("\033[47;31;5m%d ", board[i][j]);
            }
            printf("\033[0m\n     ");
        }
        printf("\n Enter 0 to quit, 10 to confirm or 11 to get a hint at ROW COL.\n");
        printf("Or please enter 3 numbers in the form of ROW COL NUM:\n");
        printf("x,y,z~[1-9]\n");
        scanf("%d", &x);

        if (!x)
            break;

        else if (x == 10)
        {
            flag = 1;
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    if (board[i][j] != fullBoard[i][j])
                        flag = 0;
            if (!flag)
                printf("Wrong Answer!\n");
            else
                printf("Congratulation! You win!\n");
        }
        else if (x == 11)
        {
            scanf("%d%d", &y, &z);
            printf("The number at [%d,%d] is %d\n", y, z, fullBoard[y - 1][z - 1]);
        }
        else
        {
            scanf("%d%d", &y, &z);
            if (!enterABLE[x - 1][y - 1])
                printf("Hey! You can't type in that block!\n");
            else
            {
                board[x - 1][y - 1] = z;
                if (!board[x - 1][y - 1])
                    holes--;
                printf("Enter successfully!\nPress Any Key to Continue...\n");
            }
        }
        getchar(), getchar();
    }
}
