#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int x,y;
    int w;
};

// 求1到n的最短路距离，如果无法从1走到n，则返回-1。
int bellman_ford(vector<Edge>& edges, int n, int start, int end)
{
    vector<int> dist(n, 0x3f);
    dist[start] = 0;    // 初始化

    // 如果第n次迭代仍然会松弛三角不等式，就说明存在一条长度是n+1的最短路径，由抽屉原理，路径中至少存在两个相同的点，说明图中存在负权回路。
    for (int i = 0; i < n; i ++ )   // n个外层循环
    {
        for (int j = 0; j < edges.size(); j ++ )   // 遍历m条边
        {
            int a = edges[j].x, b = edges[j].y, w = edges[j].w;
            // 更新三角不等式, 用dist[a]+w来更新dist[b]
            if (dist[b] > dist[a] + w)
                dist[b] = dist[a] + w;
        }
    }

    if (dist[end] > 0x3f3f3f3f / 2) return -1;
    return dist[end];
}

int main()
{
    int x,y,w;
    int num_vertex, num_edge;//n是点,m是边

    ifstream in("/home/larry/programs/c++code/algorithm/graph.txt");
    cin.rdbuf(in.rdbuf());
    cin>>num_vertex>>num_edge;

    vector<Edge> edges;
    edges.resize(num_edge);

    for(int i=0; i<num_edge; i++)
    {
        cin>>x>>y>>w;
        edges[i].x=x;
        edges[i].y=y;
        edges[i].w=w;
    }

    cout << bellman_ford(edges, num_vertex, 0, 3) <<endl;
    return 0;
}