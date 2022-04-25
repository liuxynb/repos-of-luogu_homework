#include "stdio.h"
#include "stdlib.h"
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode {  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;
typedef struct {  //线性表的集合类型定义  
    struct {
        char name[30];
        LinkList L;
    } elem[10];
    int length;
}LISTS;
LISTS Lists;      //线性表集合的定义Lists
status InitList(LinkList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if (L) return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    L->data = 0;
    L->next = NULL;
    return OK;
}
status DestroyList(LinkList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    LinkList p, q;
    p = L;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    L = NULL;
    return OK;
}
status ClearList(LinkList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    LinkList p, q;
    p = L->next;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    L->next = NULL;
    return OK;
}
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    if (L->next) return FALSE;
    return TRUE;
}
int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    int Length = 0;
    LinkList p = L->next;
    while (p)
    {
        p = p->next;
        Length++;
    }
    return Length;
}
status GetElem(LinkList L, int i, ElemType& e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    if (i < 1) return ERROR;
    int j = 0;
    LinkList p = L->next;
    while (p)
    {
        j++;
        if (j == i)
        {
            e = p->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}
status LocateElem(LinkList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    int j = 0;
    LinkList p = L->next;
    while (p)
    {
        j++;
        if (e == p->data)
        {
            return j;
        }
        p = p->next;
    }
    return ERROR;
}
status PriorElem(LinkList L, ElemType e, ElemType& pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    LinkList p = L->next;
    if (L->next == NULL) return ERROR;
    while (p->next && p->next->data != e)
        p = p->next;

    if (p->next == NULL) return ERROR;
    pre = p->data;
    return OK;
}
status NextElem(LinkList L, ElemType e, ElemType& next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    if (L->next == NULL) return ERROR;
    LinkList p = L->next;
    while (p->next && p->data != e)
        p = p->next;
    if (p->next == NULL) return ERROR;
    next = p->next->data;
    return OK;
}
status ListInsert(LinkList& L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    //if(i<1) return ERROR;
    LinkList p = L;
    int j = 1;
    while (j < i && p)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i) return ERROR;
    LinkList q = (LinkList)malloc(sizeof(LNode));
    if (!q) exit(OVERFLOW);
    q->data = e;
    q->next = p->next;
    p->next = q;
    return OK;
}
status ListDelete(LinkList& L, int i, ElemType& e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    LinkList p = L;
    int j = 1;
    while (j < i && p)
    {
        p = p->next;
        j++;
    }
    if (!p->next || j > i) return ERROR;
    LinkList q = p->next;
    p->next = p->next->next;
    e = q->data;
    free(q);
    return OK;
}
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    LinkList p = L->next;
    while (p)
    {
        printf("%d", p->data);
        if (p->next) putchar(' ');
        p = p->next;
    }

    return OK;
}
status SaveList(LinkList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if (L == NULL) return INFEASIBLE;
    FILE* fp = fopen(FileName, "w");
    if (fp == NULL)
        printf("失败");
    LinkList p = L->next;
    while (p)
    {
        fprintf(fp, "%d ", p->data);
        p = p->next;
    }
    fclose(fp);
    return OK;
}
status LoadList(LinkList& L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    if (L) return INFEASIBLE;
    FILE* fp = fopen(FileName, "r");
    if (fp == NULL) return ERROR;
    L = (LinkList)malloc(sizeof(LNode));
    L->data = 0;
    L->next = NULL;
    LinkList p = L;
    int num;
    while (fscanf(fp, "%d", &num) != EOF)
    {
        if (!num) break;
        LinkList q = (LinkList)malloc(sizeof(LNode));
        q->data = num;
        p->next = q;
        p = q;
        p->next = NULL;
    }
    fclose(fp);
    return OK;
}
status reverseList(LinkList& L)
//初始条件是线性表L已存在；操作结果是将L翻转.
{
    LNode* p1, * p2, * p3;
    if (L == NULL || L->next == NULL)
    {
        return INFEASIBLE;
    }
    p1 = L;
    p2 = p1->next;
    p3 = p2->next;
    while (NULL != p3)
    {
        p2->next = p1;
        p1 = p2;
        p2 = p3;
        p3 = p3->next;
    }
    p2->next = p1;
    L->next->next = NULL;
    L->next = p2;
    return OK;
}
void sortList(LinkList &L)
//操作结果是将L由小到大排序。
{
    LNode* p;
    int i, j, listLen, swaped = 1;
    ElemType temp;
    if (L == NULL || (L)->next == NULL)
    {
        return;
    }
    listLen = ListLength(L);
    p = L;
    for (i = 1; i < listLen; i++)
    {
        swaped = 0;
        p = L;
        for (j = 0; j < listLen - i; j++)
        {
            if (p->data > p->next->data)
            {
                temp = p->data;
                p->data = p->next->data;
                p->next->data = temp;
                swaped = 1;
            }
            p = p->next;
        }
        if (swaped == 0) break;
    }

}
status RemoveNthFromEnd(LinkList& L, int n)
//删除链表的倒数第n个结点：函数名称是RemoveNthFromEnd(L,n); 初始条件是线性表L已存在且非空, 操作结果是该链表中倒数第n个节点；
{
    if (L == NULL||L->next == NULL) return INFEASIBLE;
    LinkList end_node = L->next, delete_node = L->next, pre = NULL, next = L->next->next;
    for (int i = 0; i < n - 1; i++)
        end_node = end_node->next;
    while (end_node->next)
    {
        end_node = end_node->next;
        delete_node = delete_node->next;
        if (pre) pre = pre->next;
        else pre = L->next;
        next = next->next;
    }
    if (delete_node == L->next)
        L->next = L->next->next;
    else pre->next = next;
    free(delete_node);
    return OK;
}

