#include<iostream>
#include<cstring>
#include<iomanip>
#include<vector>
#include<string>
#include<stack>
using namespace std;
typedef int Status;
//�궨�岿��
#define OPTR_NUM 8
#define LOGIC_ERROR 0
#define SYNTAX_ERROR -1
#define CORRECT 1
//ȫ�ֱ���
int priority[][8] =
{
	'>','<','<','<','<','<','>','>',
	'>','>','<','<','<','<','>','>',
	'>','>','>','<','<','<','>','>',
	'>','>','>','>','<','<','>','>',
	'>','>','>','>','>','<','>','>',
	'<','<','<','<','<','<','=','\0',
	'>','>','>','>','>','\0','>','>',
	'<','<','<','<','<','<','\0','=',
};//���ȼ��Ƚ�����
int Map[128];//�������������optr�е�����Լ����������v�е���ţ�v��һ���ֲ��������������и�����
char optr[] = { '~','^','|','&','!','(',')','#' };//���е�������š������Լ�#
//��������
bool isOperator(char);
Status init(string, vector<char>&);
bool operate(bool, char, bool= 0);
bool get_value(char, int, int);
Status evaluate_expression(string, int, int, int&);
void printHead();
void printRes(string, vector<char>);
void Suspend();

int main()
{
	printHead();//��ӡ����
	string expression;//������ʽ
	cin >> expression;
	vector<char>v;//�����������
	if (init(expression, v) != CORRECT)
	{
		cout << "\n��ʽ����" << endl;
		Suspend();
		return -1;
	}
	//��������ı��ʽѰ�����������浽v�У�ͬʱ���������ж�
	printRes(expression, v);//�����ֵ���Լ���ʽ
	Suspend();
	return 0;
}

/*****************************************************************
�������ƣ�isOperator
��ʽ������ch
����ֵ��bool
�������ã��ж�һ���ַ��Ƿ����߼�������Ż�#
*****************************************************************/
bool isOperator(char ch)
{
	for (int i = 0; i < OPTR_NUM; ++i)
		if (optr[i] == ch)return 1;
	return 0;
}

/*****************************************************************
�������ƣ�init
��ʽ������string,vector<char>&
����ֵ��Status(=int)
�������ã�  �١���ʼ��Map
			�ڡ����û�����ı��ʽ��Ѱ�������������������ж�
����˵���������ڱ����и����µ��޶������������ֻ���ɵ���ascii����
����ɣ����Ի����Ƿ��жѻ���һ��ı������aa��������У����
��������ʾ
*****************************************************************/
Status init(string expression, vector<char>& v)
{
	memset(Map, -1, sizeof(Map));//��Map�ĳ�ʼֵ��Ϊ-1
	//optr�д����char��ascii��ֵ����ΪMap����������optr�ж�ӦԪ�ص���������ΪMap��ֵ���൱��optr����ӳ��
	for (int i = 0; i < OPTR_NUM; ++i)Map[int(optr[i])] = i;
	int las_i = -2;//��һ�η��ʵ���i��Ϊ�˼���Ƿ��жѻ���һ��ı���
	//Ѱ���������
	for (int i = 0; i < expression.size(); ++i)
	{
		//������������������Ϊ���������
		if (!isOperator(expression[i]))
		{
			if (las_i == i - 1)return SYNTAX_ERROR;//�ѻ��ж�
			las_i = i;
			if (Map[expression[i]] != -1)continue;//����������Ѿ����ֹ�
			v.push_back(expression[i]);
			Map[expression[i]] = v.size() - 1;//��Map�д���expression�б��������
		}
	}
	return CORRECT;
}

/*****************************************************************
�������ƣ�operate
��ʽ������bool , char , bool 
����ֵ��bool
�������ã�����a op b���� op a��opΪ��ʱ���ļ���
*****************************************************************/
bool operate(bool a, char op, bool b)
{
	//�����߼�����
	if (op == '!')return !a;
	else if (op == '&')return a && b;
	else if (op == '|')return a || b;
	else if (op == '^')return !a || b;
	else if (op == '~')return (!a || b) && (a || !b);
	//��op���������������£���Ȼ�ڱ������в��ᷢ����������Ӧ
	return 0;
}

/*****************************************************************
�������ƣ�get_value
��ʽ������char , int , int 
����ֵ��bool
�������ã�����x�ж�ch��ֵ��0����1
	e.g. xΪ3��n=8��������Ϊ 0000 0011�����ch��v�е������0-5����
	����0�������6����7���򷵻�1��v�д�������������
*****************************************************************/
bool get_value(char ch, int x, int n)
{
	return (1 << (n - Map[ch] - 1)) & x;
}

