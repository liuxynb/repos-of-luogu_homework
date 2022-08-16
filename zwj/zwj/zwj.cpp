#include "stdio.h"
#include "stdlib.h"
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef int QElemType;
typedef int ElemType;
typedef struct {
	KeyType  key;
	char others[20];
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
	int adjvex;              //顶点位置编号 
	struct ArcNode* nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode {				//头结点及其数组类型定义
	VertexType data;       	//顶点信息
	ArcNode* firstarc;      	 //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
	AdjList vertices;     	 //头结点数组
	int vexnum, arcnum;   	  //顶点数、弧数
	GraphKind  kind;        //图的类型
} ALGraph;
typedef struct GraphQueue {
	VertexType data[20];
	int top, tail;
}GraphQueue;

status CreateCraph(ALGraph& G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph& G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph& G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph& G, VertexType v);
status DeleteVex(ALGraph& G, KeyType v);
status InsertArc(ALGraph& G, KeyType v, KeyType w);
status DeleteArc(ALGraph& G, KeyType v, KeyType w);
void DFS(ALGraph G, int v);
status DFSTraverse(ALGraph& G, void (*visit)(VertexType));
status BFSTraverse(ALGraph& G, void (*visit)(VertexType));
status CreateCraphf(ALGraph& G, VertexType V[], KeyType VR[][2]);
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph& G, char FileName[]);
void visit(VertexType v);
int LocateGraph(ALGraph G[], char name[]);
status RemoveGraph(ALGraph* L, char name[]);

