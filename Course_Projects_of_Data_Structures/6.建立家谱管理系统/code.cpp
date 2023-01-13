#include<iostream>
#include<cstdlib> 
#include<cstdio>
#include<windows.h>
#include<string>
using namespace std;
#define OVERFLOW -2
#define OK 1
#define ERROR 0
typedef int Status;

template<class T>
class Queue {
private:
    T* e; //存储元素信息 
    int S; //当前元素个数 
    int MAXS; //最大能存储多少个元素 
    int _front; //队头 
    int _rear; //队尾 
    const int INIT_SIZE = 100;
public:
    Queue();
    Queue(Queue<T>& Q) :S(Q.S), MAXS(Q.MAXS), _front(Q._front), _rear(Q._rear), INIT_SIZE(Q.INIT_SIZE)
    {
        e = new T[S];
        for (int i = 0; i < S; ++i)
        {
            int j = (i + _front) % MAXS;
            e[i] = Q.e[j];
        }
    }
    Queue<T>& operator=(Queue<T>& Q)
    {
        S = Q.S, MAXS = Q.MAXS, _front = Q._front, _rear = Q._rear;
        delete[]e;
        e = new T[S];
        for (int i = 0; i < S; ++i)
        {
            int j = (i + _front) % MAXS;
            e[i] = Q.e[j];
        }
        return *this;
    }
    void deleteQueue() { delete[]e; }
    bool empty() { return !S; }
    int size() { return S; }
    T front() { if (!S) { printf("队列为空！无法弹出！\n"); exit(-1); } return *(e + _front); }
    Status popQueue(T& e);
    T pop();
    void push(T);
    void printQueue();
    ~Queue();
};

template<class T>
Queue<T>::Queue()
{
    MAXS = INIT_SIZE;
    _front = _rear = S = 0;
    //给e申请INIT_SIZE大小的空间
    e = new(nothrow)T[INIT_SIZE];
    //溢出检测
    if (!e)exit(OVERFLOW);
}

template<class T>
Status Queue<T>::popQueue(T& ele)
{
    //队列为空
    if (!S)return ERROR;
    //更新大小
    --S;
    //记录删除的元素
    ele = e[_front];
    //更新_front的位置
    _front = (_front + 1) % MAXS;
    return OK;
}

template<class T>
T Queue<T>::pop()
{
    if (!S) { printf("队列为空！无法弹出！\n"); exit(-1); }
    //更新大小
    --S;
    //记录删除的元素
    T ele = e[_front];
    //更新_front的位置
    _front = (_front + 1) % MAXS;
    return ele;
}

template<class T>
void Queue<T>::printQueue()
{
    if (!S)
    {
        cout << "队列为空！" << endl;
        return;
    }
    cout << "队列从队头到队尾包含：" << endl;
    for (int i = 0; i < S; ++i)
    {
        cout << e[(i + _front) % MAXS] << ' ';
        if (!((i + 1) % 20))cout << endl;
    }
    cout.put('\n');
}

template<class T>
Queue<T>:: ~Queue()
{
    int x;
    while (S)pop();
    _front = _rear = 0;
}

template<class T>
void Queue<T>::push(T ele)
{
    //如果队列已满，更新申请的空间
    if (S == MAXS)
    {
        //记录旧位置
        T* oldE = e;
        //申请新空间
        e = new(nothrow) T[MAXS *= 2];
        if (!e)exit(OVERFLOW);
        //将旧储存的值转移到新位置
        for (int i = 0; i < S; ++i)e[i] = oldE[(i + _front) % S];
        //更新_front和_rear的值
        _front = 0, _rear = S;
        //删除旧位置
        delete[]oldE;
    }
    //加入新元素
    e[_rear] = ele;
    //更新_rear的值
    _rear = (_rear + 1) % MAXS;
    //更新大小
    ++S;
}

int readInt(bool (*)(int)=NULL);
bool range(int n);

