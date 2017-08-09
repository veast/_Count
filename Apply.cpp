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

//��Դȷ�Ϲ���
void apply() {
	system("cls");
	int N;	//��Դ��������
	N = getN();
	struct resource *r = new resource[N];
	readIn(r);
	cout << "======================" << endl;
	cout << "    ��ǰ�����ͳ��" << endl;
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

void readIn(resource *r) {		//���������ļ�
	ifstream ReadFile;
	string temp;
	int n = 0;
	ReadFile.open("ApplyConfiguration.txt", ios::in);
	if (ReadFile.fail())
		return;
	else {
		while (!ReadFile.eof()) {	//��������
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

void doApply(resource *r, int N) {	//�������
	cout << "======================" << endl;
	cout << "���������Դ���루����-1�˳�; ����-2������������Դ��Ŀ��ʾ��" << endl;
	//�����ǰ����1.����� 2.���ݿ�....
	int ch;
	while (1) {
		cin >> ch;
		if (ch == -1) break;
		else if (ch == -2) {
			system("cls");
			displayCurrent(r, N);
			cout << "======================" << endl;
			cout << "    ��ǰ�����ͳ��" << endl;
			cout << "======================" << endl;
			cout << "���������Դ���루����-1�˳�; ����-2������������Դ��Ŀ��ʾ��" << endl;
		}
		else if (ch >= 1 && ch <= N) {
			r[--ch].count++;
			//��ȡ��ǰ����
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

			doSave(r, N);	//�޸����ֱ�ӱ���
		}
		else {
			cout << "�����˴���ѡ��밴�س�ȷ�ϣ�" << endl;
			getchar();
			while (getchar() != '\n');
			cout << "���������룺" << endl;
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

//�޸�����  ��� ɾ�� �޸�
void addR() {
	system("cls");
	int N;	//��Դ��������
	N = getN();
	struct resource *r = new resource[N];
	readIn(r);

	cout << "======================" << endl;
	cout << "    ��ǰ�����ͳ��" << endl;
	cout << "======================" << endl;
	displayCurrent(r, N);
	cout << "======================" << endl;
	//����Ƿ��Ѿ����ڸ���Դ����


	struct resource *r_new = new resource[N + 1];
	for (int i = 0; i < N; i++) {
		r_new[i].name = r[i].name;
		r_new[i].number = r[i].number;
		r_new[i].count = r[i].count;
	}

	string name;
	string number;
	int count;
	cout << "���������κ�һ������-1�˳�" << endl;
	cout << "======================" << endl;
	cout << "������������Դ����" << endl;
	cin >> name;
	if (name == "-1")
		return;
	cout << "��������Դ���" << endl;
	cin >> number;
	if (name == "-1")
		return;
	cout << "��������Դͳ����Ŀ" << endl;
	cin >> count;
	if (count == -1)
		return;

	r_new[N].name = name;
	r_new[N].number = number;
	r_new[N].count = count;

	doSave(r_new, N + 1);

	cout << "��ӳɹ���" << endl;
	Sleep(600);
}

void deleteR() {
	system("cls");
	int N;	//��Դ��������
	N = getN();
	struct resource *r = new resource[N];
	readIn(r);

	cout << "======================" << endl;
	cout << "    ��ǰ�����ͳ��" << endl;
	cout << "======================" << endl;
	displayCurrent(r, N);

	int no;

	cout << "======================" << endl;
	cout << "����������-1�˳�" << endl;
	cout << "======================" << endl;
	cout << "��������ɾ������Դ���" << endl;
	cin >> no;
	if (no == -1)
		return;


	bool flag = false;

	if (no <= N && no > 0) {
		for (int j = no - 1; j < N - 1; j++) {	//��λ��ǰ��
			r[j].name = r[j + 1].name;
			r[j].number = r[j + 1].number;
			r[j].count = r[j + 1].count;
		}
		flag = 1;
	}

	if (!flag) {
		cout << "û���ҵ�����ɾ������Դ���ƣ��밴�س�ȷ�ϣ�" << endl;
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
		cout << "ɾ���ɹ���" << endl;
		Sleep(600);
	}
}

void changeR() {
	system("cls");
	int N;	//��Դ��������
	N = getN();
	struct resource *r = new resource[N];
	readIn(r);

	cout << "======================" << endl;
	cout << "    ��ǰ�����ͳ��" << endl;
	cout << "======================" << endl;
	int func;
	displayCurrent(r, N);
	cout << "======================" << endl;
	cout << "���������κ�һ������-1�˳�" << endl;
	cout << "======================" << endl;

	int no;
	bool flag = false;
	cout << "�����������޸ĵ���Դ���" << endl;
	cin >> no;
	if (no == -1)
		return;

	string name;
	string number;
	int count;

	if (no <= N && no > 0) {
		flag = true;
		cout << "��ѡ�������޸ĵ���Ŀ" << endl;
		cout << "1.����" << endl;
		cout << "2.���" << endl;
		cout << "3.����" << endl;
		cin >> func;
		switch (func) {
		case 1:cout << "�������µ���Դ����" << endl; cin >> name; if (name == "-1") return; r[no - 1].name = name; break;
		case 2:cout << "�������µ���Դ���" << endl; cin >> number; if (number == "-1") return; r[no - 1].number = number; break;
		case 3:cout << "�������µ�����" << endl; cin >> count; if (count == -1) return; r[no - 1].count = count; break;
		case -1:return;
		default:cout << "�����ѡ��(�밴�س�ȷ�ϣ�" << endl; getchar(); while (getchar() != '\n'); break; 
		}

	}
	if (flag) {
		cout << "�޸ĳɹ���" << endl;
		doSave(r, N);
		Sleep(600);
	}
	else {
		cout << "û���ҵ������޸ĵ���Դ���밴�س�ȷ�ϣ�" << endl;
		getchar(); while (getchar() != '\n');
	}
}

void doApplyRevise() {
	int func;
	while (1) {
		system("cls");
		cout << "==============" << endl;
		cout << "1.�����Դ" << endl;
		cout << "2.ɾ����Դ" << endl;
		cout << "3.�޸���Դ" << endl;
		cout << "4.����" << endl;
		cout << "==============" << endl;
		cin >> func;
		switch (func) {
		case 1:addR(); break;
		case 2:deleteR(); break;
		case 3:changeR(); break;
		case 4:return;
		default:cout << "�����ѡ��(������س�ȷ�ϣ�" << endl; getchar(); while (getchar() != '\n'); break;
		}
	}
}