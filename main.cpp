#include <iostream>
#include "Confirm.h"
#include "Apply.h"

using namespace std;

int main() {
	int func;
	while (1) {
		system("cls");
		cout << " =====================" << endl;
		cout << "| ���������ֽ���ѡ�� |" << endl;
		cout << "| 1.ȷ�ϱ�	     |" << endl;
		cout << "| 2.�����	     |" << endl;
		cout << "| 3.�޸�ȷ�ϱ�����   |" << endl;
		cout << "| 4.�޸����������   |" << endl;
		cout << "| 5.�˳�	     |" << endl;
		cout << " =====================" << endl;
		cin >> func;
		switch (func) {
		case 1:confirm(); break;
		case 2:apply(); break;
		case 3:doConfirmRevise(); break;
		case 4:doApplyRevise(); break;
		case 5:return 0;
		default:cout << "�����ѡ��(������س�ȷ�ϣ�" << endl; getchar(); while (getchar() != '\n'); break;
		}
	}
	return 0;
}