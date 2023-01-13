#include<iostream>
using namespace std;
typedef struct LNode
{
	int data;
	LNode* next;
}*Linklist;
class List
{
private: Linklist first[3];
public:
	List()
	{
		for (int i = 1; i < 3; ++i)
		{
			first[i] = new LNode;
			first[i]->next = NULL;
			LNode* tail = first[i];
			int x, last;
			bool fir = 1;
			while (1)
			{
				cin >> x;
				if (x == -1)break;
				if (fir) { fir = 0; last = x; }
				else
				{
					if (x < last) { cout << "输入的不是非降序列！\n"; exit(-1); }
					last = x;
				}
				insert(tail, x);
			}
		}
	}
	void insert(Linklist& tail,int x)
	{
		LNode* p = new LNode{ x,NULL };
		tail->next = p;
		tail = p;
	}
	void merge()
	{
		Linklist p = first[1]->next, q = first[2]->next;
		Linklist tail = first[0] = new LNode{ 0,NULL };
		while (p && q)
		{
			if (p->data < q->data)p = p->next;
			else if (p->data == q->data) { insert(tail, q->data); p = p->next; q = q->next; }
			else q = q->next;
		}
	}
	void display()
	{
		if (!first[0]->next)cout << "NULL";
		else
		{
			bool fir = 1;
			for (Linklist p = first[0]->next; p; p = p->next)
				if (fir) { fir = 0; cout << p->data; }
				else cout << ' ' << p->data;
		}
	}
};
int main()
{
	cout << "请输入两个有序链表，以-1结尾：\n";
	List L;
	L.merge();
	cout << "两个链表的交集为：\n";
	L.display();
	return 0;
}
