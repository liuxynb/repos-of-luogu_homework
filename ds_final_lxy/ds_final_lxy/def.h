#pragma once
//本项目数据结构采用邻接表
//dpll算法采用文字子句消隐法
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define status int
#define OK 1
#define INFEASIBLE -1

typedef struct cNode {
    int data;
    struct cNode* next;
}cNode;//
typedef struct clause {
    int num;//该子句所含变元个数
    struct clause* next;
    cNode* head;
}clause;//邻接表表头结点定义