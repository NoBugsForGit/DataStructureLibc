#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <map>
#include <limits>
#include <algorithm>
#include <cstring>

// 邻接表结构的图
template <typename T>
class AdjacencyListGraph
{
public:
    // 添加节点
    void addVertex(const T &vertex)
    {
        adjList[vertex] = std::list<std::pair<T, int>>();
    }

    // 添加边
    void addEdge(const T &src, const T &dest, int weight)
    {
        adjList[src].push_back({dest, weight});
        adjList[dest].push_back({src, weight}); // 无向图，若为有向图则移除此行
    }

    // 深度优先搜索
    void DFS(const T &startVertex)
    {
        std::unordered_map<T, bool> visited;
        std::stack<T> stack;

        stack.push(startVertex);
        while (!stack.empty())
        {
            T current = stack.top();
            stack.pop();

            if (!visited[current])
            {
                std::cout << current << " ";
                visited[current] = true;
            }

            for (const auto &neighbor : adjList[current])
            {
                if (!visited[neighbor.first])
                {
                    stack.push(neighbor.first);
                }
            }
        }
        std::cout << std::endl;
    }

    // 广度优先搜索
    void BFS(const T &startVertex)
    {
        std::unordered_map<T, bool> visited;
        std::queue<T> queue;

        visited[startVertex] = true;
        queue.push(startVertex);

        while (!queue.empty())
        {
            T current = queue.front();
            queue.pop();
            std::cout << current << " ";

            for (const auto &neighbor : adjList[current])
            {
                if (!visited[neighbor.first])
                {
                    visited[neighbor.first] = true;
                    queue.push(neighbor.first);
                }
            }
        }
        std::cout << std::endl;
    }

    // Dijkstra算法
    void Dijkstra(const T &startVertex)
    {
        std::unordered_map<T, int> distances;
        for (const auto &pair : adjList)
        {
            distances[pair.first] = std::numeric_limits<int>::max();
        }
        distances[startVertex] = 0;

        auto compare = [&distances](const T &left, const T &right)
        { return distances[left] > distances[right]; };
        std::priority_queue<T, std::vector<T>, decltype(compare)> pq(compare);
        pq.push(startVertex);

        while (!pq.empty())
        {
            T current = pq.top();
            pq.pop();

            for (const auto &neighbor : adjList[current])
            {
                int newDist = distances[current] + neighbor.second;
                if (newDist < distances[neighbor.first])
                {
                    distances[neighbor.first] = newDist;
                    pq.push(neighbor.first);
                }
            }
        }

        std::cout << "Vertex Distance from Source" << std::endl;
        for (const auto &pair : distances)
        {
            std::cout << pair.first << " \t\t " << pair.second << std::endl;
        }
    }

    std::unordered_map<T, std::list<std::pair<T, int>>> adjList;
};

// 邻接矩阵结构的图
template <typename T>
class AdjacencyMatrixGraph
{
public:
    AdjacencyMatrixGraph(int vertices) : numVertices(vertices)
    {
        adjMatrix.resize(vertices, std::vector<int>(vertices, std::numeric_limits<int>::max()));
        for (int i = 0; i < vertices; ++i)
        {
            adjMatrix[i][i] = 0;
        }
    }

    // 添加节点
    void addVertex(const T &vertex)
    {
        vertexMap[vertex] = vertexCount++;
    }

    // 添加边
    void addEdge(const T &src, const T &dest, int weight)
    {
        int srcIndex = vertexMap[src];
        int destIndex = vertexMap[dest];
        adjMatrix[srcIndex][destIndex] = weight;
        adjMatrix[destIndex][srcIndex] = weight; // 无向图，若为有向图则移除此行
    }

    // 深度优先搜索
    void DFS(const T &startVertex)
    {
        std::vector<bool> visited(numVertices, false);
        std::stack<int> stack;
        int startIndex = vertexMap[startVertex];

        stack.push(startIndex);
        while (!stack.empty())
        {
            int currentIndex = stack.top();
            stack.pop();

            if (!visited[currentIndex])
            {
                std::cout << getKey(currentIndex) << " ";
                visited[currentIndex] = true;
            }

            for (int i = 0; i < numVertices; ++i)
            {
                if (adjMatrix[currentIndex][i] != std::numeric_limits<int>::max() && !visited[i])
                {
                    stack.push(i);
                }
            }
        }
        std::cout << std::endl;
    }

    // 广度优先搜索
    void BFS(const T &startVertex)
    {
        std::vector<bool> visited(numVertices, false);
        std::queue<int> queue;
        int startIndex = vertexMap[startVertex];

        visited[startIndex] = true;
        queue.push(startIndex);

        while (!queue.empty())
        {
            int currentIndex = queue.front();
            queue.pop();
            std::cout << getKey(currentIndex) << " ";

            for (int i = 0; i < numVertices; ++i)
            {
                if (adjMatrix[currentIndex][i] != std::numeric_limits<int>::max() && !visited[i])
                {
                    visited[i] = true;
                    queue.push(i);
                }
            }
        }
        std::cout << std::endl;
    }

    // Dijkstra算法
    void Dijkstra(const T &startVertex)
    {
        std::vector<int> dist(numVertices, std::numeric_limits<int>::max());
        std::vector<bool> sptSet(numVertices, false);
        int startIndex = vertexMap[startVertex];
        dist[startIndex] = 0;

        for (int count = 0; count < numVertices - 1; ++count)
        {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;

            for (int v = 0; v < numVertices; ++v)
            {
                if (!sptSet[v] && adjMatrix[u][v] && dist[u] != std::numeric_limits<int>::max() && dist[u] + adjMatrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + adjMatrix[u][v];
                }
            }
        }

        printSolution(dist);
    }

