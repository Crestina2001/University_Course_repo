#include<iostream>
#include<iomanip>
#include<time.h>
//macro definition
#define ERROR 0
#define OK 1
#define OVERFLOW -2
using namespace std;
//special define
typedef int Status;
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
};

template<class T>
class Sort
{
private:
	
public:
	Sort() {};
	void BubbleSort(T *arr,int _num)
	{
		long long exchangeTime = 0, compareTime = 0;
		int runTime;
		bool change = 1;//记录是否有发生交换
		clock_t startTime, endTime;
		startTime = clock();
		for (int i = _num; change && i > 0; --i)
		{
			change = 0;
			//一轮起泡过程
			for (int j = 1; j < i; ++j)
				if (arr[j] > arr[j + 1])
				{
					swap(arr[j], arr[j + 1]);
					change = 1;
					++exchangeTime;
				}
			compareTime += i - 1;
		}
		endTime = clock();
		runTime = double(endTime - startTime) * 1000 / CLOCKS_PER_SEC;
		cout << "冒泡排序所用时间：\t" << runTime << "ms\n";
		cout << "冒泡排序交换次数：\t" << exchangeTime << endl;
		cout << "冒泡排序比较次数：\t" << compareTime << endl;
	}
	void SelectSort(T *arr,int _num)
	{
		//记录时间部分
		long long exchangeTime = 0, compareTime = 0;
		int runTime;
		clock_t startTime, endTime;
		startTime = clock();
		//选择排序部分
		for (int i = 1; i <= _num; ++i)
		{
			int k = i;
			for (int j = i + 1; j <= _num; ++j)
				if (arr[j] < arr[k]) { k = j; ++exchangeTime; }
			//将i与k进行交换
			if (k != i) { swap(arr[i], arr[k]); exchangeTime += 3; }//一次赋值等效于1/3次交换
		}
		endTime = clock();
		compareTime = (long long)_num * ((long long)_num - 1) / 2;
		runTime = double(endTime - startTime) * 1000 / CLOCKS_PER_SEC;
		exchangeTime /= 3;
		cout << "选择排序所用时间：\t" << runTime << "ms\n";
		cout << "选择排序交换次数：\t" << exchangeTime << endl;
		cout << "选择排序比较次数：\t" << compareTime << endl;
	}
	void InsertSort(T *arr,int _num)
	{
		long long exchangeTime = 0, compareTime = 0;
		int runTime;
		clock_t startTime, endTime;
		startTime = clock();
		for (int i = 2; i <= _num; ++i)
		{
			if (arr[i] < arr[i - 1])
			{
				arr[0] = arr[i];
				arr[i] = arr[i - 1];
				int j = 0;
				//寻找小于待插入元素的元素
				for (j = i - 2; arr[0] < arr[j]; --j)
				{
					arr[j + 1] = arr[j];
					++compareTime;
				}
				arr[j + 1] = arr[0];
				exchangeTime += i - j + 2;
			}
		}
		endTime = clock();
		exchangeTime /= 3;//三次赋值相当于一次交换
		runTime = double(endTime - startTime) * 1000 / CLOCKS_PER_SEC;
		cout << "直接插入排序所用时间：\t" << runTime << "ms\n";
		cout << "直接插入排序交换次数：\t" << exchangeTime << endl;
		cout << "直接插入排序比较次数：\t" << compareTime << endl;
	}
	void ShellInsert(T*arr,int _num, int dk,long long &exchangeTime)
	{
		//arr[0]暂存元素
		for(int i=dk+1;i<=_num;++i)
			if (arr[i] < arr[i - dk])
			{//需要将arr[i]插入有序增量子表
				arr[0] = arr[i];
				int j;
				//记录后移，寻找插入位置
				for (j = i - dk; j > 0 && arr[0] < arr[j]; j -= dk)
					arr[j + dk] = arr[j];
				arr[j + dk] = arr[0];//插入
				exchangeTime += 2 + (i - j ) / dk; 
			}
	}
	void ShellSort(T *arr,int _num)
	{
		int dlta[9] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1 };//Marcin Ciura间距值
		long long exchangeTime = 0, compareTime = 0;
		int runTime;
		clock_t startTime, endTime;
		startTime = clock();
		for (int i = 0; i < 9; ++i)
		{
			ShellInsert(arr, _num, dlta[i], exchangeTime);
			compareTime += _num - dlta[i];
		}
		endTime = clock();
		runTime = double(endTime - startTime) * 1000 / CLOCKS_PER_SEC;
		exchangeTime /= 3;
		cout << "希尔排序所用时间：\t" << runTime << "ms\n";
		cout << "希尔排序交换次数：\t" << exchangeTime << endl;
		cout << "希尔排序比较次数：\t" << compareTime << endl;
	}
	int Partition(T *arr,int low, int high,long long &exchangeTime,long long &compareTime)
	{
		int mid = (low + high) >> 1;
		if (arr[low] < arr[mid])swap(arr[mid], arr[low]);
		if (arr[high] < arr[low])swap(arr[high], arr[low]);
		if (arr[low] < arr[mid])swap(arr[mid], arr[low]);
		arr[0] = arr[low];//取子表的第一个作为枢轴记录
		int pivotKey = arr[low];
		compareTime += high - low;
		exchangeTime += high - low;
		while (low < high)
		{
			while (low < high && pivotKey <= arr[high])--high;
			arr[low] = arr[high];//将比枢轴小的记录移动到低端
			while (low < high && arr[low] <= pivotKey)++low;
			arr[high] = arr[low];//将比枢轴大的记录移动到高端
			exchangeTime += 2;
			++compareTime;
		}
		arr[low] = arr[0];
		exchangeTime += 11;
		return low;//返回枢轴位置
	}
	void QuickSort(T *arr,int _num)
	{
		long long exchangeTime = 0, compareTime = 0;
		int runTime;
		clock_t startTime, endTime;
		startTime = clock();
		Stack<int>S;
		int low = 1, high = _num;
		//采用非递归算法，防止在最坏情况下栈的深度为O(n)导致栈溢出。
		if (low < high)
		{
			int mid = Partition(arr, low, high, exchangeTime,compareTime);
			if (low < mid - 1) { S.push(low); S.push(mid - 1); }
			if (mid + 1 < high) { S.push(mid + 1); S.push(high); }
		}
		while (S.size())
		{
			int q = S.pop(), p = S.pop();
			int mid = Partition(arr, p, q, exchangeTime, compareTime);
			if (p < mid - 1) { S.push(p); S.push(mid - 1); }
			if (mid + 1 < q) { S.push(mid + 1); S.push(q); }
		}
		endTime = clock();
		runTime = double(endTime - startTime) * 1000 / CLOCKS_PER_SEC;
		exchangeTime /= 3;
		cout << "快速排序所用时间：\t" << runTime << "ms\n";
		cout << "快速排序交换次数：\t" << exchangeTime << endl;
		cout << "快速排序比较次数：\t" << compareTime << endl;
	}
	void HeapAdjust(T* arr, int s, int m,long long &exchangeTime,long long &compareTime)
	{
		int rc = arr[s];
		for (int j = (s << 1); j <= m; j = (j << 1))
		{
			//沿值较大的孩子向下筛选
			if (j < m && arr[j] < arr[j + 1])++j;
			if (arr[j] <= rc)break;
			arr[s] = arr[j]; s = j;
			exchangeTime += 2;
			compareTime += 2;
		}
		arr[s] = rc;
		exchangeTime += 2;
	}
	void HeapSort(T*arr,int _num)
	{
		long long exchangeTime = 0, compareTime = 0;
		int runTime;
		clock_t startTime, endTime;
		startTime = clock();
		for (int i =( _num >> 1); i > 0; --i)
			HeapAdjust(arr, i, _num,exchangeTime,compareTime);
		for (int i = _num; i > 1; --i)
		{
			swap(arr[1], arr[i]);
			//将arr重新调整为大顶堆
			HeapAdjust(arr, 1, i - 1, exchangeTime,compareTime);
		}
		endTime = clock();
		runTime = double(endTime - startTime) * 1000 / CLOCKS_PER_SEC;
		exchangeTime /= 3;
		cout << "堆排序所用时间：\t" << runTime << "ms\n";
		cout << "堆排序交换次数：\t" << exchangeTime << endl;
		cout << "堆排序比较次数：\t" << compareTime << endl;
	}
	void merge(T *arr,int low, int high,int mid,long long &exchangeTime) {
		//gap小于等于32时使用插入排序
		if (high - low <= 33)
		{
			for (int i = mid; i < high; ++i)
			{
				if (arr[i] < arr[i - 1])
				{
					arr[0] = arr[i];
					arr[i] = arr[i - 1];
					int j;
					for (j = i - 2; j >= low && arr[0] < arr[j]; --j) { arr[j + 1] = arr[j]; ++exchangeTime; }
					arr[j + 1] = arr[0];
					exchangeTime += 3;
				}
			}
			return;
		}
		//否则使用递归排序
		T* tempArr = new T[mid - low];
		//辅助数组只需要复制一半
		for (int i = low; i < mid; ++i)tempArr[i - low] = arr[i];
		int p = low, q = mid, cur = p;
		while (p < mid || q < high)
		{
			if (q >= high || (p < mid && tempArr[p - low] < arr[q]))
				arr[cur++] = tempArr[p++ - low];
			else arr[cur++] = arr[q++];
		}
		exchangeTime += (high + mid - 2 * low);
		delete[]tempArr;
	}
	void MergeSort(T* arr, int _num)
	{
		long long exchangeTime = 0, compareTime = 0;
		int runTime;
		clock_t startTime, endTime;
		startTime = clock();
		int n = _num;
		int s = 2, i;
		while (s <= n) {
			i = 1;
			while (i + s <= n + 1) {
				//只有在arr[mid - 1] > arr[mid]时才进行归并
				if (arr[i + s / 2 - 1] > arr[i + s / 2])
				{
					merge(arr, i, i + s, i + s / 2, exchangeTime);
					compareTime += s;
				}
				i += s;
			}
			//cout << i<<' '<<i + s / 2 << endl;
			//处理末尾残余部分
			if (i + s / 2 < n + 1) merge(arr, i, n + 1, i + s / 2, exchangeTime);
			compareTime += n + 1 - i;
			s = (s << 1);
		}
		//最后再从头到尾处理一遍
		 merge(arr, 1, n + 1, s / 2 + 1, exchangeTime);
		endTime = clock();
		compareTime += n;
		runTime = double(endTime - startTime) * 1000 / CLOCKS_PER_SEC;
		exchangeTime /= 3;
		cout << "归并排序所用时间：\t" << runTime << "ms\n";
		cout << "归并排序交换次数：\t" << exchangeTime << endl;
		cout << "归并排序比较次数：\t" << compareTime << endl;
	}
	int maxbit(T* data, int n) //辅助函数，求数据的最大位数
	{
		T maxData = data[1];      ///< 最大数
		/// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数
		for (int i = 2; i <= n; ++i)
		{
			if (maxData < data[i])
				maxData = data[i];
		}
		int d = 1;
		int p = 10;
		while (maxData >= p)
		{
			maxData /= 10;
			++d;
		}
		return d;

	}
	void radixsort(T* data, int _num) //基数排序
	{
		long long exchangeTime = 0, compareTime = 0;
		int runTime;
		clock_t startTime, endTime;
		startTime = clock();
		int n = _num;
		int d = maxbit(data, n);
		T* tmp = new T[n + 1];
		int* count = new int[10]; //计数器
		int i, j, k;
		int radix = 1;
		for (i = 1; i <= d; i++) //进行d次排序
		{
			for (j = 0; j < 10; j++)
				count[j] = 0; //每次分配前清空计数器
			for (j = 1; j <= n; j++)
			{
				k = (data[j] / radix) % 10; //统计每个桶中的记录数
				count[k]++;
			}
			for (j = 1; j < 10; j++)
				count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
			for (j = n; j > 0; j--) //将所有桶中记录依次收集到tmp中
			{
				k = (data[j] / radix) % 10;
				tmp[count[k]] = data[j];
				count[k]--;
			}
			for (j = 1; j <= n; j++) //将临时数组的内容复制到data中
				data[j] = tmp[j];
			radix = radix * 10;
		}
		endTime = clock();
		exchangeTime = (2 * n + 7) * d;
		runTime = double(endTime - startTime) * 1000 / CLOCKS_PER_SEC;
		cout << "基数排序所用时间：\t" << runTime << "ms\n";
		cout << "基数排序交换次数：\t" << exchangeTime << endl;
		cout << "基数排序比较次数：\t" << compareTime << endl;
		delete[]tmp;
		delete[]count;
	}
	bool isSorted(T* arr,int _num)
	{
		for (int i = 1; i < _num; ++i)if (arr[i + 1] < arr[i])return 0;
		return 1;
	}
	
};
void printHead();
template<class T>
void display(T*arr,int _num)
	{
		cout << "\n排好序的数组为：\n";
		for (int i = 1; i <= _num; ++i)
		{
			if (i % 30 == 0)cout.put('\n');
			cout << arr[i] << ' ';
		}
		cout.put('\n');
	}
