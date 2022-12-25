#include <iostream>
using namespace std;

int main_menu() {
	int menu;

	cout << "###################################" << endl
		<< "#              Level              #" << endl
		<< "###################################" << endl
		<< "1 - User Level " << endl
		<< "2 - Admin Level " << endl
		<< endl << "Please select one of the menu(default: 1): ";
	cin >> menu;

	switch (menu) {
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	default:
		return 1;
	}
	return 0;
}