char GraphName[10][20];
int visited[MAX_VERTEX_NUM];
void (*VisitFunc)(VertexType);
int main()
{
	int op = 1, i, i_num = 0, key;
	VertexType e, v, g, va, vb; //无向图中的节点
	KeyType m;
	i = 0;
	char FileName[20];
	char graphname[20];
	ALGraph G[10]; //十个图
	for (i = 0; i < 10; i++)
	{
		G[i].arcnum = 0;
		G[i].vexnum = 0;
		G[i].kind = DG;
		GraphName[i][0] = '\0';
		int j = 0;
		for (j = 0; j < MAX_VERTEX_NUM; j++)
		{
			G[i].vertices[j].data.key = -1;
			G[i].vertices[j].data.others[0] = '\0';
			G[i].vertices[j].firstarc = NULL;
		}
	}
	ALGraph G0;
	VertexType V[30];
	for (i = 0; i < 30; i++)
	{
		V[i].key = -1;
		V[i].others[0] = '\0';
	}
	KeyType VR[100][2];
	for (i = 0; i < 100; i++)
	{
		VR[i][0] = -1;
		VR[i][1] = -1;
	}
	while (op)
	{
		system("cls"); //用于清屏
		printf("\n\n");
		printf("\t\t      Menu for Undirected Graph On Chain Structure \n");
		printf("\t******************************************************************************\n");
		printf("\t\t\t1.  CreateGraph \t 2.  DestroyGraph\n");
		printf("\t\t\t3.  LocateVex   \t 4.  GetVex\n");
		printf("\t\t\t5.  PutVex      \t 6.  FirstAdjVex\n");
		printf("\t\t\t7.  NextAdjVex  \t 8.  InsertVex\n");
		printf("\t\t\t9.  DeleteVex   \t 10. InsertArc\n");
		printf("\t\t\t11. DeleteArc   \t 12. DFSTraverse\n");
		printf("\t\t\t13. BFSTraverse \t 14. SaveFile\n");
		printf("\t\t\t15. LoadFile	  \t 16. ChooseMult\n");
		printf("\t\t\t17. DeleteMult  \t 18. LocateMult\n");
		printf("\t\t\t0.  Exit        \t \n");
		printf("\t******************************************************************************\n");
		printf("\t\t\t请选择你的操作[0-18]: ");
		scanf("%d", &op);
		switch (op)
		{

		case 1:
			i = 0;
			printf("\t\t\t请按格式输入数据\n");
			do
			{
				scanf("%d%s", &V[i].key, V[i].others);
			} while (V[i++].key != -1);
			i = 0;
			do
			{
				scanf("%d%d", &VR[i][0], &VR[i][1]);
			} while (VR[i++][0] != -1);
			if (CreateCraph(G[i_num], V, VR) == OK)
			{
				printf("\t\t\t输入名称\n");
				scanf("%s", GraphName[i_num]);
				printf("\t\t\t创建无向图成功!\n");
			}
			else
				printf("\t\t\t创建无向图失败!\n");
			getchar();
			getchar();
			break;

		case 2:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			if (DestroyGraph(G[i_num]) == OK)
				printf("\t\t\t销毁无向图成功!\n");
			else
				printf("\t\t\t销毁无向图失败!\n");
			getchar();
			getchar();
			break;

		case 3:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入所要查找的顶点的关键字：");
			scanf("%d", &m);
			if (LocateVex(G[i_num], m) == -1)
				printf("\t\t\t无向图中不存在该节点!\n");
			else
				printf("\t\t\t该顶点的序号位置为%d\n", LocateVex(G[i_num], m));
			getchar();
			getchar();
			break;

		case 4:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入所要查找的顶点的序号：");
			scanf("%d", &m);
			if (m >= G[i_num].vexnum || m < 0)
				printf("\t\t\t序号错误!\n");
			else
			{
				printf("\t\t\t所输入的序号对应的顶点key值为：%d\n", G->vertices[m].data.key);
			}
			getchar();
			getchar();
			break;

		case 5:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要查找的顶点的key值: ");
			scanf("%d", &m);
			if (LocateVex(G[i_num], m) == -1)
				printf("\t\t\t该顶点不存在!\n");
			else
			{
				printf("\t\t\t请输入要将该点修改为的key值: ");
				scanf("%d", &e.key);
				printf("\t\t\t请输入要将该点修改为的值: ");
				scanf("%s", e.others);
				if (PutVex(G[i_num], m, e) == ERROR)
					printf("\t\t\t赋值失败！\n");
				else
					printf("\t\t\t赋值成功！\n");
			}
			getchar();
			getchar();
			break;

		case 6:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要查找的顶点的key：");
			scanf("%d", &key);
			if (LocateVex(G[i_num], key) == -1)
				printf("\t\t\t该顶点不存在!\n");
			else
			{
				if (FirstAdjVex(G[i_num], key) == -1)
					printf("\t\t\t该顶点没有邻接顶点!\n");
				else
					printf("\t\t\t该顶点首个邻接顶点的位序为%d\n", FirstAdjVex(G[i_num], key));
			}
			getchar();
			getchar();
			break;

		case 7:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要查找的顶点的key：");
			scanf("%d", &key);
			if (LocateVex(G[i_num], key) == -1)
				printf("\t\t\t该顶点不存在!\n");
			else
			{
				printf("\t\t\t请输入和其相对的顶点的key：");
				scanf("%d", &m);
				if (LocateVex(G[i_num], m) == -1)
					printf("\t\t\t不存在该key %d的顶点！", i);
				else
				{
					if (NextAdjVex(G[i_num], key, m) == -1)
						printf("\t\t\t查找失败!\n");
					else
						printf("\t\t\tv相对于w的下一个邻接顶点的位序为 %d\n", NextAdjVex(G[i_num], key, m));
				}
			}
			getchar();
			getchar();
			break;

		case 8:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要添加的顶点的key: ");
			scanf("%d", &v.key);
			if (LocateVex(G[i_num], v.key) != -1)
				printf("\t\t\t该顶点已存在,添加失败!\n");
			else
			{
				printf("\t\t\t请输入该顶点的data值：");
				scanf("%s", v.others);
				if (InsertVex(G[i_num], v) == OK)
					printf("\t\t\t添加顶点成功!\n");
				else
					printf("\t\t\t添加顶点失败!\n");
			}
			getchar();
			getchar();
			break;

		case 9:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要删除的顶点的key: ");
			scanf("%d", &key);
			if (LocateVex(G[i_num], key) == -1)
				printf("\t\t\t该顶点不存在!\n");
			if (DeleteVex(G[i_num], key) == ERROR)
				printf("\t\t\t删除失败!\n");
			else
				printf("\t\t\t删除顶点成功!\n");
			getchar();
			getchar();
			break;

		case 10:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入边的第一个节点的key值:");
			scanf("%d", &key);
			printf("\t\t\t请输入边的第二个节点的key值:");
			scanf("%d", &m);
			if (InsertArc(G[i_num], key, m) == ERROR)
				printf("\t\t\t添加失败!\n");
			else
				printf("\t\t\t添加成功!\n");
			getchar();
			getchar();
			break;

		case 11:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入边的第一个节点的key值:");
			scanf("%d", &key);
			printf("\t\t\t请输入边的第二个节点的key值:");
			scanf("%d", &m);
			if (DeleteArc(G[i_num], key, m) == ERROR)
				printf("\t\t\t删除失败!\n");
			else
				printf("\t\t\t删除成功!\n");
			getchar();
			getchar();
			break;

		case 12:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t该无向图的深度优先搜索遍历为：");
			DFSTraverse(G[i_num], visit);
			printf("\n");
			getchar();
			getchar();
			break;

		case 13:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t该无向图的广度优先搜索遍历为：");
			BFSTraverse(G[i_num], visit);
			printf("\n");
			getchar();
			getchar();
			break;

		case 14:
			if (G[i_num].vexnum == 0)
			{
				printf("\t\t\t无向图不存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要写入的文件名\n");
			scanf("%s", FileName);
			if (SaveGraph(G[i_num], FileName) == OK)
				printf("\t\t\t文件保存成功!\n");
			else
				printf("\t\t\t文件保存失败!\n");
			getchar();
			getchar();
			break;

		case 15:
			if (G[i_num].vexnum != 0)
			{
				printf("\t\t\t无向图已存在!\n");
				getchar();
				getchar();
				break;
			}
			printf("\t\t\t请输入要读取的文件名\n");
			scanf("%s", FileName);
			if (LoadGraph(G[i_num], FileName) == OK)
				printf("\t\t\t加载成功!\n");
			else
				printf("\t\t\t加载失败!\n");
			getchar();
			getchar();
			break;

		case 16:
			printf("\t\t请输入要在第几个表操作,只支持在10个顺序表进行操作: ");
			scanf("%d", &i_num);
			if (i_num < 0 || i_num > 19)
			{
				printf("\t\t\t不支持在该表上进行操作!\n");
				i_num = 0;
			}
			getchar(); getchar();
			break;

		case 17:
			printf("\t\t\t请输入需要删除的图的名字:");
			scanf("%s", graphname);
			RemoveGraph(G, graphname);
			printf("\t\t\t删除成功！\n");
			getchar(); getchar();
			break;

		case 18:
			printf("\t\t\t请输入需要查找的图的名字:");
			scanf("%s", graphname);
			m = LocateGraph(G, graphname);
			printf("\t\t\t所找到的图的位序为:%d\n", m);
			getchar(); getchar();
			break;

		case 19:
			for (int l = 0; l < G[i_num].vexnum; ++l)
			{
				printf("\n %d %s |", G[i_num].vertices[l].data.key, G[i_num].vertices[l].data.others);
				for (ArcNode* m = G[i_num].vertices[l].firstarc; m; m = m->nextarc)
				{
					printf(" %d", m->adjvex);
				}
			}
			printf("\n 总点数和边数： %d %d", G[i_num].vexnum, G[i_num].arcnum);
			getchar();
			getchar();
			break;

		case 0:
			break;
		}//end of switch
	}//end of while
	printf("\n");
	printf("\t\t\t欢迎下次使用本系统!\n\n");
}//end of main()
status CreateCraph(ALGraph& G, VertexType V[], KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	int i = 0, j = 0, k = 0, h = 0, flag = 0;
	for (; V[i].key != -1; ++i)
		for (j = i + 1; V[j].key != -1; ++j)
			if (V[i].key == V[j].key)
				return ERROR;//key重复
	//若没返回错误，此时i为顶点数
	if (i > MAX_VERTEX_NUM)
		return ERROR;
	G.vexnum = i;
	int p[10000];//记录：p[key]是这个key在V中的位置

	for (j = 0; VR[j][0] != -1; ++j) {
		for (k = 0; k < i; ++k)
			if (V[k].key == VR[j][0])
				break;//说明符合要求弧尾VR[j][0]在V中，符合要求
		for (h = 0; h < i; ++h)
			if (V[h].key == VR[j][1])
				break;//说明符合要求弧尾VR[j][1]在V中，符合要求
		if (k == i || h == i) return ERROR;//则表明不是从break来的，即在V中都没有出现该弧尾或弧头
	}
	int one = 0, two = 0;
	i = 0;
	j = 0;
	VertexType e;
	do {
		G.vertices[i].data = V[i];
		G.vertices[i].firstarc = NULL;
	} while (V[i++].key != -1);
	G.vexnum = i - 1;
	i = 0;
	while (VR[i][0] != -1) {
		ArcNode* p;
		for (j = 0; j < G.vexnum; j++)
		{
			if (VR[i][0] == G.vertices[j].data.key)
			{
				one = j;
				break;
			}
		}
		for (j = 0; j < G.vexnum; j++)
		{
			if (VR[i][1] == G.vertices[j].data.key)
			{
				two = j;
				break;
			}
		}
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = two;
		p->nextarc = G.vertices[one].firstarc;
		G.vertices[one].firstarc = p;
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = one;
		p->nextarc = G.vertices[two].firstarc;
		G.vertices[two].firstarc = p;
		i++;
		G.arcnum++;
	}
	return OK;
	/********** End **********/
}
status DestroyGraph(ALGraph& G)
/*销毁无向图G*/
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	int i;
	ArcNode* p, * q;//边类型的指针p,q
	for (i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;//p指向第i个节点的 第一条依附于该节点的指针
		while (p)//p不为空,就依次将q指向下一条弧,释放p,最后再将p指向q，开始下一次循环
		{
			q = p->nextarc;
			free(p);
			p = q;
		}
	}
	G.vexnum = 0;//之后将图的信息,顶点数目,边数目,kind置为0
	G.arcnum = 0;
	G.kind = DG;
	return OK;

	/********** End **********/
}

