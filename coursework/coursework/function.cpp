#include <iostream>
#include <fstream>
#include <string>
#include "Student.h"
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
	ifstream inData;
	Student user[200];

	inData.open("students.txt");
	if (inData) {
		string line;
		int i = 0;
		while (getline(inData, line)) {			
			string data[8];
			char delimiter = '|';

			int j = 0;
			size_t pos;
			while ((pos = line.find(delimiter)) != string::npos) {
				string token = line.substr(0, pos);
				data[j] = token;
				line.erase(0, pos + 1);
				j++;
			}
			user[i].name = data[0];
			user[i].student_id = data[1];
			user[i].ic = data[2];
			user[i].year = data[3];
			user[i].program = data[4];
			user[i].vote = (data[5] == "0") ? false: true;
			user[i].voter = data[6];
			user[i].votes = stoi(data[7]);
			i++;
		}
	}
	inData.close();

	for (int k = 0; k < 200; k++) {
		if (user[k].ic == ic && user[k].student_id == student_id) {
			return true;
		}
	}

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
	student_id[2] = toupper(student_id[2]);
	student_id[3] = toupper(student_id[3]);
	student_id[4] = toupper(student_id[4]);
	if (validdb(ic,student_id)) {
		return 1;
	}
	
	return 0;
};

bool opennominate() {
	ifstream inData;
	inData.open("settings.txt");
	if (inData) {
		string line;
		int i = 0;
		while (getline(inData, line)) {
			string data[7];
			char delimiter = '|';

			int j = 0, pos;
			while ((pos = line.find(delimiter)) != string::npos) {
				string token = line.substr(0, pos);
				data[j] = token;
				line.erase(0, pos+1);
				j++;
			}
			i++;
		}
	}
	inData.close();

	return false;
}