    // Floyd算法
    void Floyd()
    {
        std::vector<std::vector<int>> dist = adjMatrix;

        for (int k = 0; k < numVertices; ++k)
        {
            for (int i = 0; i < numVertices; ++i)
            {
                for (int j = 0; j < numVertices; ++j)
                {
                    if (dist[i][k] != std::numeric_limits<int>::max() && dist[k][j] != std::numeric_limits<int>::max() && dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        printSolution(dist);
    }

    // Prim算法
    void Prim()
    {
        std::vector<int> parent(numVertices, -1);
        std::vector<int> key(numVertices, std::numeric_limits<int>::max());
        std::vector<bool> mstSet(numVertices, false);
        key[0] = 0;

        for (int count = 0; count < numVertices - 1; ++count)
        {
            int u = minKey(key, mstSet);
            mstSet[u] = true;

            for (int v = 0; v < numVertices; ++v)
            {
                if (adjMatrix[u][v] && !mstSet[v] && adjMatrix[u][v] < key[v])
                {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }

        printMST(parent);
    }

    int numVertices;
    int vertexCount = 0;
    std::vector<std::vector<int>> adjMatrix;
    std::unordered_map<T, int> vertexMap;

    // 获取节点值
    T getKey(int index)
    {
        for (const auto &pair : vertexMap)
        {
            if (pair.second == index)
            {
                return pair.first;
            }
        }
        return T(); // 不应该发生
    }

    // 查找最小距离的顶点
    int minDistance(const std::vector<int> &dist, const std::vector<bool> &sptSet)
    {
        int min = std::numeric_limits<int>::max(), minIndex;

        for (int v = 0; v < numVertices; v++)
        {
            if (!sptSet[v] && dist[v] <= min)
            {
                min = dist[v];
                minIndex = v;
            }
        }

        return minIndex;
    }

    // 查找键值最小的顶点
    int minKey(const std::vector<int> &key, const std::vector<bool> &mstSet)
    {
        int min = std::numeric_limits<int>::max(), minIndex;

        for (int v = 0; v < numVertices; v++)
        {
            if (!mstSet[v] && key[v] < min)
            {
                min = key[v];
                minIndex = v;
            }
        }

        return minIndex;
    }

    // 打印Dijkstra和Floyd算法的结果
    void printSolution(const std::vector<int> &dist)
    {
        std::cout << "Vertex Distance from Source\n";
        for (int i = 0; i < numVertices; ++i)
        {
            std::cout << getKey(i) << " \t\t " << dist[i] << std::endl;
        }
    }

    void printSolution(const std::vector<std::vector<int>> &dist)
    {
        std::cout << "Shortest distances between every pair of vertices:\n";
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (dist[i][j] == std::numeric_limits<int>::max())
                    std::cout << "INF ";
                else
                    std::cout << dist[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // 打印Prim算法的结果
    void printMST(const std::vector<int> &parent)
    {
        std::cout << "Edge \tWeight\n";
        for (int i = 1; i < numVertices; i++)
        {
            std::cout << parent[i] << " - " << i << " \t" << adjMatrix[i][parent[i]] << " \n";
        }
    }
};

// 孩子兄弟链结构的图
template <typename T>
class ChildSiblingGraph
{
public:
    struct Node
    {
        T data;
        Node *firstChild;
        Node *nextSibling;
        Node(const T &data) : data(data), firstChild(nullptr), nextSibling(nullptr) {}
    };

    ChildSiblingGraph() : root(nullptr) {}

    // 添加节点
    Node *addVertex(const T &data)
    {
        Node *node = new Node(data);
        if (root == nullptr)
        {
            root = node;
        }
        nodes[data] = node;
        return node;
    }

    // 添加边
    void addEdge(const T &parent, const T &child)
    {
        Node *parentNode = nodes[parent];
        Node *childNode = nodes[child];
        if (parentNode->firstChild == nullptr)
        {
            parentNode->firstChild = childNode;
        }
        else
        {
            Node *temp = parentNode->firstChild;
            while (temp->nextSibling != nullptr)
            {
                temp = temp->nextSibling;
            }
            temp->nextSibling = childNode;
        }
    }

    // 深度优先搜索
    void DFS()
    {
        std::stack<Node *> stack;
        std::unordered_map<Node *, bool> visited;

        if (root != nullptr)
        {
            stack.push(root);
        }

        while (!stack.empty())
        {
            Node *current = stack.top();
            stack.pop();

            if (!visited[current])
            {
                std::cout << current->data << " ";
                visited[current] = true;
            }

            Node *child = current->firstChild;
            while (child != nullptr)
            {
                if (!visited[child])
                {
                    stack.push(child);
                }
                child = child->nextSibling;
            }
        }
        std::cout << std::endl;
    }

    // 广度优先搜索
    void BFS()
    {
        std::queue<Node *> queue;
        std::unordered_map<Node *, bool> visited;

        if (root != nullptr)
        {
            queue.push(root);
        }

        while (!queue.empty())
        {
            Node *current = queue.front();
            queue.pop();
            std::cout << current->data << " ";
            visited[current] = true;

            Node *child = current->firstChild;
            while (child != nullptr)
            {
                if (!visited[child])
                {
                    queue.push(child);
                }
                child = child->nextSibling;
            }
        }
        std::cout << std::endl;
    }

    Node *root;
    std::unordered_map<T, Node *> nodes;
};

#endif // GRAPH_H
