#include"def.h"
#include"func.h"
#pragma warning(disable:4996)
#pragma warning(disable:6031)
extern int Vnum;//ȫ�ֱ���V_count:������Ԫ����
extern int* value;//ȫ�ֱ��� value����,���ڼ�¼���Ա�Ԫ����ֵ 1-�� 0-��
extern char filename[200];
extern int transfer[3000];//����λ����ת��Ϊ��Ԫ��Ȼ������
extern int transfer_to_loc[1700];//��Ȼ������ת��Ϊλ�ù�����
/*
 *�������ƣ�void get_transfer()
 *�������ܣ��õ���Ȼ��������λ�ù�����֮���ת������ tranfer �� transfer_to_loc
 */
void Transfer(int transfer[], int transfer_to_loc[]) {
    int n, i, j, k, cnt = 1;
    for (n = 1; n <= 2; n++) {//n-1-�����̣�n-2-������
        for (i = 1; i <= 9; i++) {//��
            for (j = 1; j <= 9; j++) {//��
                for (k = 1; k <= 9; k++) {//�����
                    transfer_to_loc[cnt] = n * 1000 + i * 100 + j * 10 + k;//��Ȼ������ת��Ϊ������
                    transfer[n * 1000 + i * 100 + j * 10 + k] = cnt;//������ת��Ϊ��Ȼ������
                    cnt++;

                }
            }
        }
    }
}//�õ�����������Ȼ������֮���ת������
/*
 *�������ƣ�void AddNode(SATNode * & head,SATNode *& newnode)
 *�������ܣ�������head�����newnode���ײ巨��
 */
void AddNode(cNode*& head, cNode*& newnode) {
    newnode->next = head->next;
    head->next = newnode;
}
/*
 *�������ƣ�void Diger(int *sudoku,int holes)
 *�������ܣ��ڶ��㷨����˫sudoku����holes����
 */
void Diger(int* sudoku, int holes) {
    int cnt = 0;
    bool mark[163];//����Ƿ���
    for (cnt = 1; cnt <= 162; cnt++) {
        mark[cnt] = false;//��ʾû�б���
    }
    cnt = 0;
    srand(time(0));
    while (cnt < holes) {
        int n = rand() % 2 + 1;
        int x = rand() % 9 + 1;
        int y = rand() % 9 + 1;
        if (mark[(n - 1) * 81 + (x - 1) * 9 + y] == false) {
            cnt++;
            if (n == 1 && x >= 7 && y >= 7) {//�ڵ��ǵ�һ��ģ������½�
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = 0;
                sudoku[81 + (x - 7) * 9 + y - 6] = 0;
                mark[(n - 1) * 81 + (x - 1) * 9 + y] = true;
                mark[81 + (x - 7) * 9 + y - 6] = true;
            }
            else if (n == 2 && x <= 3 && y <= 3) {//�ڵ��ǵڶ���ģ�����Ͻ�
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = 0;
                sudoku[(x + 5) * 9 + y + 6] = 0;
                mark[(n - 1) * 81 + (x - 1) * 9 + y] = true;
                mark[(x + 5) * 9 + y + 6] = true;
            }
            else {//�ǽ��沿��
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = 0;
                mark[(n - 1) * 81 + (x - 1) * 9 + y] = true;
            }
        }//�ڵĶ����Ϲ��� 1.֮ǰû�б��ڹ�
    }
    return;
}
/*
 *�������ƣ�Create_sudoku(int  sudoku[],AdjList * & root,int idx)
 *�������ܣ������������̺��ڶ��㷨��������ԭ��
 */
