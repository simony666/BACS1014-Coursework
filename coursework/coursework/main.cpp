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
	string error_text;

	do {
		system("cls");
		cout << "USER LEVEL" << endl;
		if (!error_text.empty()) cout << error_text << endl;

		cout << "Please enter IC: ";
		cin >> ic;
		cout << "Please enter Student Id: ";
		cin >> student_id;

		int result = validate(ic, student_id);
		switch (result) {
		case 1:
			isLogin = true;
			break;
		case 2:
			error_text = "IC is incorrect! Please make sure only enter numberic ic without -";
			break;
		case 3:
			error_text = "Student ID is incorrect! Please make sure enter a correct format!";
			break;
		case 4:
			error_text = "No Data In Database! Please contact admin if you think this is an error!";
			break;
		default:
			error_text = "Unknown error occur! Please contact admin for futeru help.";
			break;
		}
	} while (!isLogin);

	cout << "Login SUCCESS!!!" << endl;

	if (opennominate()) {
		//open for nominate
		system("cls");
		cout << "Nonimate System" << endl;
	}
	else {
		//vote
		system("cls");
		cout << "Vote System" << endl;

	}

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