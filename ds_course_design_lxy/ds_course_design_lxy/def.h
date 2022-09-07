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
typedef struct clause 
{                                //�����Ӿ�
	int mark;                   //mark=0��ʾ�Ӿ���Ч,���������ʾɾ��ʱ�ĵݹ����
	int num;                    //����Ӿ������ֵĸ���
	struct cNode* head;          //ָ����һ������
	struct clause* next;   //ָ����һ������
}clause;
typedef struct cNode 
{                             //��������
	int mark;                   //mark=0��ʾ������Ч,���������ʾɾ��ʱ�ĵݹ����
	int data;                  //��������С��0��ʾ���ھ����еĴ��з�
	struct cNode* next;          //��һ����
}node;

typedef struct SudProblem 
{								//��������
	int original[10][10];       //��¼ԭʼ��ֵ
	int answer[10][10];        //0��ʾ�ڳ��Ķ����������ͬori
	int num;                    //��0����
}Sud;
typedef struct double_sud
{
	Sud* k1;
	Sud* k2;
}DSud;                             //����˫����
struct SAT {                                           //����
	int vnum, stnum;                   //��¼��������vnum���������stnum
	struct clause* root;               //root����в��������
	int count[MAX_VARNUM + 1];            //��¼ÿ���������ֵĴ���
	bool ans[MAX_VARNUM + 1];               //��¼��
};
typedef int status;