int LocateVex(ALGraph G, KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	int i = 0;
	for (i = 0; i < G.vexnum; i++)
	{
		if (G.vertices[i].data.key == u)
			return i;
	}
	return -1;

	/********** End **********/
}

status PutVex(ALGraph& G, KeyType u, VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	int num = LocateVex(G, u);
	if (num == -1)
		return ERROR;
	if (LocateVex(G, value.key) != -1)
		if (value.key != u)
			return ERROR;
	G.vertices[num].data.key = value.key;
	int i = 0;
	for (i = 0; i < 20; i++)
		G.vertices[num].data.others[i] = value.others[i];
	return OK;

	/********** End **********/
}

int FirstAdjVex(ALGraph G, KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	int num = LocateVex(G, u);
	if (num == -1)
		return -1;
	if (G.vertices[num].firstarc == NULL)
		return -1;
	return G.vertices[num].firstarc->adjvex;

	/********** End **********/
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	ArcNode* p;
	int v1 = LocateVex(G, v);
	int w1 = LocateVex(G, w);
	if (v1 == -1 || w1 == -1)
		return -1;
	p = G.vertices[v1].firstarc;
	while (p && p->adjvex != w1)
	{
		p = p->nextarc;
	}
	if (!p) return -1;//根据返回值来判断是否有邻接点,是否是最后一个邻接点
	if (!p->nextarc) return -1;
	else return p->nextarc->adjvex;

	/********** End **********/
}

