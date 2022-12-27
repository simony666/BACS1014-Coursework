#include <iostream>
#include <fstream>
#include <string>
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

bool validdb(string ic, string student_id) {
	//TODO: Compare Login detail to database
	ifstream inData;
	ofstream outData;

	inData.open("students.txt");
	int i = 0;
	if (inData) {
		string line;
		while (getline(inData, line)) {
			cout << "This Line is " << line << endl;
		}
	}
	inData.close();

	return false;
}

int validate(string ic, string student_id) {
	// return 1 = all correct, 2 = IC not correct, 3 = Student Id not correct, 4 = Not in Databses

	if (ic.length() != 12) return 2;
	if (student_id.length() != 10) return 3;

	for (int i = 0; i < ic.length(); i++) {
		if (!isdigit(ic[i])) {
			return 2;
		}
	}
	for (int i = 0; i < student_id.length(); i++) {
		if (i == 2 || i == 3 || i == 4) {
			if (!isalpha(student_id[i])) {
				return 3;
			}
		}
		else {
			if (!isdigit(student_id[i])) {
				return 3;
			}
		}
	}	
	if (validdb(ic,student_id)) {
		return 1;
	}
	
	return 0;
};