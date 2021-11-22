#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int Prim(const vector<vector<int>>& graph, int n, int start)  //从节点1开始的最小生成树
{
    vector<int> sta(n); // 存储最小生成树边, 当前节点的前一个节点

    vector<int> lowcost(n);
    int min,minid;    // min用来存放最小权值，minid用来存放权值最小的边所对应的终点
    int sum = 0;    // 最小生成树的权值和
    for (int i = 0; i < n; i++) {
        lowcost[i] = graph[start][i]; // 初始化lowcost[i]为从start开始的节点
        sta[i]=start;   //  起始点为start
    }

    sta[start]=0; //节点start进入最小生成树
    printf("%c", start+'A');
    for(int h = 1; h < n; h++)
    {
        min=INT32_MAX;
        for(int j=0; j < n; j++)   // 找lowcost的最小值的节点
        {
            if(lowcost[j] < min && lowcost[j] != 0)
            {    
                min=lowcost[j];
                minid=j;
            }
        }
        lowcost[minid] = 0;   // 选择midid为最小生成树选择的点，所以把值置为0。防止下次访问到
        printf("%c", minid+'A');

        sum += min; // mid为最短边

        for(int s= 0; s < n; s++)   // 通过minid更新lowcost, 生成树到其他点的距离
        {
            if(lowcost[s] > graph[minid][s])  //  已经找到midId了, 就要更新下到其他生成树外节点的距离
            {
                lowcost[s] = graph[minid][s];
                sta[s]=minid;
            }
        }
    }
    return sum;

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
    cost= Prim(graph, num_vertex, 3);
    cout<<cost<<endl;
    return 0;
}