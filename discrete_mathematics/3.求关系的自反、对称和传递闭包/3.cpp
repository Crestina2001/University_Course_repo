#include<iostream>
#include<string>
using namespace std;

//��������
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
	//��һά����ģ���ά����
	//��ά�����е�(i,j)�൱��һά�����е�(i*n+j)
	int* M, n;
	while (1)
	{
		readMatrix(n, M);
		int op;
		cout << "�����Ӧ���ѡ���㷨\nl:�Է��հ�\n2:���ݱհ�\n3:�ԳƱհ�\n4:�˳�\n";
		cin >> op;
		switch (op)
		{
		case 1:self_reflex(M,n); break;
		case 2:transi(M,n); break;
		case 3:symmetry(M,n); break;
		case 4:op = -1; break;
		default:
			cout << "�������룡\n";
		}
		delete[]M;
		if (op == -1)break;
	}
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
��������matrix_plus
��ʽ������int* , int* , int 
����ֵ����
�������ܣ�������ӣ����ѽ����ֵ��M1
********************************************************/
void matrix_plus(int* M1, int* M2, int n)
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			M1[i * n + j] = M1[i * n + j] || M2[i * n + j];
}

/*******************************************************
��������matrix_multi
��ʽ������int* , int* , int
����ֵ����
�������ܣ�������ˣ����ѽ����ֵ��M1
********************************************************/
void matrix_multi(int* M1, int* M2, int n)
{
	//M3Ϊ�������󣬼�¼����˷��Ľ��
	int* M3 = new int[n * n];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			M3[i * n + j] = 0;
	//AB(i,j)=sum(A(i,k)*B(k,j))
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				//�������߼����㣬ֻҪ����ȡʽ����һ��Ϊ1�������Ϊ1��
				if (M1[i * n + k] && M2[k * n + j])
				{
					M3[i * n + j] = 1;
					break;
				}
	//�ٽ������ֵ��M1
	for (int i = 0; i < n * n; ++i)M1[i] = M3[i];
	delete[]M3;
}

/*******************************************************
��������self_reflex
��ʽ������int* , int 
����ֵ����
�������ܣ����Է��հ�
********************************************************/
void self_reflex(int* M, int n)
{
	//���Խ�����Ԫ�ظ�ֵΪ1
	for (int i = 0; i < n; ++i)M[i * n + i] = 1;
	display(M, n);
}

/*******************************************************
��������symmetry
��ʽ������int* , int 
����ֵ����
�������ܣ���ԳƱհ�
********************************************************/
void symmetry(int* M, int n)
{
	//���ڶԳƱհ��жԳ��ԣ����������Ǿ���������Ǿ����໥�Գƣ�
	//����ֻҪ��ȷ��������Ǿ��������Ǿ����൱��ֱ�ӽ������ǵĽ������
	//���ɣ����Բ���Ҫ��������
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			M[i * n + j] = M[j * n + i] || M[i * n + j];
	display(M, n);
}

/*******************************************************
��������transi
��ʽ������int* , int
����ֵ����
�������ܣ��󴫵ݱհ�
********************************************************/
void transi(int* M, int n)
{
	//M_help��M�ĸ�����
	int* M_help = new int[n * n];
	//M_res���������
	int* M_res = new int[n * n];
	//��ʼ��
	for (int i = 0; i < n * n; ++i)M_res[i] = M_help[i] = M[i];
	for (int i = 0; i < n; ++i)
	{
		//��M^k
		matrix_multi(M, M_help, n);
		//��M^k�ӵ������
		matrix_plus(M_res, M, n);
	}
	//չʾ���
	display(M_res, n);
	delete[]M_res;
	delete[]M_help;
}
//��ͣ�����û�����
void Suspend()
{
	string dump; getline(cin, dump);
	printf("\n\n\nPress enter to continue...\n");
	getchar();
}

