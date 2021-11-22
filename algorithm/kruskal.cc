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

vector<int> fa;
vector<int> rank_set;

int sum;

void make_set(int x)    //初始化并查集节点
{
  fa[x]=x;
  rank_set[x]=0;    // rank表示以x为标志的节点个数, 两个集合合并时rank越大以x为标志合并的权重越大
}

int find(int x)
{
    if(x == fa[x])
        return x;
    else{
        fa[x] = find(fa[x]);  //父节点设为根节点, 路径压缩
        return fa[x];         //返回父节点
    }
}

void union_set(int x,int y,int w)//按秩合并节点
{
    if(rank_set[x] > rank_set[y])
    {
        fa[y]=x;
    }
    else if(rank_set[x] < rank_set[y])
    {
        fa[x]=y;
    }
    else   // 合并到x
    {
        rank_set[x]++;
        fa[y]=x;
    }
    sum += w; // 最小生成树总权值加上w
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
    fa.resize(num_vertex);
    rank_set.resize(num_vertex);

    for(int i=0; i<num_edge; i++)
    {
        cin>>x>>y>>w;
        edges[i].x=x;
        edges[i].y=y;
        edges[i].w=w;

        make_set(x);    // 初始化节点
        make_set(y);
    }
    
    sort(edges.begin(),edges.end(),[](auto& lhs, auto& rhs) {
        return lhs.w < rhs.w;
    });    /// 根据边的权值排序

    sum=0;
    for(int i=0; i<num_edge; i++)    // 遍历n条边,每次拿最小的边
    {
        x=find(edges[i].x); // 找到x,y的标志(父接待你)
        y=find(edges[i].y);
        w=edges[i].w;   // 权值
        if(x!=y)    // 加入边e[i]不会形成环
        {
            union_set(x,y,w);
        }
    }
    cout<<sum<<endl;
    return 0;
}