/*****************************************************************
�������ƣ�evaluate_expression
��ʽ������string, int , int , int& 
����ֵ��Status(=int)
�������ã�����ֵ��������������ټ�����
����˵�����ô�ʹ��ջ��������׺���ʽ�����˵���ĵ�������ֵ��ʾ�ú�
���ܷ��������У�������Ľ��������value(int&)��
*****************************************************************/
Status evaluate_expression(string expression, int x, int n, int& value)
{
	expression += '#';//#��Ϊ��ʼ�������־
	stack<bool>OPND; stack<char>OPTR;//OPND������������OPTR���������
	OPTR.push('#');//�Ƚ�#��ջ
	int i = 0;
	while (i < expression.size() || OPTR.size())
	{
		char ch = expression[i++];
		//�������������get_value���������ϣ�����ֵ������������������OPNDջ��
		if (!isOperator(ch))  
			OPND.push(get_value(ch, x, n)); 
		else//������������
		{
			//n1��n2�ֱ𴢴�ջ�����ź��¶��������optr�е�����
			int n1 = Map[int(OPTR.top())], n2 = Map[int(ch)];
			//���ջ����������ȼ�С���¶���Ԫ�أ�����ջ
			if (priority[n1][n2] == '<')OPTR.push(ch);
			//�߼���������������ջ����(��ȴ������#(������������˵��������ʽ����ȷ
			else if (priority[n1][n2] == '\0')return LOGIC_ERROR;
			//������ȵ������ջ��Ԫ�ص���
			else if (priority[n1][n2] == '=')OPTR.pop();
			//ջ����������ȼ������¶���Ԫ�أ����������
			else
			{
				//һֱ�жϵ�ջ����������ȼ��������¶���Ԫ��Ϊֹ
				while (priority[n1][n2] == '>')
				{
					//�����һĿ�����
					if (OPTR.top() == '!')
					{
						OPTR.pop();
						int a = OPND.top();
						OPND.pop();
						OPND.push(operate(a, '!'));
					}
					//��Ŀ�����
					else
					{
						char op = OPTR.top();
						OPTR.pop();
						if (OPND.size() < 2)return LOGIC_ERROR;
						int b = OPND.top();
						OPND.pop();
						int a = OPND.top();
						OPND.pop();
						OPND.push(operate(a, op, b));
					}
					n1 = Map[int(OPTR.top())];
				}
				--i;//���������δ���룬���˸�һλ
			}
		}
	}
	if (OPND.size() == 1)value = OPND.top();
	else return LOGIC_ERROR;
	return CORRECT;
}

/*****************************************************************
�������ƣ�printHead
��ʽ��������
����ֵ����
�������ã��������
*****************************************************************/
void printHead()
{
	cout << "***************************************\n";  //����
	cout << "**                                   **\n";
	cout << "**         ��ӭ�����߼��������      **\n";
	cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
	cout << "**                                   **\n";
	cout << "**   ������������õ���ascii���ʾ   **\n";
	cout << "**              ��!��ʾ��            **\n";
	cout << "**              ��&��ʾ��            **\n";
	cout << "**              ��|��ʾ��            **\n";
	cout << "**             ��^��ʾ�̺�           **\n";
	cout << "**             ��~��ʾ��ֵ           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "������һ���Ϸ������⹫ʽ:\n";  //����ʽ��
}

/*****************************************************************
�������ƣ�printRes
��ʽ������string , vector<char>
����ֵ����
�������ã���ӡ��ֵ���Լ�����ȡ������ȡ��ʽ
*****************************************************************/
void printRes(string expression, vector<char>v)
{
	vector<int>M;//�洢��С��
	int value = 0;
	//ֻ��Ҫ���ڴ���һ����ֵ������֪Ϥ���ʽ�Ƿ�����߼�����
	if (evaluate_expression(expression, 0, v.size(), value) != CORRECT)
	{
		cout << "\n�߼�����\n";
		Suspend();
		exit(-1);
	}
	cout << "\n�������ĸ���Ϊ��" << v.size() << endl << endl;
	//��ӡ��ֵ��
	for (int i = 0; i < v.size(); ++i)
		cout << setw(2) << right << v[i];//�������
	cout << setw(expression.size() + 2) << right << expression << endl;//���ʽ
	//������ֵ���ֵ������ʾ
	for (int i = 0; i < (1 << v.size()); ++i)
	{
		for (int j = 0; j < v.size(); ++j)
			cout << setw(2) << right << get_value(v[j], i, v.size());
		evaluate_expression(expression, i, v.size(), value);//������ʽ��ֵ
		cout << setw((expression.size() + 2) / 2 + 2) << right << value << endl;
		if (!value)
			M.push_back(i);//M�д��������Ϊ0����
	}
	//��ӡ����ȡ��ʽ
	if (M.size()) cout << "\n�����⹫ʽ������ȡ��ʽ:\n\t";
	else cout << "\n�����⹫ʽ����������ȡ��ʽ.\n";
	for (int i = 0; i < M.size(); ++i)
	{
		if (i)cout << " \\/ ";
		cout << "M(" << M[i] << ")";
	}
	//��ӡ����ȡ��ʽ
	if (M.size() < (1 << v.size()))cout << "\n\n�����⹫ʽ������ȡ��ʽ:\n\t";
	else cout << "\n�����⹫ʽ����������ȡ��ʽ.\n";
	int j = 0, first = 1;
	for (int i = 0; i < (1 << v.size()); ++i)
	{
		while (j < M.size() && M[j] < i)++j;
		if (j < M.size() && M[j] == i)continue;
		if (first)first = 0;
		else cout << " /\\ ";
		cout << "m(" << i << ")";
	}
}
void Suspend()
{
	string dump;
	getline(cin,dump);
	printf("\n\n\npress any key to continue...\n");
	getchar(); 
 } 
