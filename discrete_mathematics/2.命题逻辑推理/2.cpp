#include<iostream>
#include<string>
using namespace std;
#define NUM_VARIABLE 5
string txt[][2] =
{
	"营业员A没有偷手表","营业员A偷了手表",
	"营业员B没有偷手表","营业员B偷了手表",
	"作案在营业时间","作案不在营业时间",
	"B提供的证据不正确","B提供的证据正确",
	"货柜已上锁","货柜未上锁"
};
//暂停，待用户输入
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
			a[j] = i & (1 << j);//给五个命题变项赋真值
		//如果是成真赋值，则进行输出，并记录情况总数
		if (((a[0] || a[1]) && (!a[0] || a[2]) && (!a[3] || a[4]) && (a[3] || !a[2]) && !a[4]))
		{
			cout << "情况" << ++cnt << ": \n";
			for (int j = 0; j < NUM_VARIABLE; ++j)
				if (j != NUM_VARIABLE - 1)cout << txt[j][a[j]] << ",\n";
				else cout << txt[j][a[j]] << "。\n";
		}
	}
	cout << "\n总共有" << cnt << "种情况！";
	Suspend();
	return 0;
}
