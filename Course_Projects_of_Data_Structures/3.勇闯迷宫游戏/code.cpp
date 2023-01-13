#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<time.h>
using namespace std;
//macro definition
#define ERROR 0
#define OK 1
#define OVERFLOW -2
//special define
typedef int Status;
long long tot = 0, MIN = (1 << 31)-1;
//˳��洢�ṹ
template<class T>
class Stack
{
private:
    T* _top;
    T* _base;
    int stackSize;
    const int STACK_INIT_SIZE = 100;
public:
    Stack()
    {
        _base = new T[STACK_INIT_SIZE];
        if (!_base)exit(OVERFLOW);
        _top = _base;
        stackSize = STACK_INIT_SIZE;
    }

    Stack& operator=(const Stack& S)
    {
        stackSize = S.stackSize;
        _base = new T[stackSize];
        if (!_base)exit(OVERFLOW);
        _top = _base;
        T* p = S._base;
        while (p != S._top) *_top++ = *p++;
        return *this;
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
            _base = (T*)realloc(_base, 2 * (stackSize) * sizeof(T));
            if (!_base)return OVERFLOW;
            _top = _base + stackSize;
            stackSize *= 2;
        }
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
    void print(void(*op)(T x))
    {
        int cnt = 0;
        for (T* p = _base; p != _top; ++p)
        {
            if ((cnt++ % 8 == 0)&&cnt-1)cout << endl;
            op(*p);
        }
        cout << endl;
    }
};


struct posType
{
	int x, y;
};
class Labyrinth
{
private:
	int* Map;//0��ʾ��ͨ��1��ʾͨ��2��ʾ��㣬3��ʾ�յ�
	int _setup, _destination, _size;
public:
	Labyrinth(const Labyrinth& L) :_setup(L._setup), _destination(L._destination), _size(L._size)
	{
		Map = new int[_size * _size];
		for (int i = 0; i < _size * _size; ++i)Map[i] = L.Map[i];
	}
	Labyrinth(int n, int pass);
	~Labyrinth() { delete[]Map; }
	void rebuild(int n, int pass) { delete[]Map; Labyrinth(n, pass); }
	posType setup() { return posType{ _setup / _size,_setup % _size }; }
	int destination() { return _destination; }
	int query(posType p)
	{
		int x = p.x, y = p.y;
		if (x < 0 || x >= _size || y < 0 || y >= _size)return -2;
		return Map[x * _size + y];
	}
	int size() { return _size; }
	int revise(posType p,int value)
	{ 
		int x = p.x, y = p.y;
		if (x < 0 || x >= _size || y < 0 || y >= _size)return ERROR;
		Map[x * _size + y] = value;
	}
	void display()
	{
		for (int i = 0; i < _size + 1; ++i)
		{
			for (int j = 0; j < _size + 1; ++j)
				if (!i && !j)continue;
				else if (!i)printf("\t%d��", j - 1);
				else if (!j)printf("%d��", i - 1);
				else
				{
					int pos = (i - 1) * _size + (j - 1); 
					if (Map[pos] == 2)printf("\t\b���");
					else if (Map[pos] == 3)printf("\t\b�յ�");
					else printf("\t%d", Map[pos]);
				}
			cout.put('\n');
		}
	}
};

