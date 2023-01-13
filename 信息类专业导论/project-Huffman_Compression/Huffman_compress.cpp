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
//暂停退出函数 
void suspend()
{
	printf("\n\n\nPlease press enter to continue:\n");
	getchar();
}
//获取文件大小的函数 
int getFileSize(const char* file_name){
	ifstream in(file_name);
	in.seekg(0, std::ios::end);
	int size = in.tellg();
	in.close();
	return size; //单位是：byte
}
/*********************************************************************
函数名：getFrequency
形式参数：const char*,int *,int&
返回值：无
函数作用：统计文本中各字符出现的频率
函数说明：形式参数filename是要统计的文本，W通过指针的形式传入，在函数中
进行修改，储存各ASCII码字符出现的频率，tot通过引用的形式传入，在函数中
进行修改，储存文本的长度
**********************************************************************/
void getFrequency(const char* fileName, int* W, int& tot)
{
	//为passage申请空间 
	int len=getFileSize(fileName);
	passage=new char[len]; 
	//打开文件
	ifstream in(fileName);
	//异常处理
	if (!in)
	{
		cout << "要压缩的文件不存在，程序异常退出！";
		exit(-1);
	}
	//将W数组置零
	for (int i = 0; i < N_CHAR; ++i)W[i] = 0;
	char ch; 
	//统计各字符出现的频率
	while (1)
	{
		ch = in.get();
		if (ch == EOF)break;
		if(int(ch)>=128||int(ch)<1)
		{
			cout<<"包含非ascii码字符！异常退出！\n";
			suspend();
			exit(-1);
		}
		passage[tot++] = ch;
		++W[int(ch)];
	}
	//关闭文件
	in.close();
}
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
void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int* W, int n = N_CHAR)
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
			if (HT[f].lc == c)s = "0" + s;//是左儿子
			else s = "1" + s;//是右儿子
		HC[i] = s;
	}
}
/*********************************************************************
函数名：string2num
形式参数：string
返回值：int
函数作用：将Huffman编码从string形式转换成int形式
函数说明：s中存放string形式的Huffman编码，通过这个函数，将其转换成这个
二进制编码对应的十进制，并且返回这个十进制的结果
**********************************************************************/
int string2num(string s)
{
	//返回的结果
	int res = 0;
	//计算对应的十进制
	for (int i = 0; i < s.size(); ++i)
	{
		res = s[i] - '0' + (res << 1);
	}
	return res;
}
/*********************************************************************
函数名：compress
形式参数：HuffmanCode（string*), int, int&
返回值：无
函数作用：对文本进行压缩，并且将压缩的结果存于“compressed.txt"文件中
函数说明：HC中存放Huffman Code，tot中储存文件的大小，最后使用二进制方式
写入文件；writen是引用变量，在函数中修改其值，储存在压缩过程中写入压缩
文件的字符数。
**********************************************************************/
void compress(HuffmanCode HC, int tot,int &writen)
{
	cout << "压缩中..." << endl;
	writen = 0;
	//s中存放编码串
	string s;
	ofstream out("compressed.txt", ios::binary);
	//异常检测
	if (!out)
	{
		cout << "无法生成压缩文件，异常退出！";
		exit(-1);
	}
	//边编码边写入文件
	for (int i = 0; i < tot;++i )
	{
		s += HC[int(passage[i])];
		while (s.size() >= 8)
		{
			//uchar为unsigned char，由于编码的首字母有可能是1，所以使用unsigned char
			uchar to_write = uchar(string2num(s.substr(0, 8)));
			out.write((char*)&to_write, sizeof(to_write));
			s = s.substr(8);
			++writen;
		}
		
	}
	//如果最后一个Huffman码长度小于8，末位补0写入
	//如果刚好将所有的编码都写入文件，s为空，则不再写入
	if (s.size())
	{
		while (s.size() < 8)s += '0';
		uchar to_write = uchar(string2num(s));
		out.write((char*)&to_write, sizeof(to_write));
		++writen;
	}
	cout << "压缩完成！" << endl;
	//关闭文件
	out.close();
}
/*********************************************************************
函数名：char2bool
形式参数：uchar(unsigned char)
返回值：string
函数作用：将从压缩文件中读入的无符号字符转化为其对应的Huffman Code
函数说明：形式参数是从压缩文件中读入的无符号字符，将其转化为Huffman编码
并且储存在字符串中，返回该字符串。
**********************************************************************/
string char2bool(uchar ch)
{
	//将unsigned char转化成整型
	int n = int(ch);
	//返回的结果
	string res;
	//转换的过程
	while (n)
	{
		res = char(n % 2 + '0') + res;
		n /= 2;
	}
	//如果不足8位，在首位补0
	while (res.size() < 8)res = '0' + res;
	return res;
}
/*********************************************************************
函数名：findRoot
形式参数：HuffmanTree(HTNode*), int
返回值：int
函数作用：返回哈夫曼树的根节点
**********************************************************************/
int findRoot(HuffmanTree HT, int n = N_CHAR)
{
	//Huffman树的大小
	int m = 2 * n - 1;
	int root = 0;
	//找到权值最大的节点，即根节点
	for (int i = n; i < m; ++i)
		if (HT[root].weight < HT[i].weight)
			root = i;
	//返回根节点
	return root;
}
/*********************************************************************
函数名：getMaxHC
形式参数：HuffmanCode(string*), int
返回值：int
函数作用：返回Huffman编码的最大长度
**********************************************************************/
int getMaxHC(HuffmanCode HC, int n = N_CHAR)
{
	int maxi = -1;
	for (int i = 0; i < n; ++i)maxi = max(maxi, int(HC[i].size()));
	return maxi;
}
/*********************************************************************
函数名：decompress
形式参数：const char*,HuffmanTree(HTNode*),int ,int ,int
返回值：无
函数作用：进行解压缩
函数说明：FileName中储存压缩文件的名字，HT中储存Huffman树的首地址，tot
中储存原文件的长度，maxHC储存最大编码长度，writen中储存压缩文件的长度。
**********************************************************************/
void decompress(const char* FileName, HuffmanTree HT, int tot, int maxHC,int writen)
{
	cout << "解压缩中..." << endl;
	ifstream in(FileName, ios::binary);
	if (!in)
	{
		cout << "无法打开压缩文件，异常退出！";
		suspend();
		exit(-1);
	}
	ofstream out("decompressed.txt");
	if (!out)
	{
		cout << "无法创建解压缩文件，异常退出！";
		suspend();
		exit(-1);
	}
	//储存待译的编码串
	string s;
	//找到Huffman树的根节点
	int root = findRoot(HT);
	//边读入边译码
	while (tot)
	{
		uchar ch;
		//writen代表压缩文件的大小
		if (writen--)
		{
			in.read((char*)&ch, sizeof(ch));
			s = s + char2bool(ch);
		}
		//如果译码还没有结束并且读入结束或者当前编码串大小大于Huffman编码的最大长度
		//开始写入解压缩文件
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
	//关闭文件
	in.close();
	out.close();
	cout << "解压缩完毕！" << endl;
}
//对展示换行，制表，空格这三种不可见符号做特殊处理
inline bool isdisplay(int* w,int i)
{
	if (!w[i])return 0;
	switch (i)
	{
		case int('\n') : cout << "换行符" << ' ';
			break;
		case int('\t') : cout << "制表符" << ' ';;
			break;
		case int(' ') : cout << "空格号" << ' ';
			break;
		default:cout << char(i) << ' ';
	}
	return 1;
}
int main()
{
	printf("请在to_compress.txt文件中输入要压缩的内容（内容中不能包含非ascii码字符）\n"); 
	//储存各个字符出现的数目
	int w[130];
	int tot = 0;
	//统计频率
	getFrequency("to_compress.txt", w, tot);
	//输出统计频率
	cout << "在文本中出现的字符频率统计：" << endl;
	for (int i = 0; i < N_CHAR; ++i)
		if (isdisplay(w,i))cout << w[i] << endl;
	cout << endl;
	HuffmanTree HT;
	HuffmanCode HC;
	//建立Huffman树和Huffman Code静态数组
	HuffmanCoding(HT, HC, w);
	int maxHC = getMaxHC(HC);
	//输出Huffman编码
	cout << "在文本中出现的字符的Huffman编码如下：" << endl;
	for (int i = 0; i < N_CHAR; ++i)
		if (isdisplay(w,i))cout << HC[i] << endl;
	cout << endl;
	int writen;
	//压缩
	compress(HC, tot,writen);
	cout << endl;
	//解压缩
	decompress("compressed.txt", HT, tot, maxHC,writen);
	suspend();
	delete[]passage;//收回申请空间 
	return 0;
}
