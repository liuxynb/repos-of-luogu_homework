// main.cpp
// Experiment_4
//
// Created by 刘兴元 on 2022/5/22.
//
#include "def.h"
#include "func.h"


int main(void) 
{
	int op = 1;
	ALGraph G;
	G.vexnum = 0;
	G.arcnum = 0;
	Graphs Gs;
	Gs.Graphs_num = 0;

	char myfile[] = "mygraph.txt";
	while (op) {
		printf("\n\n");
		printf("-----------------Menu----------------- \n");
		printf("----------------------------------------------------------------------------------\n");
		printf(" 1. CreateGraph           2. DestroyGraph\n");
		printf(" 3. LocateVex             4. PutVex\n");
		printf(" 5. FirstAdjVex           6. NextAdjVex \n");
		printf(" 7. InsertVex             8. DeleteVex\n");
		printf(" 9. InsertArc             10. DeleteArc\n");
		printf(" 11. DFSTraverse          12. BFSTraverse\n");
		printf(" 13. SaveGraph            14. LoadGraph\n");
		printf(" 15. VerticesSetLessThanK 16. ShortestPathLength\n");
		printf(" 17. AddGraphs            18. RemoveGraphs\n");
		printf(" 19. Locategraphs         20. ConnectedCompNums\n");
		printf(" 0. Exit\n");
		printf("----------------------------------------------------------------------------------\n");
		printf(" 请选择你的操作[0~20]:");
		scanf("%d", &op);
		switch (op) {
		case 1: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			VertexType V[20];
			printf("请依次输入顶点关键字和弧长顶点关键字!\n");
			int i = 0;
			do {
				scanf("%d%s", &V[i].key, V[i].others);

			} while (V[i++].key != -1);
			i = 0;
			KeyType VR[40][2];
			do {
				scanf("%d%d", &VR[i][0], &VR[i][1]);
			} while (VR[i++][0] != -1);
			if (CreateCraph(Gs.Gp[k-1].G, V, VR) == OK) {
				Gs.Graphs_num++;
				printf("创建成功!\n");
			}
			else {
				printf("创建失败!\n");
			}
			getchar(); getchar();
			break;
		}
		case 2:
			/*printf("请输⼊图的操作序号!\n");
			int k;
			scanf("%d",&k);
			Gs.Gp[k].G*/
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			if (DestroyGraph(Gs.Gp[k-1].G) == OK) {
				printf("销毁成功!\n");
				Gs.Graphs_num--;
			}
			else {
				printf("销毁失败!\n");
			}
			getchar(); getchar();
			break;
		case 3:
		{
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("请输入需要查找顶点的关键字!\n");
			int e;
			scanf("%d", &e);
			int loc = LocateVex(Gs.Gp[k-1].G, e);
			if (loc>=0) {
				printf("查找成功,关键字为%d的结点在邻接表中的位置为%d", e, loc);
			}
			else {
				printf("查找失败!\n");
			}
			getchar(); getchar();
			break;
		}
		case 4: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("请输入需要需要修改顶点的关键字以及修改后的值!\n");
			int e;
			VertexType value;
			scanf("%d%d%s", &e, &value.key, value.others);
			if (PutVex(Gs.Gp[k-1].G, e, value) == OK) {
				printf("修改成功!\n");
			}
			else {
				printf("修改失败!\n");
			}
			getchar(); getchar();
			break;
		}
		case 5:
		{
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("请输入需要获取第一邻接顶点的顶点关键字!\n");
			int u;
			scanf("%d", &u);
			int adj = FirstAdjVex(Gs.Gp[k-1].G, u);
			if (adj) {
				printf("关键字为%d的顶点的第一邻接顶点为%d,%s", u, Gs.Gp[0].G.vertices[adj].data.key, Gs.Gp[0].G.vertices[adj].data.others);
			}
			else {
				printf("无邻接点!\n");
			}
			getchar(); getchar();
			break;
		}
		case 6:
		{
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("请输入需要查询下一邻接顶点的邻接顶点以及相对位置顶点关键值!\n");
			int u, v;
			scanf("%d%d", &u, &v);
			int loc = NextAdjVex(Gs.Gp[k-1].G, u, v);
			if (loc == -1) {
				printf("查找失败!\n");
			}
			else {
				printf("关键字为%d的顶点关于关键值为%d的顶点的下一邻接顶点为%d,%s", u, v, Gs.Gp[0].G.vertices[loc].data.key, Gs.Gp[0].G.vertices[loc].data.others);
			}
			getchar(); getchar();
			break;
		}
		case 7: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("请输入新顶点的关键字和名称!\n");
			VertexType value;
			scanf("%d%s", &value.key, value.others);
			if (InsertVex(Gs.Gp[k - 1].G, value) == ERROR) {
				printf("插入失败!\n");
			}
			else {
				printf("插入成功!\n");
			}
			getchar(); getchar();
			break;
		}
		case 8: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("请输入需要删除顶点的关键字!\n");
			int u;
			scanf("%d", &u);
			if (DeleteVex(Gs.Gp[k - 1].G, u) == ERROR) {
				printf("删除失败!\n");
			}
			else {
				printf("删除成功!\n");
			}
			getchar(); getchar();
			break;
		}
		case 9: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("请输入新插入弧的两端顶点关键字!\n");
			int u, v;
			scanf("%d%d", &u, &v);
			if (InsertArc(Gs.Gp[k-1].G, u, v) == OK) {
				printf("插入成功!\n");
			}
			else {
				printf("插入失败!\n");
			}
			getchar(); getchar();
			break;
		}
		case 10: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("请输入删除弧的两端顶点关键字!\n");
			int u, v;
			scanf("%d%d", &u, &v);
			if (DeleteArc(Gs.Gp[k-1].G, u, v) == OK) {
				printf("删除成功!\n");
			}
			else {
				printf("删除失败!\n");
			}
			getchar(); getchar();
			break;
		}
		case 11: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			if (DFSTraverse(Gs.Gp[k - 1].G, visit) == OK) {
				printf("深度遍历成功!\n");
			}
			else {
				printf("遍历失败!\n");
			}
			getchar(); getchar();
			break;
		}
		case 12: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			if (BFSTraverse(Gs.Gp[k - 1].G, visit) == OK) {
				printf("广度遍历成功!\n");
			}
			else {
				printf("遍历失败!\n");
			}
			getchar(); getchar();
			break;
		}
		case 13: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			if (SaveGraph(Gs.Gp[k - 1].G, myfile) == OK) {
				printf("保存成功!\n");
			}
			else {
				printf("保存失败!\n");
			}
			getchar();
			getchar();
			break;
		}
		case 14: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			if (LoadGraph(Gs.Gp[k - 1].G, myfile) == OK) {
				Gs.Graphs_num++;
				printf("载入成功!\n");
			}
			else {
				printf("载入失败!\n");
			}
			getchar();
			getchar();
			break;
		}
		case 15: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("查找顶点关键值和距离!\n");
			int v, dis;
			scanf("%d%d", &v, &dis);
			VerticesSetLessThanK(Gs.Gp[k - 1].G, v, dis);
			getchar();
			getchar();
			break;
		}
		case 16: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("请输入需要查找最小路径两个顶点的关键值!\n");
			int v, w;
			scanf("%d%d", &v, &w);
			int length = ShortestPathLength(Gs.Gp[k - 1].G, v, w);
			if (length > Max_Path) {
				printf("两顶点不连通!\n");
			}
			else if (length == -1) {
				printf("查找失败!\n");
			}
			else {
				printf("顶点%d和%d的最短路径为%d", v, w, length);
			}
			getchar();
			getchar();
			break;
		}
		case 17: {

			printf("请输入需要添加的图的个数!\n");
			int k;
			scanf("%d", &k);
			if (AddGraph(Gs, k) == OK) {
				printf("添加成功!\n");
			}
			else {
				printf("添加失败!\n");
			}
			getchar();
			getchar();
			break;
		}
		case 18: {
			printf("请输入需要移除的图的位置!\n");
			int i;
			scanf("%d", &i);
			if (RemoveGraph(Gs, i) == OK) {
				printf("移除成功!\n");
			}
			else {
				printf("移除失败!\n");
			}
			getchar(); getchar();
			break;
		}
		case 19: {
			printf("请输入需要查找的图的名称!\n");
			char name[20];
			scanf("%s", name);
			int loc = LocateGraph(Gs, name);
			if (loc) {
				printf("名字为%s的图在多图组中的位置为%d", name, loc);
			}
			else {
				printf("查找失败!\n");
			}
			getchar(); getchar();
			break;
		}
		case 20: {
			printf("请输入图的操作序号!\n");
			int k;
			scanf("%d", &k);
			printf("图的连通分量个数为%d", ConnectedComponentsNums(Gs.Gp[k - 1].G));
			getchar();
			getchar();
			break;
		}
		case 0:
			printf("退出系统!\n");
			getchar();
			getchar();
			break;
		default:
			printf("it is not a command,please put in your choice again!\n");
			getchar();
			getchar();
			break;
		}//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
}//end of main(