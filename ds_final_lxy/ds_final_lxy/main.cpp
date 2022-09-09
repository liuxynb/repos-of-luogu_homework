//
//  main.cpp
//  Problem_of_SAT_on_dpll
//
//  Created by 刘兴元 on 2022/9/8 final edition
//文字子句消隐法
#include"def.h"
#include"func.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)



int Vnum = 0;//全局变量V_count:布尔变元个数
int* value = NULL;//全局变量 value数组,用于记录所以变元的真值 1-真 0-假
char filename[200];
int transfer[3000];//构造位置数转换为变元自然排列数
int transfer_to_loc[1700];//自然排列数转换为位置构造数

int main() {
    clause* SATList = NULL;
    int op = 1, op1 = 1, op2 = 1;
    while (op) {
        system("cls");
        printf("\n\n                    Menu for SAT Solver based on DPLL                   \n\n");
        printf("------------------------------------------------------------------------\n\n");
        printf("                                 1.SAT                                  \n\n");
        printf("                                 2.Sudoku                               \n\n");
        printf("                                 0.Exit                                 \n\n");
        printf("------------------------------------------------------------------------\n\n");
        printf("Input operator:[0~2]\n");
        scanf("%d", &op);
        switch (op) {
        case 1: {//CNF系统
            op1 = 1;
            while (op1) {
                system("cls");
                printf("\n\n                             *SAT Solver*\n");
                printf("-------------------------------------------------------------------------\n");
                printf("                             1.Read File\n\n");
                printf("                             2.Print File\n\n");
                printf("                             3.DPLL\n\n");
                printf("                             4.Print Answer\n\n");
                printf("                             0.Back\n");
                printf("-------------------------------------------------------------------------\n");
                printf("Input operator:[0~2]\n");
                scanf("%d", &op1);
                switch (op1) {
                case 1: {//Read the CNF_file
                    SATList = NULL;
                    printf("请输入需要读取的文件名!\n");
                    scanf("%s", filename);
                    if (ReadFile(filename, SATList) == OK) {
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
                    if (OutputFileContent(SATList) == OK) {
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
                    printf("                     请选择变量决策策略!\n");
                    printf("               1.VSIDS\n                      2.VSIDS_optimized\n");
                    printf("               3.2Sides_Stragety\n            4.3_optimized\n");
                    printf("               5.getNextBool_Positive_2Sided");

                    scanf("%d", &choice);
                    int ret = DPLL(SATList, choice);
                    double end = clock();
                    if (ret == 1) {
                        printf("有解!各变元的真值如下\n");
                        for (int i = 1; i <= Vnum; i++) {
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
                    if (PreserveResult(filename, ret, time) == OK) {
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
            Vnum = 729 * 2;
            Transfer(transfer, transfer_to_loc);
            op2 = 1;
            while (op2) {
                system("cls"); printf("\n\n");
                printf("------------------------------------------------------------------------\n");
                printf("     1.Sudoku Solve   2.Sudoku Play   0.Back                            \n");
                printf("------------------------------------------------------------------------\n");
                printf("    请选择你的操作[0~2]:\n");
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
                        CreateSudoku(sudoku, idx);
                        printf("\n生成数独题目如下!\n");
                        showSudoku(sudoku);
                    }//挖洞算法创建数独
                    else if (idx == 0) {
                        int n, x, y, num;
                        printf("请输入你想添加的数!(格式 n(1-左上，2-右下） i（行） j（列） k（填入的数）结束输入以0结束\n");
                        scanf("%d%d%d%d", &n, &x, &y, &num);
                        while (n) {
                            if (sudoku[(n - 1) * 81 + (x - 1) * 9 + y] == 0 && isVaild(sudoku, n, x, y, num)) {//未填入且符合填入规则
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
                        showSudoku(sudoku);
                    }
                    //show_the_sudoku(sudoku);
                    int ret = Sudoku_Solver(sudoku);
                    if (ret) {
                        printf("\n数独解如下!\n");
                        showSudoku(sudoku);
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
                    CreateSudoku(fullboard, idx);
                    for (int i = 1; i <= 162; i++) {
                        board[i] = fullboard[i];
                    }//复制得到数独题目board
                    //show_the_sudoku(board);
                    Sudoku_Solver(fullboard);
                    //show_the_sudoku(fullboard);
                    PlaySukodu(fullboard, board, idx * 20);
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