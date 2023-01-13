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
    T* e; //�洢Ԫ����Ϣ 
    int S; //��ǰԪ�ظ��� 
    int MAXS; //����ܴ洢���ٸ�Ԫ�� 
    int _front; //��ͷ 
    int _rear; //��β 
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
    T front() { if (!S) { printf("����Ϊ�գ��޷�������\n"); exit(-1); } return *(e + _front); }
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
    //��e����INIT_SIZE��С�Ŀռ�
    e = new(nothrow)T[INIT_SIZE];
    //������
    if (!e)exit(OVERFLOW);
}

template<class T>
Status Queue<T>::popQueue(T& ele)
{
    //����Ϊ��
    if (!S)return ERROR;
    //���´�С
    --S;
    //��¼ɾ����Ԫ��
    ele = e[_front];
    //����_front��λ��
    _front = (_front + 1) % MAXS;
    return OK;
}

template<class T>
T Queue<T>::pop()
{
    if (!S) { printf("����Ϊ�գ��޷�������\n"); exit(-1); }
    //���´�С
    --S;
    //��¼ɾ����Ԫ��
    T ele = e[_front];
    //����_front��λ��
    _front = (_front + 1) % MAXS;
    return ele;
}

template<class T>
void Queue<T>::printQueue()
{
    if (!S)
    {
        cout << "����Ϊ�գ�" << endl;
        return;
    }
    cout << "���дӶ�ͷ����β������" << endl;
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
    //���������������������Ŀռ�
    if (S == MAXS)
    {
        //��¼��λ��
        T* oldE = e;
        //�����¿ռ�
        e = new(nothrow) T[MAXS *= 2];
        if (!e)exit(OVERFLOW);
        //���ɴ����ֵת�Ƶ���λ��
        for (int i = 0; i < S; ++i)e[i] = oldE[(i + _front) % S];
        //����_front��_rear��ֵ
        _front = 0, _rear = S;
        //ɾ����λ��
        delete[]oldE;
    }
    //������Ԫ��
    e[_rear] = ele;
    //����_rear��ֵ
    _rear = (_rear + 1) % MAXS;
    //���´�С
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
			cout << parent->name << "�ĵ�һ�����Ϊ��\n";
			for (p = parent->firstchild; p; p = p->nextsibling)cout << p->name << ' ';
			cout.put('\n');
		}
		else cout << parent->name << "�޺󱲣�\n";
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
			printf("���ȴ���һ�����ף�\n���������ȵ�������\t");
			cin >> name;
			root = new CSNode{ name,NULL,NULL,NULL,NULL };
			cout << "�˼��׵������ǣ�" << name << endl;
			++_n;
			return;
		}
		printf("������Ҫ������ͥ���˵�������\t");
		cin >> name;
		CSNode* parent = search(root, name);
		if (!parent) { cout << "�ڼ�����û���ҵ�" << name << "!\n"; return; }
		if (parent->firstchild) { cout << name << "�Ѿ��к����ˣ�\n"; return; }
		int n;
		cout << "������" << name << "�Ķ�Ů����������������������\t";
		n = readInt(range);
		_n += n;
		cout << "������" << name << "�Ķ�Ů������\n";
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
			printf("���ȴ���һ�����ף�\n���������ȵ�������\t");
			cin >> name;
			root = new CSNode{ name,NULL,NULL,NULL,NULL };
			cout << "�˼��׵������ǣ�" << name << endl;
			return;
		}
		printf("������Ҫ��Ӻ�����˵�������\t");
		cin >> name;
		CSNode* parent = search(root, name);
		if (!parent) { cout << "�ڼ�����û���ҵ�" << name << "!\n"; return; }
		cout << "������" << name << "��ӵĺ����������\n";
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
		if (!root) { printf("����Ϊ�գ�\n"); return; }
		printf("������Ҫ��ɢ��ͥ���˵�������\t");
		cin >> name;
		CSNode* parent = search(root, name);
		if (!parent) { cout << "�ڼ�����û���ҵ�" << name << "!\n"; return; }
		print_decsendents(parent);
		CSNode* child = parent->firstchild;
		deleteNodeFromSiblings(parent);
		del(child);
	}
	void query()
	{
		string name;
		if (!root) { printf("����Ϊ�գ�\n"); return; }
		printf("������Ҫ��ѯ���˵�������\t");
		cin >> name;
		CSNode* parent = search(root, name);
		if (!parent) { cout << "�ڼ�����û���ҵ�" << name << "!\n"; return; }
		if (parent->parent)cout << parent->parent->name << "Ϊ" << parent->name << "����\n";
		else cout << parent->name << "������\n";
		if (parent->firstchild)
		{
			CSNode* p;
			cout << parent->name << "�ĵ�һ�����Ϊ��\n";
			for (p = parent->firstchild; p; p = p->nextsibling)cout << p->name << ' ';
			cout.put('\n');
		}
		else cout << parent->name << "�޺󱲣�\n";
	}
	void print()
	{
		if (!root) { printf("����Ϊ�գ�\n"); return; }
		printf("�ü����г�Ա��Ϊ��%d\n", _n);
		cout << "�ü��׵�������" << root->name << endl << endl;
		Queue<CSNode*>Q;
		Q.push(root);
		int gene = 1, num[2];
		num[0] = 1, num[1] = 0;
		bool flag = 0;
		while (Q.size())
		{
			CSNode* p = Q.pop();
			if (!p->firstchild) { cout << p->name << "�޺����\n"; }
			else
			{
				cout << p->name << "�ĺ����У�\n";
				for (CSNode* q = p->firstchild; q; q = q->nextsibling) { cout << q->name << ' '; Q.push(q); ++num[gene % 2]; }
				cout.put('\n');
				flag = 1;
			}
			if (--num[(gene - 1) % 2] == 0 && num[gene % 2]&&flag) { cout << "----�����ǵ� " << gene++ << " ���----\n\n"; flag = 0; }
		}
	}
	void revise()
	{
		if (!root) { printf("����Ϊ�գ�\n"); return; }
		string name;
		printf("������Ҫ�޸ĵ���ԭ�ȵ�������\t");
		cin >> name;
		CSNode* parent = search(root, name);
		if (!parent) { cout << "�ڼ�����û���ҵ�" << name << "!\n"; return; }
		printf("��������ĺ��������\t");
		cin >> parent->name;
		cout << name << "�Ѿ����޸ĳ�" << parent->name << endl;
	}
	
};
void printHead();
int main()
{
	CSTree T;
	while (1)
	{
		printHead();
		printf("����������룺\n");
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
			printf("�������\n");
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
	printf("**                       ���׹���ϵͳ                       **\n");
	printf("==============================================================\n");
	printf("**                       ���׹���ϵͳ                       **\n");
	printf("**                    ��ѡ��Ҫִ�еĲ���                    **\n");
	printf("**                       A--���Ƽ���                        **\n");
	printf("**                       B--��ӳ�Ա                        **\n");
	printf("**                       C--�ֲ���ɢ                        **\n");
	printf("**                       D--�޸ĳ�Ա����                    **\n");
	printf("**                       E--��ѯ��Ա                        **\n");
	printf("**                       F--��ӡ����                        **\n");
	printf("**                       G--�˳�����                        **\n");
}

int readInt(bool (*range)(int) )
{
	int n;
	while (1)
	{
		cin >> n;
		if (cin.fail())
		{
			cout << "�����ʽ����\n";
			cin.clear();
			char* ch = new char[1000];
			cin.getline(ch, 1000);
			delete[]ch;
		}
		else if (range && !range(n))
		{
			cout << "���ݷ�Χ����\n";
		}
		else break;
	}
	return n;
}

bool range(int n) { return n > 0; }
