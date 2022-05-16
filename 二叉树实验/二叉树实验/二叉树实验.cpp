#include "stdio.h"
#include "stdlib.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct {
    KeyType  key;
    char others[20];
} TElemType; //二叉树结点类型定义


typedef struct BiTNode {  //二叉链表结点的定义
    TElemType  data;
    struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

BiTNode* NewNode(const TElemType& data)
{
    BiTNode* ptr = (BiTNode*)malloc(sizeof(BiTNode));
    ptr->data = data;
    ptr->lchild = nullptr;
    ptr->rchild = nullptr;
    return ptr;
}
status CreateBiTree(BiTree& T, TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    for (int i = 0; definition[i].key != -1; i++)
        for (int j = i + 1; definition[j].key != -1; j++)
            if (definition[i].key && definition[i].key == definition[j].key) return ERROR;
    if (definition->key <= 0) return OK;
    BiTNode* tree = NewNode(*definition++);
    BiTNode* pnode;
    pnode = tree;
    BiTNode* stack[255];
    int top = 0;
    while (definition->key != -1)
    {
        while (definition->key != 0)
        {
            stack[top++] = pnode;
            pnode = pnode->lchild = NewNode(*definition++);
            if (definition->key == -1) return OK;
        }
        definition++;
        if (definition->key != 0)
        {
            stack[top++] = pnode;
            pnode = pnode->rchild = NewNode(*definition++);
            if (definition->key == -1)return OK;
        }
        else
        {
            while (top && definition->key == 0)
            {
                pnode = stack[--top];
                if (++definition->key == -1) return OK;
            }
            if (definition->key == 0) return OK;
            pnode = pnode->rchild = NewNode(*definition++);
        }
    }
    return OK;
}
