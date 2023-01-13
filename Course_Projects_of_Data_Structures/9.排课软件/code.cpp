#include<iostream>
#include<stdlib.h>
#include<stdio.h> 
#include<sstream>
#include<iomanip>
#include<fstream>
#include<algorithm>
#define NULLString ""
#define MAX_VERTEX_NUM 38
using namespace std;


int indegree[MAX_VERTEX_NUM] ;
int outdegree[MAX_VERTEX_NUM] ;
int semester[8], semester_can_choose[8];
int this_semester;
void Exit();

//macro definition
#define ERROR 0
#define OK 1
#define OVERFLOW -2
//special define
typedef int Status;
//顺序存储结构
template<class T>
class Stack
{
private:
    T* _top;
    T* _base;
    int stackSize;
    const int STACK_INIT_SIZE = 100;
public:
    Stack()
    {
        _base = new T[STACK_INIT_SIZE];
        if (!_base)exit(OVERFLOW);
        _top = _base;
        stackSize = STACK_INIT_SIZE;
    }
    Status popStack(T& e)
    {
        if (_base == _top)return ERROR;
        e = *--_top;
        return OK;
    }
    T pop()
    {
        if (_base == _top) { cout << "删除失败，因为栈为空！\n"; Exit(); }
        return *--_top;
    }
    Status push(T e)
    {
        if (_top - _base >= stackSize)
        {
            _base = (T*)realloc(_base, 2 * (stackSize) * sizeof(T));
            if (!_base)return OVERFLOW;
            _top = _base + stackSize;
            stackSize *= 2;
        }
        *_top++ = e;
        return OK;
    }
    Status get_top(T& e)
    {
        if (_base == _top)return ERROR;
        e = *(_top - 1);
        return OK;
    }
    T top()
    {
        if (_base == _top) { cout << "取栈顶失败，因为栈为空！\n"; Exit(); }
        return *(_top - 1);
    }
    int size() { return _top - _base; }
    bool empty() { return !size(); }
};

template<class T>
class Sort
{
private:

public:
	Sort() {};
	void InsertSort(T* arr, int _num)
	{
		T t;
		for (int i = 1; i < _num; ++i)
		{
			if (arr[i] < arr[i - 1])
			{
				t = arr[i];
				arr[i] = arr[i - 1];
				int j;
				for (j = i - 2; j >= 0 && t < arr[j]; --j)arr[j + 1] = arr[j];
				arr[j + 1] = t;
			}
		}

	}
};
struct arr
{
    int no;
    int outde;
    bool operator<(const arr& b)
    {
        return outde > b.outde;
    }
    bool operator<=(const arr& b)
    {
        return outde >= b.outde;
    }
}Arr[MAX_VERTEX_NUM],SELECT[MAX_VERTEX_NUM];

