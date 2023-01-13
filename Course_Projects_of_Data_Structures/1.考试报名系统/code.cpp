#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<string>
#include<Windows.h>
#define Search for (ElemType* p = head->next; p != tail; p = p->next)
using namespace std;
//
int getNum()
{
	int num;
	cin >> num;
	if (cin.fail())
	{
		cin.clear(), num = -1;
	}
	char ch = getchar();
	while (ch != ' ' && ch != '\n')ch = getchar(), num = -1;
	return num;
}
typedef struct student
{
	char* num;
	char* name;
	int age;
	char*sex;
	char* subject;
	student* last, * next;
	//���캯��������ѧ����Ϣ
	student()
	{
		num = new char[100];
		name = new char[100];
		sex = new char[5];
		subject = new char[100];
		cin >> num >> name >> sex >> age >> subject;
	}
	//�����κδ���Ĺ��캯��
	student(int num){}
	//�����������ͷ�����
	~student()
	{
		delete[]num;
		delete[]name;
		delete[]sex;
		delete[]subject;
	}
	student& operator=(const student& stu)
	{
		//��ֹ�Ը�ֵ
		if (this == &stu)return *this;
		//�ֱ𿽱���������
		strcpy(this->num, stu.num);
		strcpy(this->name, stu.name);
		strcpy(this->sex, stu.sex);
		strcpy(this->subject, stu.subject);
		age = stu.age;
		last = stu.last;
		next = stu.next;
		return *this;
	}
}ElemType;
class info_system
{
public:
	info_system()
	{
		//����ͷβָ��
		head = new ElemType(1);
		tail = new ElemType(1);
		cout << "�����뿼�������� ";
		//����������������
		while ((_size = getNum()) == -1 || _size < 1)
		{
			cout << "�����������������룡 ";
		}
		cout << "�����������뿼���Ŀ��ţ��������Ա������Լ��������" << endl;
		ElemType* las = head;
		head->next = tail;
		head->last = NULL;
		tail->last = head;
		tail->next = NULL;
		//���뿼������
		for (int i = 0; i < _size; ++i)
		{
			ElemType* cur = new ElemType;
			//��las֮���������
			insertAfter(las, cur);
			las = cur;
		}
	}
	//���ݿ����Ŀ��������ҿ���
	void search()
	{
		char* num = new char[100];
		cout << "�����뿼���Ŀ��ţ�";
		cin >> num;
		//����������Ϣ
		for (ElemType* p = head->next; p != tail; p = p->next)
		{
			//����ҵ��ÿ��ţ�����ÿ�������Ϣ
			if (!strcmp(num, p->num))
			{
				display(p);
				delete[]num;
				return;
			}
		};

		cout << "Not Found!" << endl;
		delete[]num;
	}
	void insert()
	{
		//����λ��
		cout << "��������Ҫ���뿼����λ�ã�";
		int pos;
		if ((pos = getNum()) == -1 || pos<1 || pos>_size + 1)
		{
			cout << "����λ�ô���" << endl;
			return;
		}
		//Ѱ��Ҫ����λ�õ�ǰһ��λ�ã���ָ��pָ����
		for(ElemType *p=head;p!=tail;p=p->next)
		{
			if (!(--pos))
			{
				cout << "��������Ҫ���뿼����ѧ�š����֡��Ա������Լ�����רҵ�� " << endl;
				ElemType* newE = new ElemType;
				newE->last = p, newE->next = p->next;
				p->next->last = newE, p->next = newE;
				cout << "��������Ѿ���ɣ�" << endl;
				++_size;
				return;
			}
		}
	}
	void del()
	{
		//����ɾ�������Ŀ���
		cout << "��������Ҫɾ���Ŀ����Ŀ���";
		char* num = new char[100];
		cin >> num;
		bool find = 0;
		//Ѱ��Ҫɾ���Ŀ�����Ϣ
		Search
		{
			if (!strcmp(num, p->num))
			{
				find = 1;
				cout << "��Ҫɾ���Ŀ�������Ϣ�ǣ�" << endl;
				//չʾ����Ϣ��
				display(p);
				//ɾ������
				p->last->next = p->next;
				p->next->last = p->last;
				delete p;
				--_size;
				break;
			}
		}
			if (!find)
				cout << "û�ҵ��ÿ�������Ϣ��" << endl;
		delete[]num;
	}
	//�޸�����
	void revise()
	{
		//���뿼���������ж�
		cout << "��������Ҫ�޸ĵĿ����Ŀ��ţ�";
		char* num = new char[100];
		cin >> num;
		for (ElemType* p = head->next; p != tail; p = p->next)
		{
			//�жϿ����Ƿ�ƥ��
			if (!strcmp(num, p->num))
			{
				cout << "��Ҫ�޸ĵĿ�������Ϣ�ǣ�" << endl;
				display(p);
				cout << "������ÿ����Ŀ��š��������Ա������Լ��������";
				//�����µĽڵ�newE
				ElemType* newE = new ElemType();
				newE->last = p->last;
				newE->next = p->next;
				//����student�����ص�operator=����newE��ֵ��ֵ��p
				*p = *newE;
				//ɾ��newE(newE���ֵ�Ѿ���������ֵ��p��
				delete newE;
				return;
			}
		}
		//������ʾ��û���ҵ�
		cout << "not Found! ";
	}
	//չʾ��������������
	void display()
	{
		if (!_size)
		{
			cout << "���Ա���ϵͳΪ�գ�" << endl;
			return;
		}
		//�ж��Ƿ��ǵ�һ�Σ�����ǣ���Ҫ�����ͷ
		bool fir = 1;
		for (ElemType* p = head->next; p != tail; p = p->next)
		{
			if (fir)
			{
				fir = 0;
				display(p);
			}
			else
				display(p,1);
		}
	}
	int getSize() { return _size; }
private:
	ElemType* head, * tail;
	int _size;
	void insertAfter(ElemType* e,ElemType* o)
	{
		o->last = e;
		o->next = e->next;
		e->next->last = o;
		e->next = o;
	}
	void display(ElemType* e, bool consistent = 0)
	{
		//consistentΪ1�����ͷ���������
		if(!consistent)
			cout << left << setw(10) << "����" << setw(10) << "����" << setw(10)
				<< "�Ա�" << setw(10) << "����" << setw(10) << "�������" << endl;
		cout << left << setw(10) << e->num << setw(10) << e->name << setw(10)
			<< e->sex << setw(10) << e->age << setw(10) << e->subject << endl;
	}
};
int main()
{
	info_system is;
	is.display();
	int ope;
	cout << "��������ɣ�������ת�������ҳ�棡";
	//����Sleep����ͣ����
	Sleep(3000);
	system("cls");
	while (1)
	{
		//������
		cout << "������Ҫ���еĲ���\n";
		cout << setw(10) << left << "1������" << setw(10) << left << "2��ɾ��"
			<< setw(10) << left << "3,����" << endl;
		cout << setw(10) << left << "4���޸�" << setw(10) << left << "5,���" << setw(10)
			<< left << "6������" << endl << setw(10) << left << "0���˳�" << endl;
		//�жϲ������Ƿ���ȷ
		ope = getNum();
		bool next_loop = 0;
		while (ope == -1)
		{
			cout << "�����ʽ�������������룡" << endl;
			ope = getNum();
		}
		if (!ope)
			break;
		switch (ope)
		{
		case 1:
			//����
			is.insert();
			break;
		case 2:
			//ɾ��
			is.del();
			break;
		case 3:
			//����
			is.search();
			break;
		case 4:
			//�޸�
			is.revise();
			break;
		case 5:
			//ͳ��
			is.display();
			break;
		case 6:
			//����
			system("cls");
			next_loop = 1;
			break;
		default:
			//����������ʾ
			cout << "�����������������룡" << endl;
		}
		if (next_loop)continue;//���������������ֱ�ӽ�����һ��ѭ��
		//�ж��Ƿ�Ҫ����
		cout << "�Ƿ���������Ҫ������������Y����y�����Ҫ�˳���������N����n): " << endl;
		bool ex = 0;
		while (1)
		{
			string sig;
			cin >> sig;
			if (sig == "Y" || sig == "y")
				break;
			else if (sig == "N" || sig == "n")
			{
				ex = 1;
				break;
			}
			else
				cout << "��������" << endl;
		}
		if (ex)
			break;
	}
	cout << "���˳������Ա���ϵͳ�й��� " << is.getSize() << " ������" << endl;
}
