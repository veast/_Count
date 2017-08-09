#include "Apply.h"
#include "data.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

static void displayCurrent(resource *r, int N);
static void readIn(resource* r);
static void doApply(resource *r, int N);
static void doSave(resource *r, int N);
static int getN();
static void addR();
static void deleteR();
static void changeR();

//资源确认过程
void apply() {
	system("cls");
	int N;	//资源种类总数
	N = getN();
	struct resource *r = new resource[N];
	readIn(r);
	cout << "======================" << endl;
	cout << "    当前申请表统计" << endl;
	displayCurrent(r, N);
	doApply(r, N);
}

int getN() {
	ifstream ReadFile;
	int n = 0;
	string temp;
	ReadFile.open("ApplyConfiguration.txt", ios::in);
	if (ReadFile.fail())
		return 0;
	else {
		while (getline(ReadFile, temp))
			n++;
		ReadFile.close();
		return n;
	}
}

void readIn(resource *r) {		//读入配置文件
	ifstream ReadFile;
	string temp;
	int n = 0;
	ReadFile.open("ApplyConfiguration.txt", ios::in);
	if (ReadFile.fail())
		return;
	else {
		while (!ReadFile.eof()) {	//保存数据
			ReadFile >> r[n].name;
			ReadFile >> r[n].number;
			ReadFile >> r[n].count;
			n++;
		}
	}
}

void displayCurrent(resource *r, int N) {
	cout << "======================" << endl;
	for (int i = 0; i < N; i++)
		cout << i + 1 << "." << r[i].name << " " << r[i].number << " "
		<< r[i].count << endl;
}

void doApply(resource *r, int N) {	//申请过程
	cout << "======================" << endl;
	cout << "下面进行资源申请（输入-1退出; 输入-2清屏并更新资源数目显示）" << endl;
	//输出当前数据1.虚拟机 2.数据库....
	int ch;
	while (1) {
		cin >> ch;
		if (ch == -1) break;
		else if (ch == -2) {
			system("cls");
			displayCurrent(r, N);
			cout << "======================" << endl;
			cout << "    当前申请表统计" << endl;
			cout << "======================" << endl;
			cout << "下面进行资源申请（输入-1退出; 输入-2清屏并更新资源数目显示）" << endl;
		}
		else if (ch >= 1 && ch <= N) {
			r[--ch].count++;
			//获取当前日期
			time_t nowTime;
			time(&nowTime);
			struct tm sysTime;
			localtime_s(&sysTime, &nowTime);
			/*cout << r[ch].number << " " << 1900 + sysTime.tm_year <<
			"-" << sysTime.tm_mon + 1 << "-" << sysTime.tm_mday <<
			" " << r[ch].count << endl;*/
			cout << r[ch].number << 1900 + sysTime.tm_year;
			if ((sysTime.tm_mon + 1) > 9)cout << sysTime.tm_mon + 1;
			else cout << 0 << sysTime.tm_mon + 1;
			if (sysTime.tm_mday > 9)cout << sysTime.tm_mday;
			else cout << 0 << sysTime.tm_mday;
			cout << r[ch].count << endl;

			doSave(r, N);	//修改完毕直接保存
		}
		else {
			cout << "输入了错误选项（请按回车确认）" << endl;
			getchar();
			while (getchar() != '\n');
			cout << "请重新输入：" << endl;
		}
	}
	
	return;
}

void doSave(resource *r, int N) {
	ofstream outfile;
	outfile.open("ApplyConfiguration.txt");
	for (int i = 0; i < N; i++)
		outfile << r[i].name << " " << r[i].number << " " << r[i].count << endl;
}

//修改配置  添加 删除 修改
void addR() {
	system("cls");
	int N;	//资源种类总数
	N = getN();
	struct resource *r = new resource[N];
	readIn(r);

	cout << "======================" << endl;
	cout << "    当前申请表统计" << endl;
	cout << "======================" << endl;
	displayCurrent(r, N);
	cout << "======================" << endl;
	//检查是否已经存在该资源种类


	struct resource *r_new = new resource[N + 1];
	for (int i = 0; i < N; i++) {
		r_new[i].name = r[i].name;
		r_new[i].number = r[i].number;
		r_new[i].count = r[i].count;
	}

	string name;
	string number;
	int count;
	cout << "您可以在任何一步输入-1退出" << endl;
	cout << "======================" << endl;
	cout << "请输入待添加资源名称" << endl;
	cin >> name;
	if (name == "-1")
		return;
	cout << "请输入资源编号" << endl;
	cin >> number;
	if (name == "-1")
		return;
	cout << "请输入资源统计数目" << endl;
	cin >> count;
	if (count == -1)
		return;

	r_new[N].name = name;
	r_new[N].number = number;
	r_new[N].count = count;

	doSave(r_new, N + 1);

	cout << "添加成功！" << endl;
	Sleep(600);
}

