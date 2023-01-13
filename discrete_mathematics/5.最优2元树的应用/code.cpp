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
��������Select
��ʽ������HuffmanTree(HTNode*), int,int&, int&
����ֵ����
�������ã���û�и�ĸ�Ľڵ���ѡ��Ȩֵ��С�������ڵ�
����˵����HuffmanTree����Huffman�����׵�ַ��n����Ѱ�����Χ��s1��s2ͨ
�����÷�ʽ���룬�ں������޸ģ�s1��s2�ֱ𴢴�Huffman����С�ʹ�СȨֵ�Ľ�
��������±ꡣ����ж����С�ڵ㣬s1�����һ����С�ڵ㣬s2����ڶ�����
С�ڵ㣻����ж����С�ڵ㣬s2�����һ����С�ڵ㡣
**********************************************************************/
void Select(HuffmanTree HT, int n, int& s1, int& s2)
{
	//s1��s2��ʼ��
	s1 = -1, s2 = -1;
	//����С�ʹ�С�Ľڵ�ֱ�ֵ��s1��s2
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
��������HuffmanCoding
��ʽ������HuffmanTree&(HTNode*&), HuffmanCode&(string*&), int *, int
����ֵ����
�������ã����ݸ�ASCII����ֵ�Ƶ�ʽ���Huffman����
����˵����W�д���ı��и�ASCII����ֵ�Ƶ�ʣ��ú���������б��룬HT�Ǳ�
���õ���Huffman������HC��Ÿ��ַ���Huffman�룬�������±���Ǹ�Huffman
���Ӧ��ASCII�롣nΪĬ�ϲ�����Ĭ��ֵΪASCII���������������n���ַ���
Huffman���롣
**********************************************************************/
void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int* W, int n)
{
	//m��Huffman���Ĵ�С
	int m = 2 * n - 1;
	//��HT����m�Ĵ�С�ռ�
	HT = new HTNode[m];
	HuffmanTree p = HT;
	//��Huffman����Ҷ�ӽڵ㸳��ֵ
	for (int i = 0; i < n; ++i, ++p, ++W)
	{
		p->weight = *W;
		p->ch = char(i);
	}
	//����Huffman��
	for (int i = n; i < m; ++i)
	{
		//ѡ����С�ʹ�С��λ��
		int s1, s2;
		Select(HT, i, s1, s2);
		//��s1��s2�ϲ���һ����
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lc = s1; HT[i].rc = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//��HC����n�Ĵ�С�ռ�
	HC = new string[n];
	//������ֵ����HC
	for (int i = 0; i < n; ++i)
	{
		string s;
		int c = i;
		for (int f = HT[i].parent; f; c = f, f = HT[f].parent)
			if (HT[f].lc == c)s = "1" + s;//�������
			else s = "0" + s;//���Ҷ���
		HC[i] = s;
	}
}

//��ͣ�����û�����
void Suspend()
{
	string dump; getline(cin, dump);
	printf("\n\n\nPress enter to continue...\n");
	getchar();
}

int main()
{
	//��������ַ����ֵ���Ŀ
	int w[130];
	int tot = 0;
	//ͳ��Ƶ��
	int n;
	cout << "������ڵ����(�����Ǵ���1��������):";
	cin >> n;
	cout << "������ڵ�(�Կո�ָ�):";
	for (int i = 0; i < n; i++)
		cin >> w[i];
	HuffmanTree HT;
	HuffmanCode HC;
	//����Huffman����Huffman Code��̬����
	HuffmanCoding(HT, HC, w, n);
	//���Huffman����
	cout << "Huffman�������£�" << endl;
	for (int i = 0; i < n; ++i)
		cout <<w[i]<<": "<< HC[i] << endl;
	cout << endl;
	Suspend();
	return 0;
}
