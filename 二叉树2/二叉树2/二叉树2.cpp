//
//  main.cpp
//
//  Created by 刘兴元 on 2022/5/9.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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


typedef struct {
	int pos;
	TElemType data;
} DEF;
typedef struct {
	BiTNode* T;
	char name[20];
} BiTreep;
typedef struct {
	BiTreep Tp[10];
	int num;
	int Frorest_size;
} Forest;


BiTNode* NewNode(const TElemType& data)
{
	BiTNode* ptr = (BiTNode*)malloc(sizeof(BiTNode));
	if (!ptr) exit(OVERFLOW);
	ptr->data = data;
	ptr->lchild = nullptr;
	ptr->rchild = nullptr;
	return ptr;
}
status CreateBiTree(BiTree& T, const TElemType* definition)
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
	for (int i = 0; definition[i].key != -1; ++i)
		for (int j = i + 1; definition[j].key != -1; ++j)
			if (definition[i].key && definition[i].key == definition[j].key)
				return ERROR;
	if (definition->key == 0 || definition->key == -1)
		return OK;
	BiTNode* pnode = T = NewNode(*definition++);
	BiTNode* stack[256];
	int top = 0;
	while (definition->key != -1) {
		while (definition->key != 0) {
			stack[top++] = pnode;
			pnode = pnode->lchild = NewNode(*definition++);
			if (definition->key == -1) return OK;
		}
		definition++;
		if (definition->key != 0) {
			stack[top++] = pnode;
			pnode = pnode->rchild = NewNode(*definition++);
			if (definition->key == -1) return OK;
		}
		else {
			while (top && definition->key == 0) {
				pnode = stack[--top];
				if ((++definition)->key == -1) return OK;
			}
			if (definition->key == 0) return OK;
			pnode = pnode->rchild = NewNode(*definition++);
		}
	}
	return OK;
}
status DestroyBiTree(BiTree& T) //销毁⼆叉树
{
	if (T)
	{
		DestroyBiTree(T->lchild); //采⽤递归销毁
		DestroyBiTree(T->rchild);
		free(T); //释放空间
		T = NULL; //置空
	}
	return OK;
}
status ClearBiTree(BiTree& T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
	if (T == NULL) return INFEASIBLE;
	else
	{
		BiTNode* stack[255];
		int top = 0;
		stack[top++] = T;
		while (top)
		{
			BiTNode* toFree = stack[--top];
			if (toFree->rchild) stack[top++] = toFree->rchild;
			if (toFree->lchild) stack[top++] = toFree->lchild;
			free(toFree);
		}
	}
	T = NULL;
	return OK;
}
status BiTreeEmpty(BiTree T) {
	if (T == NULL) { //空⼆叉树
		return TRUE;
	}
	else { //⾮空
		return FALSE;
	}
}
int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
	int depth = 0;
	if (T == NULL) return 0;
	int depthleft = BiTreeDepth(T->lchild);
	int depthright = BiTreeDepth(T->rchild);
	depth = 1 + (depthleft > depthright ? depthleft : depthright);
	return depth;
}
BiTNode* LocateNode(BiTree T, KeyType e)
//查找结点
{
	if (T == NULL) return NULL;
	if (T->data.key == e) return T;
	BiTNode* ans = LocateNode(T->lchild, e);
	if (ans) return ans;
	return LocateNode(T->rchild, e);
}
status Assign(BiTree& T, KeyType e, TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
	if (e != value.key && LocateNode(T, value.key)) return ERROR;
	BiTNode* p = LocateNode(T, e);
	if (p == NULL) return ERROR;
	p->data = value;
	return OK;
}
BiTNode* GetSibling(BiTree T, KeyType e)
//实现获得兄弟结点
{
	BiTNode* stack[255];
	int top = 0;
	stack[top++] = T;
	while (top)
	{
		BiTNode* t = stack[--top];
		if (t->lchild != NULL && t->rchild != NULL)
		{
			if (t->lchild->data.key == e) return t->rchild;
			if (t->rchild->data.key == e) return t->lchild;
		}
		if (t->rchild != NULL) stack[top++] = t->rchild;
		if (t->lchild != NULL) stack[top++] = t->lchild;
	}
	return NULL;
}
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
	BiTNode* parent = LocateNode(T, e);
	if (!parent) return ERROR;
	if (LocateNode(T, c.key)) return ERROR;//待插入结点关键字有重复，无法插入结点.
	BiTNode* temp = (BiTNode*)malloc(sizeof(BiTNode));
	temp->data = c;//赋值
	temp->lchild = temp->rchild = NULL;
	if (LR == -1)
	{
		temp->rchild = T;
		T = temp;
		return OK;
	}
	else if (LR == 0)
	{
		temp->rchild = parent->lchild;
		parent->lchild = temp;
		return OK;
	}
	else if (LR == 1)
	{
		temp->rchild = parent->rchild;
		parent->rchild = temp;
		return OK;
	}

}
status DeleteNode(BiTree& T, KeyType e)
//删除结点。
{
	if (!T) return ERROR;
	if (T->data.key == e)
	{
		BiTNode* ToFree = T;
		if (T->lchild && T->rchild)
		{
			BiTNode* p = T->lchild;
			while (p->rchild)
				p = p->rchild;
			p->rchild = T->rchild;
			T = T->lchild;
		}
		else if (T->lchild) T = T->rchild;
		else if (T->rchild) T = T->rchild;
		else T = NULL;
		free(ToFree);
		return OK;
	}
	if (DeleteNode(T->lchild, e) == OK) return OK;
	if (DeleteNode(T->rchild, e) == OK) return OK;
	return ERROR;
}
void visit(BiTree T)
{
	printf(" %d,%s", T->data.key, T->data.others);
}
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
//先序遍历二叉树T
{
	if (!T) return ERROR;
	else
	{
		visit(T);
		PreOrderTraverse(T->lchild, visit);
		PreOrderTraverse(T->rchild, visit);
		return OK;
	}
}
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
//中序遍历二叉树T
{
	if (!T) return ERROR;
	else
	{
		InOrderTraverse(T->lchild, visit);
		visit(T);
		InOrderTraverse(T->rchild, visit);
		return OK;
	}
}
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
//后序遍历二叉树T
{
	if (!T) return ERROR;
	else
	{
		PostOrderTraverse(T->lchild, visit);
		PostOrderTraverse(T->rchild, visit);
		visit(T);
		return OK;
	}
}
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
//按层遍历二叉树T
{
	BiTNode* queue[255];
	int front = 0, tail = 0;
	queue[tail++] = T;
	while (front != tail)
	{
		BiTNode* t = queue[front++];//出队
		visit(t);
		if (t->lchild != NULL)//孩⼦⼊队
			queue[tail++] = t->lchild;
		if (t->rchild != NULL)//孩⼦⼊队
			queue[tail++] = t->rchild;
	}
	return OK;
}
status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
	FILE* fp = fopen(FileName, "w");
	if (fp == NULL) return INFEASIBLE;
	else
	{
		BiTNode* stack[255];
		int top = 0;
		stack[top++] = T;
		BiTNode* t = T;
		while (top)
		{
			t = stack[--top];
			if (t != NULL) fprintf(fp, "%d %s ", t->data.key, t->data.others); //不是空结点
			else fprintf(fp, "0 null ");
			if (t)//孩子结点入栈.
			{
				stack[top++] = t->rchild;
				stack[top++] = t->lchild;
			}
		}
		fprintf(fp, "-1, null");
		fclose(fp);
		return OK;
	}
}
status LoadBiTree(BiTree& T, char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
	int top = 0, i = 0;
	TElemType definition[500];
	FILE* fp = fopen(FileName, "r");
	if (fp == NULL) return INFEASIBLE;
	do
	{
		fscanf(fp, "%d%s", &definition[i].key, definition[i].others);
	} while (definition[i++].key != -1);
	CreateBiTree(T, definition);
	return OK;
}
/*
函数名称:InvertTree(BiTree & T)
初始条件:⼆叉树T存在
操作结果:翻转⼆叉树
*/
status InvertTree(BiTree& T) {
	if (T == NULL) {
		return INFEASIBLE;
	}
	else {
		BiTNode* St[100];
		int top = 0;
		St[top++] = T;
		BiTNode* t = T;
		while (top) {
			t = St[--top];
			if (t->rchild) {
				St[top++] = t->rchild;
			}
			if (t->lchild) {
				St[top++] = t->lchild;
			}
			if (t->rchild || t->lchild) {
				BiTNode* temp = t->rchild;
				t->rchild = t->lchild;
				t->lchild = temp;
			}
		}
		return OK;
	}
}
/*
函数名称:LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2)
初始条件:⼆叉树T存在
操作结果:找到关键字为e1，e2的最近公共祖先
*/
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2) {
	if (T == NULL) {
		return NULL;
	}
	if (T->data.key == e1 || T->data.key == e2) {
		return T; //找到关键字为e1，e2的结点
	}
	//如果没找到,往左右⼦树去找
	BiTNode* left = LowestCommonAncestor(T->lchild, e1, e2);
	BiTNode* right = LowestCommonAncestor(T->rchild, e1, e2);
	if (left == NULL && right == NULL) {
		return NULL; //左右都没找到,返回NULL
	}
	if (left && right) {
		return T; //左右都找到了，第⼀个返回
	}
	return left == NULL ? right : left; // 只找到⼀边
}
/*
函数名称:MaxPathSum(BiTree T)
初始条件:⼆叉树T存在
操作结果:查找根到叶⼦结点的最⼤路径和
*/
int MaxPathSum(BiTree T) {
	if (T == NULL) {
		return 0;
	}
	int left = MaxPathSum(T->lchild);
	int right = MaxPathSum(T->rchild);
	return left > right ? left + T->data.key : right + T->data.key;
}
/*
函数名称:AddBiTree(Forest & Forest,int k)
初始条件:森林Forest存在,插⼊数量合法
操作结果:在森林中插⼊k个树
*/
status AddBiTree(Forest& Forest, int k) {
	if (k + Forest.num >= Forest.Frorest_size) {
		return ERROR;
	}
	else {
		while (k--) {
			printf("请输入第%d个树的名字和带空结点的先序序列!\n", Forest.num + 1);
			scanf("%s", Forest.Tp[Forest.num].name);
			int i = 0;
			TElemType pre_definition[100];
			do {
				scanf("%d%s", &pre_definition[i].key, pre_definition[i].others);
			} while (pre_definition[i++].key != -1);
			Forest.Tp[Forest.num].T = NULL;
			CreateBiTree(Forest.Tp[Forest.num].T, pre_definition);
			Forest.num++;
		}
		return OK;
	}
}
/*
函数名称:RemoveTree(Forest &F,int loc)
初始条件:森林Forest存在,删除位置合法
操作结果:删除森林中第loc个树
*/
status RemoveTree(Forest& F, int loc) {
	if (F.Frorest_size == 0) {
		return INFEASIBLE;
	}
	else {
		if (loc<1 || loc>F.num) {
			return ERROR;
		}
		else {
			BiTNode* St[100];
			int top = 0;
			St[top++] = F.Tp[loc - 1].T;
			while (top) {
				BiTNode* t = St[--top];
				if (t->rchild) {
					St[top++] = t->rchild;
				}
				if (t->lchild) {
					St[top++] = t->lchild;
				}
				free(t);
			}
			F.Tp[loc - 1].T = NULL;
			for (int i = loc - 1; i < F.num - 1; i++) {
				F.Tp[i] = F.Tp[i + 1];
			}
		}
		F.num--;
	}
	return OK;
}
/*
函数名称:LocateTree(Forest F,char name[]){
初始条件:森林Forest存在
操作结果:查找森林F中名字为name的树的位置
*/
int LocateTree(Forest F, char name[]) {
	if (F.Frorest_size == 0) {
		return INFEASIBLE;
	}
	else {
		for (int i = 0; i < F.num; i++) {
			if (strcmp(F.Tp[i].name, name) == 0) {
				return i + 1;
			}
		}
	}
	return ERROR;
}
/*
函数名称:ForestPreTraverse(Forest F){
初始条件:森林Forest存在
操作结果:遍历森林的每⼀颗树，先序输出森林F的每⼀颗树
*/
status ForestPreTraverse(Forest F) {
	if (F.Frorest_size == 0) {
		return INFEASIBLE;
	}
	for (int i = 0; i < F.num; i++) {
		printf("%s ", F.Tp[i].name);
		BiTNode* St[100];
		int top = 0;
		St[top++] = F.Tp[i].T;
		while (top) {
			BiTNode* t = St[--top];
			printf("%d %s ", t->data.key, t->data.others);
			if (t->rchild) {
				St[top++] = t->rchild;
			}
			if (t->lchild) {
				St[top++] = t->lchild;
			}
		}
		printf("\n");
	}
	return OK;
}
/*
函数名称:ExchangeTree(Forest F, BiTree& T,char name[])
初始条件:森林Forest存在
*/
status ExchangeTree(Forest F, BiTree& T,char name[]) {
	if (F.Frorest_size == 0) {
		return INFEASIBLE;
	}
	int location;
	if ((location = LocateTree(F, name)) == 0)return ERROR;
	else
	{
		T = F.Tp[location].T;
	}
	return OK;
}
int main(void)
{
	int option = 1;
	BiTree T = NULL;
	Forest F;
	F.Frorest_size = 10;
	F.num = 0;
	char myfile[1000] = "123";
		while (option) {
			printf("\n\n");
			printf("      Menu for Binary Tree On List Structure \n");
			printf("-------------------------------------------------\n");
			printf("      1. CreateBiTree       2. DestroyBiTree\n");
			printf("      3. ClearBiTree        4. BiTreeEmpty \n");
			printf("      5. BiTreeDepth        6. LocateNode \n");
			printf("      7. Assign             8. GetSibling\n");
			printf("      9. InsertNode        10. DeleteNode\n");
			printf("     11. PreOrderTraverse  12. InOrderTraverse\n");
			printf("     13. PostOrderTraverse 14. LevelOrderTraverse\n");
			printf("     15. SaveBiTree        16. LoadBiTree\n");
			printf("     17. InvertTree        18. LowestCommonAnc\n");
			printf("     19. MaxPathSum        20. AddBiTree\n");
			printf("     21. RemoveBiTree      22. LocateBiTree\n");
			printf("     23. ForestPreTraverse 24. ExchangeTree\n");
			printf("          0. Exit\n");
			printf("-------------------------------------------------\n");
			printf("    请选择你的操作[0~23]:");
			scanf("%d", &option);
			switch (option) {
			case 1: {
				//创建二叉树
				printf("请入输入带空结点的先序遍历序列!\n");
				TElemType pre_definition[100];
				int i = 0;
				do
				{
					scanf("%d%s", &pre_definition[i].key, pre_definition[i].others);
				} while (pre_definition[i++].key != -1);
				status flag = CreateBiTree(T, pre_definition);
				if (flag == INFEASIBLE) {
					printf("创建失败,二叉树已存在!\n");
				}
				else if (flag == OK) {
					printf("创建成功!\n");
				}
				else {
					printf("创建失败,关键字不唯一!\n");
				}
				getchar(); getchar();
				break; }
			case 2: {
				//销毁二叉树
				if (DestroyBiTree(T) == OK) {
					printf("销毁成功!\n");
				}
				else {
					printf("销毁失败!\n");
				}
				getchar(); getchar();
				break;
			}
			case 3: {
				//清除二叉树
				if (ClearBiTree(T) == OK) {
					printf("清除成功!\n");
				}
				else {
					printf("清除失败!\n");
				}
				getchar();
				getchar();
				break;
			}
			case 4: {
				//判定空二叉树
				if (BiTreeEmpty(T) == TRUE) {
					printf("二叉树为空!\n");
				}
				else {
					printf("二叉树不为空!\n");
				}
				getchar();
				getchar();
				break;
			}
			case 5: {
				//求二叉树深度
				printf("二叉树的深度为%d!\n", BiTreeDepth(T));
				getchar();
				getchar();
				break; }
			case 6: {
				//查找结点
				KeyType e;
				printf("请输入需要查找的结点关键字!\n");
				scanf("%d", &e);
				BiTNode* flag = LocateNode(T, e);
				if (flag == NULL) {
					printf("查找失败,元素不在二叉树内!\n");
				}
				else {
					printf("查找成功,元素的名称为%s!\n", flag->data.others);
				}
				getchar(); getchar();
				break; }
			case 7: {
				//为结点赋值
				KeyType e;
				TElemType value;
				printf("请依次输入进行赋值操作的结点关键字和新结点元素值!\n");
				scanf("%d%d%s", &e, &value.key, value.others);
				status ans = Assign(T, e, value);
				if (ans == INFEASIBLE) {
					printf("空二叉树!\n");
				}
				else if (ans == OK) {
					printf("修改成功!\n");
				}
				else {
					printf("二叉树中不存在关键字为%d的结点!\n", e);
				}
				getchar(); getchar();
				break; }
			case 8: {
				//获取兄弟结点
				printf("请输入需要获取兄弟结点元素的关键字!\n");
				int e;
				scanf("%d", &e);
				BiTNode* ans = GetSibling(T, e);
				if (ans == NULL) {
					printf("查找失败!\n");
				}
				else {
					printf("关键字为%d的兄弟结点为%d,%s!\n", e, ans->data.key, ans->data.others);
				}
				getchar(); getchar();
				break; }
			case 9: {
				//插入结点
				printf("请输入插入位置结点的关键字!\n");
				int e;
				scanf("%d", &e);
				printf("请选择插入的位置,0 - 左,1 - 右,-1 - 根!\n");
				int LR;
				scanf("%d", &LR);
				printf("请输入插入新结点的关键字和名称!\n");
				TElemType value;
				scanf("%d%s", &value.key, value.others);
				status ans = InsertNode(T, e, LR, value);
				if (ans == ERROR) {
					printf("插入失败!\n");
				}
				else {
					printf("插入成功!\n");
				}
				getchar(); getchar();
				break; }
			case 10: {
				//删除结点
				printf("请输入删除位置结点的关键字!\n");
				int e;
				scanf("%d", &e);
				if (DeleteNode(T, e) == ERROR) {
					printf("删除失败,二叉树无该结点!\n");
				}
				else {
					printf("删除成功!\n");
				}
				getchar(); getchar();
				break; }
			case 11: {
				//前序遍历
				PreOrderTraverse(T, visit);
				printf("遍历成功!\n");
				getchar(); getchar();
				break;
			}
			case 12: {
				//中序遍历
				InOrderTraverse(T, visit);
				printf("遍历成功!\n");
				getchar(); getchar();
				break;
			}
			case 13: {
				//后序遍历
				PostOrderTraverse(T, visit);
				printf("遍历成功!\n");
				getchar(); getchar();
				break;
			}
			case 14: {
				//层序遍历
				LevelOrderTraverse(T, visit);
				printf("遍历成功!\n");
				getchar(); getchar();
				break;
			}
			case 15: {
				//保存在文件内
				if (SaveBiTree(T, myfile) == OK) {
					printf("保存成功!\n");
				}
				else {
					printf("保存失败!\n");
				}
				getchar(); getchar();
				break;
			}
			case 16: {
				//根据文件内容创建二叉树
				if (LoadBiTree(T, myfile) == OK) {
					printf("载入成功!\n");
				}
				else {
					printf("载入失败!\n");
				}
				getchar();
				getchar();
				break;
			}
			case 17: {
				//翻转二叉树
				status flag = InvertTree(T);
				if (flag == OK) {
					printf("翻转成功!\n");
				}
				else {
					printf("翻转失败!\n");
				}
				getchar(); getchar();
				break;
			}
			case 18: {
				//查找最近公共祖先
				printf("请输入需要查找的两个结点的关键字!\n");
				int e1, e2;
				scanf("%d%d", &e1, &e2);
				if (LocateNode(T, e1) != NULL && LocateNode(T, e2) != NULL) {
					BiTNode* Anc = LowestCommonAncestor(T, e1, e2);
					if (Anc == NULL) {
						printf("不存在公共祖先!\n");
					}
					else {
						printf("公共祖先关键字为%d,名称为%s!\n", Anc->data.key, Anc->data.others);
					}
				}
				else {
					printf("不存在公共祖先!\n");
				}
				getchar();
				getchar();
				break;
			}
			case 19: {
				//查找最大路径
				int length = MaxPathSum(T);
				printf("最大路径和为%d!\n", length);
				getchar();
				getchar();
				break;
			}
			case 20: {
				printf("请输入需要添加的二叉树个数!\n");
				int k;
				scanf("%d", &k);
				if (AddBiTree(F, k) == ERROR) {
					printf("添加失败!\n");
				}
				else {
					printf("添加成功!\n");
				}
				getchar(); getchar();
				break;
			}
			case 21: {
				//删除树
				printf("请输入需要删除的树的位置!\n");
				int loc;
				scanf("%d", &loc);
				if (RemoveTree(F, loc) == ERROR) {
					printf("删除位置不合法!\n");
				}
				else {
					printf("删除成功!\n");
				}
				getchar();
				getchar();
				break;
			}
			case 22: {
				//查找树
				printf("请输入需要查找的树的名称!\n");
				char name[20];
				scanf("%s", name);
				int loc = LocateTree(F, name);
				if (loc == ERROR) {
					printf("查找失败,森林中不存在该树!\n");
				}
				else {
					printf("该树在森林中的位置为%d!\n", loc);
				}
				getchar();
				getchar();
				break; }
			case 23:{
				if (ForestPreTraverse(F) == OK) {
					printf("遍历成功!\n");
				}
				getchar();
				getchar();
				break;
			}
			case 24: {
				//切换树
				printf("请输入需要切换的树的名称!\n");
				char name[20];
				scanf("%s", name);
				int loc = ExchangeTree(F, T,name);
				if (loc == ERROR) {
					printf("切换失败,森林中不存在该树!\n");
				}
				else {
					printf("切换成功\n");
				}
				getchar();
				getchar();
				break; }
			case 0:
				printf("欢迎下次在使用本系统!\n");
				break;
			default:
				printf("It is not a command!Please input another!\n");
				getchar();
				getchar();
				break;
		}
}
}


