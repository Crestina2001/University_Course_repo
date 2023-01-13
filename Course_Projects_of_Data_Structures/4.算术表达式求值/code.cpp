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
//˳��洢�ṹ
template<class T>
class Stack
{
private:
    T* _top;    //��ʾջ������һ��Ԫ��
    T* _base;   //��ʾջ��Ԫ��
    int stackSize;  //��ʾջ���ڴ�������Ĵ�С
    const int STACK_INIT_SIZE = 100;    //�涨ջ��ʼ��ʱ������ڴ�
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
        if (_base == _top) { cout << "ɾ��ʧ�ܣ���ΪջΪ�գ�\n"; exit(-1); }
        return *--_top;
    }
    Status push(T e)
    {
        if (_top - _base >= stackSize)
        {
            //��ȡ���������Ĳ��ԣ��ô˷������ݵ�ƽ�����Ӷ�ΪO(1)
            _base = (T*)realloc(_base, 2 * (stackSize) * sizeof(T));
            if (!_base)return OVERFLOW;
            _top = _base + stackSize;
            stackSize *= 2;
        }
        //��e��ֵ��ֵ��_top��ָ������_topָ����һ��Ԫ��
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
        if (_base == _top) { cout << "ȡջ��ʧ�ܣ���ΪջΪ�գ�\n"; exit(-1); }
        return *(_top - 1);
    }
    int size() { return _top - _base; }
    bool empty() { return !size(); }
};

//ȫ�ֱ���
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
};//���ȼ��Ƚ�����

int Map[128];//�������������optr�е����
char optr[] = { '=','(',')','+','-','*','/','%','^','!' };//���е��������
bool check_char(char ch)
{
    for (int i = 0; i < OPTR_NUM - 1; ++i)
        if (optr[i] == ch)return 1;
    return 0;
}
ll operate(bool& flag,ll a, char op, ll b = 0 )
{
    //�����߼�����
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
    memset(Map, -1, sizeof(Map));//��Map�ĳ�ʼֵ��Ϊ-1
    //optr�д����char��ascii��ֵ����ΪMap����������optr�ж�ӦԪ�ص���������ΪMap��ֵ���൱��optr����ӳ��
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
            printf("���ڲ���ʶ��ķǷ��ַ�,��ascii��Ϊ %d\n",ori[i]);
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
    --i;//����ǰ�������ֵ���num
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
	Stack<ll>OPND; Stack<char>OPTR;//OPND������������OPTR���������
	OPTR.push('=');//�Ƚ�=��ջ
    char ch = expression[0];//��ȡ��һ���ַ�
    ll num ;
    int i = 1;//ָ��ǰ�������һ���ַ�
    while (ch != '=' || OPTR.top() != '=')
	{
        
        if (isdigit(ch)) { 
            readNum(expression, num, i); 
            OPND.push(num); 
            ch = expression[i++]; 
        //    cout << "input " << num << endl;//�������
        }
		else//������������
		{
            //�ж��Ƿ��ǵ�Ŀ�����������-�����Ϊ!������+������ֱ�Ӻ���
            if (i==1||isSingle(expression[i-2]))
            {
                if (ch == '+') { ch = expression[i++];continue;}
                else if (ch == '-') { ch = '!'; }
            }
			int n1 = Map[int(OPTR.top())], n2 = Map[int(ch)];
            //ջ���������ȼ������¶������
            if (priority[n1][n2] == '<') { 
                OPTR.push(ch); 
            //    cout << "input " << ch << endl;//�������
                ch = expression[i++];
                
            }
            //�߼�����
            else if (priority[n1][n2] == '\0') {  return LOGIC_ERROR; }
            //ջ���������ȼ������¶������
            else if (priority[n1][n2] == '=') { 
                OPTR.pop(); 
                ch = expression[i++];
             //   cout << "pop\n";
            }
            //ջ���������ȼ������¶������
			else
            {
                //��Ŀ�����
                if (OPTR.top() == '!')
                {
                    OPTR.pop();
                    if (OPND.empty())return LOGIC_ERROR;
                    ll a = OPND.pop();
                    bool flag = 0;
                    OPND.push(operate(flag, a, '!'));
                    if (flag)return MATH_ERROR;
                //    cout << "calculate -" << a << endl;//�������
                }
                //��Ŀ�����
                else
                {
                    char op = OPTR.pop();
                    if (OPND.size() < 2) { return LOGIC_ERROR; }
                    ll b = OPND.pop();
                    ll a = OPND.pop();
                    bool flag = 0;
                    OPND.push(operate(flag, a, op, b));
                    if (flag)return MATH_ERROR;
                 //  cout << "calculate " << a << " " << op << " " << b << endl;//�������
                }
			}
		}
	}
	if (OPND.size() == 1)value = OPND.top();//����ջ��Ԫ��
	else return LOGIC_ERROR;
	return CORRECT;
}
void printHead()
{
    printf("================================��ӭ������ʽ��ֵ����================================\n");
    printf("==============================��������㷶Χ��-2^63-2^63-1==============================\n");
    printf("=========================����������ʹ�õ��������+ - * / ^ = ( )========================\n");
}
int main()
{
    printHead();
    initMap();
    ll x;
    while (1)
    {
        printf("\n����һ����������ʽ���Իس�����β��\n");
        //��ȡ���ʽ��������
        char* expression = read_expression_without_blank();//
        //������ʽ�в����зǷ��ַ�
        if (expression != NULL)
        {
            int t;
            //������ʽ�к����߼�����
            if ((t = evaluate_expression(expression, x)) == CORRECT)
            {
                cout << "������Ϊ��\n" << x << endl;
            }
            else if (!t) printf("�߼�����\n");
            else printf("��ѧ����\n");
            delete[]expression;
        }
        printf("�Ƿ������(y/n): ");
        int flag;
        //�ϸ��y/n��鲿�֣���getline��ȡһ���У���һ������ֻ���ɿո��һ��y��n��ɣ����򱨴�
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
            if (flag == -1||!flag)printf("�Ƿ����룡���������룺");
            else break;
            delete[]expression;
        }
        if (flag == 2)break;

    }
    printf("��ӭ�ٴ�ʹ�øó���\n");
    return 0;
}
