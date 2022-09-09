#pragma once
#include"def.h"

//Part1-CNF
status ReadFile(char* filename, clause*& SATList);//�ļ���ȡ/
status OutputFileContent(clause* root);//ȫ���Ӿ����/
status DestroyAdjList(clause*& root);//�����ڽӱ�/
bool isUnitClause(cNode* head);//�ж��Ƿ�Ϊ���Ӿ�/
bool evaluateClause(cNode* head);//�ж��Ƿ��Ӿ������/
status RemoveClause(clause*& root, clause* relist);//ɾ���Ӿ�/
status AddClause(clause*& root, clause*& newlist);//����Ӿ�/
void Back_up(clause*& root_1, clause* origin_root);//����,���ڸ��ƻ���/
bool emptyClause(clause* root);//�ж��Ƿ��п��Ӿ�/
bool DPLL(clause*& SATList, int choice);//DPLL�㷨
void DestroyClause(clause*& alist);//ɾ��һ���Ӿ�
status PreserveResult(char filename[], int ret, double time);//������/
void AddNode(cNode*& head, cNode*& newnode);//��ӽ��
int getbool_2sides_optimized(clause* root);//�Ż�/
int getbool_2sides(clause* root);//ͬʱȨ���Ӿ䳤�Ⱥͳ���Ƶ��/
int getMaxbool(clause* SATList);//����Ƶ�����/
int getMaxbool_optimized(clause* SATList);//�Ż�/
double J(int n);
int getNextBool_Positive_2SidedJW(clause* root);

//Part2-Sudoku
int  Sudoku_Solver(int sudoku[]);//�������/
void Transfer(int transfer[], int transfer_to_loc[]);//�õ�ת������,������Ȼ��������λ�ù�������ת��/
void CreateSudoku(int* sudoku, int idx);//����˫�������/
bool isVaild(int sudoku[], int n, int i, int j, int k);//�ж���������Ƿ����/
void showSudoku(int sudoku[]);//������ֳ���
void Diger(int sudoku[], int holes);//�ڶ�/
void PlaySukodu(int* fullboard, int* board, int holes);//��������Ϸ
