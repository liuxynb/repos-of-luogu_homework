#pragma once
#include"def.h"

//Part1-CNF
status ReadFile(char* filename, clause*& SATList);//文件读取/
status OutputFileContent(clause* root);//全部子句输出/
status DestroyAdjList(clause*& root);//销毁邻接表/
bool isUnitClause(cNode* head);//判断是否为单子句/
bool evaluateClause(cNode* head);//判断是否子句真假性/
status RemoveClause(clause*& root, clause* relist);//删除子句/
status AddClause(clause*& root, clause*& newlist);//添加子句/
void Back_up(clause*& root_1, clause* origin_root);//备份,用于复制回溯/
bool emptyClause(clause* root);//判断是否含有空子句/
bool DPLL(clause*& SATList, int choice);//DPLL算法
void DestroyClause(clause*& alist);//删除一个子句
status PreserveResult(char filename[], int ret, double time);//保存结果/
void AddNode(cNode*& head, cNode*& newnode);//添加结点
int getbool_2sides_optimized(clause* root);//优化/
int getbool_2sides(clause* root);//同时权衡子句长度和出现频率/
int getMaxbool(clause* SATList);//出现频率最大/
int getMaxbool_optimized(clause* SATList);//优化/
double J(int n);
int getNextBool_Positive_2SidedJW(clause* root);

//Part2-Sudoku
int  Sudoku_Solver(int sudoku[]);//数独解决/
void Transfer(int transfer[], int transfer_to_loc[]);//得到转换数组,用于自然排列数和位置构造数的转换/
void CreateSudoku(int* sudoku, int idx);//创建双数独格局/
bool isVaild(int sudoku[], int n, int i, int j, int k);//判断填入的数是否符合/
void showSudoku(int sudoku[]);//数独格局呈现
void Diger(int sudoku[], int holes);//挖洞/
void PlaySukodu(int* fullboard, int* board, int holes);//交互玩游戏
