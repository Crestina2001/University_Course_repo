#include<iostream>
#include<cstring>
#include<iomanip>
#include<vector>
#include<string>
#include<stack>
using namespace std;
typedef int Status;
//宏定义部分
#define OPTR_NUM 8
#define LOGIC_ERROR 0
#define SYNTAX_ERROR -1
#define CORRECT 1
//全局变量
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
};//优先级比较数组
int Map[128];//储存运算符号在optr中的序号以及命题变项在v中的序号（v是一个局部变量，主函数中给出）
char optr[] = { '~','^','|','&','!','(',')','#' };//所有的运算符号、括号以及#
//函数定义
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
	printHead();//打印标语
	string expression;//储存表达式
	cin >> expression;
	vector<char>v;//储存命题变项
	if (init(expression, v) != CORRECT)
	{
		cout << "\n格式错误！" << endl;
		Suspend();
		return -1;
	}
	//根据输入的表达式寻找命题变项并储存到v中，同时进行正误判断
	printRes(expression, v);//输出真值表以及范式
	Suspend();
	return 0;
}

/*****************************************************************
函数名称：isOperator
形式参数：ch
返回值：bool
函数作用：判断一个字符是否是逻辑运算符号或#
*****************************************************************/
bool isOperator(char ch)
{
	for (int i = 0; i < OPTR_NUM; ++i)
		if (optr[i] == ch)return 1;
	return 0;
}

/*****************************************************************
函数名称：init
形式参数：string,vector<char>&
返回值：Status(=int)
函数作用：  ①、初始化Map
			②、从用户输入的表达式中寻找命题变项，并进行正误判断
额外说明：由于在标语中给出新的限定——命题变项只能由单个ascii码字
符组成，所以会检测是否有堆积在一起的变项（比如aa），如果有，会给
出错误提示
*****************************************************************/
Status init(string expression, vector<char>& v)
{
	memset(Map, -1, sizeof(Map));//将Map的初始值设为-1
	//optr中储存的char的ascii码值，作为Map的索引；而optr中对应元素的索引，作为Map的值，相当于optr的逆映射
	for (int i = 0; i < OPTR_NUM; ++i)Map[int(optr[i])] = i;
	int las_i = -2;//上一次访问到的i，为了检测是否有堆积在一起的变项
	//寻找命题变项
	for (int i = 0; i < expression.size(); ++i)
	{
		//如果不是运算符，则认为是命题变项
		if (!isOperator(expression[i]))
		{
			if (las_i == i - 1)return SYNTAX_ERROR;//堆积判定
			las_i = i;
			if (Map[expression[i]] != -1)continue;//该命题变项已经出现过
			v.push_back(expression[i]);
			Map[expression[i]] = v.size() - 1;//在Map中储存expression中变项的索引
		}
	}
	return CORRECT;
}

/*****************************************************************
函数名称：operate
形式参数：bool , char , bool 
返回值：bool
函数作用：进行a op b或者 op a（op为非时）的计算
*****************************************************************/
bool operate(bool a, char op, bool b)
{
	//进行逻辑运算
	if (op == '!')return !a;
	else if (op == '&')return a && b;
	else if (op == '|')return a || b;
	else if (op == '^')return !a || b;
	else if (op == '~')return (!a || b) && (a || !b);
	//在op不是运算符的情况下（虽然在本程序中不会发生）作出回应
	return 0;
}

/*****************************************************************
函数名称：get_value
形式参数：char , int , int 
返回值：bool
函数作用：根据x判断ch的值是0还是1
	e.g. x为3，n=8，二进制为 0000 0011，如果ch在v中的序号是0-5，则
	返回0，如果是6或者7，则返回1（v中储存所有命题变项）
*****************************************************************/
bool get_value(char ch, int x, int n)
{
	return (1 << (n - Map[ch] - 1)) & x;
}