bool permutation_used[MAX_VERTEX_NUM];
int course_table[4][5];
struct ArcNode
{
    int adjvex;
   // int length;
    ArcNode* nextarc;
};
struct info
{
    string num, name, pre[2];
    int time, assign;
    void readIn(ifstream&in)
    {

        in >> num >> name >> time >> assign;
        //cout << num << ' ' << name << endl;
        char ch;
        pre[0] = pre[1] = NULLString;
        
        string AllPre;
        getline(in, AllPre);
        //cout << AllPre << endl;
        int i = -1;
        for (int j = 0; j < AllPre.size(); ++j)
            if (AllPre[j] == 'c')pre[++i] += AllPre[j];
            else if (AllPre[j] >= '0' && AllPre[j] <= '9')pre[i] += AllPre[j];
        //for (int k = 0; k < 2; ++k)cout << pre[k] << endl;
    }
    void print()
    {
        cout << num << ' ' << name << ' ' << time << ' ' << assign;
        for (int i = 0; i < 2 && pre[i] != NULLString; ++i)cout << ' ' << pre[i];
        cout.put('\n');
    }
};
int getNum(string s)
{
    if (s[1] == '0')return s[2] - '0';
    else return (s[1] - '0') * 10 + s[2] - '0';
}
typedef struct VNode
{
    info data;
    int inde, outde;
    int term;
    ArcNode* firstarc;
    VNode() { inde = outde = 0; }
    void print()
    {
        data.print();
        cout << inde << ' ' << outde << ' ' << term << endl;
    }
    
}AdjList[MAX_VERTEX_NUM + 2];
class ALGraph
{
private:
    AdjList vertices;
    int vexnum, arcnum;
    int MAX(int a, int b) { return a > b ? a : b; }
public:
    ALGraph()
    {
        vexnum = MAX_VERTEX_NUM;
        arcnum = 0;
        for (int i = 0; i < vexnum; ++i)
            vertices[i].firstarc = NULL, vertices[i].inde = vertices[i].outde = 0;
        ifstream in("course.txt");
        if (!in) { printf("找不到课程文件！\n"); Exit(); }
        //for (int i = 0; i < 8; ++i)in >> semester[i];
        for (int i = 0; i < vexnum; ++i)
        {
            vertices[i].data.readIn(in);
            string* pre = vertices[i].data.pre;
            for (int j = 0; j < 2 && pre[j] != NULLString; ++j)
            {
                int k = getNum(pre[j]) - 1;
                //cout << k << endl;
                ArcNode* A = new ArcNode{ i,vertices[k].firstarc };
                vertices[k].firstarc = A;
                ++vertices[k].outde;
                ++vertices[i].inde;
                ++arcnum;
            }
        }
        in.close();
    }
    void init()
    {
        for (int i = 0; i < vexnum; ++i)
        {
            indegree[i] = vertices[i].inde, outdegree[i] = vertices[i].outde;
            int assign = vertices[i].data.assign;
            if (assign)--semester_can_choose[assign-1];
        }
    }
    void print() { for (int i = 0; i < vexnum; ++i)vertices[i].print(); }
    bool judgeOk(int num,ofstream &out)
    {
        int ok_2 = 10, ok_3 = 10;
        for (int i = 0; i < num; ++i)
        {
            int t = vertices[SELECT[i].no].data.time;
            if (t == 3)--ok_3;
            else if (t == 4)ok_2 -= 2;
            else if (t == 5)--ok_2, --ok_3;
            else if (t == 6)ok_3 -= 2;
        }
        if (ok_2 < 0 || ok_3 < 0)return 0;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 5; ++j)course_table[i][j] = -1;
        bool arrange[MAX_VERTEX_NUM] = { 0 };
        for (int i = 0; i < num; ++i)
        {
            int t = vertices[SELECT[i].no].data.time;
            if (t == 3)continue;
            int n = SELECT[i].no;
            arrange[n] = 1;
            int day1, day2;
            if (t == 4)
            {
                if ((day1 = arrange_time(0, n, 2)) == -1)return 0;
                if ((day2 = arrange_time(day1 + 2, n, 2)) == -1)return 0;
            }
            
            if (t == 5)
            {
                if ((day1 = arrange_time(0, n, 2)) == -1)return 0;
                if ((day2 = arrange_time(day1 + 2, n, 3)) == -1)return 0;
            }
            if (t == 6)
            {
                if ((day1 = arrange_time(0, n, 3)) == -1)return 0;
                if ((day2 = arrange_time(day1 + 2, n, 3)) == -1)return 0;
            }
        }
        for (int i = 0; i < num; ++i)
        {
            int n = SELECT[i].no;
            if (arrange[n])continue;
            if (arrange_time(0, n, 3) == -1)return 0;
        }
        printTable(out);
        return 1;
    }
    int arrange_time(int day, int n,int t)
    {
        int begin = t == 2 ? 0 : 1;
        for (int j = day; j < 5; ++j)
        {
            for (int i = begin; i < 4; i += 2)
                if (course_table[i][j]!=-1)continue;
                else { course_table[i][j] = n; return j; }
        }
        return -1;
    }
    void printTable(ofstream&cout)
    {
        string x = "NULL";
        const string Time[] = { "L1-2","L3-5" ,"L6-7" ,"L8-10" };
        cout<<"以下为第 "<<this_semester<<" 学期的课表：\n";
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 6; ++j)
                if (!i && !j)cout << setw(5) << ' ';
                else if (!i)cout << setw(25) << "weekday " << j;
                else if (!j)cout << setw(5) << Time[i - 1];
                else if(i&&j)cout <<setw(25)<< (course_table[i-1][j-1] != -1 ? vertices[course_table[i-1][j-1]].data.name : x) ;
            cout << endl;
        }
    }
    int Select(int n, int Num, int t,ofstream&out)
    {
        int num = semester_can_choose[t];
        if (n==num)
        {
            //for (int i = 0; i < n; ++i)cout << SELECT[i].no << " ";
            //cout << endl;
            if (judgeOk(semester[t],out)) {   return 1;}
            return 0;
        }
        for (int i = 0; i < Num; ++i)
        {
            if (permutation_used[i])continue;
            permutation_used[i] = 1;
            SELECT[n++] = Arr[i];
            if (Select(n, Num, t,out))return 1;
            
            --n;
            permutation_used[i] = 0;
        }
        return 0;
    }
    Status TopoSelect()
    {
        ofstream out("result.txt");
        init();
        Stack<int>s;
        int num = 0;
        for (int i = 0; i < vexnum; ++i)
        {
            if (!indegree[i]&&!vertices[i].data.assign) { Arr[num++] = { i,vertices[i].outde }; }
        }
        Sort<arr>S;
        //for (int i = 0; i < num; ++i)cout << vertices[Arr[i].no].data.num << ' '; cout << endl;
        S.InsertSort(Arr, num);
        //for (int i = 0; i < num; ++i)cout << vertices[Arr[i].no].data.num << ' '; cout << endl;
        int x2 = semester_can_choose[0];
        for (int i = 0; i < MAX_VERTEX_NUM; ++i)if (vertices[i].data.assign==1)SELECT[x2++] = { i,vertices[i].outde };
        this_semester = 1;
        int sig = Select(0, num, 0,out);
        if (!sig) { printf("第%d学期的课表无法按照最优排法排出！\n",this_semester); Exit(); }
        //cout << Select(0, num, 0) << endl;
        for (int i = 1; i < 8; ++i)
        {
            int last_num = num;
            num = 0;
            arr last_Arr[MAX_VERTEX_NUM];
            for (int l = 0; l < last_num; ++l)last_Arr[l] = Arr[l];
            for (int l = 0; l < last_num; ++l)
            {
                bool ok = 1;
                for (int m = 0; m < semester[i - 1]; ++m)if (SELECT[m].no == last_Arr[l].no) { ok = 0; break; }
                if (!ok)continue;
                Arr[num++] = last_Arr[l];
            }
            for (int I = 0; I < MAX_VERTEX_NUM; ++I)permutation_used[I] = 0;
            for (int j = 0; j < semester[i - 1]; ++j)
            {
                int k = SELECT[j].no;
                for (ArcNode* p = vertices[k].firstarc; p; p = p->nextarc)
                {
                    int l = p->adjvex;
                    if (!(--indegree[l] && !vertices[l].data.assign)) { Arr[num++] = { l,vertices[l].outde }; }
                }
            }
            //for (int i = 0; i < num; ++i)cout << vertices[Arr[i].no].data.num << ' '; cout << endl;
            S.InsertSort(Arr, num);
            //for (int i = 0; i < num; ++i)cout << vertices[Arr[i].no].data.num << ' '; cout << endl;
            int x2 = semester_can_choose[i];
            for (int l = 0; l < MAX_VERTEX_NUM; ++l)if (vertices[l].data.assign == i + 1) SELECT[x2++] = { l,vertices[l].outde };
            ++this_semester;
            int sig = Select(0, num, i,out);
            if (!sig) { printf("第%d学期的课表无法按照最优排法排出！\n",this_semester); Exit(); }
        }
        out.close();
        return 1;
       
    }
};

void readInput();
int main()
{
    readInput();
    ALGraph G;
    G.TopoSelect();
    printf("PS:输出结果储存在文件result.txt中！");
    printf("\n\n\nPress enter to continue...\n");
    getchar();
    return 0;
}
void readInput()
{
    for (int i = 0; i < 8; ++i)semester[i] = semester_can_choose[i] = -1;
    ifstream in("input.txt");
    if (!in) { printf("找不到输入数据文件！\n"); Exit(); }
    int SUM = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (in.eof()) { printf("输入数据不足！应该输入8个数据！\n"); Exit(); }
        in >> semester[i], SUM += semester[i], semester_can_choose[i] = semester[i];
        if (in.fail()) { printf("包含非法字符！\n"); Exit(); }
    }
    if (SUM != MAX_VERTEX_NUM) { printf("请检查输入！输入之和不是38！\n"); Exit(); }
    
}
void Exit()
{
	printf("\n\n\nPress enter to continue...\n");
	getchar();
	exit(-1);
}
