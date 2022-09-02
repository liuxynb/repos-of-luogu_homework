#pragma once
#pragma once
#include"define.h"
void DPLL(struct problem* P);                     //DPLL�㷨
void initP(struct problem* P);                    //��ʼ������
void _ReadFile(struct problem* P, FILE* fp);      //��ȡһ��cnf�ļ���ע��
void ReadFile(struct problem* P, FILE* fp);       //��ȡһ��cnf�ļ��ĸ����Ӿ�
void PrintFile(struct problem* P);                //��ӡcnf�ļ��еĸ����Ӿ�
int FindUnitClause(struct problem* P);            //���Ӿ伯���ҵ�һ�����Ӿ䣬���ظõ��Ӿ��������������ֵ�ֵ
status DeleteUnitClause(struct problem* P, int x, int depth);//���Ӿ伯��ɾ������x���Ӿ䣬���Ӹ����Ӿ�ɾ������-x������ɾ��ʱ�����depth
void recover(struct problem* P, int depth);       //��ԭ�ڻ������Ϊdepthʱ��ɾ�����Ӿ�����
void AddUnitClause(struct problem* P, int x);     //��P�ĸ��ڵ�������ײ巨����һ�����Ӿ䣬���Ӿ���Ψһ���ֵ�ֵΪx
void FreeClause(statement* s);                    //�ͷ��Ӿ�s�Ŀռ�(���ͷ�s�Ŀռ䣬������ָ���Ӿ�s��ǰһ�Ӿ��sָ��ĺ�һ�Ӿ�)
void DeleteFirstClause(struct problem* P);        //ɾ��AddUnitClause��������ĵ�һ���Ӿ䣬���ͷ��䴢��ռ�
int SelectMax(struct problem* P);                 //�ҵ�һ�����ִ������ı��������ر�����ֵ������ֵ������ֵ
void PrintCount(struct problem* P);               //��ӡ�����������ֵĴ���
status solve(struct problem* P, int depth, int x);//��SAT������⣬PΪ���������⣬depthΪ�Ѿ����е���ȣ�xΪ��������
void FormAnsFile(struct problem* P, int result, int time, char name[200]);
//����׺Ϊ.cnf���ļ��γ����Ӧ�Ĵ��ļ���resultΪ���н����timeΪ����ʱ�䣬nameΪcnf�ļ���
void PrintAns(struct problem P);                  //��ӡSAT�ļ��Ĵ�
status CheckAns(struct problem P);                //�����Ƿ���ȷ
status solve1(struct problem* P, int depth, int x);
int SelectFirst(struct problem* P);


void SudSolve();                              //���һ������
void transform(sud S, char FileName[200]);    //�������ļ�ת��ΪCNF�ļ�
void PrintSud(sud S);                         //��ӡ������ʽ
void initS(sud* S);                           //��ʼ����������S
int VarTrans(int i, int j, int n);            //����ת�����������������ת��Ϊ��Ȼ˳����룬���������i��j����������n
void ReadSudFile(sud* S, char FileName[200]); //����һ�������ļ�
void SudAns(struct problem* P, sud* S);       //������ֵת��Ϊ������
void SudPlay();                               //��������
sud* Sudcreate();                             //����һ�������������
void DigHole(sud* k);                         //�������ڶ�
status Candig(sud* k, int x, int y);          //�ж��Ƿ�Ϊ�����ڶ�
void hint(sud* k);                            //������ʾ