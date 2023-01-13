#include<iostream>
#include<string>
using namespace std;

//��������
void Suspend();
void display(int*, int);
void readMatrix(int&, int*&);
void warshall(int*, int);

int main()
{
	//��һά����ģ���ά����
	//��ά�����е�(i,j)�൱��һά�����е�(i*n+j)
	int* M, n;
	readMatrix(n, M);
	warshall(M, n);
	Suspend();
	return 0;
}

/*******************************************************
��������display
��ʽ������int*,int
����ֵ����
�������ܣ�չʾ�����ϵ����
********************************************************/
void display(int* M, int n)
{
	cout << "�����ϵ����Ϊ:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << M[i * n + j];
		cout << "\n";
	}
}

/*******************************************************
��������readMatrix
��ʽ������int&,int*&
����ֵ����
�������ܣ������ϵ����
********************************************************/
void readMatrix(int& n, int*& M)
{
	cout << "���������Ľ���:";
	cin >> n;
	cout << "�������ϵ����:\n";
	M = new int[n * n];
	for (int i = 0; i < n; i++)
	{
		cout << "\n";
		cout << "���������ĵ�" << i << "��Ԫ��(Ԫ���Կո�ָ�):\n";
		for (int j = 0; j < n; j++)
		{
			cin >> M[i * n + j];
			//�����û������зǷ����룬�ʽ����з�1������ת����1
			if (M[i * n + j])M[i * n + j] = 1;
		}
	}
}

/*******************************************************
��������warshall
��ʽ������int*,int
����ֵ����
�������ܣ�ͨ��warshall�㷨�󴫵ݱհ�
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

//��ͣ�����û�����
void Suspend()
{
	string dump; getline(cin, dump);
	printf("\n\n\nPress enter to continue...\n");
	getchar();
}

