#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// 求1号点到n号点的最短路，如果不存在则返回-1
int dijkstra(const vector<vector<int>>& graph, int start, int end)
{
    int n = graph.size();
    vector<int> dist (n, 0x3f3f3f);
    for (int i = 0; i < n; i++) {
        dist[i] = graph[start][i];
    }
    vector<int> visited(n, 0);
    dist[start] = 0;

    for (int i = 0; i < n - 1; i ++ )   // 循环n-1次
    {
        int t = -1;     // 在还未确定最短路的点中，寻找距离最小的点
        for (int j = 0; j < n; j ++ )
            if (!visited[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
        // 已经找到t为路径最短点
        // 用t更新其他点的距离
        for (int j = 0; j < n; j ++ )
            dist[j] = min(dist[j], dist[t] + graph[t][j]);

        visited[t] = 1;
    }

    if (dist[end] == 0x3f3f3f3f) return -1;
    return dist[end];
}

int main()
{
    int num_vertex, num_edge;
    int x, y, w;
    int cost;
    vector<vector<int>> graph;
    ifstream in("/home/larry/programs/c++code/algorithm/graph.txt");
    cin.rdbuf(in.rdbuf());
    cin>>num_vertex >>num_edge;
    graph.resize(num_vertex, vector<int>(num_vertex, INT32_MAX));

    for (int i = 0; i < num_vertex; i++) {
        graph[i][i] = 0;
    }
    for (int i = 0; i < num_edge; i++) {
        cin >> x >> y >> w;
        graph[x][y] = w;
        graph[y][x] = w;
    }
    cost= dijkstra(graph, 0, 3);
    cout<<cost<<endl;
    return 0;
}