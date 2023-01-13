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
	char *vexs;				//һά����
	int *arcs;				//��ά����
	closedge* close;
	int vexnum, arcnum;
	int MIN(int a, int b) { return a < b ? a : b; }
public:
	int LocateVex(char u) { for (int i = 0; i < vexnum; ++i)if (u == vexs[i])return i; printf("�Ҳ�������%c!\n",u); return -1; }
	Graph()
	{
		printf("�����붥������\t");
		vexnum = readInt(range);
		vexs = new char[vexnum];
		close = new closedge[vexnum];
		arcs = new int[vexnum * vexnum];
		for (int i = 0; i < vexnum * vexnum; ++i)arcs[i] = INFINITY;
		printf("���������붥������ƣ��õ��ַ���ʾ����\n");
		for (int i = 0; i < vexnum; ++i) { cin>>vexs[i]; }
		printf("�����������\t");
		arcnum = readInt(range);
		for (int k = 0; k < arcnum; ++k)
		{
			printf("���������������Լ��ߵĳ��ȣ�");
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
			if (i == j)printf("���棺�����Ի���\n");
			int len= readInt(range);
			if (arcs[i * vexnum + j] < len)
			{
				printf("\n�ظ����붥��%c��%c����ȡ���б��г��ȵ���С��\n\n",vexs[i],vexs[j]);
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
		printf("�������ʼ���㣺\t");
		cin >> u;
		int k = LocateVex(u);
		for (int j = 0; j < vexnum; ++j)
			if (j != k) close[j] = { u,arcs[k * vexnum + j] };
		close[k].lowcost = 0;
		for (int i = 1; i < vexnum; ++i)
		{
			int k = -1, MIN = INFINITY;
			for (int j = 0; j < vexnum; ++j)if (close[j].lowcost && close[j].lowcost < MIN)k = j, MIN = close[j].lowcost;
			if (k==-1) { printf("ͼ����ͨ��\n"); break; }
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
	printf("**                  �������ģ��ϵͳ                  **\n");
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
			cout << "�����ʽ����\n";
			cin.clear();
			char* ch = new char[1000];
			cin.getline(ch, 1000);
			delete[]ch;
		}
		else if (range && !range(n))
		{
			cout << "���ݷ�Χ����\n";
		}
		else break;
	}
	return n;
}
bool range(int n) { return n > 0; }
