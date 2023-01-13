#include<iostream>
#include<cstdio>
#include<string>
#include<stdlib.h>
using namespace std;
#define INFINITY (1<<31)-1
int readInt(bool (*range)(int) = NULL);
bool range(int);
struct closedge
{
	char adjvex;
	int lowcost;
};
class Graph
{
private:
	char *vexs;				//一维数组
	int *arcs;				//二维数组
	closedge* close;
	int vexnum, arcnum;
	int MIN(int a, int b) { return a < b ? a : b; }
public:
	int LocateVex(char u) { for (int i = 0; i < vexnum; ++i)if (u == vexs[i])return i; printf("找不到顶点%c!\n",u); return -1; }
	Graph()
	{
		printf("请输入顶点数：\t");
		vexnum = readInt(range);
		vexs = new char[vexnum];
		close = new closedge[vexnum];
		arcs = new int[vexnum * vexnum];
		for (int i = 0; i < vexnum * vexnum; ++i)arcs[i] = INFINITY;
		printf("请依次输入顶点的名称（用单字符表示）：\n");
		for (int i = 0; i < vexnum; ++i) { cin>>vexs[i]; }
		printf("请输入边数：\t");
		arcnum = readInt(range);
		for (int k = 0; k < arcnum; ++k)
		{
			printf("请输入两个顶点以及边的长度：");
			char v1, v2;
			int i, j;
			do
			{
				cin >> v1;
				i = LocateVex(v1);
			} while (i == -1);
			do
			{
				cin >> v2;
				j = LocateVex(v2);
			} while (j == -1);
			if (i == j)printf("警告：输入自环！\n");
			int len= readInt(range);
			if (arcs[i * vexnum + j] < len)
			{
				printf("\n重复输入顶点%c与%c，已取所有边中长度的最小者\n\n",vexs[i],vexs[j]);
			}
			arcs[j * vexnum + i] = arcs[i * vexnum + j] = MIN(arcs[i * vexnum + j], len);
		}
	}
	Graph(const Graph& G) :vexnum(G.vexnum), arcnum(G.arcnum)
	{
		vexs = new char[vexnum];
		arcs = new int[vexnum * vexnum];
		close = new closedge[vexnum];
		for (int i = 0; i < vexnum; ++i) { vexs[i] = G.vexs[i];  }
		for (int i = 0; i < vexnum * vexnum; ++i)arcs[i] = G.arcs[i];
	}
	void MiniSpanTree_Prim()
	{
		char u;
		printf("请输入初始顶点：\t");
		cin >> u;
		int k = LocateVex(u);
		for (int j = 0; j < vexnum; ++j)
			if (j != k) close[j] = { u,arcs[k * vexnum + j] };
		close[k].lowcost = 0;
		for (int i = 1; i < vexnum; ++i)
		{
			int k = -1, MIN = INFINITY;
			for (int j = 0; j < vexnum; ++j)if (close[j].lowcost && close[j].lowcost < MIN)k = j, MIN = close[j].lowcost;
			if (k==-1) { printf("图不连通！\n"); break; }
			//cout << vexs[k] << endl;
			printf("%c--<%d>--%c\n", close[k].adjvex, close[k].lowcost, vexs[k]);
			close[k].lowcost = 0;
			for (int j = 0; j < vexnum; ++j)
				if (arcs[k * vexnum + j] < close[j].lowcost)close[j] = { vexs[k],arcs[k * vexnum + j] };
		}
	}
};

void printHead();
void program_concluding();
int main()
{
	printHead();
	Graph G;
	G.MiniSpanTree_Prim();
	program_concluding();
	return 0;
}
void printHead()
{
	printf("**                  电网造价模拟系统                  **\n");
	printf("********************************************************\n\n");
}
void program_concluding()
{
	string dump;
	getline(cin, dump);
	printf("Press enter to continue...");
	getchar();
}
int readInt(bool (*range)(int))
{
	int n;
	while (1)
	{
		cin >> n;
		if (cin.fail())
		{
			cout << "输入格式有误！\n";
			cin.clear();
			char* ch = new char[1000];
			cin.getline(ch, 1000);
			delete[]ch;
		}
		else if (range && !range(n))
		{
			cout << "数据范围有误！\n";
		}
		else break;
	}
	return n;
}
bool range(int n) { return n > 0; }
