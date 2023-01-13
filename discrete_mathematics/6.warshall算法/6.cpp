#include<iostream>
#include<string>
using namespace std;

//函数声明
void Suspend();
void display(int*, int);
void readMatrix(int&, int*&);
void warshall(int*, int);

int main()
{
	//用一维数组模拟二维数组
	//二维数组中的(i,j)相当于一维数组中的(i*n+j)
	int* M, n;
	readMatrix(n, M);
	warshall(M, n);
	Suspend();
	return 0;
}

/*******************************************************
函数名：display
形式参数：int*,int
返回值：无
函数功能：展示所求关系矩阵
********************************************************/
void display(int* M, int n)
{
	cout << "所求关系矩阵为:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << M[i * n + j];
		cout << "\n";
	}
}

/*******************************************************
函数名：readMatrix
形式参数：int&,int*&
返回值：无
函数功能：读入关系矩阵
********************************************************/
void readMatrix(int& n, int*& M)
{
	cout << "请输入矩阵的阶数:";
	cin >> n;
	cout << "请输入关系矩阵:\n";
	M = new int[n * n];
	for (int i = 0; i < n; i++)
	{
		cout << "\n";
		cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔):\n";
		for (int j = 0; j < n; j++)
		{
			cin >> M[i * n + j];
			//由于用户可能有非法输入，故将所有非1的输入转换成1
			if (M[i * n + j])M[i * n + j] = 1;
		}
	}
}

/*******************************************************
函数名：warshall
形式参数：int*,int
返回值：无
函数功能：通过warshall算法求传递闭包
********************************************************/
void warshall(int* M, int n)
{
	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (M[i * n + k] && M[k * n + j])M[i * n + j] = 1;
	}
	display(M, n);
}

//暂停，待用户输入
void Suspend()
{
	string dump; getline(cin, dump);
	printf("\n\n\nPress enter to continue...\n");
	getchar();
}

