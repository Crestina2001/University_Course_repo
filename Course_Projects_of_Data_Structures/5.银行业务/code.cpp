
#include<iostream>
#include<string>
#include<cstdio>
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

int readInt()
{
	int n;
	
	while(1)
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
		else break;
	}
	return n;
}
int main()
{
	Queue<int> QA, QB;
	printf("�������Ŷ�������N��\t");
	int N;
	while(1)
	{
		N=readInt();
		if(N>0)break;
		printf("���뷶Χ����\n");
	}
	
	printf("�������Ŷ��ߵı�ţ�\n");
	for (int i = 0; i < N; ++i)
	{
		int x;
		x=readInt();
		if (x % 2)QA.push(x);
		else QB.push(x);
	}
//	QA.printQueue();
//	QB.printQueue();
	printf("ҵ������ɺ��˳���ǣ�\n");
	while (QA.size() && QB.size())
	{
		if (QA.size() >= 2) {
			cout << QA.pop() << ' ';
			cout << QA.pop() << ' ';
		}
		else cout << QA.pop() << ' ';
		cout << QB.pop() << ' ';
	}
	while (QB.size())cout << QB.pop() << ' ';
	while (QA.size())cout << QA.pop() << ' ';
	cout << "\b\n\n\n";
	 string s;
	 getline(cin,s);
	 printf("Print enter to continue...");
	 getchar();
	return 0;
}
