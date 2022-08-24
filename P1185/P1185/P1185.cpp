#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;
#define MAXN 10086
int m, n, width, depth;  // 层数，要删去的节点个数，所需的地图宽度，所需的地图高度
char map[MAXN][MAXN];
int le[MAXN] = { 0, 0, 1, 2, 5 };
bool del[MAXN][MAXN];

void DFS(int p, int q, int level, int times, bool left, int num) {
    if (times == 0) {
        map[p][q] = 'o';
        if (del[level][num]) {
            map[p][q] = ' ';
            if (left) 
                for (int i = p - 1, j = q + 1; map[i][j] != 'o'; i--, j++) 
                    map[i][j] = ' ';
            else 
                for (int i = p - 1, j = q - 1; map[i][j] != 'o'; i--, j--) 
                    map[i][j] = ' ';
            return;
        }
        if (level == m) return;
        DFS(p + 1, q - 1, level, times + 1, true, num * 2 - 1);
        DFS(p + 1, q + 1, level, times + 1, false, num * 2);
    }
    else {
        map[p][q] = left ? '/' : '\\';
        if (times == le[m + 1 - level]) 
        {
            if (left)
                DFS(p + 1, q - 1, level + 1, 0, true, num);
            else
                DFS(p + 1, q + 1, level + 1, 0, false, num);
        }
        else 
        {
            if (left)
                DFS(p + 1, q - 1, level, times + 1, true, num);
            else
                DFS(p + 1, q + 1, level, times + 1, false, num);
        }
    }
}
void input_tr(void)
{
    for (int i = 3; i < 100; i++) {
        le[i] = 3 * pow(2, i - 3) - 1;
    }
    cin >> m >> n;
    if (m == 1) {
        width = 1;
        depth = 1;
    }
    else {
        width = 6 * pow(2, m - 2) - 1;
        depth = 3 * pow(2, m - 2);
    }
}
void print_tr(void)
{
    for (int i = 1; i <= depth; i++) {
        for (int j = 1; j <= width; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
}
int main(void) 
{
    memset(map, ' ', sizeof(map));  //初始化
    input_tr();
    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        del[x][y] = true;
    }
    DFS(1, width / 2 + 1, 1, 0, 0, 1);
    print_tr();
    return 0;
}
