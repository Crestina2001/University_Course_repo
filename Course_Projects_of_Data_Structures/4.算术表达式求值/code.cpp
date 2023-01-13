#include<iostream>
#include<cstdio>
#include<cstring>
//macro definition
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define OPTR_NUM 10
#define LOGIC_ERROR 0
#define MATH_ERROR -1
#define CORRECT 1
#define MAX_EXPRESSION_SIZE 1000
using namespace std;
//special define
typedef int Status;
typedef long long ll;
//顺序存储结构
template<class T>
class Stack
{
private:
    T* _top;    //表示栈顶的上一个元素
    T* _base;   //表示栈底元素
    int stackSize;  //表示栈在内存中申请的大小
    const int STACK_INIT_SIZE = 100;    //规定栈初始化时申请的内存
public:
    Stack()
    {
        _base = new T[STACK_INIT_SIZE];
        if (!_base)exit(OVERFLOW);
        _top = _base;
        stackSize = STACK_INIT_SIZE;
    }
    Status popStack(T& e)
    {
        if (_base == _top)return ERROR;
        e = *--_top;
        return OK;
    }
    T pop()
    {
        if (_base == _top) { cout << "删除失败，因为栈为空！\n"; exit(-1); }
        return *--_top;
    }
    Status push(T e)
    {
        if (_top - _base >= stackSize)
        {
            //采取容量扩增的策略，用此方法扩容的平均复杂度为O(1)
            _base = (T*)realloc(_base, 2 * (stackSize) * sizeof(T));
            if (!_base)return OVERFLOW;
            _top = _base + stackSize;
            stackSize *= 2;
        }
        //将e的值赋值给_top所指，并且_top指向下一个元素
        *_top++ = e;
        return OK;
    }
    Status get_top(T& e)
    {
        if (_base == _top)return ERROR;
        e = *(_top - 1);
        return OK;
    }
    T top()
    {
        if (_base == _top) { cout << "取栈顶失败，因为栈为空！\n"; exit(-1); }
        return *(_top - 1);
    }
    int size() { return _top - _base; }
    bool empty() { return !size(); }
};

//全局变量
int priority[][OPTR_NUM] =
{
    '=','<','\0','<','<','<','<','<','<','<',
    '\0','<','=','<','<','<','<','<','<','<',
    '>', '>','>','>','>','>','>','>','>','>',
     '>','<','>','>','>','<','<','<','<','<',
    '>','<','>','>','>','<','<','<','<','<',
    '>','<','>','>','>','>','>','<','<','<',
    '>','<','>','>','>','>','>','<','<','<',
    '>','<','>','>','>','>','>','>','<','<',
    '>','<','>','>','>','>','>','>','<','<',
    '>','<','>','>','>','>','>','>','>','<'
};//优先级比较数组

int Map[128];//储存运算符号在optr中的序号
char optr[] = { '=','(',')','+','-','*','/','%','^','!' };//所有的运算符号
bool check_char(char ch)
{
    for (int i = 0; i < OPTR_NUM - 1; ++i)
        if (optr[i] == ch)return 1;
    return 0;
}
ll operate(bool& flag,ll a, char op, ll b = 0 )
{
    //进行逻辑运算
    if (op == '!')return -a;
    else if (op == '+')return a + b;
    else if (op == '-')return a - b;
    else if (op == '*')return a * b;
    else if (op == '/') {
        if (!b) { flag = 1; return 0; }
        return a / b;
    }
    else if (op == '%') {
        if (!b) { flag = 1; return 0; }
        return a % b;
    }
    else if (op == '^') {
        if (b < 0)
        {
            if (!a) { flag = 1; return 0; }
            else if (a == 1)return 1;
            else if (a == -1)return b % 2 ? -1 : 1;
            else return 0;
        }
        else if (!a && !b) { flag = 1; return 0; }
        long long res = 1;
        for (int i = 0; i < b; ++i)res *= a;
        return res;
    }
    return 0;
}
Status initMap()
{
    memset(Map, -1, sizeof(Map));//将Map的初始值设为-1
    //optr中储存的char的ascii码值，作为Map的索引；而optr中对应元素的索引，作为Map的值，相当于optr的逆映射
    for (int i = 0; i < OPTR_NUM; ++i)Map[int(optr[i])] = i;
    return CORRECT;
}

bool isLegal(char ch)
{
    if (ch>='0'&&ch<='9')return 1;
    for (int i = 0; i < OPTR_NUM - 1; ++i)if (ch == optr[i])return 1;
    return ch == ' ' || ch == '\n';
}