void CreateSudoku(int  sudoku[], int idx) {
    Vnum = 729 * 2;
    //��������

    //������Ӽ�����
    //srand(time(0));
    srand(time(NULL));
    int n, x, y, num;
    int flag = 1;
    for (int t = 0; t < 16 && flag;) {//
        n = rand() % 2 + 1;
        x = rand() % 9 + 1;//��
        y = rand() % 9 + 1;//��
        num = rand() % 9 + 1;//�����
        if (sudoku[(n - 1) * 81 + (x - 1) * 9 + y] == 0 && isVaild(sudoku, n, x, y, num)) {//δ�����ҷ����������
            t++;
            if (n == 1 && x >= 7 && y >= 7) {//��һģ������½�
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = num;
                sudoku[81 + (x - 7) * 9 + y - 6] = num;
            }
            else if (n == 2 && x <= 3 && y <= 3) {//�ڶ�ģ������½�
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = num;
                sudoku[(x + 5) * 9 + y + 6] = num;
            }
            else {//�ǽ��沿��
                sudoku[(n - 1) * 81 + (x - 1) * 9 + y] = num;
            }
            if (t > 10) {
                if (Sudoku_Solver(sudoku)) {//��������
                    flag = 0;
                    //printf("��������!\n");
                    //show_the_sudoku(sudoku);//
                }
            }
        }
    }

    //�ڶ� diger
    Diger(sudoku, idx * 20);

}
/*
 *�������ƣ�bool isTrue(int sudoku[],int n,int i,int j,int k)
 *�������ܣ��ж���������Ƿ������������
 */
bool isVaild(int sudoku[], int n, int i, int j, int k) {//sudokuΪ˫���飬nΪ�ĸ��̣�iΪ��(��1��ʼ����jΪ�У���1��ʼ����kΪ����1-9��
    //��Ҫ�ж����Ƿ����ظ������Ƿ����ظ����Ź������Ƿ����ظ�

    for (int m = 1; m <= 9; m++) {
        if (sudoku[(n - 1) * 81 + (i - 1) * 9 + m] == k) return false;//�д�����ͬ��
        if (sudoku[(n - 1) * 81 + (m - 1) * 9 + j] == k) return false;//�д�����ͬ��
    }
    //�Ź���
    int line = ((i - 1) / 3) * 3 + 1, col = ((j - 1) / 3) * 3 + 1;//�Ź������ʼ����
    for (int a = line; a < line + 3; a++) {
        for (int b = col; b < col + 3; b++) {
            if (sudoku[(n - 1) * 81 + (a - 1) * 9 + b] == k) return false;//�Ź����ڴ�����ͬ��
        }
    }
    return true;
}
/*
 *��������:void init_value(int value[])
 *�������ܣ���ʼ��value���飬���������Ϊ1
 */
void init_value(int value[]) {
    for (int i = 1; i <= Vnum; i++) {
        value[i] = 1;//value ��ʼ��
    }
}
/*
 *�������ƣ�int Sudoku_Solver(int sudoku[])
 *�������ܣ�����������ת��Ϊ������Ԫ�Լ�CNF��䣬����DPLL��Ⲣ����Ԫת��Ϊ����
 */
