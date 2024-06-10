#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define MAX_VERTICES 100

// 邻接表节点结构
typedef struct AdjListNode
{
    int dest;
    struct AdjListNode *next;
    int weight; // 用于加权图
} AdjListNode;

// 邻接表结构
typedef struct AdjList
{
    AdjListNode *head;
} AdjList;

// 邻接表图结构
typedef struct AdjListGraph
{
    int numVertices;
    AdjList *array;
} AdjListGraph;

// 邻接矩阵图结构
typedef struct AdjMatrixGraph
{
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
} AdjMatrixGraph;

// 孩子兄弟链节点结构
typedef struct CSNode
{
    char data;
    struct CSNode *firstChild;
    struct CSNode *nextSibling;
} CSNode;

// 孩子兄弟链图结构
typedef struct ChildSiblingGraph
{
    CSNode *root;
    CSNode *nodes[MAX_VERTICES];
    int numVertices;
} ChildSiblingGraph;

// 创建邻接表图
AdjListGraph *createAdjListGraph(int vertices)
{
    AdjListGraph *graph = (AdjListGraph *)malloc(sizeof(AdjListGraph));
    graph->numVertices = vertices;
    graph->array = (AdjList *)malloc(vertices * sizeof(AdjList));
    for (int i = 0; i < vertices; ++i)
    {
        graph->array[i].head = NULL;
    }
    return graph;
}

