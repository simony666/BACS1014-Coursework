/*
* BACS1014 Assignment
* Member : Yong Choy Mun, Wang Siew You, Eddie Chua Kok Seng
*/

#include <iostream>
#include "Student.h"
#include "function.h"

using namespace std;
void user() {
	bool isLogin = false;
	string ic, student_id;
	bool valid = true;
	
	do {
		system("cls");
		cout << "Please enter IC";
		cin >> ic;
		cout << "Please enter Student Id";
		cin >> student_id;

		for (int i = 0; i < ic.length(); i++) {
			if (!isdigit(ic[i])) {
				valid = false;
				break;
			}
		}
		if (!valid) continue;


	} while (!isLogin);
}
void admin() {
}

int main() {
	int menu = main_menu();
	system("cls");
	if (menu == 1) {
		user();
	}
	else if (menu == 2) {
		admin();
	}

	return 0;
}