int Sudoku_Solver(int sudoku[]) {//����dpll
    clause* root = (clause*)malloc(sizeof(clause));
    root->head = NULL;
    root->next = NULL;//�ڽӱ������ʼ��

    value = (int*)malloc(sizeof(int) * Vnum + 1);
    init_value(value);
    int i, j, k, n;

    //Part0-����Լ��
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
                    for (int m = k + 1; m <= 9; m++) {//�����ظ�
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
                AddClause(root, newlist);//newlist��֤ÿ�����Ӷ������1-9
            }
        }
    }
    //Part1-��Լ����
    //Step1-ÿһ��ģ�飬����ÿһ������ÿһ�ж������
    for (n = 1; n <= 2; n++) {//ģ��
        for (k = 1; k <= 9; k++) {//1-9
            for (i = 1; i <= 9; i++) {//��
                clause* newlist = (clause*)malloc(sizeof(clause));
                newlist->head = (cNode*)malloc(sizeof(cNode));
                newlist->next = NULL;
                newlist->head->next = NULL;
                for (j = 1; j <= 9; j++) {//��
                    cNode* newnode = (cNode*)malloc(sizeof(cNode));
                    newnode->next = NULL;
                    newnode->data = transfer[n * 1000 + i * 100 + j * 10 + k];
                    newnode->next = newlist->head->next;
                    newlist->head->next = newnode;//�ײ巨,newlist��֤ÿ���ж���1-9
                    //debug
                    //fprintf(fp, "%d(%d) ",newnode->data,n*1000+i*100+j*10+k);
                    for (int m = j + 1; m <= 9; m++) {//newlist2 ��֤һ����������������ͬ
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

    //Part2-��Լ��
    //Step1-��֤ÿ�ж������1-9
    for (n = 1; n <= 2; n++) {
        for (k = 1; k <= 9; k++) {
            for (j = 1; j <= 9; j++) {
                clause* newlist = (clause*)malloc(sizeof(clause));
                newlist->next = NULL;
                newlist->head = (cNode*)malloc(sizeof(cNode));
                newlist->head->next = NULL;//newlist��֤ÿһ�ж���1-9

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
                        AddClause(root, newlist2);//newlist2��֤ÿһ��1-9���ظ�
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
    //Part3-�Ź���Լ��
    for (n = 1; n <= 2; n++) {
        for (int a = 1; a <= 9; a += 3) {
            for (int b = 1; b <= 9; b += 3) {//a,b��ʾ��Լ���Ź�������Ͻ�����
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
                                    AddClause(root, newlist2);//newlist2���ڱ�֤�Ź�����1-9���ظ�
                                }
                            }
                        }
                    }
                    // fprintf(fp, "\n");
                    AddClause(root, newlist1);//newlist1���ڱ�֤�Ź���һ�������1-9
                }
            }
        }
    }
    //fclose(fp);
    //return ;

    //Part4-˫�������沿�ֵȼ�ʽԼ��
    for (k = 1; k <= 9; k++) {
        int n_1 = 1, a_1 = 7, b_1 = 7;//�����̵����һ���Ź��񣬴�7-7��ʼ
        int n_2 = 2, a_2 = 1, b_2 = 1;//�����̵ĵ�һ���Ź��񣬴�1-1��ʼ
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
                AddClause(root, newlist1);//newlist1�� 1��2��

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
                AddClause(root, newlist2);//newlist2��1��2��
            }
        }
    }
    //fclose(fp);
    //return ;

    //Part5-��֪����ת��Ϊ���Ӿ�
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

    //���
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
                int num = transfer_to_loc[i];//ת��Ϊ������
                int n_, i_, j_, k_;
                k_ = num % 10;//��λ
                num /= 10;//������λ

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
        //printf("dpllʧ��!\n");
        return 0;
    }

}
/*
 *�������ƣ�void show_the_sudoku(int sudoku[])
 *�������ܣ�չ���������
 */
