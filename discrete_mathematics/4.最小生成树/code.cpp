#include<algorithm>
#include<iostream>
#include<string>
#include<cstdio>

using namespace std;
//����Ԥ����
int readInt(bool (*)(int)=NULL);
bool range(int );
void Suspend();
//ʮ������ṹ�壬�洢ͼ�ı�
struct EBox
{
	//�洢�ߵ������ڵ�
	int ivex, jvex;
	//�洢�ߵĳ���
	int len;
	//����sort�Ĳ���
	bool operator<(const EBox E) { return len < E.len; }
};
//ͼ��
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
��������find
��ʽ������int
����ֵ��int
���:Graph����˽�к���
�������ã���������Ԫ���Ƿ���ͬһ�����鼯��
*************************************************************************************/
int Graph:: find(int x)
{
	if (x == parent[x])return x;
	return parent[x] = find(parent[x]);
}

/*************************************************************************************
��������merge
��ʽ������int,int
����ֵ����
���:Graph����˽�к���
�������ã��ϲ��������鼯
*************************************************************************************/
void Graph:: merge(int x, int y)
{
	int m = find(x), n = find(y);
	parent[m] = find(n);
}

/*************************************************************************************
��������Graph
��ʽ��������
���:Graph����޲ι��캯��
�������ã�����Graph�ಢ�Ҷ�������
*************************************************************************************/
Graph:: Graph()
{
	printf("�����붥�����ͱ�����\n");
	vexnum = readInt(range), arcnum = readInt(range);
	Arcs = new EBox[arcnum], parent = new int[vexnum + 1];
	for (int i = 1; i <= vexnum; ++i)parent[i] = i;
	printf("�Ѿ��Զ�Ϊ����� 1 �� %d ��ţ�\n", vexnum);
	printf("�����붥�����ź����ǵ�Ȩֵ(Ӧ��Ϊ��������\n");
	for (int i = 0; i < arcnum; ++i)
	{
		//����i���㲢���м��
		while ((Arcs[i].ivex = readInt(range)) > vexnum)printf("���붥�㲻���ڣ�\n");
		//����j���㲢���м��
		while ((Arcs[i].jvex = readInt(range)) > vexnum)printf("���붥�㲻���ڣ�\n");
		Arcs[i].len = readInt(range);
	}
}

/*************************************************************************************
��������Kruskal
��ʽ��������
����ֵ����
���:Graph���ڹ��к���
�������ã�ͨ��Kruskal�㷨�����С������
*************************************************************************************/
void Graph:: Kruskal()
{
	int added_edge = 0, //�����Ѿ�������С�������ıߵ�����
		len = 0;
	//ͨ���ߵ�Ȩֵ�����ߴ�С�����������
	sort(Arcs, Arcs + arcnum);
	for (int i = 0; i < arcnum && added_edge < vexnum - 1; ++i)
	{
		//���һ���ߵ��������㲻��ͬһ�����鼯�ڣ����������С�������������ɻ�
		if (find(Arcs[i].ivex) != find(Arcs[i].jvex))
		{
			//����������ϲ�
			merge(Arcs[i].ivex, Arcs[i].jvex);
			++added_edge;
			len += Arcs[i].len;
			cout << Arcs[i].ivex << "--" << Arcs[i].len << "--" << Arcs[i].jvex << endl;
		}
	}
	if (added_edge < vexnum - 1)printf("��ͼ����ͨ��\n");
	else printf("��С�������ĳ�����СֵΪ%d\n", len);
}

//������
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

//�������ݷ�Χ
bool range(int n) { return n > 0; }

//��ͣ�����û�����
void Suspend()
{
	string dump; getline(cin, dump);
	printf("\n\n\nPress enter to continue...\n");
	getchar();
}