void deleteR() {
	system("cls");
	int N;	//资源种类总数
	N = getN();
	struct resource *r = new resource[N];
	readIn(r);

	cout << "======================" << endl;
	cout << "    当前申请表统计" << endl;
	cout << "======================" << endl;
	displayCurrent(r, N);

	int no;

	cout << "======================" << endl;
	cout << "您可以输入-1退出" << endl;
	cout << "======================" << endl;
	cout << "请输入想删除的资源序号" << endl;
	cin >> no;
	if (no == -1)
		return;


	bool flag = false;

	if (no <= N && no > 0) {
		for (int j = no - 1; j < N - 1; j++) {	//后位置前移
			r[j].name = r[j + 1].name;
			r[j].number = r[j + 1].number;
			r[j].count = r[j + 1].count;
		}
		flag = 1;
	}

	if (!flag) {
		cout << "没有找到您想删除的资源名称（请按回车确认）" << endl;
		getchar();
		while (getchar() != '\n');
	}
	else {
		struct resource*r_new = new resource[N - 1];
		for (int i = 0; i < N - 1; i++) {
			r_new[i].name = r[i].name;
			r_new[i].number = r[i].number;
			r_new[i].count = r[i].count;
		}
		doSave(r_new, N - 1);
		cout << "删除成功！" << endl;
		Sleep(600);
	}
}

void changeR() {
	system("cls");
	int N;	//资源种类总数
	N = getN();
	struct resource *r = new resource[N];
	readIn(r);

	cout << "======================" << endl;
	cout << "    当前申请表统计" << endl;
	cout << "======================" << endl;
	int func;
	displayCurrent(r, N);
	cout << "======================" << endl;
	cout << "您可以在任何一步输入-1退出" << endl;
	cout << "======================" << endl;

	int no;
	bool flag = false;
	cout << "请输入你想修改的资源序号" << endl;
	cin >> no;
	if (no == -1)
		return;

	string name;
	string number;
	int count;

	if (no <= N && no > 0) {
		flag = true;
		cout << "请选择您想修改的项目" << endl;
		cout << "1.名称" << endl;
		cout << "2.编号" << endl;
		cout << "3.数量" << endl;
		cin >> func;
		switch (func) {
		case 1:cout << "请输入新的资源名称" << endl; cin >> name; if (name == "-1") return; r[no - 1].name = name; break;
		case 2:cout << "请输入新的资源编号" << endl; cin >> number; if (number == "-1") return; r[no - 1].number = number; break;
		case 3:cout << "请输入新的数量" << endl; cin >> count; if (count == -1) return; r[no - 1].count = count; break;
		case -1:return;
		default:cout << "错误的选项(请按回车确认）" << endl; getchar(); while (getchar() != '\n'); break; 
		}

	}
	if (flag) {
		cout << "修改成功！" << endl;
		doSave(r, N);
		Sleep(600);
	}
	else {
		cout << "没有找到您想修改的资源（请按回车确认）" << endl;
		getchar(); while (getchar() != '\n');
	}
}

void doApplyRevise() {
	int func;
	while (1) {
		system("cls");
		cout << "==============" << endl;
		cout << "1.添加资源" << endl;
		cout << "2.删除资源" << endl;
		cout << "3.修改资源" << endl;
		cout << "4.返回" << endl;
		cout << "==============" << endl;
		cin >> func;
		switch (func) {
		case 1:addR(); break;
		case 2:deleteR(); break;
		case 3:changeR(); break;
		case 4:return;
		default:cout << "错误的选项(请输入回车确认）" << endl; getchar(); while (getchar() != '\n'); break;
		}
	}
}