status InsertVex(ALGraph& G, VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	if (LocateVex(G, v.key) != -1) return ERROR;
	if (G.vexnum == MAX_VERTEX_NUM) return ERROR;
	G.vertices[G.vexnum].data = v;
	G.vexnum++;
	return OK;
	/********** End **********/
}
status DeleteVex(ALGraph& G, KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	int i, j;
	ArcNode* p, * q;
	j = LocateVex(G, v);
	if (j == -1)
		return ERROR;
	if (G.vexnum == 1)
		return ERROR;
	p = G.vertices[j].firstarc;
	while (p)//删点
	{
		q = p;
		p = p->nextarc;
		free(q);
		G.arcnum--;
	}
	G.vexnum--;
	for (i = j; i < G.vexnum; i++)
		G.vertices[i] = G.vertices[i + 1];
	for (i = 0; i < G.vexnum; i++)//删边
	{
		p = G.vertices[i].firstarc;
		while (p)
		{
			if (p->adjvex == j)//删
			{
				if (p == G.vertices[i].firstarc)
				{
					G.vertices[i].firstarc = p->nextarc;
					free(p);
					p = G.vertices[i].firstarc;
				}
				else
				{
					q->nextarc = p->nextarc;
					free(p);
					p = q->nextarc;
				}
			}
			else//下一个
			{
				if (p->adjvex > j)//删除结点前的位置信息改变
					p->adjvex--;
				q = p;
				p = p->nextarc;
			}
		}
	}
	return OK;

	/********** End **********/
}
status InsertArc(ALGraph& G, KeyType v, KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	ArcNode* p, * q;
	int  i, j, flag;
	flag = 0;
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if (i == -1 || j == -1)
		return ERROR;
	q = G.vertices[i].firstarc;
	while (q)
	{
		if (q->adjvex == j)
			return ERROR;
		q = q->nextarc;
	}
	q = G.vertices[j].firstarc;
	while (q)
	{
		if (q->adjvex == i)
			return ERROR;
		q = q->nextarc;
	}
	G.arcnum++;
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = j;
	p->nextarc = G.vertices[i].firstarc;
	G.vertices[i].firstarc = p;
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = i;
	p->nextarc = G.vertices[j].firstarc;
	G.vertices[j].firstarc = p;
	return OK;

	/********** End **********/
}

