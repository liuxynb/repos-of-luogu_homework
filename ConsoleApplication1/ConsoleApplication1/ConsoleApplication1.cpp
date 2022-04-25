/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct {  //顺序表（顺序结构）的定义
    ElemType* elem;
    int length;
    int listsize;
}SqList;
/*-----page 19 on textbook ---------*/
status InitList(SqList& L) {
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL) {
        L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
        if (!L.elem) exit(OVERFLOW);
        L.length = 0;
        L.listsize = LIST_INIT_SIZE;
        return OK;
    }
    else {
        return INFEASIBLE;
    }


    /********** End **********/
}
status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if (L.elem != NULL)
    {
        free(L.elem);
        L.elem = NULL;
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
    else
        return INFEASIBLE;
}

    /********** End **********/
}
status ClearList(SqList& L) {
    // 请在这里补充代码，完成本关任务// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE
    /********** Begin *********/
    if (L.elem != NULL) {
        L.length = 0;
        return OK;
    }
    else {
        return INFEASIBLE;
    }

    /********** End **********/
}
status ListEmpty(SqList L) {
    // 请在这里补充代码，完成本关任务
    // 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem != NULL) {
        if (L.length == 0)return TRUE;
        else return FALSE;
    }
    else {
        return INFEASIBLE;
    }

    /********** End **********/
}
status ListLength(SqList L) {
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem != NULL) {
        return L.length;
    }
    else {
        return INFEASIBLE;
    }

    /********** End **********/
}
status GetElem(SqList  L, int  i, ElemType& e) {
    // 请在这里补充代码，完成本关任务
    // 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem != NULL) {
        if (i > L.length || i < 1)return ERROR;
        else {
            e = (L.elem[i - 1]);
            return OK;
        }
    }
    else {
        return INFEASIBLE;
    }

    /********** End **********/
}
status LocateElem(SqList L, ElemType e) {
    // 请在这里补充代码，完成本关任务// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
    /********** Begin *********/
    if (L.elem != NULL) {
        int j = 0;
        while (e != L.elem[j] && j < L.length) {
            j++;
        }
        if (j == L.length) {
            return 0;
        }
        else {
            return j + 1;
        }
    }
    else {
        return INFEASIBLE;
    }

    /********** End **********/
} //简化过
status PriorElem(SqList L, ElemType e, ElemType& pre) {
    // 请在这里补充代码，完成本关任务// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem != NULL) {
        int j = 0;
        while (e != L.elem[j] && j < L.length) {
            j++;
        }
        if (j == L.length) {
            return ERROR;
        }
        else {
            if (j == 0)return ERROR;
            else {
                pre = L.elem[j - 1];
                return OK;
            }
        }
    }
    else {
        return INFEASIBLE;
    }

    /********** End **********/
}
status NextElem(SqList L, ElemType e, ElemType& next) {
    // 请在这里补充代码，完成本关任务// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem != NULL) {
        int j = 0;
        while (e != L.elem[j] && j < L.length) {
            j++;
        }
        if (j == L.length) {
            return ERROR;
        }
        else {
            if (j == L.length - 1)return ERROR;
            else {
                next = L.elem[j + 1];
                return OK;
            }
        }
    }
    else {
        return INFEASIBLE;
    }

    /********** End **********/
}
status ListInsert(SqList& L, int i, ElemType e) {
    // 请在这里补充代码，完成本关任务// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK;当插入位置不正确时，返回ERROR;如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem != NULL) {
        if (i<1 || i>L.length + 1) return ERROR;
        else {
            if (L.length >= L.listsize) {
                ElemType* newbase;
                newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
                L.elem = newbase;
                L.listsize += LISTINCREMENT;
            }
            for (int j = L.length - 1; j >= i - 1; j--)
                L.elem[j + 1] = L.elem[j];
            L.elem[i - 1] = e;
            L.length++;
            return OK;
        }

    }
    else {
        return INFEASIBLE;
    }
}
status  ListDelete(SqList& L, int i, ElemType& e) {
    // 请在这里补充代码，完成本关任务// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem != NULL) {
        if (i<1 || i>L.length)return ERROR;
        else {
            e = L.elem[i - 1];
            for (int j = i - 1; j < L.length - 1; j++)
                L.elem[j] = L.elem[j + 1];
            L.length--;
            return OK;
        }
    }
    else {
        return INFEASIBLE;
    }

    /********** End **********/
}
status ListTrabverse(SqList L) {
    // 请在这里补充代码，完成本关任务// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
    /********** Begin *********/
    if (L.elem != NULL) {
        for (int i = 0; i < L.length; i++) {
            if (i != L.length - 1)
                printf("%d ", L.elem[i]);
            else printf("%d", L.elem[L.length - 1]);
        }

        return OK;
    }
    else {
        return INFEASIBLE;
    }

    /********** End **********/
}  //简化过
/*--------------------------------------------*/
int main(void) {
    SqList L;  int op = 1;
   // InitList(L);
    DestroyList(L);
    while (op) {
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       7. LocateElem\n");
        printf("    	  2. DestroyList8. PriorElem\n");
        printf("    	  3. ClearList       9. NextElem \n");
        printf("    	  4. ListEmpty     10. ListInsert\n");
        printf("    	  5. ListLength     11. ListDelete\n");
        printf("    	  6. GetElem       12. ListTrabverse\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~12]:");
        scanf("%d", &op);
        switch (op) {
        case 1:

            if (InitList(L)==OK) printf("线性表创建成功！\n");
            else printf("线性表创建失败！\n");
            getchar(); getchar();
            break;
        case 2:
            if (DestroyList(L)) {
                printf("\n线性表销毁成功\n");
            }
            else {
                printf("\n线性表为不存在销毁失败\n");
            }
            getchar(); getchar();
            break;
        case 3:
            if (ClearList(L) == OK) {
                printf("\n线性表清空成功\n");
            }
            else {
                printf("\n线性表不存在,清空失败\n");
            }
            getchar(); getchar();
            break;
        case 4: {
            int temp1 = ListEmpty(L);
            if (temp1 == INFEASIBLE) {
                printf("线性表不存在\n");
            }
            else if (temp1 == TRUE) {
                printf("\n线性表为空表\n");
            }
            else {
                printf("\n线性表不为空表\n");
            }
            getchar(); getchar();
            break;
        }

        case 5:
        {
            int temp = ListLength(L);
            if (temp != INFEASIBLE) {
                printf("\n线性表的长度为%2d\n", temp);
            }
            else {
                printf("\n线性表不存在 \n");
            }

        }
        getchar(); getchar();
        break;
        case 6:
        {
            int e;
            int i;
            printf("请输入要寻找的元素的位置i");
            scanf("%d", &i);
            int n = GetElem(L, i, e);
            if (n == INFEASIBLE) {
                printf("线性表不存在!请先创建线性表!\n");
            }
            else if (n == ERROR) {
                printf("输入的位置i不在正确范围,请输入[1~%d]范围内的整数\n", L.length);
            }
            else {
                printf("第%d个元素是:%d\n", i, e);
            }

        }
        getchar(); getchar();
        break;
        case 7:
        {

            int e;
            int i;
            printf("请输入要寻找的元素的位置e");
            scanf("%d", &e);
            i = LocateElem(L, e);
            if (i == INFEASIBLE) {
                printf("线性表不存在\n");
            }
            else if (i == ERROR) {
                printf("线性表中不存在元素%d\n", e);
            }
            else {
                printf("线性表中第一次出现的元素%d在第%d个位置\n", e, i);
            }

        }
        getchar(); getchar();
        break;
        case 8:
        {
            int pre;
            int e;
            int i;
            printf("请输入元素e\n");
            scanf("%d", &e);
            i = PriorElem(L, e, pre);
            if (i == INFEASIBLE) {
                printf("线性表不存在\n");
            }
            else if (i == ERROR) {
                printf("未找到前驱\n");
            }
            else
            {
                printf("线性表中第一次出现的元素%d的前驱为%d\n", e, pre);
            }
        }
        getchar(); getchar();
        break;
        case 9:
        {
            int next;
            int e;
            printf("请输入元素e\n");
            scanf("%d", &e);
            int i = NextElem(L, e, next);
            if (i == INFEASIBLE) {
                printf("线性表不存在\n");
            }
            else if (i == ERROR) {
                printf("未找到后继\n");
            }
            else {
                printf("线性表中第一次出现的元素%d的后继为%d\n", e, next);
            }
        }
        getchar(); getchar();
        break;
        case 10:
        {
            int loc;
            int e;
            printf("请输入要元素的位置i\n");
            scanf("%d", &loc);
            printf("请输入元素e\n");
            scanf("%d", &e);
            int i = ListInsert(L, loc, e);
            if (i == INFEASIBLE) {
                printf("线性表不存在\n");
            }
            else if (i == ERROR) {
                printf("输入的i不合法,请输入[1~%d]的整数\n", L.length + 1);

            }
            else {
                printf("元素%d成功插入到线性表L的第%d个元素之前\n", e, loc);
            }
        }
        getchar(); getchar();
        break;
        case 11:
        {
            int loc;
            printf("请输入要删除元素的位置i");
            scanf("%d", &loc);
            int e;
            int i = ListDelete(L, loc, e);
            if (i == INFEASIBLE) {
                printf("线性表不存在!请先创建线性表!\n");
            }
            else if (i == ERROR) {
                printf("输入的位置i不在正确范围,请输入[1~%d]范围内的整数\n", L.length);
            }
            else {
                printf("第%d个元素%d已成功删除\n", loc, e);
            }
        }
        getchar(); getchar();
        break;
        case 12:
            if (!ListTrabverse(L)) printf("线性表是空表\n");
            else printf("\n线性表遍历成功\n");
            getchar(); getchar();
            break;
        case 0:
            break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
}//end of main()
/*--------page 23 on textbook --------------------*/
/*status InitList(SqList& L){
    L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
if(!L.elem) exit(OVERFLOW);
    L.length=0;
L.listsize=LIST_INIT_SIZE;
    return OK;
}
status ListTrabverse(SqList L){
int i;
printf("\n-----------all elements -----------------------\n");
for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
printf("\n------------------ end ------------------------\n");
returnL.length;
}*/

