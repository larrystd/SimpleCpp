#include <iostream>
#include <fstream>
using namespace std;
#define INFINE 99999999//假装自己是无穷大
const int N = 1010;
int graph[N][N];
int vertexnum, arcnum;
//lowcost[i]:表示以i为终点的边的最小权值,
//当lowcost[i]=0说明以i为终点的边的最小权值=0,
//也就是表示i点加入了MST

//mst[i]:表示对应lowcost[i]的起点，
//即说明边<mst[i],i>是MST的一条边
void Prim(int v, int n) {
	int sum = 0;
	int locatest[N];
	int mst[N];
	for (int i = 1; i <= n; i++) {
		locatest[i] = graph[v][i];
		mst[i] = v;
	}
	mst[v] = 0;
	locatest[v] = 0;
	for (int i = 2; i <= n; i++) {
		int minx = INFINE;
		int minid = 0;
		for (int k = 1; k <= n; k++) {
			if (locatest[k] != 0 && locatest[k] < minx) {
				minx = locatest[k];
				minid = k;
			}
		}
        char start = 'A' + mst[minid]-1;
        char end = 'A' + minid-1;
		cout << "V" << start << "-" << "V" << end << " = " << minx << endl;
		locatest[minid] = 0;
		sum += minx;
		for (int i = 1; i <= n; i++) {
			if ( graph[minid][i] < locatest[i]) {
				locatest[i] = graph[minid][i];
				mst[i] = minid;
			}
		}
	}
	cout << sum << endl;
	return;
}


void CreateGraph() {
    ifstream in("graph.txt");
    cin.rdbuf(in.rdbuf());

	cin >> vertexnum >> arcnum;//输入点的个数，边的条数

	for (int i = 1; i <= vertexnum; i++)
		for (int j = 1; j <= vertexnum; j++)
			graph[i][j] = INFINE;
	for (int i = 1; i <= arcnum; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		graph[a][b] = w;//无向图,故两边都要赋值
		graph[b][a] = w;
	}
}

int main() {
	CreateGraph();
	Prim(8, vertexnum);//以点1为最小生成树的起点
	return 0;
}