// 删除邻接表图
void deleteAdjListGraph(AdjListGraph *graph)
{
    for (int i = 0; i < graph->numVertices; ++i)
    {
        AdjListNode *node = graph->array[i].head;
        while (node)
        {
            AdjListNode *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

// 创建一个新的邻接表节点
AdjListNode *newAdjListNode(int dest, int weight)
{
    AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// 添加邻接表边
void addAdjListEdge(AdjListGraph *graph, int src, int dest, int weight)
{
    AdjListNode *newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// 深度优先搜索辅助函数
void DFSAdjListUtil(AdjListGraph *graph, int v, bool visited[])
{
    visited[v] = true;
    printf("%d ", v);

    AdjListNode *node = graph->array[v].head;
    while (node)
    {
        if (!visited[node->dest])
        {
            DFSAdjListUtil(graph, node->dest, visited);
        }
        node = node->next;
    }
}

// 深度优先搜索
void DFSAdjList(AdjListGraph *graph, int startVertex)
{
    bool *visited = (bool *)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; ++i)
    {
        visited[i] = false;
    }

    DFSAdjListUtil(graph, startVertex, visited);
    printf("\n");

    free(visited);
}

// 广度优先搜索
void BFSAdjList(AdjListGraph *graph, int startVertex)
{
    bool *visited = (bool *)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; ++i)
    {
        visited[i] = false;
    }

    int *queue = (int *)malloc(graph->numVertices * sizeof(int));
    int front = 0;
    int rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        AdjListNode *temp = graph->array[currentVertex].head;
        while (temp)
        {
            int adjVertex = temp->dest;
            if (!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");

    free(queue);
    free(visited);
}

// Dijkstra算法（邻接表）
void dijkstraAdjList(AdjListGraph *graph, int startVertex)
{
    int *dist = (int *)malloc(graph->numVertices * sizeof(int));
    bool *sptSet = (bool *)malloc(graph->numVertices * sizeof(bool));

    for (int i = 0; i < graph->numVertices; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[startVertex] = 0;

    for (int count = 0; count < graph->numVertices - 1; count++)
    {
        int min = INT_MAX, minIndex;

        for (int v = 0; v < graph->numVertices; v++)
        {
            if (!sptSet[v] && dist[v] <= min)
            {
                min = dist[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        sptSet[u] = true;

        AdjListNode *node = graph->array[u].head;
        while (node != NULL)
        {
            int v = node->dest;
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + node->weight < dist[v])
            {
                dist[v] = dist[u] + node->weight;
            }
            node = node->next;
        }
    }

    printf("Vertex Distance from Source\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }

    free(dist);
    free(sptSet);
}

// 创建邻接矩阵图
AdjMatrixGraph *createAdjMatrixGraph(int vertices)
{
    AdjMatrixGraph *graph = (AdjMatrixGraph *)malloc(sizeof(AdjMatrixGraph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; ++i)
    {
        for (int j = 0; j < vertices; ++j)
        {
            graph->adjMatrix[i][j] = INT_MAX;
        }
    }

    return graph;
}

// 删除邻接矩阵图
void deleteAdjMatrixGraph(AdjMatrixGraph *graph)
{
    free(graph);
}

// 添加邻接矩阵边
void addAdjMatrixEdge(AdjMatrixGraph *graph, int src, int dest, int weight)
{
    graph->adjMatrix[src][dest] = weight;
    graph->adjMatrix[dest][src] = weight;
}

// 深度优先搜索辅助函数
void DFSAdjMatrixUtil(AdjMatrixGraph *graph, int v, bool visited[])
{
    visited[v] = true;
    printf("%d ", v);

    for (int i = 0; i < graph->numVertices; ++i)
    {
        if (graph->adjMatrix[v][i] != INT_MAX && !visited[i])
        {
            DFSAdjMatrixUtil(graph, i, visited);
        }
    }
}

// 深度优先搜索
void DFSAdjMatrix(AdjMatrixGraph *graph, int startVertex)
{
    bool *visited = (bool *)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; ++i)
    {
        visited[i] = false;
    }

    DFSAdjMatrixUtil(graph, startVertex, visited);
    printf("\n");

    free(visited);
}

// 广度优先搜索
void BFSAdjMatrix(AdjMatrixGraph *graph, int startVertex)
{
    bool *visited = (bool *)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; ++i)
    {
        visited[i] = false;
    }

    int *queue = (int *)malloc(graph->numVertices * sizeof(int));
    int front = 0;
    int rear = 0;

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->numVertices; ++i)
        {
            if (graph->adjMatrix[currentVertex][i] != INT_MAX && !visited[i])
            {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");

    free(queue);
    free(visited);
}

// Dijkstra算法（邻接矩阵）
void dijkstraAdjMatrix(AdjMatrixGraph *graph, int startVertex)
{
    int *dist = (int *)malloc(graph->numVertices * sizeof(int));
    bool *sptSet = (bool *)malloc(graph->numVertices * sizeof(bool));

    for (int i = 0; i < graph->numVertices; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[startVertex] = 0;

    for (int count = 0; count < graph->numVertices - 1; count++)
    {
        int min = INT_MAX, minIndex;

        for (int v = 0; v < graph->numVertices; v++)
        {
            if (!sptSet[v] && dist[v] <= min)
            {
                min = dist[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        sptSet[u] = true;

        for (int v = 0; v < graph->numVertices; v++)
        {
            if (!sptSet[v] && graph->adjMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph->adjMatrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph->adjMatrix[u][v];
            }
        }
    }

    printf("Vertex Distance from Source\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }

    free(dist);
    free(sptSet);
}

// Floyd算法（邻接矩阵）
void floydAdjMatrix(AdjMatrixGraph *graph)
{
    int dist[MAX_VERTICES][MAX_VERTICES];

    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else if (graph->adjMatrix[i][j] != INT_MAX)
                dist[i][j] = graph->adjMatrix[i][j];
            else
                dist[i][j] = INT_MAX;
        }
    }

    for (int k = 0; k < graph->numVertices; k++)
    {
        for (int i = 0; i < graph->numVertices; i++)
        {
            for (int j = 0; j < graph->numVertices; j++)
            {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < graph->numVertices; i++)
    {
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (dist[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

// Prim算法（邻接矩阵）
void primAdjMatrix(AdjMatrixGraph *graph)
{
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool mstSet[MAX_VERTICES];

    for (int i = 0; i < graph->numVertices; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph->numVertices - 1; count++)
    {
        int min = INT_MAX, minIndex;

        for (int v = 0; v < graph->numVertices; v++)
        {
            if (!mstSet[v] && key[v] < min)
            {
                min = key[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        mstSet[u] = true;

        for (int v = 0; v < graph->numVertices; v++)
        {
            if (graph->adjMatrix[u][v] && !mstSet[v] && graph->adjMatrix[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph->adjMatrix[u][v];
            }
        }
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < graph->numVertices; i++)
    {
        printf("%d - %d \t%d \n", parent[i], i, graph->adjMatrix[i][parent[i]]);
    }
}

// Kruskal算法
typedef struct Edge
{
    int src, dest, weight;
} Edge;

typedef struct Graph
{
    int V, E;
    Edge *edge;
} Graph;

Graph *createGraph(int V, int E)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge *)malloc(E * sizeof(Edge));
    return graph;
}

int find(int parent[], int i)
{
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y)
{
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

int compare(const void *a, const void *b)
{
    Edge *a1 = (Edge *)a;
    Edge *b1 = (Edge *)b;
    return a1->weight > b1->weight;
}

void kruskalMST(Graph *graph)
{
    int V = graph->V;
    Edge result[MAX_VERTICES];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compare);

    int *parent = (int *)malloc(V * sizeof(int));
    memset(parent, -1, V * sizeof(int));

    while (e < V - 1 && i < graph->E)
    {
        Edge next_edge = graph->edge[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y)
        {
            result[e++] = next_edge;
            Union(parent, x, y);
        }
    }

    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);

    free(parent);
}

// 创建孩子兄弟链图
ChildSiblingGraph *createChildSiblingGraph()
{
    ChildSiblingGraph *graph = (ChildSiblingGraph *)malloc(sizeof(ChildSiblingGraph));
    graph->root = NULL;
    graph->numVertices = 0;
    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        graph->nodes[i] = NULL;
    }
    return graph;
}

// 删除孩子兄弟链图
void deleteChildSiblingGraph(CSNode *node)
{
    if (node == NULL)
        return;
    deleteChildSiblingGraph(node->firstChild);
    deleteChildSiblingGraph(node->nextSibling);
    free(node);
}

// 添加孩子兄弟链节点
CSNode *addCSNode(ChildSiblingGraph *graph, char data)
{
    CSNode *node = (CSNode *)malloc(sizeof(CSNode));
    node->data = data;
    node->firstChild = NULL;
    node->nextSibling = NULL;
    graph->nodes[graph->numVertices++] = node;
    if (graph->root == NULL)
    {
        graph->root = node;
    }
    return node;
}

// 添加孩子兄弟链边
void addCSEdge(ChildSiblingGraph *graph, char parent, char child)
{
    CSNode *parentNode = NULL;
    CSNode *childNode = NULL;
    for (int i = 0; i < graph->numVertices; ++i)
    {
        if (graph->nodes[i]->data == parent)
        {
            parentNode = graph->nodes[i];
        }
        if (graph->nodes[i]->data == child)
        {
            childNode = graph->nodes[i];
        }
    }
    if (parentNode && childNode)
    {
        if (parentNode->firstChild == NULL)
        {
            parentNode->firstChild = childNode;
        }
        else
        {
            CSNode *temp = parentNode->firstChild;
            while (temp->nextSibling != NULL)
            {
                temp = temp->nextSibling;
            }
            temp->nextSibling = childNode;
        }
    }
}

// 深度优先搜索
void DFSChildSibling(CSNode *node)
{
    if (node == NULL)
        return;
    printf("%c ", node->data);
    DFSChildSibling(node->firstChild);
    DFSChildSibling(node->nextSibling);
}

// 广度优先搜索
void BFSChildSibling(CSNode *root)
{
    if (root == NULL)
        return;

    CSNode *queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear)
    {
        CSNode *current = queue[front++];
        printf("%c ", current->data);

        CSNode *child = current->firstChild;
        while (child)
        {
            queue[rear++] = child;
            child = child->nextSibling;
        }
    }
    printf("\n");
}