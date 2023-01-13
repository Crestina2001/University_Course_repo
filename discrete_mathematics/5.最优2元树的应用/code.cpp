#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<fstream>
using namespace std;

typedef struct HTNode
{
	int weight;
	int parent, lc, rc;
	char ch;
	HTNode() :weight(0), parent(0), lc(0), rc(0), ch('\0') {};
}*HuffmanTree;
typedef string* HuffmanCode;

/*********************************************************************
函数名：Select
形式参数：HuffmanTree(HTNode*), int,int&, int&
返回值：无
函数作用：从没有父母的节点中选出权值最小的两个节点
函数说明：HuffmanTree传入Huffman树的首地址，n是搜寻的最大范围，s1与s2通
过引用方式传入，在函数中修改，s1与s2分别储存Huffman树最小和次小权值的节
点的数组下标。如果有多个最小节点，s1储存第一个最小节点，s2储存第二个最
小节点；如果有多个次小节点，s2储存第一个次小节点。
**********************************************************************/
void Select(HuffmanTree HT, int n, int& s1, int& s2)
{
	//s1与s2初始化
	s1 = -1, s2 = -1;
	//将最小和次小的节点分别赋值给s1和s2
	for (int i = 0; i < n; ++i)
	{
		if (HT[i].parent)continue;
		if (s1 == -1)
			s1 = i;
		else if (s2 == -1)
		{
			if (HT[i].weight < HT[s1].weight)
			{
				s2 = s1;
				s1 = i;
			}
			else
				s2 = i;
		}
		else
		{
			if (HT[i].weight < HT[s1].weight)
			{
				s2 = s1;
				s1 = i;
			}
			else if (HT[i].weight < HT[s2].weight)
				s2 = i;
		}
	}

}
/*********************************************************************
函数名：HuffmanCoding
形式参数：HuffmanTree&(HTNode*&), HuffmanCode&(string*&), int *, int
返回值：无
函数作用：根据各ASCII码出现的频率进行Huffman编码
函数说明：W中存放文本中各ASCII码出现的频率，该函数对其进行编码，HT是编
码后得到的Huffman树，而HC存放各字符的Huffman码，其数组下标就是该Huffman
码对应的ASCII码。n为默认参数，默认值为ASCII码总量，代表求出n个字符的
Huffman编码。
**********************************************************************/
void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int* W, int n)
{
	//m是Huffman树的大小
	int m = 2 * n - 1;
	//给HT分配m的大小空间
	HT = new HTNode[m];
	HuffmanTree p = HT;
	//给Huffman树的叶子节点赋初值
	for (int i = 0; i < n; ++i, ++p, ++W)
	{
		p->weight = *W;
		p->ch = char(i);
	}
	//建立Huffman树
	for (int i = n; i < m; ++i)
	{
		//选出最小和次小的位置
		int s1, s2;
		Select(HT, i, s1, s2);
		//将s1与s2合并成一棵树
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lc = s1; HT[i].rc = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//给HC分配n的大小空间
	HC = new string[n];
	//将编码值存入HC
	for (int i = 0; i < n; ++i)
	{
		string s;
		int c = i;
		for (int f = HT[i].parent; f; c = f, f = HT[f].parent)
			if (HT[f].lc == c)s = "1" + s;//是左儿子
			else s = "0" + s;//是右儿子
		HC[i] = s;
	}
}

//暂停，待用户输入
void Suspend()
{
	string dump; getline(cin, dump);
	printf("\n\n\nPress enter to continue...\n");
	getchar();
}

int main()
{
	//储存各个字符出现的数目
	int w[130];
	int tot = 0;
	//统计频率
	int n;
	cout << "请输入节点个数(必须是大于1的正整数):";
	cin >> n;
	cout << "请输入节点(以空格分隔):";
	for (int i = 0; i < n; i++)
		cin >> w[i];
	HuffmanTree HT;
	HuffmanCode HC;
	//建立Huffman树和Huffman Code静态数组
	HuffmanCoding(HT, HC, w, n);
	//输出Huffman编码
	cout << "Huffman编码如下：" << endl;
	for (int i = 0; i < n; ++i)
		cout <<w[i]<<": "<< HC[i] << endl;
	cout << endl;
	Suspend();
	return 0;
}
