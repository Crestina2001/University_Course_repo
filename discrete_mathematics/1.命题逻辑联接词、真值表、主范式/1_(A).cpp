#include <iostream>
#include <windows.h>
using namespace std;
void printHead(); 
void calcu(int* a, int i, int j);
void printRes(int* a);
int main()
{
	int a[4];
	int i = -1, j = -1;
	char s;
tt:	printHead();
	cout << "\n  ������P��ֵ��0��1��,�Իس�����:";
	cin>>i;  //��ȡP��ֵ
	if (i != 0 && i != 1)
	{
		cout<<"\n  P��ֵ��������,����������!";
		Sleep(2000);
		system("cls");  //����
		goto tt;
	}
	cout<<"\n  ������Q��ֵ��0��1��,�Իس�����:";
	cin>>j;  //��ȡQ��ֵ
	if (j != 0 && j != 1)
	{
		cout<<"\n  Q��ֵ��������,����������!";
		Sleep(2000);
		system("cls");  //����
		goto tt;
	}
	calcu(a, i, j);
	printRes(a);
bb:cout<<"\n�Ƿ��������?��y/n��";  //ѯ���Ƿ��������
	cin >> s;
	if (s == 'y' || s == 'n')
	{
		if (s == 'y')
		{
			system("cls");  //����
			goto tt;  //���ض���
		}
		else
		{
			cout<<"��ӭ�´��ٴ�ʹ��!\n";  //�˳�
			return 0;
		}
	}
	else
	{
		cout<<"�������,����������!\n"; //����У��
		goto bb;
	}
	return 0;
}
void printHead()
{
	cout << "***************************************\n";  //����
	cout << "**                                   **\n";
	cout << "**        ��ӭ�����߼��������       **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
}
void calcu(int* a, int i, int j)
{
	a[0] = i && j;  //������
	a[1] = i || j;  //������
	a[2] = (!i) || j;  //�̺����㣬����ת��Ϊ������ʽ
	a[3] = ((!i) || j) && ((!j) || i);  //��ֵ���㣬����ת��Ϊ������ʽ
}//��������
void printRes(int* a)
{
	cout << "\n\n  ��ȡ:\n       P/\\Q = " << a[0] << endl;  //������
	cout << "  ��ȡ:\n       P\\/Q = " << a[1] << endl;
	cout << "  ����:\n       P->Q = " << a[2] << endl;
	cout << "  ˫����:\n       P<->Q = " << a[3] << endl;
}//���������
