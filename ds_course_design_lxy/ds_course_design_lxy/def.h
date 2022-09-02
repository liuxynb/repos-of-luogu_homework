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
	struct node* firstNode;          //ָ����һ������
	struct statement* nextSt;   //ָ����һ������
}statement;
typedef struct node {           //��������
	int mark;                   //mark=0��ʾ������Ч,���������ʾɾ��ʱ�ĵݹ����
	int value;                  //��������С��0��ʾ���ھ����еĴ��з�
	struct node* nextNode;          //��һ����
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
}Sud;
typedef struct double_sud
{
	Sud* k1;
	Sud* k2;
}DSud;                          //����˫����

typedef int status;
