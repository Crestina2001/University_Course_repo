#include<algorithm>
#include<iostream>
#include<string>
#include<cstdio>

using namespace std;
//函数预申明
int readInt(bool (*)(int)=NULL);
bool range(int );
void Suspend();
//十字链表结构体，存储图的边
struct EBox
{
	//存储边的两个节点
	int ivex, jvex;
	//存储边的长度
	int len;
	//用于sort的参数
	bool operator<(const EBox E) { return len < E.len; }
};
//图类
class Graph
{
private:
	EBox* Arcs;
	int* parent;
	int vexnum, arcnum;
	int find(int );
	void merge(int , int );
public:
	Graph();
	
	~Graph() { delete[]Arcs; delete[]parent; }
	void Kruskal();
};
int main()
{
	Graph G;
	G.Kruskal();
	Suspend();
	return 0;
}


/*************************************************************************************
函数名：find
形式参数：int
返回值：int
身份:Graph类内私有函数
函数作用：查找两个元素是否在同一个并查集内
*************************************************************************************/
int Graph:: find(int x)
{
	if (x == parent[x])return x;
	return parent[x] = find(parent[x]);
}

/*************************************************************************************
函数名：merge
形式参数：int,int
返回值：五
身份:Graph类内私有函数
函数作用：合并两个并查集
*************************************************************************************/
void Graph:: merge(int x, int y)
{
	int m = find(x), n = find(y);
	parent[m] = find(n);
}

/*************************************************************************************
函数名：Graph
形式参数：无
身份:Graph类的无参构造函数
函数作用：构造Graph类并且读入数据
*************************************************************************************/
Graph:: Graph()
{
	printf("请输入顶点数和边数：\n");
	vexnum = readInt(range), arcnum = readInt(range);
	Arcs = new EBox[arcnum], parent = new int[vexnum + 1];
	for (int i = 1; i <= vexnum; ++i)parent[i] = i;
	printf("已经自动为顶点从 1 到 %d 编号！\n", vexnum);
	printf("请输入顶点的序号和它们的权值(应该为正数）：\n");
	for (int i = 0; i < arcnum; ++i)
	{
		//读入i顶点并进行检查
		while ((Arcs[i].ivex = readInt(range)) > vexnum)printf("输入顶点不存在！\n");
		//读入j顶点并进行检查
		while ((Arcs[i].jvex = readInt(range)) > vexnum)printf("输入顶点不存在！\n");
		Arcs[i].len = readInt(range);
	}
}

/*************************************************************************************
函数名：Kruskal
形式参数：无
返回值：无
身份:Graph类内公有函数
函数作用：通过Kruskal算法求出最小生成树
*************************************************************************************/
void Graph:: Kruskal()
{
	int added_edge = 0, //代表已经加入最小生成树的边的数量
		len = 0;
	//通过边的权值，将边从小到大进行排序
	sort(Arcs, Arcs + arcnum);
	for (int i = 0; i < arcnum && added_edge < vexnum - 1; ++i)
	{
		//如果一条边的两个顶点不在同一个并查集内，则将其加入最小生成树不会生成环
		if (find(Arcs[i].ivex) != find(Arcs[i].jvex))
		{
			//将两个顶点合并
			merge(Arcs[i].ivex, Arcs[i].jvex);
			++added_edge;
			len += Arcs[i].len;
			cout << Arcs[i].ivex << "--" << Arcs[i].len << "--" << Arcs[i].jvex << endl;
		}
	}
	if (added_edge < vexnum - 1)printf("该图不连通！\n");
	else printf("最小生成树的长度最小值为%d\n", len);
}

//读入检查
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

//读入数据范围
bool range(int n) { return n > 0; }

//暂停，待用户输入
void Suspend()
{
	string dump; getline(cin, dump);
	printf("\n\n\nPress enter to continue...\n");
	getchar();
}

