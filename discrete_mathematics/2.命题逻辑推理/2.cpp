#include<iostream>
#include<string>
using namespace std;
#define NUM_VARIABLE 5
string txt[][2] =
{
	"ӪҵԱAû��͵�ֱ�","ӪҵԱA͵���ֱ�",
	"ӪҵԱBû��͵�ֱ�","ӪҵԱB͵���ֱ�",
	"������Ӫҵʱ��","��������Ӫҵʱ��",
	"B�ṩ��֤�ݲ���ȷ","B�ṩ��֤����ȷ",
	"����������","����δ����"
};
//��ͣ�����û�����
void Suspend()
{

	printf("\n\n\nPress enter to continue...\n");
	getchar();
}
int main()
{
	bool a[NUM_VARIABLE];
	int cnt = 0;
	for (int i = 0; i < (1 << NUM_VARIABLE); ++i)
	{
		for (int j = 0; j < NUM_VARIABLE; ++j)
			a[j] = i & (1 << j);//�������������ֵ
		//����ǳ��渳ֵ����������������¼�������
		if (((a[0] || a[1]) && (!a[0] || a[2]) && (!a[3] || a[4]) && (a[3] || !a[2]) && !a[4]))
		{
			cout << "���" << ++cnt << ": \n";
			for (int j = 0; j < NUM_VARIABLE; ++j)
				if (j != NUM_VARIABLE - 1)cout << txt[j][a[j]] << ",\n";
				else cout << txt[j][a[j]] << "��\n";
		}
	}
	cout << "\n�ܹ���" << cnt << "�������";
	Suspend();
	return 0;
}