status DeleteArc(ALGraph& G, KeyType v, KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	ArcNode* p, * q;
	int i, j;
	i = LocateVex(G, v);
	j = LocateVex(G, w);
	if (i == -1 || j == -1)
		return ERROR;
	p = G.vertices[i].firstarc;
	while (p->adjvex != j)
	{
		q = p;
		p = p->nextarc;
		if (!p)
			return ERROR;
	}
	if (p->adjvex == j)
	{
		if (p == G.vertices[i].firstarc)
			G.vertices[i].firstarc = p->nextarc;
		else
			q->nextarc = p->nextarc;
		free(p);
		G.arcnum--;
	}
	p = G.vertices[j].firstarc;
	while (p && p->adjvex != i)
	{
		q = p;
		p = p->nextarc;
		if (!p)
			return ERROR;
	}
	if (p && p->adjvex == i)
	{
		if (p == G.vertices[j].firstarc)
			G.vertices[j].firstarc = p->nextarc;
		else
			q->nextarc = p->nextarc;
		free(p);
	}
	return OK;

	/********** End **********/
}
void DFS(ALGraph G, int v)
{
	visited[v] = 1;
	VisitFunc(G.vertices[v].data);
	for (int w = FirstAdjVex(G, G.vertices[v].data.key); w >= 0; w = NextAdjVex(G, G.vertices[v].data.key, G.vertices[w].data.key))
		if (!visited[w])
			DFS(G, w);
}
status DFSTraverse(ALGraph& G, void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	VisitFunc = visit;
	int i = 0;
	for (i = 0; i < G.vexnum; ++i)
	{
		visited[i] = 0;
	}
	for (i = 0; i < G.vexnum; ++i)
	{
		if (!visited[i])
			DFS(G, i);
	}
	return OK;
	/********** End **********/
}

status BFSTraverse(ALGraph& G, void(*visit)(VertexType))
{
	int v, u, w, i;
	VertexType va, vb;
	GraphQueue Q;
	for (i = 0; i < G.vexnum; i++)
		visited[i] = FALSE;
	int j = 0;
	for (j = 0; j < 20; j++)
	{
		Q.data[j].key = -1;
		Q.data[j].others[0] = '\0';
	}
	Q.tail = 0;
	Q.top = 0;
	for (i = 0; i < G.vexnum; i++)
		if (!visited[i])
		{
			visited[i] = TRUE;//表示已经访问过该节点
			visit(G.vertices[i].data);//访问该节点的data域
			Q.data[Q.top++] = G.vertices[i].data;//利用队列类型的性质，进行广度优先遍历
			while (Q.top != Q.tail)
			{
				va = Q.data[Q.tail++];
				for (w = FirstAdjVex(G, va.key); w >= 0; w = NextAdjVex(G, va.key, G.vertices[w].data.key))
					if (!visited[w])
					{
						visited[w] = TRUE;
						visit(G.vertices[w].data);
						Q.data[Q.top++] = G.vertices[w].data;//利用队列类型的性质，进行广度优先遍历
					}
			}
		}
	return OK;
}
void visit(VertexType v)
{
	printf(" %d %s", v.key, v.others);
}

