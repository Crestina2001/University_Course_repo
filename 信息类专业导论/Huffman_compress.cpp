#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<string>
#include<cstring>
#include<fstream>
using namespace std;
const int N_CHAR = 127;
typedef unsigned char uchar;
typedef struct HTNode
{
	int weight;
	int parent, lc, rc;
	char ch;
	HTNode() :weight(0), parent(0), lc(0), rc(0), ch('\0') {};
}*HuffmanTree;
typedef string* HuffmanCode;
char *passage;
//��ͣ�˳����� 
void suspend()
{
	printf("\n\n\nPlease press enter to continue:\n");
	getchar();
}
//��ȡ�ļ���С�ĺ��� 
int getFileSize(const char* file_name){
	ifstream in(file_name);
	in.seekg(0, std::ios::end);
	int size = in.tellg();
	in.close();
	return size; //��λ�ǣ�byte
}
/*********************************************************************
��������getFrequency
��ʽ������const char*,int *,int&
����ֵ����
�������ã�ͳ���ı��и��ַ����ֵ�Ƶ��
����˵������ʽ����filename��Ҫͳ�Ƶ��ı���Wͨ��ָ�����ʽ���룬�ں�����
�����޸ģ������ASCII���ַ����ֵ�Ƶ�ʣ�totͨ�����õ���ʽ���룬�ں�����
�����޸ģ������ı��ĳ���
**********************************************************************/
void getFrequency(const char* fileName, int* W, int& tot)
{
	//Ϊpassage����ռ� 
	int len=getFileSize(fileName);
	passage=new char[len]; 
	//���ļ�
	ifstream in(fileName);
	//�쳣����
	if (!in)
	{
		cout << "Ҫѹ�����ļ������ڣ������쳣�˳���";
		exit(-1);
	}
	//��W��������
	for (int i = 0; i < N_CHAR; ++i)W[i] = 0;
	char ch; 
	//ͳ�Ƹ��ַ����ֵ�Ƶ��
	while (1)
	{
		ch = in.get();
		if (ch == EOF)break;
		if(int(ch)>=128||int(ch)<1)
		{
			cout<<"������ascii���ַ����쳣�˳���\n";
			suspend();
			exit(-1);
		}
		passage[tot++] = ch;
		++W[int(ch)];
	}
	//�ر��ļ�
	in.close();
}
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
void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int* W, int n = N_CHAR)
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
			if (HT[f].lc == c)s = "0" + s;//�������
			else s = "1" + s;//���Ҷ���
		HC[i] = s;
	}
}
/*********************************************************************
��������string2num
��ʽ������string
����ֵ��int
�������ã���Huffman�����string��ʽת����int��ʽ
����˵����s�д��string��ʽ��Huffman���룬ͨ���������������ת�������
�����Ʊ����Ӧ��ʮ���ƣ����ҷ������ʮ���ƵĽ��
**********************************************************************/
int string2num(string s)
{
	//���صĽ��
	int res = 0;
	//�����Ӧ��ʮ����
	for (int i = 0; i < s.size(); ++i)
	{
		res = s[i] - '0' + (res << 1);
	}
	return res;
}
/*********************************************************************
��������compress
��ʽ������HuffmanCode��string*), int, int&
����ֵ����
�������ã����ı�����ѹ�������ҽ�ѹ���Ľ�����ڡ�compressed.txt"�ļ���
����˵����HC�д��Huffman Code��tot�д����ļ��Ĵ�С�����ʹ�ö����Ʒ�ʽ
д���ļ���writen�����ñ������ں������޸���ֵ��������ѹ��������д��ѹ��
�ļ����ַ�����
**********************************************************************/
void compress(HuffmanCode HC, int tot,int &writen)
{
	cout << "ѹ����..." << endl;
	writen = 0;
	//s�д�ű��봮
	string s;
	ofstream out("compressed.txt", ios::binary);
	//�쳣���
	if (!out)
	{
		cout << "�޷�����ѹ���ļ����쳣�˳���";
		exit(-1);
	}
	//�߱����д���ļ�
	for (int i = 0; i < tot;++i )
	{
		s += HC[int(passage[i])];
		while (s.size() >= 8)
		{
			//ucharΪunsigned char�����ڱ��������ĸ�п�����1������ʹ��unsigned char
			uchar to_write = uchar(string2num(s.substr(0, 8)));
			out.write((char*)&to_write, sizeof(to_write));
			s = s.substr(8);
			++writen;
		}
		
	}
	//������һ��Huffman�볤��С��8��ĩλ��0д��
	//����պý����еı��붼д���ļ���sΪ�գ�����д��
	if (s.size())
	{
		while (s.size() < 8)s += '0';
		uchar to_write = uchar(string2num(s));
		out.write((char*)&to_write, sizeof(to_write));
		++writen;
	}
	cout << "ѹ����ɣ�" << endl;
	//�ر��ļ�
	out.close();
}
/*********************************************************************
��������char2bool
��ʽ������uchar(unsigned char)
����ֵ��string
�������ã�����ѹ���ļ��ж�����޷����ַ�ת��Ϊ���Ӧ��Huffman Code
����˵������ʽ�����Ǵ�ѹ���ļ��ж�����޷����ַ�������ת��ΪHuffman����
���Ҵ������ַ����У����ظ��ַ�����
**********************************************************************/
string char2bool(uchar ch)
{
	//��unsigned charת��������
	int n = int(ch);
	//���صĽ��
	string res;
	//ת���Ĺ���
	while (n)
	{
		res = char(n % 2 + '0') + res;
		n /= 2;
	}
	//�������8λ������λ��0
	while (res.size() < 8)res = '0' + res;
	return res;
}
/*********************************************************************
��������findRoot
��ʽ������HuffmanTree(HTNode*), int
����ֵ��int
�������ã����ع��������ĸ��ڵ�
**********************************************************************/
int findRoot(HuffmanTree HT, int n = N_CHAR)
{
	//Huffman���Ĵ�С
	int m = 2 * n - 1;
	int root = 0;
	//�ҵ�Ȩֵ���Ľڵ㣬�����ڵ�
	for (int i = n; i < m; ++i)
		if (HT[root].weight < HT[i].weight)
			root = i;
	//���ظ��ڵ�
	return root;
}
/*********************************************************************
��������getMaxHC
��ʽ������HuffmanCode(string*), int
����ֵ��int
�������ã�����Huffman�������󳤶�
**********************************************************************/
int getMaxHC(HuffmanCode HC, int n = N_CHAR)
{
	int maxi = -1;
	for (int i = 0; i < n; ++i)maxi = max(maxi, int(HC[i].size()));
	return maxi;
}
/*********************************************************************
��������decompress
��ʽ������const char*,HuffmanTree(HTNode*),int ,int ,int
����ֵ����
�������ã����н�ѹ��
����˵����FileName�д���ѹ���ļ������֣�HT�д���Huffman�����׵�ַ��tot
�д���ԭ�ļ��ĳ��ȣ�maxHC���������볤�ȣ�writen�д���ѹ���ļ��ĳ��ȡ�
**********************************************************************/
void decompress(const char* FileName, HuffmanTree HT, int tot, int maxHC,int writen)
{
	cout << "��ѹ����..." << endl;
	ifstream in(FileName, ios::binary);
	if (!in)
	{
		cout << "�޷���ѹ���ļ����쳣�˳���";
		suspend();
		exit(-1);
	}
	ofstream out("decompressed.txt");
	if (!out)
	{
		cout << "�޷�������ѹ���ļ����쳣�˳���";
		suspend();
		exit(-1);
	}
	//�������ı��봮
	string s;
	//�ҵ�Huffman���ĸ��ڵ�
	int root = findRoot(HT);
	//�߶��������
	while (tot)
	{
		uchar ch;
		//writen����ѹ���ļ��Ĵ�С
		if (writen--)
		{
			in.read((char*)&ch, sizeof(ch));
			s = s + char2bool(ch);
		}
		//������뻹û�н������Ҷ���������ߵ�ǰ���봮��С����Huffman�������󳤶�
		//��ʼд���ѹ���ļ�
		while (tot && (!writen || s.size() > maxHC))
		{
			int i;
			int p = root;
			for (i = 0; HT[p].ch == '\0'; ++i)
			{
				if (s[i] == '0')p = HT[p].lc;
				else p = HT[p].rc;
			}
			out.put(HT[p].ch);
			--tot;
			s = s.substr(i);
		}
	}
	//�ر��ļ�
	in.close();
	out.close();
	cout << "��ѹ����ϣ�" << endl;
}
//��չʾ���У��Ʊ��ո������ֲ��ɼ����������⴦��
inline bool isdisplay(int* w,int i)
{
	if (!w[i])return 0;
	switch (i)
	{
		case int('\n') : cout << "���з�" << ' ';
			break;
		case int('\t') : cout << "�Ʊ��" << ' ';;
			break;
		case int(' ') : cout << "�ո��" << ' ';
			break;
		default:cout << char(i) << ' ';
	}
	return 1;
}
int main()
{
	printf("����to_compress.txt�ļ�������Ҫѹ�������ݣ������в��ܰ�����ascii���ַ���\n"); 
	//��������ַ����ֵ���Ŀ
	int w[130];
	int tot = 0;
	//ͳ��Ƶ��
	getFrequency("to_compress.txt", w, tot);
	//���ͳ��Ƶ��
	cout << "���ı��г��ֵ��ַ�Ƶ��ͳ�ƣ�" << endl;
	for (int i = 0; i < N_CHAR; ++i)
		if (isdisplay(w,i))cout << w[i] << endl;
	cout << endl;
	HuffmanTree HT;
	HuffmanCode HC;
	//����Huffman����Huffman Code��̬����
	HuffmanCoding(HT, HC, w);
	int maxHC = getMaxHC(HC);
	//���Huffman����
	cout << "���ı��г��ֵ��ַ���Huffman�������£�" << endl;
	for (int i = 0; i < N_CHAR; ++i)
		if (isdisplay(w,i))cout << HC[i] << endl;
	cout << endl;
	int writen;
	//ѹ��
	compress(HC, tot,writen);
	cout << endl;
	//��ѹ��
	decompress("compressed.txt", HT, tot, maxHC,writen);
	suspend();
	delete[]passage;//�ջ�����ռ� 
	return 0;
}
