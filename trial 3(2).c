#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10000 // 最大节点数

// 图的邻接表表示
struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int numNodes;
    struct Node** adjLists;
};

// 创建邻接表节点
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 创建图
struct Graph* createGraph(int numNodes) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numNodes = numNodes;
    graph->adjLists = (struct Node**)malloc(numNodes * sizeof(struct Node*));
    int i;
    for (i = 0; i < numNodes; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// 添加边
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// BFS算法
void bfs(struct Graph* graph, int startNode, int* distances) {
    bool* visited = (bool*)malloc(graph->numNodes * sizeof(bool));
    int i;
    for (i = 0; i < graph->numNodes; i++) {
        visited[i] = false;
        distances[i] = -1; // 初始化距离为-1
    }
    visited[startNode] = true;
    distances[startNode] = 0;
    int* queue = (int*)malloc(graph->numNodes * sizeof(int));
    int front = 0, rear = 0;
    queue[rear++] = startNode;
    while (front!= rear) {
        int currentNode = queue[front++];
        struct Node* temp = graph->adjLists[currentNode];
        while (temp) {
            int neighbor = temp->data;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                distances[neighbor] = distances[currentNode] + 1;
                queue[rear++] = neighbor;
            }
            temp = temp->next;
        }
    }
    free(visited);
    free(queue);
}

// 计算每个节点的百分比
void calculatePercentages(struct Graph* graph,int n) {
    int i, j;
    for (i = 0; i < graph->numNodes; i++) {
        int* distances = (int*)malloc(graph->numNodes * sizeof(int));
        bfs(graph, i, distances);
        int count = 0; // 初始化count为0，用于统计距离<=6的节点数
        for (j = 0; j < graph->numNodes; j++) {
            if (distances[j] <= 6) {
                count++;
            }
        }
                printf("%d: %.2f%%\n", i + 1, (count /(float) n) * 100); // 使用浮点数除法

        free(distances);
    }
}

int main() {
    int n, m;
    int i, j;
    int u, v;

    // 读入节点数和边数
    scanf("%d %d", &n, &m);

    // 创建图
    struct Graph* graph = createGraph(n);

    // 读入边
    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        addEdge(graph, u - 1, v - 1); // 节点编号从0开始
    }

    // 计算并输出百分比
    calculatePercentages(graph,n);

    return 0;
}