struct CSNode
{
	string name;
	CSNode* firstchild, * lastchild;
	CSNode* nextsibling, * parent;
};
class CSTree
{
private:
	CSNode* root;
	int _n;
	void print_decsendents(CSNode* parent)
	{
		if (parent->firstchild)
		{
			CSNode* p;
			cout << parent->name << "的第一代后代为：\n";
			for (p = parent->firstchild; p; p = p->nextsibling)cout << p->name << ' ';
			cout.put('\n');
		}
		else cout << parent->name << "无后辈！\n";
	}

	CSNode* search(CSNode* cur, string key)
	{
		if (!cur)return NULL;
		if (cur->name == key)return cur;
		CSNode* p = search(cur->firstchild, key);
		if (p)return p;
		return search(cur->nextsibling, key);
	}

	void del(CSNode* cur)
	{
		if (!cur)return;
		del(cur->nextsibling);
		del(cur->firstchild);
		delete cur;
		--_n;
	}
	void deleteNodeFromSiblings(CSNode* p)
	{
		if (!p)return;
		--_n;
		if (p == root) { delete p; root = NULL; return; }
		CSNode* parent = p->parent;
		if (parent->firstchild == p)
		{
			if (parent->lastchild == p)parent->firstchild = parent->lastchild = NULL;
			else parent->firstchild = p->nextsibling;
		}
		else
		{
			CSNode* q;
			for (q = parent->firstchild; q->nextsibling != p; q = q->nextsibling);
			q->nextsibling = p->nextsibling;
		}
		delete p;
	}
public:
	CSTree():_n(0)
	{
		root = NULL;
	}
	void build()
	{
		string name;
		if (!root)
		{
			printf("首先创建一个家谱！\n请输入祖先的姓名：\t");
			cin >> name;
			root = new CSNode{ name,NULL,NULL,NULL,NULL };
			cout << "此家谱的祖先是：" << name << endl;
			++_n;
			return;
		}
		printf("请输入要建立家庭的人的姓名：\t");
		cin >> name;
		CSNode* parent = search(root, name);
		if (!parent) { cout << "在家谱里没有找到" << name << "!\n"; return; }
		if (parent->firstchild) { cout << name << "已经有孩子了！\n"; return; }
		int n;
		cout << "请输入" << name << "的儿女人数（请输入正整数）：\t";
		n = readInt(range);
		_n += n;
		cout << "请输入" << name << "的儿女姓名：\n";
		string child_name;
		for (int i = 0; i < n; ++i)
		{
			cin >> child_name;
			CSNode* child = new CSNode{ child_name,NULL,NULL,NULL,parent };
			if (!parent->firstchild)parent->firstchild = parent->lastchild = child;
			else parent->lastchild->nextsibling = child, parent->lastchild = child;
		}
		print_decsendents(parent);
	}
	void insert()
	{
		string name;
		++_n;
		if (!root)
		{
			printf("首先创建一个家谱！\n请输入祖先的姓名：\t");
			cin >> name;
			root = new CSNode{ name,NULL,NULL,NULL,NULL };
			cout << "此家谱的祖先是：" << name << endl;
			return;
		}
		printf("请输入要添加后代的人的姓名：\t");
		cin >> name;
		CSNode* parent = search(root, name);
		if (!parent) { cout << "在家谱里没有找到" << name << "!\n"; return; }
		cout << "请输入" << name << "添加的后代的姓名：\n";
		string child_name;
		cin >> child_name;
		CSNode* child = new CSNode{ child_name,NULL,NULL,NULL,parent };
		if (!parent->firstchild)parent->firstchild = parent->lastchild = child;
		else parent->lastchild->nextsibling = child, parent->lastchild = child;
		print_decsendents(parent);
	}
	
