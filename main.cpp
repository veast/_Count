#include <iostream>
#include "Confirm.h"
#include "Apply.h"

using namespace std;

int main() {
	int func;
	while (1) {
		system("cls");
		cout << " =====================" << endl;
		cout << "| 请输入数字进行选择 |" << endl;
		cout << "| 1.确认表	     |" << endl;
		cout << "| 2.申请表	     |" << endl;
		cout << "| 3.修改确认表内容   |" << endl;
		cout << "| 4.修改申请表内容   |" << endl;
		cout << "| 5.退出	     |" << endl;
		cout << " =====================" << endl;
		cin >> func;
		switch (func) {
		case 1:confirm(); break;
		case 2:apply(); break;
		case 3:doConfirmRevise(); break;
		case 4:doApplyRevise(); break;
		case 5:return 0;
		default:cout << "错误的选项(请输入回车确认）" << endl; getchar(); while (getchar() != '\n'); break;
		}
	}
	return 0;
}