char* read_expression_without_blank()
{
    char* ori = new char[MAX_EXPRESSION_SIZE];
    while (1)
    {
        cin.getline(ori, MAX_EXPRESSION_SIZE);
        if (ori[0] != '\0')break;
    }
    
 //   cout << ori << endl;
    char*rid= new char[MAX_EXPRESSION_SIZE];
    int i = 0, j = 0;
    while (i < strlen(ori))
    {
        if (isLegal(ori[i]))
        {
            if (ori[i] != ' ')rid[j++] = ori[i];
            i++;
        }
        else
        {
            printf("存在不可识别的非法字符,其ascii码为 %d\n",ori[i]);
            delete[]ori;
            delete[]rid;
            return NULL;
        }        
    }
    if (rid[j-1] == '=')rid[j++] = '\0';
    else { rid[j++] = '='; rid[j++] = '\0'; }
    delete[]ori;
    return rid;
}
void readNum(char* expression,ll& num, int& i)
{
    num = 0;
    --i;//将当前读的数字导入num
    while (i < strlen(expression) && isdigit(expression[i]))
    {
        num = num * 10 + expression[i++] - '0';
    }
}
bool isSingle(char last)
{
    for (int i = 0; i < OPTR_NUM - 1; ++i)if (i && i != 2 && last == optr[i])return 1;
    return 0;
}
Status evaluate_expression(char *expression,ll& value)
{
	Stack<ll>OPND; Stack<char>OPTR;//OPND储存运算数，OPTR储存运算符
	OPTR.push('=');//先将=入栈
    char ch = expression[0];//读取第一个字符
    ll num ;
    int i = 1;//指向当前读完的下一个字符
    while (ch != '=' || OPTR.top() != '=')
	{
        
        if (isdigit(ch)) { 
            readNum(expression, num, i); 
            OPND.push(num); 
            ch = expression[i++]; 
        //    cout << "input " << num << endl;//测试语句
        }
		else//是运算符的情况
		{
            //判断是否是单目运算符，若是-，则改为!，若是+，可以直接忽略
            if (i==1||isSingle(expression[i-2]))
            {
                if (ch == '+') { ch = expression[i++];continue;}
                else if (ch == '-') { ch = '!'; }
            }
			int n1 = Map[int(OPTR.top())], n2 = Map[int(ch)];
            //栈顶符号优先级低于新读入符号
            if (priority[n1][n2] == '<') { 
                OPTR.push(ch); 
            //    cout << "input " << ch << endl;//测试语句
                ch = expression[i++];
                
            }
            //逻辑错误
            else if (priority[n1][n2] == '\0') {  return LOGIC_ERROR; }
            //栈顶符号优先级等于新读入符号
            else if (priority[n1][n2] == '=') { 
                OPTR.pop(); 
                ch = expression[i++];
             //   cout << "pop\n";
            }
            //栈顶符号优先级大于新读入符号
			else
            {
                //单目运算符
                if (OPTR.top() == '!')
                {
                    OPTR.pop();
                    if (OPND.empty())return LOGIC_ERROR;
                    ll a = OPND.pop();
                    bool flag = 0;
                    OPND.push(operate(flag, a, '!'));
                    if (flag)return MATH_ERROR;
                //    cout << "calculate -" << a << endl;//测试语句
                }
                //二目运算符
                else
                {
                    char op = OPTR.pop();
                    if (OPND.size() < 2) { return LOGIC_ERROR; }
                    ll b = OPND.pop();
                    ll a = OPND.pop();
                    bool flag = 0;
                    OPND.push(operate(flag, a, op, b));
                    if (flag)return MATH_ERROR;
                 //  cout << "calculate " << a << " " << op << " " << b << endl;//测试语句
                }
			}
		}
	}
	if (OPND.size() == 1)value = OPND.top();//返回栈顶元素
	else return LOGIC_ERROR;
	return CORRECT;
}
void printHead()
{
    printf("================================欢迎进入表达式求值程序！================================\n");
    printf("==============================本程序计算范围：-2^63-2^63-1==============================\n");
    printf("=========================本程序允许使用的运算符：+ - * / ^ = ( )========================\n");
}
int main()
{
    printHead();
    initMap();
    ll x;
    while (1)
    {
        printf("\n请在一行内输入表达式，以回车键结尾：\n");
        //读取表达式兼正误检查
        char* expression = read_expression_without_blank();//
        //如果表达式中不含有非法字符
        if (expression != NULL)
        {
            int t;
            //如果表达式中含有逻辑错误
            if ((t = evaluate_expression(expression, x)) == CORRECT)
            {
                cout << "计算结果为：\n" << x << endl;
            }
            else if (!t) printf("逻辑错误！\n");
            else printf("数学错误！\n");
            delete[]expression;
        }
        printf("是否继续？(y/n): ");
        int flag;
        //严格的y/n审查部分，用getline读取一整行，这一行里面只能由空格和一个y或n组成，否则报错
        while (1)
        {
            flag = 0;
            expression = new char[1000];
            cin.getline(expression, 1000);
            for (int i = 0; i < strlen(expression); ++i)
            {
                if (expression[i] == ' ')continue;
                else if (expression[i] == 'y')
                {
                    if (!flag)flag = 1;
                    else if (flag)flag = -1;
                }
                else if (expression[i] == 'n')
                {
                    if (!flag)flag = 2;
                    else if (flag)flag = -1;
                }
                else flag = -1;
                if (flag == -1)break;
            }
            if (flag == -1||!flag)printf("非法输入！请重新输入：");
            else break;
            delete[]expression;
        }
        if (flag == 2)break;

    }
    printf("欢迎再次使用该程序！\n");
    return 0;
}
