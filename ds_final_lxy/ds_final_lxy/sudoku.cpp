#include"def.h"
#include"func.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
extern int Vnum;//全局变量V_count:布尔变元个数
extern int* value;//全局变量 value数组,用于记录所以变元的真值 1-真 0-假
extern char filename[200];
extern int transfer[3000];//构造位置数转换为变元自然排列数
extern int transfer_to_loc[1700];//自然排列数转换为位置构造数
/*
 *函数名称：void get_transfer()
 *函数功能：得到自然排列数与位置构造数之间的转换数组 tranfer 和 transfer_to_loc
 */
void Transfer(int transfer[], int transfer_to_loc[]) {
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
void AddNode(cNode*& head, cNode*& newnode) {
    newnode->next = head->next;
    head->next = newnode;
}
/*
 *函数名称：void Diger(int *sudoku,int holes)
 *函数功能：挖洞算法，在双sudoku中挖holes个洞
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
void CreateSudoku(int  sudoku[], int idx) {
    Vnum = 729 * 2;
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
        if (sudoku[(n - 1) * 81 + (x - 1) * 9 + y] == 0 && isVaild(sudoku, n, x, y, num)) {//未填入且符合填入规则
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
bool isVaild(int sudoku[], int n, int i, int j, int k) {//sudoku为双数组，n为哪个盘，i为行(从1开始），j为列（从1开始），k为数（1-9）
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
    for (int i = 1; i <= Vnum; i++) {
        value[i] = 1;//value 初始化
    }
}
/*
 *函数名称：int Sudoku_Solver(int sudoku[])
 *函数功能：将数独规则转化为布尔变元以及CNF语句，利用DPLL求解并将变元转化为数独
 */
int Sudoku_Solver(int sudoku[]) {//利用dpll
    clause* root = (clause*)malloc(sizeof(clause));
    root->head = NULL;
    root->next = NULL;//邻接表根结点初始化

    value = (int*)malloc(sizeof(int) * Vnum + 1);
    init_value(value);
    int i, j, k, n;

    //Part0-格子约束
    for (n = 1; n <= 2; n++) {
        for (i = 1; i <= 9; i++) {
            for (j = 1; j <= 9; j++) {
                clause* newlist = (clause*)malloc(sizeof(clause));
                newlist->next = NULL;
                newlist->head = (cNode*)malloc(sizeof(cNode));
                newlist->head->next = NULL;
                for (k = 1; k <= 9; k++) {
                    cNode* newnode = (cNode*)malloc(sizeof(cNode));
                    newnode->next = NULL;
                    newnode->data = transfer[n * 1000 + i * 100 + j * 10 + k];
                    AddNode(newlist->head, newnode);
                    for (int m = k + 1; m <= 9; m++) {//不会重复
                        clause* newlist1 = (clause*)malloc(sizeof(clause));
                        newlist1->next = NULL;
                        newlist1->head = (cNode*)malloc(sizeof(cNode));
                        newlist1->head->next = NULL;
                        cNode* newnode1 = (cNode*)malloc(sizeof(cNode));
                        newnode1->next = NULL;
                        newnode1->data = -transfer[n * 1000 + i * 100 + j * 10 + k];
                        cNode* newnode2 = (cNode*)malloc(sizeof(cNode));
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
                clause* newlist = (clause*)malloc(sizeof(clause));
                newlist->head = (cNode*)malloc(sizeof(cNode));
                newlist->next = NULL;
                newlist->head->next = NULL;
                for (j = 1; j <= 9; j++) {//列
                    cNode* newnode = (cNode*)malloc(sizeof(cNode));
                    newnode->next = NULL;
                    newnode->data = transfer[n * 1000 + i * 100 + j * 10 + k];
                    newnode->next = newlist->head->next;
                    newlist->head->next = newnode;//首插法,newlist保证每行中都有1-9
                    //debug
                    //fprintf(fp, "%d(%d) ",newnode->data,n*1000+i*100+j*10+k);
                    for (int m = j + 1; m <= 9; m++) {//newlist2 保证一行中任意两个不相同
                        clause* newlist2 = (clause*)malloc(sizeof(clause));
                        newlist2->next = NULL;
                        newlist2->head = (cNode*)malloc(sizeof(cNode));
                        newlist2->head->next = NULL;
                        cNode* newnode1 = (cNode*)malloc(sizeof(cNode));
                        newnode1->next = NULL;
                        newnode1->data = -transfer[n * 1000 + i * 100 + j * 10 + k];
                        newnode1->next = newlist2->head->next;
                        newlist2->head->next = newnode1;
                        cNode* newnode2 = (cNode*)malloc(sizeof(cNode));
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
                clause* newlist = (clause*)malloc(sizeof(clause));
                newlist->next = NULL;
                newlist->head = (cNode*)malloc(sizeof(cNode));
                newlist->head->next = NULL;//newlist保证每一列都有1-9

                for (i = 1; i <= 9; i++) {
                    cNode* newnode = (cNode*)malloc(sizeof(cNode));
                    newnode->next = NULL;
                    newnode->data = transfer[n * 1000 + i * 100 + j * 10 + k];
                    newnode->next = newlist->head->next;
                    newlist->head->next = newnode;
                    //debug
                    //fprintf(fp, "%d(%d) ",newnode->data,n*1000+i*100+j*10+k);
                    int temp = i;
                    for (int m = i + 1; m <= 9; m++) {
                        clause* newlist2 = (clause*)malloc(sizeof(clause));
                        newlist2->head = (cNode*)malloc(sizeof(cNode));
                        newlist2->next = NULL;
                        newlist2->head->next = NULL;
                        cNode* newnode1 = (cNode*)malloc(sizeof(cNode));
                        newnode1->data = -transfer[n * 1000 + temp * 100 + j * 10 + k];
                        newnode1->next = newlist2->head->next;
                        newlist2->head->next = newnode1;
                        cNode* newnode2 = (cNode*)malloc(sizeof(cNode));
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
                    clause* newlist1 = (clause*)malloc(sizeof(clause));
                    newlist1->next = NULL;
                    newlist1->head = (cNode*)malloc(sizeof(cNode));
                    newlist1->head->next = NULL;
                    for (i = a; i < a + 3; i++) {
                        for (j = b; j < b + 3; j++) {
                            cNode* newnode = (cNode*)malloc(sizeof(cNode));
                            newnode->next = NULL;
                            newnode->data = transfer[n * 1000 + i * 100 + j * 10 + k];
                            AddNode(newlist1->head, newnode);
                            // fprintf(fp, "%d(%d) ",newnode->data,n*1000+i*100+j*10+k);
                            for (int c = i; c < a + 3; c++) {
                                for (int d = c == i ? j + 1 : b; d < b + 3; d++) {
                                    clause* newlist2 = (clause*)malloc(sizeof(clause));
                                    newlist2->next = NULL;
                                    newlist2->head = (cNode*)malloc(sizeof(cNode));
                                    newlist2->head->next = NULL;
                                    cNode* newnode1 = (cNode*)malloc(sizeof(cNode));
                                    newnode1->next = NULL;
                                    newnode1->data = -transfer[n * 1000 + i * 100 + j * 10 + k];
                                    AddNode(newlist2->head, newnode1);
                                    cNode* newnode2 = (cNode*)malloc(sizeof(cNode));
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
                clause* newlist1 = (clause*)malloc(sizeof(clause));
                newlist1->next = NULL;
                newlist1->head = (cNode*)malloc(sizeof(cNode));
                newlist1->head->next = NULL;
                cNode* newnode1 = (cNode*)malloc(sizeof(cNode));
                newnode1->next = NULL;
                newnode1->data = transfer[n_1 * 1000 + i_1 * 100 + j_1 * 10 + k];
                cNode* newnode2 = (cNode*)malloc(sizeof(cNode));
                newnode2->next = NULL;
                newnode2->data = -transfer[n_2 * 1000 + i_2 * 100 + j_2 * 10 + k];
                AddNode(newlist1->head, newnode1);
                AddNode(newlist1->head, newnode2);
                //fprintf(fp, "%d(%d) %d(%d) \n",newnode1->data,n_1*1000+i_1*100+j_1*10+k,newnode2->data,n_2*1000+i_2*100+j_2*10+k);
                AddClause(root, newlist1);//newlist1是 1正2负

                clause* newlist2 = (clause*)malloc(sizeof(clause));
                newlist2->next = NULL;
                newlist2->head = (cNode*)malloc(sizeof(cNode));
                newlist2->head->next = NULL;
                cNode* newnode3 = (cNode*)malloc(sizeof(cNode));
                newnode3->next = NULL;
                newnode3->data = -transfer[n_1 * 1000 + i_1 * 100 + j_1 * 10 + k];
                AddNode(newlist2->head, newnode3);
                cNode* newnode4 = (cNode*)malloc(sizeof(cNode));
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
                    clause* newlist = (clause*)malloc(sizeof(clause));
                    newlist->next = NULL;
                    newlist->head = (cNode*)malloc(sizeof(cNode));
                    newlist->head->next = NULL;
                    cNode* newnode = (cNode*)malloc(sizeof(cNode));
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
        for (i = 1; i <= Vnum; i++) {
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
void showSudoku(int sudoku[]) {
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

void PlaySukodu(int* fullboard, int* board, int holes) {//fullboard是答案，board是挖空后的结果（即生成的题目），holes是数独剩余未填个数
    bool enter[163] = { 0 };//表示是否填入 0-未填入 1-已填入
    int n, i, j, k;
    for (i = 1; i <= 162; i++) {
        if (board[i]) {
            enter[i] = 1;//表示已经填入了数
        }
    }
    while (1) {
        system("cls");
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