status AddList(LISTS& Lists, char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{    
    if (!InitList(Lists.elem[Lists.length].L))
        exit(ERROR);   
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.length++;
    return OK;
}
status RemoveList(LISTS& Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    for (int i = 0; i < Lists.length; i++)
    {
        if (!strcmp(ListName, Lists.elem[i].name))
        {
            for (int j = i; j < Lists.length; j++)
                Lists.elem[j] = Lists.elem[j + 1];
            return OK;
        }
    }
    return ERROR;
}
int LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    for (int i = 0; i < Lists.length; i++)
    {
        int flag = 1;
        for (int j = 0; ListName[j]; j++)
        {
            if (Lists.elem[i].name[j] != ListName[j])
            {
                flag = 0;
                break;
            }
        }
        if (flag) return i + 1;
    }
    return 0;
}
void main(void) {
    LinkList L;  int op = 1;
    L = NULL;
    while (op) {
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Single-linked List Structure       \n");
        printf("--------------------------------------------------------\n");
        printf("    	  1. InitList           7. LocateElem\n");
        printf("    	  2. DestroyList        8. PriorElem\n");
        printf("    	  3. ClearList          9. NextElem \n");
        printf("    	  4. ListEmpty          10. ListInsert\n");
        printf("    	  5. ListLength         11. ListDelete\n");
        printf("    	  6. GetElem            12. ListTrabverse\n\n");
        printf("          EXTRA(Additional features)\n\n");
        printf("    	  13.reverseList        16. SaveList\n");
        printf("    	  14. RemoveNthFromEnd       17. List Control\n");
        printf("    	  15. sortList  \n");
        printf("          0.Exit              \n");
        printf("--------------------------------------------------------\n");
        printf("Please select what feature you need to use(just choose ONE)[0~17]:");
        scanf("%d", &op);
        int i, num, ret, e;
        char ListName1[100];
        switch (op) {
        case 1:
            //printf("\n----IntiList功能待实现！\n");
            if (InitList(L) == OK) printf("线性表创建成功！\n");
            else printf("线性表创建失败！\n");
            getchar(); getchar();
            break;
        case 2:
            if (DestroyList(L) == OK) printf("线性表销毁成功！\n");
            else printf("线性表销毁失败！\n");
            getchar(); getchar();
            break;
        case 3:
            if (ClearList(L) == OK) printf("线性表清空成功！\n");
            else printf("线性表清空失败！\n");
            getchar(); getchar();
            break;
        case 4:
            if (ListEmpty(L) == OK) printf("线性表为空！\n");
            else if (ListEmpty(L) == FALSE) printf("线性表不为空！\n");
            else printf("线性表不存在！\n");
            getchar(); getchar();
            break;
        case 5:
            int Len;
            if ((Len = ListLength(L)) != (-1))
                printf("线性表长度为%d", Len);
            else printf("线性表不存在");
            getchar(); getchar();
            break;
        case 6:
            printf("输入要获取第i个元素的位置i\n");
            int get_num;
            scanf("%d", &i);
            ret = GetElem(L, i, get_num);
            if (ret == 0) printf("i不合法。\n");
            else if (ret == -1)printf("线性表不存在。\n");
            else printf("第%d个元素为%d\n", i, get_num);
            getchar(); getchar();
            break;
        case 7:
            //printf("\n----LocateElem功能待实现！\n");
            scanf("%d", &num);
            ret = LocateElem(L, num);
            if (ret == 0) printf("这样的数据不存在。\n");
            else if (ret == -1)printf("线性表不存在。\n");
            else printf("%d的位置为%d\n", num, ret);
            getchar(); getchar();
            break;
        case 8:
            //printf("\n----PriorElem功能待实现！\n");
            int pre;
            scanf("%d", &num);
            ret = PriorElem(L, num, pre);
            if (ret == 0) printf("没有前驱。\n");
            else if (ret == -1)printf("线性表不存在。\n");
            else printf("%d的前驱为%d\n", num, pre);
            getchar(); getchar();
            break;
        case 9:
            //printf("\n----NextElem功能待实现！\n");
            int next;
            scanf("%d", &num);
            ret = NextElem(L, num, next);
            if (ret == 0) printf("插入失败。\n");
            else if (ret == -1)printf("线性表不存在。\n");
            else printf("%d的后继为%d\n", num, next);
            getchar(); getchar();
            break;
        case 10:
            //printf("\n----ListInsert功能待实现！\n");
            printf("需要将元素e插入到线性表L的第i个元素之前(输入e，i)。\n");
            scanf("%d %d", &e, &i);
            ret = ListInsert(L, i, e);
            if (ret == 0) printf("插入失败。\n");
            else if (ret == -1)printf("线性表不存在。\n");
            else printf("插入成功\n");
            getchar(); getchar();
            break;
        case 11:
            //printf("\n----ListDelete功能待实现！\n");
            printf("需要删除第i个元素？(输入i)。\n");
            scanf("%d", &i);
            ret = ListDelete(L, i, e);
            if (ret == 0) printf("删除位置不正确。\n");
            else if (ret == -1)printf("线性表不存在。\n");
            else printf("删除成功，删除的元素值为%d\n", e);
            getchar(); getchar();
            break;
        case 12:
            //printf("\n----ListTrabverse功能待实现！\n");     
            if (!ListTraverse(L)) printf("线性表是空表！\n");
            getchar(); getchar();
            break;
        case 13:
            //链表翻转：
            if (!reverseList(L)) printf("线性表是空表！\n");
            else printf("翻转成功！\n");           
            getchar(); getchar();
            break;
        case 14:
            //删除链表的倒数第n个结点
            printf("请输入需要删除倒数第几个节点：");
            int n;
            scanf("%d", &n);
            ret = RemoveNthFromEnd(L, n);
            if (ret == 0 || ret == -1) printf("ERROR!\n");
            else printf("删除成功！\n", ret);
            getchar(); getchar();
            break;
        case 15:
            //单链表排序
            if (L == NULL || L->next == NULL)printf("线性表不存在或为空。\n");
            else
            {
                sortList(L);
                printf("排序成功！\n");
            }
            getchar(); getchar();
            break;
        case 16:
            //实现线性表的文件形式保存
            printf("输入需要存入的文件名");
            char filename1[100];
            scanf("%s", filename1);
            ret = SaveList(L, filename1);
            if (ret == (-1)) printf("ERROR!");
            else printf("保存成功");
            getchar(); getchar();
            break;
        case 17://实现多个线性表管理
            int input;
            do
            {

                printf("      Menu for Linear Table On Sequence Structure    \n");
                printf("-------------------------------------------------\n");
                printf("    	  1. AddList      \n");
                printf("    	  2. RemoveList       \n");
                printf("    	  3. LocateList       \n");
                printf("    	  0. Exit       \n");
                printf("-------------------------------------------------\n");
                printf("    请选择你的操作[0~3]:");
                scanf("%d", &input);
                switch (input)
                {
                case 1:

                    printf("输入新线性表的名字");
                    scanf("%s", ListName1);
                    ret = AddList(Lists, ListName1);
                    if (ret) printf("添加成功");
                    else printf("添加失败");
                    getchar(); getchar();
                    break;
                case 2:
                    printf("输入需要删除的线性表的名字");
                    scanf("%s", ListName1);
                    ret = RemoveList(Lists, ListName1);
                    if (ret) printf("删除成功");
                    else printf("删除失败");
                    getchar(); getchar();
                    break;
                case 3:
                    printf("输入需要查找的线性表的名字");
                    scanf("%s", ListName1);
                    ret = LocateList(Lists, ListName1);
                    if (!ret) printf("查找失败");
                    else printf("成功，序号为%d", ret);
                    getchar(); getchar();
                    break;
                case 0:
                    break;
                }
            } while (input);


        case 0:
            break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
}//end of main()
