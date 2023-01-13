#include<iostream>
#include<string>
using namespace std;

//函数声明
void Suspend();
void display(int*, int );
void readMatrix(int& , int*& );
void matrix_plus(int* , int* , int );
void matrix_multi(int* , int* , int );
void self_reflex(int* , int );
void symmetry(int* , int);
void transi(int* , int );

int main()
{
	//用一维数组模拟二维数组
	//二维数组中的(i,j)相当于一维数组中的(i*n+j)
	int* M, n;
	while (1)
	{
		readMatrix(n, M);
		int op;
		cout << "输入对应序号选择算法\nl:自反闭包\n2:传递闭包\n3:对称闭包\n4:退出\n";
		cin >> op;
		switch (op)
		{
		case 1:self_reflex(M,n); break;
		case 2:transi(M,n); break;
		case 3:symmetry(M,n); break;
		case 4:op = -1; break;
		default:
			cout << "错误输入！\n";
		}
		delete[]M;
		if (op == -1)break;
	}
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
函数名：matrix_plus
形式参数：int* , int* , int 
返回值：无
函数功能：矩阵相加，并把结果赋值给M1
********************************************************/
void matrix_plus(int* M1, int* M2, int n)
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			M1[i * n + j] = M1[i * n + j] || M2[i * n + j];
}

/*******************************************************
函数名：matrix_multi
形式参数：int* , int* , int
返回值：无
函数功能：方阵相乘，并把结果赋值给M1
********************************************************/
void matrix_multi(int* M1, int* M2, int n)
{
	//M3为辅助矩阵，记录矩阵乘法的结果
	int* M3 = new int[n * n];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			M3[i * n + j] = 0;
	//AB(i,j)=sum(A(i,k)*B(k,j))
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				//由于是逻辑运算，只要在析取式中有一项为1，结果就为1，
				if (M1[i * n + k] && M2[k * n + j])
				{
					M3[i * n + j] = 1;
					break;
				}
	//再将结果赋值回M1
	for (int i = 0; i < n * n; ++i)M1[i] = M3[i];
	delete[]M3;
}

/*******************************************************
函数名：self_reflex
形式参数：int* , int 
返回值：无
函数功能：求自反闭包
********************************************************/
void self_reflex(int* M, int n)
{
	//主对角线上元素赋值为1
	for (int i = 0; i < n; ++i)M[i * n + i] = 1;
	display(M, n);
}

/*******************************************************
函数名：symmetry
形式参数：int* , int 
返回值：无
函数功能：求对称闭包
********************************************************/
void symmetry(int* M, int n)
{
	//由于对称闭包有对称性，所以上三角矩阵和下三角矩阵相互对称，
	//所以只要正确求出上三角矩阵，下三角矩阵相当于直接将上三角的结果复制
	//即可，所以不需要辅助数组
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			M[i * n + j] = M[j * n + i] || M[i * n + j];
	display(M, n);
}

/*******************************************************
函数名：transi
形式参数：int* , int
返回值：无
函数功能：求传递闭包
********************************************************/
void transi(int* M, int n)
{
	//M_help是M的复制体
	int* M_help = new int[n * n];
	//M_res储存计算结果
	int* M_res = new int[n * n];
	//初始化
	for (int i = 0; i < n * n; ++i)M_res[i] = M_help[i] = M[i];
	for (int i = 0; i < n; ++i)
	{
		//求M^k
		matrix_multi(M, M_help, n);
		//将M^k加到结果中
		matrix_plus(M_res, M, n);
	}
	//展示结果
	display(M_res, n);
	delete[]M_res;
	delete[]M_help;
}
//暂停，待用户输入
void Suspend()
{
	string dump; getline(cin, dump);
	printf("\n\n\nPress enter to continue...\n");
	getchar();
}

