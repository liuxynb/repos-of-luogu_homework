#include"def.h"
#include"func.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
char FileName[200] = { '\0' };
struct SAT P;
Sud S;
clause* p1 = NULL;
int main()
{
	int choice = 1, op1 = 1, op2 = 1;
	int flag = 0;
	while (choice) {
		system("cls");
		printf("\n\n                    Menu for SAT Solver based on DPLL                   \n\n");
		printf("------------------------------------------------------------------------\n\n");
		printf("                                 1.SAT                                  \n\n");
		printf("                                 2.Sudoku                               \n\n");
		printf("                                 0.Exit                                 \n\n");
		printf("------------------------------------------------------------------------\n\n");
		printf("Input operator:[0~2]\n");
		scanf("%d", &choice);
		if (choice == 1)//进入SAT问题
		{
			op1 = 1;
			while (op1)
			{
				system("cls");
				printf("\n\n                             *SAT Solver*\n");
				printf("-------------------------------------------------------------------------\n");
				printf("                             1.Read File\n\n");
				printf("                             2.Print File\n\n");
				printf("                             3.DPLL\n\n");
				printf("                             4.Print Answer\n\n");
				printf("                             5.Check Answer\n\n");
				printf("                             0.Back\n");
				printf("-------------------------------------------------------------------------\n");
				scanf("%d", &op1);
				FILE* fp = NULL;
				switch (op1) {
				case 1:
					printf("请输入测试文件名:");
					scanf("%s", FileName);
					fp = fopen(FileName, "r");
					initP(&P);
					ReadFile_check(&P, fp);
					if (fp) {
						ReadFile(&P, fp);
						printf("文件中共有%d个变量，%d个子句\n", P.vnum, P.stnum);
						printf("cnf文件读取完毕！\n");
						fclose(fp);
					}
					getchar(); getchar();
					break;
				case 2:
					PrintFile(&P);
					//PrintCount(P);
					getchar(); getchar();
					break;
				case 3:
					DPLL(&P);
					getchar(); getchar();
					break;
				case 4:
					PrintAns(P);
					getchar(); getchar();
					break;
				case 5:
					flag = CheckAns(P);
					if (flag == OK)
						printf("答案正确！");
					else printf("答案不正确！");
					getchar(); getchar();
					break;
				default:
					break;
				}
			}
		}
		else if (choice == 2) //进入数独问题
		{
			op2 = 1;
			while (op2)
			{
				system("cls");
				printf("------------------------------------------------------------------------\n");
				printf("     1.Sudoku Solve   2.Sudoku Play   0.Back                            \n");
				printf("------------------------------------------------------------------------\n");
				scanf("%d", &op2);
				switch (op2) {
				case 1:
					SudSolve();
					getchar(); getchar();
					break;
				case 2:
					SudPlay();
					getchar();
					break;
				default:
					break;
				}
			}
		}
		else break;
	}
	return 0;
}