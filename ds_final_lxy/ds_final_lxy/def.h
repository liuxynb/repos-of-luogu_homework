#pragma once
//����Ŀ���ݽṹ�����ڽӱ�
//dpll�㷨���������Ӿ�������
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
    int num;//���Ӿ�������Ԫ����
    struct clause* next;
    cNode* head;
}clause;//�ڽӱ��ͷ��㶨��