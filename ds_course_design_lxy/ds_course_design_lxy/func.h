#pragma once
#pragma once
#include"def.h"
void DPLL(struct SAT* P);                     
void initP(struct SAT* P);                    
void ReadFile_check(struct SAT* P, FILE* fp);     
void ReadFile(struct SAT* P, FILE* fp);       
void PrintFile(struct SAT* P);               
int FindUnitClause(struct SAT* P);            
status DeleteUnitClause(struct SAT* P, int x, int depth);
void recover(struct SAT* P, int depth);      
void AddUnitClause(struct SAT* P, int x);     
void FreeClause(clause* s);                    
void DeleteFirstClause(struct SAT* P);        
int SelectMax(struct SAT* P);                 
void PrintCount(struct SAT* P);               
status solve(struct SAT* P, int depth, int x);
void FormAnsFile(struct SAT* P, int result, int time, char name[200]);
void PrintAns(struct SAT P);                  
status CheckAns(struct SAT P);                
status solve1(struct SAT* P, int depth, int x);
int SelectFirst(struct SAT* P);
double J(int n);
int getNextBool_2SidedJW_optimized(clause* cnf);
int getNextBool_Positive_2SidedJW(clause* cnf);




void SudSolve();                              
void transformToCnf(Sud S, char FileName[200]);    
void PrintSud(Sud S);                         
void initS(Sud* S);                          
int VarTrans(int i, int j, int n);            
void ReadSudFile(Sud* S, char FileName[200]); 
void SudAns(struct SAT* P, Sud* S);       
void SudPlay();                              
DSud* Sudcreate();                             
void DigHole(Sud* k);                         
void DigHole2(Sud* k, Sud* k2);               
status Candig(Sud* k, int x, int y);         
status Candig2(Sud* k, int x, int y);       
void hint(Sud* k, Sud* k2);                            
void InputSud2(Sud* k, Sud* k2, SAT* P);