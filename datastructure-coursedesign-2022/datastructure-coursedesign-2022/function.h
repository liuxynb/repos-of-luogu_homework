#pragma once
#pragma once
#include"define.h"
void DPLL(struct problem* P);                     //DPLL算法
void initP(struct problem* P);                    //初始化问题
void _ReadFile(struct problem* P, FILE* fp);      //读取一个cnf文件的注释
void ReadFile(struct problem* P, FILE* fp);       //读取一个cnf文件的各个子句
void PrintFile(struct problem* P);                //打印cnf文件中的各个子句
int FindUnitClause(struct problem* P);            //在子句集中找到一个单子句，返回该单子句中所包含的文字的值
status DeleteUnitClause(struct problem* P, int x, int depth);//从子句集中删除包含x的子句，并从各个子句删除文字-x，保存删除时的深度depth
void recover(struct problem* P, int depth);       //复原在回溯深度为depth时被删除的子句或句子
void AddUnitClause(struct problem* P, int x);     //在P的根节点后运用首插法插入一个单子句，单子句中唯一文字的值为x
void FreeClause(statement* s);                    //释放子句s的空间(仅释放s的空间，不考虑指向子句s的前一子句和s指向的后一子句)
void DeleteFirstClause(struct problem* P);        //删除AddUnitClause函数插入的第一个子句，并释放其储存空间
int SelectMax(struct problem* P);                 //找到一个出现次数最多的变量，返回变量的值，返回值总是正值
void PrintCount(struct problem* P);               //打印各个变量出现的次数
status solve(struct problem* P, int depth, int x);//对SAT问题求解，P为所求解的问题，depth为已经进行的深度，x为线索变量
void FormAnsFile(struct problem* P, int result, int time, char name[200]);
//给后缀为.cnf的文件形成其对应的答案文件，result为运行结果，time为运行时间，name为cnf文件名
void PrintAns(struct problem P);                  //打印SAT文件的答案
status CheckAns(struct problem P);                //检查答案是否正确
status solve1(struct problem* P, int depth, int x);
int SelectFirst(struct problem* P);


void SudSolve();                              //求解一个数独
void transform(sud S, char FileName[200]);    //将数独文件转换为CNF文件
void PrintSud(sud S);                         //打印数独样式
void initS(sud* S);                           //初始化数独问题S
int VarTrans(int i, int j, int n);            //变量转换函数，将语义编码转换为自然顺序编码，输入变量名i行j列填入数字n
void ReadSudFile(sud* S, char FileName[200]); //读入一个数独文件
void SudAns(struct problem* P, sud* S);       //将变量值转换为数独答案
void SudPlay();                               //可玩数独
sud* Sudcreate();                             //生成一个可以玩的数独
void DigHole(sud* k);                         //给数独挖洞
status Candig(sud* k, int x, int y);          //判断是否为可以挖洞
void hint(sud* k);                            //给出提示