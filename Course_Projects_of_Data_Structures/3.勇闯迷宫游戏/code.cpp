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
//顺序存储结构
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
        if (_base == _top) { cout << "删除失败，因为栈为空！\n"; exit(-1); }
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
        if (_base == _top) { cout << "取栈顶失败，因为栈为空！\n"; exit(-1); }
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
	int* Map;//0表示不通，1表示通，2表示起点，3表示终点
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
				else if (!i)printf("\t%d列", j - 1);
				else if (!j)printf("%d行", i - 1);
				else
				{
					int pos = (i - 1) * _size + (j - 1); 
					if (Map[pos] == 2)printf("\t\b起点");
					else if (Map[pos] == 3)printf("\t\b终点");
					else printf("\t%d", Map[pos]);
				}
			cout.put('\n');
		}
	}
};

typedef struct
{
	posType pos;
	int di;//方向
	
}SElemType;
Stack<SElemType>MIN_S;
void display(SElemType e)
{
	const char* direction[] = { "左","右","上","下" };
	cout << "(" << e.pos.x << "," << e.pos.y << ")";
	if (e.di != -1)cout << "向"  << direction[e.di] << "到 ";
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
			cout << "该路线的路程长度为：" << num << endl;
			S.print(display);
		}
		else
		{
			clock_t curTime = clock();
			if (curTime - lastTime >= 200)
			{
				lastTime = curTime;
				cout << "\r已经搜索到";
				if (tot > 1e8)cout << (long long)(tot / 1e8) << "亿";
				else if(tot>1e4)cout << (long long)(tot / 1e4) << "万";
				else if (tot > 1e3)cout << (long long)(tot / 1e3) << "千";
				else cout<<tot;
				cout<<"条路径...";
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
		if (!tot)cout << "未找到通路！\n" << endl;
		else
		{
			if (tot > 10)cout << "\n(只显示前10条搜索结果）";
			cout << "总共有 " << tot << " 种通路\n";
			cout << "其中最短方案经过的路程为：" << MIN << endl;
			cout << "一种最短方案的路径为：\n";
			MIN_S.print(display);
		}
		getchar();
		printf("是否继续？(y/n): ");
		int flag;
		//严格的y/n审查部分，用getline读取一整行，这一行里面只能由空格和一个y或n组成，否则报错
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
			if (flag == -1 || flag == 0) printf("非法输入！请重新输入：");
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
	printf("==========================程序说明==========================\n");
	printf("============由用户输入地图的大小以及连通块的数量============\n");
	printf("===============地图中，0表示不连通，1表示连通===============\n\n");

}
void readIn(int& n, int& pass)
{
	while (1)
	{
		printf("请输入地图的大小(请保证在 2 到 15 之间)：\t");
		cin >> n;
		if (cin.fail())
		{
			cout << "输入格式有误！\n";
			cin.clear();
			char* ch = new char[1000];
			cin.getline(ch, 1000);
			delete[]ch;
		}
		else if (n < 2 || n > 15)
		{
			cout << "数据范围有误！\n";
		}
		else break;
	}
	while (1)
	{
		int suggest[] = { 45,54,67,78,90,98,113,130,142 };
		printf("请输入可通块的的数量(请保证在 1 到 %d 之间)：\t", n * n - 2);
		if (n > 6)
		{
			printf("\n(建议输入不要超过%d，否则程序可能会长时间无法结束！)\n", suggest[n - 7]);
		}
		
		cin >> pass;
		if (cin.fail())
		{
			cout << "输入格式有误！\n";
			cin.clear();
			char* ch = new char[1000];
			cin.getline(ch, 1000);
			delete[]ch;
		}
		else if (pass < 1 || pass > n* n - 2)
		{
			cout << "数据范围有误！\n";
		}
		else break;
	}
}
