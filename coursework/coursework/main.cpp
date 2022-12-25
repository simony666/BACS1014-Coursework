/*
* BACS1014 Assignment
* Member : Yong Choy Mun, Wang Siew You, Eddie Chua Kok Seng
*/

#include <iostream>
#include "Student.h"
#include "function.h"

using namespace std;
void user() {
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