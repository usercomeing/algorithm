#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10000 // 最大节点数
#define INF 1000000     // 无穷大

// 图的邻接矩阵表示
int graph[MAX_NODES][MAX_NODES];

// Floyd算法
void floyd(int n) {
    int i, j, k;
    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

// 计算每个节点的百分比
void calculatePercentages(int n) {
    int i, j;
    float count;
    for (i = 1; i <= n; i++) {
        count = 0;
        for (j = 1; j <= n; j++) {
            if (graph[i][j] <= 6) {
                count++;
            }
        }
        printf("%d: %.2f%%\n", i, (count / n) * 100);
    }
}

int main() {
    int n, m;
    int i, j;
    int u, v;
  
    // 读入节点数和边数
    scanf("%d %d", &n, &m);

    // 初始化图
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (i == j) {
                graph[i][j] = 0;
            } else {
                graph[i][j] = INF;
            }
        }
    }

    // 读入边
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1; // 无向图
    }

    // 运行Floyd算法
    floyd(n);

    // 计算并输出百分比
    calculatePercentages(n);

    return 0;
}