status CreateCraphf(ALGraph& G, VertexType V[], KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
	// 请在这里补充代码，完成本关任务
	/********** Begin *********/
	int i = 0, j = 0, k = 0, h = 0, flag = 0;
	for (; V[i].key != -1; ++i)
		for (j = i + 1; V[j].key != -1; ++j)
			if (V[i].key == V[j].key)
				return ERROR;//key重复
	//若没返回错误，此时i为顶点数
	if (i > MAX_VERTEX_NUM)
		return ERROR;
	G.vexnum = i;
	int p[10000];//记录：p[key]是这个key在V中的位置

	for (j = 0; VR[j][0] != -1; ++j) {
		for (k = 0; k < i; ++k)
			if (V[k].key == VR[j][0])
				break;//说明符合要求弧尾VR[j][0]在V中，符合要求
		for (h = 0; h < i; ++h)
			if (V[h].key == VR[j][1])
				break;//说明符合要求弧尾VR[j][1]在V中，符合要求
		if (k == i || h == i) return ERROR;//则表明不是从break来的，即在V中都没有出现该弧尾或弧头
	}
	int one = 0, two = 0;
	i = 0;
	j = 0;
	VertexType e;
	do {
		G.vertices[i].data = V[i];
		G.vertices[i].firstarc = NULL;
	} while (V[i++].key != -1);
	G.vexnum = i - 1;
	i = 0;
	ArcNode* p1;
	while (VR[i][0] != -1)
	{
		ArcNode* p;
		for (j = 0; j < G.vexnum; j++)
		{
			if (VR[i][0] == G.vertices[j].data.key)
			{
				one = j;
				break;
			}
		}
		for (j = 0; j < G.vexnum; j++)
		{
			if (VR[i][1] == G.vertices[j].data.key)
			{
				two = j;
				break;
			}
		}
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = two;
		p->nextarc = NULL;
		p1 = G.vertices[one].firstarc;
		if (p1 == NULL)
		{
			G.vertices[one].firstarc = p;
		}
		else
		{
			while (p1->nextarc)
				p1 = p1->nextarc;
			p1->nextarc = p;
		}
		i++;
	}
	/********** End **********/
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
	// 请在这里补充代码，完成本关任务
	/********** Begin 1 *********/
	FILE* fp;
	fp = fopen(FileName, "w+");
	int i = 0;
	for (i = 0; i < G.vexnum; i++)
	{
		fprintf(fp, "%d ", G.vertices[i].data.key);
		fprintf(fp, "%s ", G.vertices[i].data.others);
	}
	fprintf(fp, "%d ", -1);
	fprintf(fp, "%s ", "nil");
	for (i = 0; i < G.vexnum; i++)
	{
		ArcNode* p1 = G.vertices[i].firstarc;
		while (p1)
		{
			fprintf(fp, "%d ", G.vertices[i].data.key);
			fprintf(fp, "%d ", G.vertices[p1->adjvex].data.key);
			p1 = p1->nextarc;
		}
	}
	fprintf(fp, "%d ", -1);
	fprintf(fp, "%d ", -1);
	fclose(fp);
	return OK;

	/********** End 1 **********/
}
status LoadGraph(ALGraph& G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
	// 请在这里补充代码，完成本关任务
	/********** Begin 2 *********/
	FILE* fp;
	VertexType V[20];
	KeyType VR[100][2];
	int c, i, sum, j;
	sum = 0;
	i = 0, j = 0;
	for (j = 0; j < 20; j++)
	{
		V[j].key = -1;
		V[j].others[0] = '\0';
	}
	for (j = 0; j < 100; j++)
	{
		VR[j][0] = -1;
		VR[j][1] = -1;
	}
	fp = fopen(FileName, "r+");
	c = fgetc(fp);
	for (j = 0; c != EOF;)
	{
		if (c == 45)
		{
			c = fgetc(fp);
			c = fgetc(fp);
			char s0[20];
			V[i].key = -1;
			fscanf(fp, "%s", s0);
			strcpy(V[i].others, s0);
			c = fgetc(fp);
			break;
		}
		c = c - 48;
		if (c == -16)
		{
			V[i].key = sum;
			sum = 0;
			char s0[20];
			fscanf(fp, "%s", s0);
			strcpy(V[i].others, s0);
			c = fgetc(fp);
			c = fgetc(fp);
			i++;
			continue;
		}
		sum = sum * 10 + c;
		c = fgetc(fp);
	}
	c = fgetc(fp);
	int cnt = 0;
	for (i = 0; c != EOF;)
	{
		if (c == 45)
		{
			VR[j][0] = -1;
			VR[j][1] = -1;
			break;
		}
		c = c - 48;
		if (c == -16)
		{

			if (cnt == 0)
			{
				VR[j][0] = sum;
				cnt++;
			}
			else if (cnt == 1)
			{
				VR[j][1] = sum;
				cnt--;
				j++;
			}
			sum = 0;
			c = fgetc(fp);
			continue;
		}
		sum = sum * 10 + c;
		c = fgetc(fp);
	}
	printf("\n");
	CreateCraphf(G, V, VR);
	return OK;
	/********** End 2 **********/
}
int LocateGraph(ALGraph G[], char name[])
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		if (strcmp(GraphName[i], name) == 0)
			return i + 1;
	}
	return 0;
}
status RemoveGraph(ALGraph* L, char name[])
{
	int i = LocateGraph(L, name);
	DestroyGraph(L[i]);
	for (; i < 9; i++)
	{
		L[i] = L[i + 1];
	}
	DestroyGraph(L[i]);
	return OK;
}

