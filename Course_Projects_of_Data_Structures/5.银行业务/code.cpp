
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

int readInt()
{
	int n;
	
	while(1)
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
		else break;
	}
	return n;
}
int main()
{
	Queue<int> QA, QB;
	printf("请输入排队总人数N：\t");
	int N;
	while(1)
	{
		N=readInt();
		if(N>0)break;
		printf("输入范围有误！\n");
	}
	
	printf("请输入排队者的编号：\n");
	for (int i = 0; i < N; ++i)
	{
		int x;
		x=readInt();
		if (x % 2)QA.push(x);
		else QB.push(x);
	}
//	QA.printQueue();
//	QB.printQueue();
	printf("业务处理完成后的顺序是：\n");
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