typedef struct
{
	int data;
	int next;
}ALCell;

template<class T>
class Array
{
private:
	T* to_sort, * sorted;
	int _num;
public:
	Array(int n)
	{
		_num = n;
		to_sort = new T[n + 1];
		sorted = new T[n + 1];
		srand(time(0));
		for (int i = 1; i <= n; ++i)to_sort[i] = rand();
		
	}
	T* provide_an_array()
	{
		for (int i = 1; i <= _num; ++i)sorted[i] = to_sort[i];
		return sorted;
	}
	int size() { return _num; }
	~Array() 
	{ 
		delete[]to_sort; 
		delete[]sorted;
	}
};

int main()
{
	int n;
	printHead();
	printf("\n请输入要产生的随机数的个数：");
	cin >> n;
	Array<int> Arr(n);
	Sort<int> S;
//	S.ShellSort();
//	S.display();
	int op;
	while (1)
	{
		bool ex = 0;
		printf("\n请选择排序算法：\t");
		cin >> op;
		int* arr = Arr.provide_an_array(), n = Arr.size();
		switch (op)
		{
		case 1:
			S.BubbleSort(arr,n);
			break;
		case 2:
			S.SelectSort(arr,n);
			//cout << S.isSorted(arr, n) << endl;
			break;
		case 3:
			S.InsertSort(arr,n);
			break;
		case 4:
			S.ShellSort(arr,n);
			//cout << S.isSorted(arr, n) << endl;
			break;
		case 5:
			S.QuickSort(arr, n);
			break;
		case 6:
			S.HeapSort(arr, n);
			break;
		case 7:
			S.MergeSort(arr, n);
			//display(arr, n);
			//cout << S.isSorted(arr, n);
			break;
		case 8:
			S.radixsort(arr, n);
			//display(arr, n);
			//cout << S.isSorted(arr, n);
			break;
		default:
			ex = 1;
		}
		if (ex)break;
	}
//	S.display();
	return 0;
}
void printHead()
{
	printf("**                        排序算法比较                          **\n");
	printf("==================================================================\n");
	printf("**                        1---冒泡排序                          **\n");
	printf("**                        2---选择排序                          **\n");
	printf("**                        3---直接插入排序                      **\n");
	printf("**                        4---希尔排序                          **\n");
	printf("**                        5---快速排序                          **\n");
	printf("**                        6---堆排序                            **\n");
	printf("**                        7---归并排序                          **\n");
	printf("**                        8---基数排序                          **\n");
	printf("**                        9---退出程序                          **\n");
	printf("==================================================================\n");

}