typedef struct
{
	posType pos;
	int di;//����
	
}SElemType;
Stack<SElemType>MIN_S;
void display(SElemType e)
{
	const char* direction[] = { "��","��","��","��" };
	cout << "(" << e.pos.x << "," << e.pos.y << ")";
	if (e.di != -1)cout << "��"  << direction[e.di] << "�� ";
}
void dfs(Labyrinth& L, Stack<SElemType>& S, posType cur,clock_t&lastTime, int num = 0)
{
	int judge = L.query(cur);
	if (judge==-2||!judge)return;
	if (judge == 3)
	{
		S.push(SElemType{ cur,-1 });
		if (++tot <= 10)
		{
			cout << "��·�ߵ�·�̳���Ϊ��" << num << endl;
			S.print(display);
		}
		else
		{
			clock_t curTime = clock();
			if (curTime - lastTime >= 200)
			{
				lastTime = curTime;
				cout << "\r�Ѿ�������";
				if (tot > 1e8)cout << (long long)(tot / 1e8) << "��";
				else if(tot>1e4)cout << (long long)(tot / 1e4) << "��";
				else if (tot > 1e3)cout << (long long)(tot / 1e3) << "ǧ";
				else cout<<tot;
				cout<<"��·��...";
			}
		}
		if (MIN > num)
		{
			MIN = num;
			MIN_S = S;
		}
		S.pop();
		return;
	}
	L.revise(cur, 0);
	const int mov_x[] = { 0,0,-1,1 }, mov_y[] = { -1,1,0,0 };
	for (int i = 0; i < 4; ++i)
	{
		S.push(SElemType{cur,i});
		cur.x += mov_x[i], cur.y += mov_y[i];
		dfs(L, S, cur, lastTime,num + 1);
		cur.x -= mov_x[i], cur.y -= mov_y[i];
		S.pop();
	}
	L.revise(cur, judge);
}
void readIn(int&, int&);
void printHead();
int main()
{
	while (1)
	{
		tot = 0, MIN = (1 << 31)-1;
		printHead();
		int n, pass;
		readIn(n, pass);
		Labyrinth L(n, pass);
		L.display();
		Stack<SElemType>S;
		clock_t startTime = clock();
		dfs(L, S, L.setup(),startTime);
		if (!tot)cout << "δ�ҵ�ͨ·��\n" << endl;
		else
		{
			if (tot > 10)cout << "\n(ֻ��ʾǰ10�����������";
			cout << "�ܹ��� " << tot << " ��ͨ·\n";
			cout << "������̷���������·��Ϊ��" << MIN << endl;
			cout << "һ����̷�����·��Ϊ��\n";
			MIN_S.print(display);
		}
		getchar();
		printf("�Ƿ������(y/n): ");
		int flag;
		//�ϸ��y/n��鲿�֣���getline��ȡһ���У���һ������ֻ���ɿո��һ��y��n��ɣ����򱨴�
		while (1)
		{
			flag = 0;
			char* expression = new char[1000];
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
			if (flag == -1 || flag == 0) printf("�Ƿ����룡���������룺");
			else break;
			delete[]expression;
		}
		if (flag == 2)break;
		system("cls");
	}
	
	return 0;
}
Labyrinth::Labyrinth(int n, int pass)
{
	_size = n;
	Map = new int[n * n];
	for (int i = 0; i < n * n; ++i)Map[i] = 0;
	srand(time(0));
	for (int i = 2; i < 4;)
	{
		int x = rand() % (n * n);
		//cout << x << ' ' << Map[x] << endl;
		if (Map[x])continue;
		Map[x] = i;
		(i == 2 ? _setup = x : _destination = x);
		++i;
	}
	for (int i = 0; i < pass;)
	{
		int x = rand() % (n * n);
		if (Map[x])continue;
		Map[x] = 1;
		++i;
	}

}
void printHead()
{
	printf("==========================����˵��==========================\n");
	printf("============���û������ͼ�Ĵ�С�Լ���ͨ�������============\n");
	printf("===============��ͼ�У�0��ʾ����ͨ��1��ʾ��ͨ===============\n\n");

}
void readIn(int& n, int& pass)
{
	while (1)
	{
		printf("�������ͼ�Ĵ�С(�뱣֤�� 2 �� 15 ֮��)��\t");
		cin >> n;
		if (cin.fail())
		{
			cout << "�����ʽ����\n";
			cin.clear();
			char* ch = new char[1000];
			cin.getline(ch, 1000);
			delete[]ch;
		}
		else if (n < 2 || n > 15)
		{
			cout << "���ݷ�Χ����\n";
		}
		else break;
	}
	while (1)
	{
		int suggest[] = { 45,54,67,78,90,98,113,130,142 };
		printf("�������ͨ��ĵ�����(�뱣֤�� 1 �� %d ֮��)��\t", n * n - 2);
		if (n > 6)
		{
			printf("\n(�������벻Ҫ����%d�����������᳤ܻʱ���޷�������)\n", suggest[n - 7]);
		}
		
		cin >> pass;
		if (cin.fail())
		{
			cout << "�����ʽ����\n";
			cin.clear();
			char* ch = new char[1000];
			cin.getline(ch, 1000);
			delete[]ch;
		}
		else if (pass < 1 || pass > n* n - 2)
		{
			cout << "���ݷ�Χ����\n";
		}
		else break;
	}
}
