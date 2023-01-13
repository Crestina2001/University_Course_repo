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
	//构造函数，输入学生信息
	student()
	{
		num = new char[100];
		name = new char[100];
		sex = new char[5];
		subject = new char[100];
		cin >> num >> name >> sex >> age >> subject;
	}
	//不做任何处理的构造函数
	student(int num){}
	//析构函数，释放数据
	~student()
	{
		delete[]num;
		delete[]name;
		delete[]sex;
		delete[]subject;
	}
	student& operator=(const student& stu)
	{
		//防止自赋值
		if (this == &stu)return *this;
		//分别拷贝数据内容
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
		//建立头尾指针
		head = new ElemType(1);
		tail = new ElemType(1);
		cout << "请输入考生人数： ";
		//考生人数输入与检查
		while ((_size = getNum()) == -1 || _size < 1)
		{
			cout << "输入有误，请重新输入！ ";
		}
		cout << "请你依次输入考生的考号，姓名，性别，年龄以及报考类别：" << endl;
		ElemType* las = head;
		head->next = tail;
		head->last = NULL;
		tail->last = head;
		tail->next = NULL;
		//输入考生数据
		for (int i = 0; i < _size; ++i)
		{
			ElemType* cur = new ElemType;
			//在las之后插入数据
			insertAfter(las, cur);
			las = cur;
		}
	}
	//根据考生的考号来查找考生
	void search()
	{
		char* num = new char[100];
		cout << "请输入考生的考号：";
		cin >> num;
		//遍历所有信息
		for (ElemType* p = head->next; p != tail; p = p->next)
		{
			//如果找到该考号，输出该考生的信息
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
		//输入位置
		cout << "请输入你要插入考生的位置：";
		int pos;
		if ((pos = getNum()) == -1 || pos<1 || pos>_size + 1)
		{
			cout << "输入位置错误" << endl;
			return;
		}
		//寻找要插入位置的前一个位置，用指针p指向它
		for(ElemType *p=head;p!=tail;p=p->next)
		{
			if (!(--pos))
			{
				cout << "请输入你要插入考生的学号、名字、性别、年龄以及报考专业： " << endl;
				ElemType* newE = new ElemType;
				newE->last = p, newE->next = p->next;
				p->next->last = newE, p->next = newE;
				cout << "插入操作已经完成！" << endl;
				++_size;
				return;
			}
		}
	}
	void del()
	{
		//输入删除考生的考号
		cout << "请输入你要删除的考生的考号";
		char* num = new char[100];
		cin >> num;
		bool find = 0;
		//寻找要删除的考生信息
		Search
		{
			if (!strcmp(num, p->num))
			{
				find = 1;
				cout << "你要删除的考生的信息是：" << endl;
				//展示该信息：
				display(p);
				//删除内容
				p->last->next = p->next;
				p->next->last = p->last;
				delete p;
				--_size;
				break;
			}
		}
			if (!find)
				cout << "没找到该考生的信息！" << endl;
		delete[]num;
	}
	//修改数据
	void revise()
	{
		//输入考号与正误判断
		cout << "请输入你要修改的考生的考号：";
		char* num = new char[100];
		cin >> num;
		for (ElemType* p = head->next; p != tail; p = p->next)
		{
			//判断考号是否匹配
			if (!strcmp(num, p->num))
			{
				cout << "你要修改的考生的信息是：" << endl;
				display(p);
				cout << "请输入该考生的考号、姓名、性别、年龄以及报考类别：";
				//建立新的节点newE
				ElemType* newE = new ElemType();
				newE->last = p->last;
				newE->next = p->next;
				//调用student中重载的operator=，将newE的值赋值给p
				*p = *newE;
				//删除newE(newE里的值已经被拷贝赋值给p）
				delete newE;
				return;
			}
		}
		//错误提示：没有找到
		cout << "not Found! ";
	}
	//展示链表中所有数据
	void display()
	{
		if (!_size)
		{
			cout << "考试报名系统为空！" << endl;
			return;
		}
		//判断是否是第一次，如果是，需要输出表头
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
		//consistent为1输出表头，否则不输出
		if(!consistent)
			cout << left << setw(10) << "考号" << setw(10) << "姓名" << setw(10)
				<< "性别" << setw(10) << "年龄" << setw(10) << "报考类别" << endl;
		cout << left << setw(10) << e->num << setw(10) << e->name << setw(10)
			<< e->sex << setw(10) << e->age << setw(10) << e->subject << endl;
	}
};
int main()
{
	info_system is;
	is.display();
	int ope;
	cout << "输入已完成，马上跳转进入操作页面！";
	//调用Sleep，暂停三秒
	Sleep(3000);
	system("cls");
	while (1)
	{
		//输入表格：
		cout << "请输入要进行的操作\n";
		cout << setw(10) << left << "1，插入" << setw(10) << left << "2，删除"
			<< setw(10) << left << "3,查找" << endl;
		cout << setw(10) << left << "4，修改" << setw(10) << left << "5,输出" << setw(10)
			<< left << "6，清屏" << endl << setw(10) << left << "0，退出" << endl;
		//判断操作数是否正确
		ope = getNum();
		bool next_loop = 0;
		while (ope == -1)
		{
			cout << "输入格式有误，请重新输入！" << endl;
			ope = getNum();
		}
		if (!ope)
			break;
		switch (ope)
		{
		case 1:
			//插入
			is.insert();
			break;
		case 2:
			//删除
			is.del();
			break;
		case 3:
			//查找
			is.search();
			break;
		case 4:
			//修改
			is.revise();
			break;
		case 5:
			//统计
			is.display();
			break;
		case 6:
			//清屏
			system("cls");
			next_loop = 1;
			break;
		default:
			//输入有误提示
			cout << "输入有误，请重新输入！" << endl;
		}
		if (next_loop)continue;//如果是清屏操作，直接进入下一轮循环
		//判断是否要继续
		cout << "是否继续（如果要继续，请输入Y或者y，如果要退出，请输入N或者n): " << endl;
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
				cout << "错误输入" << endl;
		}
		if (ex)
			break;
	}
	cout << "已退出，考试报名系统中共有 " << is.getSize() << " 个数据" << endl;
}