/*****************************************************************
函数名称：evaluate_expression
形式参数：string, int , int , int& 
返回值：Status(=int)
函数作用：将真值代入命题变量，再计算结果
额外说明：该处使用栈来计算中缀表达式，详见说明文档；返回值表示该函
数能否正常运行，而计算的结果储存在value(int&)中
*****************************************************************/
Status evaluate_expression(string expression, int x, int n, int& value)
{
	expression += '#';//#作为开始与结束标志
	stack<bool>OPND; stack<char>OPTR;//OPND储存运算数，OPTR储存运算符
	OPTR.push('#');//先将#入栈
	int i = 0;
	while (i < expression.size() || OPTR.size())
	{
		char ch = expression[i++];
		//不是运算符，用get_value函数（见上）将真值代入命题变项，并储存在OPND栈中
		if (!isOperator(ch))  
			OPND.push(get_value(ch, x, n)); 
		else//是运算符的情况
		{
			//n1和n2分别储存栈顶符号和新读入符号在optr中的索引
			int n1 = Map[int(OPTR.top())], n2 = Map[int(ch)];
			//如果栈顶运算符优先级小于新读入元素，则入栈
			if (priority[n1][n2] == '<')OPTR.push(ch);
			//逻辑错误的情况，例如栈顶是(，却读入了#(结束符），则说明输入表达式不正确
			else if (priority[n1][n2] == '\0')return LOGIC_ERROR;
			//两者相等的情况，栈顶元素弹出
			else if (priority[n1][n2] == '=')OPTR.pop();
			//栈顶运算符优先级大于新读入元素，则进行运算
			else
			{
				//一直判断到栈顶运算符优先级不大于新读入元素为止
				while (priority[n1][n2] == '>')
				{
					//如果是一目运算符
					if (OPTR.top() == '!')
					{
						OPTR.pop();
						int a = OPND.top();
						OPND.pop();
						OPND.push(operate(a, '!'));
					}
					//二目运算符
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
				--i;//新运算符并未读入，故退格一位
			}
		}
	}
	if (OPND.size() == 1)value = OPND.top();
	else return LOGIC_ERROR;
	return CORRECT;
}

/*****************************************************************
函数名称：printHead
形式参数：无
返回值：无
函数作用：输出标语
*****************************************************************/
void printHead()
{
	cout << "***************************************\n";  //标语
	cout << "**                                   **\n";
	cout << "**         欢迎进入逻辑运算软件      **\n";
	cout << "**   (可运算真值表,主范式,支持括号)  **\n";
	cout << "**                                   **\n";
	cout << "**   所有命题变项用单个ascii码表示   **\n";
	cout << "**              用!表示非            **\n";
	cout << "**              用&表示与            **\n";
	cout << "**              用|表示或            **\n";
	cout << "**             用^表示蕴含           **\n";
	cout << "**             用~表示等值           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "请输入一个合法的命题公式:\n";  //输入式子
}

/*****************************************************************
函数名称：printRes
形式参数：string , vector<char>
返回值：无
函数作用：打印真值表以及主合取与主析取范式
*****************************************************************/
void printRes(string expression, vector<char>v)
{
	vector<int>M;//存储极小项
	int value = 0;
	//只需要对于代入一组真值，即可知悉表达式是否存在逻辑错误
	if (evaluate_expression(expression, 0, v.size(), value) != CORRECT)
	{
		cout << "\n逻辑错误！\n";
		Suspend();
		exit(-1);
	}
	cout << "\n命题变项的个数为：" << v.size() << endl << endl;
	//打印真值表
	for (int i = 0; i < v.size(); ++i)
		cout << setw(2) << right << v[i];//命题变项
	cout << setw(expression.size() + 2) << right << expression << endl;//表达式
	//计算真值表的值并且显示
	for (int i = 0; i < (1 << v.size()); ++i)
	{
		for (int j = 0; j < v.size(); ++j)
			cout << setw(2) << right << get_value(v[j], i, v.size());
		evaluate_expression(expression, i, v.size(), value);//计算表达式的值
		cout << setw((expression.size() + 2) / 2 + 2) << right << value << endl;
		if (!value)
			M.push_back(i);//M中储存计算结果为0的项
	}
	//打印主和取范式
	if (M.size()) cout << "\n该命题公式的主合取范式:\n\t";
	else cout << "\n该命题公式不存在主析取范式.\n";
	for (int i = 0; i < M.size(); ++i)
	{
		if (i)cout << " \\/ ";
		cout << "M(" << M[i] << ")";
	}
	//打印主析取范式
	if (M.size() < (1 << v.size()))cout << "\n\n该命题公式的主析取范式:\n\t";
	else cout << "\n该命题公式不存在主析取范式.\n";
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
