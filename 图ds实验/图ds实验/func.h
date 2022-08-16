status CreateCraph(ALGraph& G, VertexType V[], KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    G.vexnum = G.arcnum = 0;
    int used[100];
    for (int i = 0; i < 100; i++)used[i] = -1;
    for (int i = 0; V[i].key != -1; i++)//输入数据到表头节点中。
    {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
        used[V[i].key] = i;
        G.vexnum++;
        if (G.vexnum > 20)
        {
            G.vexnum = 0;
            return ERROR;
        }
        for (int j = i + 1; V[j].key != -1; j++)//判断是否有重复关键字。
            if (V[i].key == V[j].key)
            {
                G.vexnum = 0;
                return ERROR;
            }
    }
    if (G.vexnum == 0) return ERROR;
    for (int i = 0; VR[i][0] != -1; i++)
    {
        G.arcnum++;
        if (used[VR[i][0]] == -1 || used[VR[i][1]] == -1)//判断是否有无效的弧。
        {
            G.vexnum = G.arcnum = 0;
            return ERROR;
        }
    }

    //首插法
    for (int i = 0; i < G.arcnum; i++)
    {
        if (used[VR[i][1]] == used[VR[i][0]]) continue;
        ArcNode* NewNode1 = (ArcNode*)malloc(sizeof(ArcNode));
        ArcNode* NewNode2 = (ArcNode*)malloc(sizeof(ArcNode));
        NewNode1->adjvex = used[VR[i][0]];
        NewNode2->adjvex = used[VR[i][1]];
        //ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        NewNode1->nextarc = G.vertices[used[VR[i][1]]].firstarc;
        G.vertices[used[VR[i][1]]].firstarc = NewNode1;
        NewNode2->nextarc = G.vertices[used[VR[i][0]]].firstarc;
        G.vertices[used[VR[i][0]]].firstarc = NewNode2;
    }
    return OK;
}
status DestroyGraph(ALGraph& G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    if (G.vexnum == 0) return INFEASIBLE;
    for (int i = 0; i < G.vexnum; i++)
    {
        ArcNode* p = G.vertices[i].firstarc;
        while (p)
        {
            ArcNode* temp = p;
            p = p->nextarc;
            free(temp);
        }
        G.vertices[i].firstarc = NULL;
    }
    G.vexnum = G.arcnum = 0;
    return OK;
}
int LocateVex(ALGraph G, KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    for (int i = 0; i < G.vexnum; i++)
        if (G.vertices[i].data.key == u)
            return i;
    return INFEASIBLE;
}
status PutVex(ALGraph& G, KeyType u, VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    int location = LocateVex(G, u);//找到第一个关键字与节点相符的节点。
    if (location == -1) return ERROR;
    int find_same = LocateVex(G, value.key);
    if (find_same != location && find_same != -1)/*出现重复关键字*/
        return ERROR;
    G.vertices[location].data = value;
    return OK;
}
int FirstAdjVex(ALGraph G, KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    int loc = LocateVex(G, u);
    if (loc == -1 || G.vertices[loc].firstarc == NULL)
        return INFEASIBLE;
    return G.vertices[loc].firstarc->adjvex;
}
int NextAdjVex(ALGraph G, KeyType v, KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
{
    int loc = LocateVex(G, v);
    if (loc == -1) return INFEASIBLE;
    ArcNode* p = G.vertices[loc].firstarc;
    for (; p; p = p->nextarc)
    {
        if (G.vertices[p->adjvex].data.key == w)
        {
            if (p->nextarc)
                return p->nextarc->adjvex;
            else
                break;
        }
    }
    return INFEASIBLE;
}
status InsertVex(ALGraph& G, VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    if (G.vexnum >= 20)
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
        if (G.vertices[i].data.key == v.key)
            return ERROR;
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum++].firstarc = NULL;
    return OK;
}
status DeleteVex(ALGraph& G, KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    int location = LocateVex(G, v);
    if (G.vexnum <= 1)
        return ERROR;
    if (location == -1)
        return ERROR;
    else
    {
        ArcNode* temp = NULL;
        ArcNode* p = G.vertices[location].firstarc;
        while (p)
        {
            temp = p;
            p = p->nextarc;
            free(temp);
        }
        G.vertices[location].firstarc = NULL;
        for (int i = location; i + 1 < G.vexnum; i++)
            G.vertices[i] = G.vertices[i + 1];
        G.vexnum--;
        for (int i = 0; i < G.vexnum; i++)
        {
            ArcNode* to_be_dele = NULL;
            ArcNode* p = G.vertices[i].firstarc;
            while (p) {
                if (p->adjvex == location)
                {
                    if (to_be_dele)
                    {
                        to_be_dele->nextarc = p->nextarc;
                        ArcNode* temp = p;
                        p = p->nextarc;
                        free(temp);
                    }
                    else
                    {
                        ArcNode* temp = p;
                        p = p->nextarc;
                        G.vertices[i].firstarc = p;
                        free(temp);
                    }
                    G.arcnum--;
                }
                else {
                    if (p->adjvex > location)
                    {
                        p->adjvex--;
                    }
                    to_be_dele = p;
                    p = p->nextarc;

                }
            }
        }
        return OK;
    }
}
status InsertArc(ALGraph& G, KeyType v, KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    int loc1 = LocateVex(G, v);
    int loc2 = LocateVex(G, w);
    if (loc1 == -1 || loc2 == -1) return ERROR;
    ArcNode* p = G.vertices[loc1].firstarc;
    for (; p; p = p->nextarc)
        if (p->adjvex == loc2) return ERROR;//是否有重复弧，如果重复了，则停止添加，返回ERROR；
    ArcNode* newnode1 = (ArcNode*)malloc(sizeof(ArcNode));
    ArcNode* newnode2 = (ArcNode*)malloc(sizeof(ArcNode));
    newnode1->adjvex = loc2;
    newnode2->adjvex = loc1;
    newnode1->nextarc = G.vertices[loc1].firstarc;
    G.vertices[loc1].firstarc = newnode1;
    newnode2->nextarc = G.vertices[loc2].firstarc;
    G.vertices[loc2].firstarc = newnode2;
    G.arcnum++;
    return OK;
}
status DeleteArc(ALGraph& G, KeyType v, KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    int loc1 = LocateVex(G, v);
    int loc2 = LocateVex(G, w);
    if (loc1 == -1 || loc2 == -1) return ERROR;
    ArcNode* p = G.vertices[loc1].firstarc;
    ArcNode* pre = NULL;
    int flag = 0;
    while (p)
    {
        if (p->adjvex == loc2)
        {
            if (pre == NULL) {
                ArcNode* temp = G.vertices[loc1].firstarc;
                G.vertices[loc1].firstarc = G.vertices[loc1].firstarc->nextarc;
                free(temp);
                flag = 1;
                break;
            }
            else
            {
                pre->nextarc = p->nextarc;
                free(p);
                flag = 1;
                break;
            }
        }
        else
        {
            pre = p;
            p = p->nextarc;
        }
    }
    pre = NULL;
    p = G.vertices[loc2].firstarc;
    if (flag == 0) return ERROR;
    else
    {
        while (p)
        {
            if (p->adjvex == loc1) {
                if (pre == NULL) {
                    ArcNode* temp = G.vertices[loc2].firstarc;
                    G.vertices[loc2].firstarc = G.vertices[loc2].firstarc->nextarc;
                    free(temp);
                    flag = 1;
                    break;
                }
                else
                {
                    pre->nextarc = p->nextarc;
                    free(p);
                    flag = 1;
                    break;
                }
            }
            else
            {
                pre = p;
                p = p->nextarc;
            }
        }
    }
    G.arcnum--;
    return OK;
}
int visited[MAX_VERTEX_NUM];
void visit(VertexType v)
{
    printf(" %d %s", v.key, v.others);
}
void DFS(ALGraph& G, int i, void (*visit)(VertexType))
{
    ArcNode* p = G.vertices[i].firstarc;
    visited[i] = 1;
    visit(G.vertices[i].data);
    while (p != NULL)
    {
        int w = p->adjvex;
        if (visited[w] == 0)
            DFS(G, w, visit);
        p = p->nextarc;
    }
}
status DFSTraverse(ALGraph& G, void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{

    for (int i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    for (int i = 0; i < G.vexnum; i++)
        if (visited[i] == 0) DFS(G, i, visit);
    return OK;
}
status BFSTraverse(ALGraph& G, void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int visited[MAX_VERTEX_NUM];
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    VNode queue[100];
    int front = 0, tail = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (visited[i] == 0)
        {
            visited[i] = 1;
            queue[tail++] = G.vertices[i];
        }
        ArcNode* p = G.vertices[i].firstarc;
        for (; p; p = p->nextarc)
        {
            if (visited[p->adjvex] == 0)
            {
                visited[p->adjvex] = 1;
                queue[tail++] = G.vertices[p->adjvex];
            }
        }
    }
    while (front != tail)
    {
        visit(queue[front++].data);
    }
    printf("\n");
    return OK;
}
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写⼊到⽂件FileName中
{
    FILE* fp = fopen(FileName, "w");
    if (fp == NULL) return INFEASIBLE;
    for (int i = 0; i < G.vexnum; i++)
    {
        fprintf(fp, "%d %s", G.vertices[i].data.key, G.vertices[i].data.others);
        ArcNode* p = G.vertices[i].firstarc;
        for (; p; p = p->nextarc)
            fprintf(fp, " %d", p->adjvex);
        fprintf(fp, " -1");
        fprintf(fp, "\n");
    }
    fprintf(fp, "-1");
    fclose(fp);
    return OK;

}

status LoadGraph(ALGraph& G, char FileName[])
//读⼊⽂件FileName的图数据，创建图的邻接表
{
    FILE* fp = fopen(FileName, "r");
    if (fp == NULL) return INFEASIBLE;
    G.vexnum = G.arcnum = 0;
    int key_num;
    fscanf(fp, "%d", &key_num);
    while (key_num != -1)
    {
        G.vertices[G.vexnum].data.key = key_num;
        G.vertices[G.vexnum].firstarc = NULL;
        fscanf(fp, "%s", G.vertices[G.vexnum].data.others);
        int e;
        fscanf(fp, "%d", &e);
        ArcNode* tail_num = G.vertices[G.vexnum].firstarc;
        while (e != -1)
        {
            ArcNode* newnode = (ArcNode*)malloc(sizeof(ArcNode));
            newnode->adjvex = e;
            newnode->nextarc = NULL;
            G.arcnum++;
            if (tail_num == NULL)
            {
                G.vertices[G.vexnum].firstarc = newnode;
                tail_num = newnode;
            }
            else
            {
                tail_num->nextarc = newnode;
                tail_num = newnode;
            }
            fscanf(fp, "%d", &e);
        }
        fscanf(fp, "%d", &key_num);
        G.vexnum++;
    }

    fclose(fp);
    return OK;
}
/*
函数名称:VerticesSetLessThanK(ALGraph &G,KeyType v,int k)
初始条件:图G存在
操作结果:输出顶点v距离⼩于k的顶点集合；
*/
status VerticesSetLessThanK(ALGraph& G, KeyType v, int k) {
    //返回与顶点v距离⼩于k的顶点集合；
    //采⽤⼴度优先搜索
    VNode queue[20];
    int front = 0, tail = 0;//队列队尾位置
    int loc_index[100]; //通过关键值找到位置的索引数组
    memset(loc_index, -1, sizeof(int) * 100);//初始化为1
    bool Vvisit[20];//F表示未被访问,T已完成访问
    for (int i = 0; i < G.vexnum; i++) {
        Vvisit[i] = false;
        loc_index[G.vertices[i].data.key] = i;
    }
    int distance[20] = { 0 };//初始值为零,数组含义为到关键值为v顶点的距离
    queue[tail++] = G.vertices[loc_index[v]];
    Vvisit[loc_index[v]] = true;
    int cnt = 1, n_cnt = 0;//cnt表示正在遍历层的结点数量，n_cnt表示下⼀层；
    int dis = 1;
    while (front != tail) {
        while (cnt) {
            VNode vex = queue[front++];//出队
            cnt--;
            ArcNode* p = vex.firstarc;
            for (; p; p = p->nextarc) {
                if (Vvisit[p->adjvex] == false) {
                    queue[tail++] = G.vertices[p->adjvex];
                    Vvisit[p->adjvex] = true;
                    n_cnt++;
                    distance[p->adjvex] = dis;
                }
            }
        }
        cnt = n_cnt;
        n_cnt = 0;
        dis++;
    }
    for (int i = 0; i < G.vexnum; i++) {
        if (distance[i] && distance[i] < k) {
            printf(" %d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
        }
    }
    return OK;
}
/*
函数名称:ShortestPathLength(ALGraph & G,KeyType v,KeyType w)
初始条件:图G存在
操作结果:输出顶点v与顶点w的最短路径
*/
int ShortestPathLength(ALGraph& G, KeyType v, KeyType w) {
    int visited[MAX_VERTEX_NUM];
    for (int i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    VNode queue[100];
    int front = 0, tail = 0;
    int loc = -1, step = 0, flag = 0;
    for(int i = 0;i<G.vexnum;i++)
        if (v == G.vertices[i].data.key) {
            loc = i;
            break;
        }
    if (loc == -1)return -1;
    ArcNode* p = G.vertices[loc].firstarc;
    for (; p; p = p->nextarc) {
        queue[tail++] = G.vertices[p->adjvex];
        flag++;
    }
    while (front != tail)
    {
        if (queue[front++].data.key == w) { step++; return step; }
        else
        {
            ArcNode* q = queue[front - 1].firstarc;
            while (q) {
                queue[tail++] = G.vertices[q->adjvex];
                q = q->nextarc;
            }
            flag--;
            if (flag == 0)step++;
        }
    }
    return -1;
}
/*
函数名称:AddGraph(Graphs & Gs,int k)
初始条件:多图组存在
操作结果:在多图组中添加k个图
*/
status AddGraph(Graphs& Gs, int k) {
    if (Gs.Graphs_num + k > 10) {
        return INFEASIBLE;
    }

    while (k--) {
        printf("请输入%d个⽆向图的名字!\n", Gs.Graphs_num + 1);
        scanf("%s", Gs.Gp[Gs.Graphs_num].name);
        printf("请输入第%d个⽆向图的顶点和边!\n", Gs.Graphs_num + 1);
        VertexType V[20];
        int i = 0;
        do {
            scanf("%d%s", &V[i].key, V[i].others);
        } while (V[i++].key != -1);
        i = 0;
        KeyType VR[40][2];
        do {
            scanf("%d%d", &VR[i][0], &VR[i][1]);
        } while (VR[i++][0] != -1);
        CreateCraph(Gs.Gp[Gs.Graphs_num].G, V, VR);
        Gs.Graphs_num++;
    }
    return OK;
}
/*
函数名称:RemoveGraph(Graphs& Gs, int i)
初始条件 : 多图组存在
操作结果 : 在多图组中删除第i个图
*/
status RemoveGraph(Graphs& Gs, int i) {
    if (i<1 || i>Gs.Graphs_num) {
        return INFEASIBLE;
    }
    DestroyGraph(Gs.Gp[i - 1].G);
    for (int j = i - 1; j + 1 < Gs.Graphs_num; j++) {
        Gs.Gp[j] = Gs.Gp[j + 1];
    }
    Gs.Graphs_num--;
    return OK;
}

/*
函数名称:LocateGraph(Graphs & Gs,char name[])
初始条件:多图组存在
操作结果:在多图组中查找名字为name的图
*/
int LocateGraph(Graphs& Gs, char name[]) {
    for (int i = 0; i < Gs.Graphs_num; i++) {
        if (strcmp(name, Gs.Gp[i].name) == 0) {
            return i + 1;
        }
    }
    return ERROR;
}
int ConnectedComponentsNums(ALGraph& G) {
    int num = 0;
    int i;
    bool V_Visit[20];
    for (i = 0; i < G.vexnum; i++) {
        V_Visit[i] = false;//F表示未访问，T表示访问
    }
    VNode V_Stack[100];
    int top = 0;
    for (i = 0; i < G.vexnum; i++) {
        if (V_Visit[i] == false) {
            V_Stack[top++] = G.vertices[i];
            V_Visit[i] = true;
            num++;
        }
        while (top) {
            VNode t = V_Stack[--top];
            ArcNode* p = t.firstarc;
            for (; p; p = p->nextarc) {
                if (V_Visit[p->adjvex] == false) {
                    V_Stack[top++] = G.vertices[p->adjvex];
                    V_Visit[p->adjvex] = true;
                }
            }
        }

    }
    return num;
}