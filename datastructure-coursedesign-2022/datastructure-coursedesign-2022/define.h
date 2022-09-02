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
typedef struct statement {      //�����Ӿ�
	int mark;                   //mark=0��ʾ�Ӿ���Ч,���������ʾɾ��ʱ�ĵݹ����
	int num;                    //����Ӿ������ֵĸ���
	struct node* next;          //ָ����һ������
	struct statement* nextst;   //ָ����һ������
}statement;
typedef struct node {           //��������
	int mark;                   //mark=0��ʾ������Ч,���������ʾɾ��ʱ�ĵݹ����
	int value;                  //��������С��0��ʾ���ھ����еĴ��з�
	struct node* next;          //��һ����
}node;
struct problem {                //����
	int vnum, stnum;            //��¼��������vnum���������stnum
	struct statement* root;     //root����в��������
	int count[MAX_VARNUM + 1];  //��¼ÿ���������ֵĴ���
	bool ans[MAX_VARNUM + 1];   //��¼��
};
typedef struct sudproblem {     //��������
	int original[10][10];       //��¼ԭʼ��ֵ
	int pattern[10][10];        //0��ʾ�ڳ��Ķ����������ͬori
	int num;                    //��0����
}sud;
typedef int status;