	void dismiss()
	{
		string name;
		if (!root) { printf("家谱为空！\n"); return; }
		printf("请输入要解散家庭的人的姓名：\t");
		cin >> name;
		CSNode* parent = search(root, name);
		if (!parent) { cout << "在家谱里没有找到" << name << "!\n"; return; }
		print_decsendents(parent);
		CSNode* child = parent->firstchild;
		deleteNodeFromSiblings(parent);
		del(child);
	}
	void query()
	{
		string name;
		if (!root) { printf("家谱为空！\n"); return; }
		printf("请输入要查询的人的姓名：\t");
		cin >> name;
		CSNode* parent = search(root, name);
		if (!parent) { cout << "在家谱里没有找到" << name << "!\n"; return; }
		if (parent->parent)cout << parent->parent->name << "为" << parent->name << "祖先\n";
		else cout << parent->name << "无祖先\n";
		if (parent->firstchild)
		{
			CSNode* p;
			cout << parent->name << "的第一代后代为：\n";
			for (p = parent->firstchild; p; p = p->nextsibling)cout << p->name << ' ';
			cout.put('\n');
		}
		else cout << parent->name << "无后辈！\n";
	}
	void print()
	{
		if (!root) { printf("家谱为空！\n"); return; }
		printf("该家谱中成员数为：%d\n", _n);
		cout << "该家谱的祖先是" << root->name << endl << endl;
		Queue<CSNode*>Q;
		Q.push(root);
		int gene = 1, num[2];
		num[0] = 1, num[1] = 0;
		bool flag = 0;
		while (Q.size())
		{
			CSNode* p = Q.pop();
			if (!p->firstchild) { cout << p->name << "无后代！\n"; }
			else
			{
				cout << p->name << "的孩子有：\n";
				for (CSNode* q = p->firstchild; q; q = q->nextsibling) { cout << q->name << ' '; Q.push(q); ++num[gene % 2]; }
				cout.put('\n');
				flag = 1;
			}
			if (--num[(gene - 1) % 2] == 0 && num[gene % 2]&&flag) { cout << "----以上是第 " << gene++ << " 后代----\n\n"; flag = 0; }
		}
	}
	void revise()
	{
		if (!root) { printf("家谱为空！\n"); return; }
		string name;
		printf("请输入要修改的人原先的姓名：\t");
		cin >> name;
		CSNode* parent = search(root, name);
		if (!parent) { cout << "在家谱里没有找到" << name << "!\n"; return; }
		printf("请输入更改后的姓名：\t");
		cin >> parent->name;
		cout << name << "已经被修改成" << parent->name << endl;
	}
	
};
void printHead();
int main()
{
	CSTree T;
	while (1)
	{
		printHead();
		printf("请输入操作码：\n");
		string op;
		cin >> op;
		bool exit = 0;
		switch (op[0])
		{
		case 'A':
			T.build();
			break;
		case 'B':
			T.insert();
			break;
		case 'C':
			T.dismiss();
			break;
		case 'D':
			T.revise();
			break;
		case 'E':
			T.query();
			break;
		case 'F':
			T.print();
			break;
		case 'G':
			exit = 1;
			break;
		default:
			printf("输入错误！\n");
		}
		getline(cin, op);
		printf("Press enter to continue...\n");
		getchar();
		if (exit)break;
		else system("cls");
	}
	return 0;
}
void printHead()
{
	printf("**                       家谱管理系统                       **\n");
	printf("==============================================================\n");
	printf("**                       家谱管理系统                       **\n");
	printf("**                    请选择要执行的操作                    **\n");
	printf("**                       A--完善家谱                        **\n");
	printf("**                       B--添加成员                        **\n");
	printf("**                       C--局部解散                        **\n");
	printf("**                       D--修改成员姓名                    **\n");
	printf("**                       E--查询成员                        **\n");
	printf("**                       F--打印家谱                        **\n");
	printf("**                       G--退出程序                        **\n");
}

int readInt(bool (*range)(int) )
{
	int n;
	while (1)
	{
		cin >> n;
		if (cin.fail())
		{
			cout << "输入格式有误！\n";
			cin.clear();
			char* ch = new char[1000];
			cin.getline(ch, 1000);
			delete[]ch;
		}
		else if (range && !range(n))
		{
			cout << "数据范围有误！\n";
		}
		else break;
	}
	return n;
}

bool range(int n) { return n > 0; }
