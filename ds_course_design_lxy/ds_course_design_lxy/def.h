#pragma once
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define MAX_STNUM 20000
#define MAX_VARNUM 2000
#define ERROR 0
#define OK 1
typedef struct statement {      //保存子句
	int mark;                   //mark=0表示子句有效,其他情况表示删除时的递归深度
	int num;                    //标记子句中文字的个数
	struct node* firstNode;          //指向下一个文字
	struct statement* nextSt;   //指向下一个句子
}statement;
typedef struct node {           //保存文字
	int mark;                   //mark=0表示变量有效,其他情况表示删除时的递归深度
	int value;                  //文字名，小于0表示其在句子中的带有非
	struct node* nextNode;          //下一变量
}node;
struct problem {                //问题
	int vnum, stnum;            //记录变量数量vnum、语句数量stnum
	struct statement* root;     //root结点中不存放数据
	int count[MAX_VARNUM + 1];  //记录每个变量出现的次数
	bool ans[MAX_VARNUM + 1];   //记录答案
};
typedef struct sudproblem {     //数独问题
	int original[10][10];       //记录原始数值
	int pattern[10][10];        //0表示挖出的洞，其他情况同ori
	int num;                    //非0个数
}Sud;
typedef struct double_sud
{
	Sud* k1;
	Sud* k2;
}DSud;                          //储存双数独

typedef int status;
