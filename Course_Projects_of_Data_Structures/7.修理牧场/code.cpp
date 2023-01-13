#include<iostream>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<time.h>
using namespace std;
typedef long long ll;
template<class T>
class Heap
{
private:
	T* Data;
	int _size;
	int _capacity;
	const int INIT_SIZE = 100;
	T Max(T a, T b) { return a > b ? a : b; }
	T Min(T a, T b) { return a < b ? a : b; }
public:
	Heap() :_size(0) { _capacity = INIT_SIZE; Data = new T[_capacity]; }

	Heap(int );
	Heap& operator=(const Heap& H)
	{
		_size = H._size, _capacity=H._capacity;
		delete[]Data;
		Data = new T[_capacity];
		for (int i = 1; i <= _size; ++i)Data[i] = H.Data[i];
		return *this;
	}
	Heap(const Heap& );
	void insert(T );
	T top() { return Data[1]; }
	T pop();
	int size() { return _size; }
	int empty() { return !_size; }
	void print(){for (int i = 1; i <= _size; ++i)cout << Data[i] << ' ';cout << endl;}
};

template<class T>
 Heap<T>::Heap(int n) :_size(0)
{
	if (n > INIT_SIZE)_capacity = (n + 1) * 2;
	else _capacity = INIT_SIZE + 1;
	Data = new T[_capacity];
	T x;
	for (int i = 0; i < n; ++i)
	{
		cin >> x;
		insert(x);
		//	cout << top() << endl;
	}

}

 template<class T>
 Heap<T>::Heap(const Heap& H) :_size(H._size), _capacity(H._capacity), INIT_SIZE(H.INIT_SIZE)
 {
	 Data = new T[_capacity];
	 for (int i = 1; i <= _size; ++i)Data[i] = H.Data[i];
 }

 template<class T>
 void Heap<T>::insert(T e)
 {
	 if (_size + 2 >= _capacity)
	 {
		 T* oldData = Data;
		 Data = new T[(_capacity << 1)];
		 for (int i = 1; i <= _size; ++i)Data[i] = oldData[i];
		 delete[]oldData;
		 _capacity <<= 1;
	 }
	 Data[++_size] = e;
	 int i = _size;
	 while (i > 1 && Data[i] < Data[i / 2])
	 {
		 swap(Data[i], Data[i / 2]);
		 i >>= 1;
	 }
 }

 template<class T>
 T Heap<T>:: pop()
 {
	 if (!_size) { printf("堆中没有元素！\n"); exit(-1); }
	 T e = Data[1];
	 swap(Data[1], Data[_size--]);
	 int i = 1;
	 while (i * 2 <= _size)
	 {
		 int k;
		 if (i * 2 == _size || Data[i * 2] < Data[i * 2 + 1])
			 k = (i << 1);
		 else k = (i << 1) + 1;
		 //cout << k << endl;
		 if (Data[k] < Data[i])
		 {
			 swap(Data[i], Data[k]);
			 i = k;
		 }
		 else break;
	 }
	 return e;
 }

int readInt(bool (*)(int) = NULL);
bool range(int);
int main()
{
	int n;
	printf("请输入要锯成的块数：\t");
	n = readInt(range);
	printf("请输入各个块数的长度：\n");
	Heap<ll> H(n);
	ll SUM = 0;
	while (H.size() > 1)
	{
		ll len = H.pop() + H.pop();
		SUM += len;
		H.insert(len);
	}
	cout << "总共花费的时间为：\t" << SUM;
	string dump;
	getline(cin,dump);
	printf("\n\n\nprint enter to continue...");
	getchar();
	return 0;

}

int readInt(bool (*range)(int))
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