void showSudoku(int sudoku[]) {
    int i, j;
    //�����һ��������ǰ����
    for (i = 0; i < 6; i++) {
        for (j = 1; j <= 9; j++) {
            printf("%d ", sudoku[i * 9 + j]);
        }
        printf("\n");
    }
    //����в����������
    for (i = 6; i < 9; i++) {
        for (j = 1; j <= 9; j++) {
            printf("%d ", sudoku[i * 9 + j]);
        }//��һ�������ĵ�9��
        for (int k = 0; k < 6; k++) {
            printf("%d ", sudoku[i * 9 + j + 21 + k]);
        }
        printf("\n");
    }
    //����ڶ��������ĺ�����
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

void PlaySukodu(int* fullboard, int* board, int holes) {//fullboard�Ǵ𰸣�board���ڿպ�Ľ���������ɵ���Ŀ����holes������ʣ��δ�����
    bool enter[163] = { 0 };//��ʾ�Ƿ����� 0-δ���� 1-������
    int n, i, j, k;
    for (i = 1; i <= 162; i++) {
        if (board[i]) {
            enter[i] = 1;//��ʾ�Ѿ���������
        }
    }
    while (1) {
        system("cls");
        printf("        Holes Left:%d\n", holes);
        printf("\033[37;32m    1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n");
        //�����һ��������ǰ����
        int line = 1;
        for (i = 0; i < 6; i++) {
            printf("\033[37;32m%d   ", line++);//����к�
            for (j = 1; j <= 9; j++) {
                if (enter[i * 9 + j] == 1)
                    printf("\033[37;31m%d  ", board[i * 9 + j]);
                else
                    printf("\033[37;34m%d  ", board[i * 9 + j]);
            }
            printf("\n");
        }
        //����в����������
        for (i = 6; i < 9; i++) {
            printf("\033[37;32m%d   ", line++);
            for (j = 1; j <= 9; j++) {
                if (enter[i * 9 + j] == 1)
                    printf("\033[37;31m%d  ", board[i * 9 + j]);
                else
                    printf("\033[37;34m%d  ", board[i * 9 + j]);
            }//��һ�������ĵ�9��
            for (int k = 0; k < 6; k++) {
                if (enter[i * 9 + j + 21 + k] == 1)
                    printf("\033[37;31m%d  ", board[i * 9 + j + 21 + k]);
                else
                    printf("\033[37;34m%d  ", board[i * 9 + j + 21 + k]);
            }
            printf("\n");
        }
        //����ڶ��������ĺ�����
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
        printf("\033[37;37m������ѡ��Ĳ�����0-������Ϸ��3-����𰸣�4-������ʾ,5-��Ƥ��\n");
        printf("������4������д������(��ʽ n(1-���ϣ�2-���£� i���У� j���У� k�������������\n");
        scanf("%d", &n);
        if (n == 0) {//������Ϸ
            printf("��Ϸ����!\n");
            break;
        }
        else if (n == 3) {//������Ϸ
            int flag = 1;
            for (int m = 1; m <= 162; m++) {
                if (board[m] != fullboard[m]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                printf("��ϲ�㣬ͨ���ˣ�\n");
            }
            else {
                printf("��Ǹ���𰸴���\n");
            }
        }
        else if (n == 4) {
            printf("������������ʾ��λ��:(��ʽ n(1-���ϣ�2-���£� i���У� j���У�)\n");
            scanf("%d%d%d", &n, &i, &j);
            if (n == 1) {
                printf("���Ͻǵ�%d�е�%d�е���Ϊ%d\n", i, j, fullboard[(n - 1) * 81 + (i - 1) * 9 + j]);
                getchar();
                getchar();
            }
            else {
                printf("���½ǵ�%d�е�%d�е���Ϊ%d\n", i, j, fullboard[(n - 1) * 81 + (i - 1) * 9 + j]);
                getchar();
                getchar();
            }
        }
        else if (n == 5) {//��ȥ
            printf("������������������λ��:(��ʽ n(1-���ϣ�2-���£� i���У� j���У�)\n");
            scanf("%d%d%d", &n, &i, &j);
            if (n == 1 && i >= 7 && i >= 7) {//��һģ������½�
                board[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
                board[81 + (i - 7) * 9 + j - 6] = 0;
                enter[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
                enter[81 + (i - 7) * 9 + j - 6] = 0;
            }
            else if (n == 2 && i <= 3 && j <= 3) {//�ڶ�ģ������Ͻ�
                board[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
                board[(i + 5) * 9 + j + 6] = 0;
                enter[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
                enter[(i + 5) * 9 + j + 6] = 0;
            }
            else {//�ǽ��沿��
                board[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
                enter[(n - 1) * 81 + (i - 1) * 9 + j] = 0;
            }
            holes++;
            printf("�����ɹ�!\n");
        }
        else {
            scanf("%d%d%d", &i, &j, &k);
            if (enter[(n - 1) * 81 + (i - 1) * 9 + j] == false) {
                if (n == 1 && i >= 7 && i >= 7) {//��һģ������½�
                    board[(n - 1) * 81 + (i - 1) * 9 + j] = k;
                    board[81 + (i - 7) * 9 + j - 6] = k;
                    enter[(n - 1) * 81 + (i - 1) * 9 + j] = 1;
                    enter[81 + (i - 7) * 9 + j - 6] = 1;
                }
                else if (n == 2 && i <= 3 && j <= 3) {//�ڶ�ģ������½�
                    board[(n - 1) * 81 + (i - 1) * 9 + j] = k;
                    board[(i + 5) * 9 + j + 6] = k;
                    enter[(n - 1) * 81 + (i - 1) * 9 + j] = 1;
                    enter[(i + 5) * 9 + j + 6] = 1;
                }
                else {//�ǽ��沿��
                    board[(n - 1) * 81 + (i - 1) * 9 + j] = k;
                    enter[(n - 1) * 81 + (i - 1) * 9 + j] = true;
                }
                holes--;
                printf("����ɹ�!\n");
            }
            else {
                printf("���λ���ѱ�����!\n");
            }
        }
        getchar();
        getchar();
    }
}
