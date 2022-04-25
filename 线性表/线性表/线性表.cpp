#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1 
#define TRUE 1
#define FALSE 0

#define INIT_LIST_SIZE 100
#define LISTINCREMENT 10

typedef int Status;
typedef int ElemType;
typedef struct {
    ElemType* elem;
    int length;
    int listsize;
}SqList;
Status InitList(SqList* L)
{
    L->elem = (ElemType*)malloc(INIT_LIST_SIZE * sizeof(ElemType));
    if (!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = INIT_LIST_SIZE;
    return OK;
}

Status ListEmpty(SqList L)    //判空
{
    if (L.length = 0) return TRUE;
    else return FALSE;
}

Status ListInsert(SqList* L, int i, ElemType e)    //插入
{
    ElemType* newbase, * q, * p;
    if (i<1 || i>L->length + 1) return ERROR;
    if (L->length > L->listsize)
    {
        newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase) exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    q = L->elem + i - 1;    //q为插入位置
    for (p = L->elem + L->length - 1; p >= q; p--)
    {
        *(p + 1) = *p;
    }
    *q = e;
    ++L->length;
    return OK;
}

Status ListDelete(SqList* L, int i, ElemType* e)    //删除
{
    ElemType* p, * q;
    if (i<1 || i>L->length) return ERROR;
    p = L->elem + i - 1;    //p为被删除元素位置
    *e = *p;    //被删除元素的值赋值给e
    q = L->elem + L->length - 1;    //表尾元素位置
    for (++p; p <= q; ++p)
    {
        *(p - 1) = *p;
    }
    L->length--;
    return OK;
}

Status GetElem(SqList* L, int i, ElemType* e)    //取值
{
    if (i<1 || i>L->length) return ERROR;
    *e = *(L->elem + i - 1);    //获取第i个元素的地址
    return OK;
}

int LocateElem(SqList L, ElemType e)    //定位
{
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)
            return ++i;
    }
    if (i == L.length) return 0;
}

Status PriorElem(SqList L, ElemType e, ElemType& pre_e)    //求直接前驱
{
    int LocateElem(SqList L, ElemType e);
    int i = LocateElem(L, e);
    if ((i == 0) || (i == 1)) return ERROR;
    pre_e = L.elem[i - 2];
    return OK;
}

Status GetLength(SqList* L)    //求长度
{
    return L->length;
}

void PrnList(SqList* L)    //遍历
{
    int i;
    for (i = 0; i < (*L).length; i++)
    {
        if (i == 0)printf("(");
        printf(" %d ", L->elem[i]);
        if (i == (*L).length - 1)printf(")\n");
    }
}

Status ClearList(SqList* L)    //清空
{
    L->length = 0;
    return OK;
}

Status Destroy(SqList* L)    //销毁
{
    free(L->elem);
    L->elem = NULL;
    L->length = 0;
    L->listsize = 0;
    return OK;
}


int main()
{
    int n = 0, rc;
    int a, i;
    int e, e1;

    SqList L;
    if (InitList(&L)) printf("OK\n");

    FILE* fp = fopen("D:/1.txt", "r");
    if (fp == NULL)
    {
        printf("打开文件失败");
    }
    printf("从1.txt文件读入几个数：");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &a);
        ListInsert(&L, i + 1, a);
    }
    fclose(fp);
    PrnList(&L);

    char k;
    printf("\n1.插入\n2.删除\n3.取值\n4.定位\n5.直接前驱\n6.求长度\n7.遍历\n8.清空\n9.销毁\n");
    while (1) {
        k = getchar();
        switch (k) {
        case '1':
            printf("在第几个位置插入何数：");
            scanf("%d%d", &i, &e);
            if (ListInsert(&L, i, e))printf("i=%d,e=%d 已经插入\n", i, e);
            else printf("插入失败\n");
            break;
        case '2':
            printf("删除第几个数：\n");
            scanf("%d", &i);
            if (ListDelete(&L, i, &e))printf("i=%d,e=%d 已经删除\n", i, e);
            else printf("删除失败\n");
            break;
        case '3':
            printf("取第几个数：\n");
            scanf("%d", &i);
            if (GetElem(&L, i, &e))printf("第i=%d号,e=%d 被取出！\n", i, e);
            else printf("取值失败\n");
            break;
        case '4':
            printf("定位数字：");
            scanf("%d", &e);
            if (LocateElem(L, e) != 0) printf("OK,位序为：%d\n", LocateElem(L, e));
            else printf("ERROR\n");
            break;
        case '5':
            printf("寻找何数直接前驱:");
            scanf("%d", &e);
            if (PriorElem(L, e, e1)) printf("前驱为:%d\n", e1);
            else printf("ERROR\n");
            break;
        case '6':
            printf("表长为%d\n", GetLength(&L));
            break;
        case  '7':
            printf("遍历：\n");
            PrnList(&L);
            break;
        case '8':
            if (ClearList(&L)) printf("清空成功\n");
            else printf("清空失败\n");
            break;
        case '9':
            printf("销毁\n");
            Destroy(&L);
            printf("销毁成功\n");
            exit(0);
            return 0;
        }
    }
    return 0;
}
